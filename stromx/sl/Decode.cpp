/* 
*  Copyright 2016 Matthias Fuchs
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/

#include "stromx/sl/Decode.h"

#include <stromx/runtime/DataProvider.h>
#include <stromx/runtime/EnumParameter.h>
#include <stromx/runtime/Id2DataPair.h>
#include <stromx/runtime/Id2DataComposite.h>
#include <stromx/runtime/Image.h>
#include <stromx/runtime/NumericParameter.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/Matrix.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/String.h>
#include <stromx/runtime/Variant.h>

#include <stromx/cvsupport/Image.h>
#include <stromx/cvsupport/Matrix.h>
#include <stromx/cvsupport/Utilities.h>

#include <codec/Codec.h>

#include "stromx/sl/Locale.h"

using namespace stromx::runtime;
    
namespace stromx
{
namespace sl
{        

const std::string Decode::TYPE("Decode");

const std::string Decode::PACKAGE(STROMX_SL_PACKAGE_NAME);
const runtime::Version Decode::VERSION(0, 1, 0);
    
Decode::Decode()
    : OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters())
    , m_decoder(0)
    , m_codecType(codecTypeGrayCode)
    , m_direction(CodecDirBoth)
    , m_currentPattern(0)
{
}

const runtime::DataRef Decode::getParameter(const unsigned int id) const
{
    switch(id)
    {
    case CODEC_TYPE:
        return m_codecType;
    case WIDTH:
        return m_width;
    case HEIGHT:
        return m_height;
    case DIRECTION:
        return m_direction;
    default:
        throw WrongParameterId(id, *this);
    }
}

void Decode::setParameter(const unsigned int id, const runtime::Data& value)
{
    try
    {
        switch(id)
        {
        case CODEC_TYPE:
            m_codecType = data_cast<Enum>(value);
            break;
        case DIRECTION:
            m_direction = data_cast<Enum>(value);
            break;
        case WIDTH:
            m_width = data_cast<UInt32>(value);
            break;
        case HEIGHT:
            m_height = data_cast<UInt32>(value);
            break;
        default:
            throw WrongParameterId(id, *this);
        }
    }
    catch(std::bad_cast&)
    {
        throw WrongParameterType(parameter(id), *this);
    }
}

void Decode::activate()
{
    m_decoder = Decoder::NewDecoder(CodecType(int(m_codecType)), m_width,
                                    m_height, CodecDir(int(m_direction)));
    m_currentPattern = 0;
}

void Decode::deactivate()
{
    delete m_decoder;
}

void Decode::execute(runtime::DataProvider& provider)
{
    Id2DataPair inputMapper(PATTERN);
    provider.receiveInputData(inputMapper);
    ReadAccess access(inputMapper.data());
    
    const Image & image = access.get<Image>();
    cv::Mat cvImage = cvsupport::getOpenCvMat(image);
    m_decoder->setFrame(m_currentPattern, cvImage);
    m_currentPattern++;
    
    if (m_currentPattern == m_decoder->getNPatterns())
    {
        cv::Mat cvHorizontal(m_height, m_width, CV_32F);
        cv::Mat cvVertical(m_height, m_width, CV_32F);
        cv::Mat cvShading;
        cv::Mat cvMask;
        
        m_decoder->decodeFrames(cvHorizontal, cvVertical, cvMask, cvShading);
        
        DataContainer horizontal(new cvsupport::Matrix(cvHorizontal));
        DataContainer vertical(new cvsupport::Matrix(cvVertical));
        DataContainer mask(new cvsupport::Image(cvMask));
        DataContainer shading(new cvsupport::Image(cvShading));
        
        provider.sendOutputData(
            Id2DataPair(HORIZONTAL, horizontal) &&
            Id2DataPair(VERTICAL, vertical) &&
            Id2DataPair(MASK, mask) &&
            Id2DataPair(SHADING, shading)
        );
    }
}

const std::vector<const runtime::Input*> Decode::setupInputs()
{
    std::vector<const Input*> inputs;
    
    Input* pattern = new Input(PATTERN, runtime::Variant::MONO_8_IMAGE);
    pattern->setTitle(L_("Pattern image"));
    pattern->setOperatorThread(INPUT_THREAD);
    inputs.push_back(pattern);
                    
    return inputs;
}

const std::vector<const runtime::Output*> Decode::setupOutputs()
{
    std::vector<const runtime::Output*> outputs;
    
    Output* horizontal = new Output(HORIZONTAL, runtime::Variant::FLOAT_32_MATRIX);
    horizontal->setTitle(L_("Horizontal encoding"));
    horizontal->setOperatorThread(OUTPUT_THREAD);
    outputs.push_back(horizontal);
    
    Output* vertical = new Output(VERTICAL, runtime::Variant::FLOAT_32_MATRIX);
    vertical->setTitle(L_("Vertical encoding"));
    vertical->setOperatorThread(OUTPUT_THREAD);
    outputs.push_back(vertical);
    
    Output* shading = new Output(SHADING, runtime::Variant::MONO_8_IMAGE);
    shading->setTitle(L_("Shading"));
    shading->setOperatorThread(OUTPUT_THREAD);
    outputs.push_back(shading);
    
    Output* mask = new Output(MASK, runtime::Variant::MONO_16_IMAGE);
    mask->setTitle(L_("Mask"));
    mask->setOperatorThread(OUTPUT_THREAD);
    outputs.push_back(mask);
    
    return outputs;
}

const std::vector<const runtime::Parameter*> Decode::setupParameters()
{
    std::vector<const Parameter*> parameters;
    
    EnumParameter* codecType = new EnumParameter(CODEC_TYPE);
    codecType->setTitle(L_("Codec"));
    codecType->setAccessMode(Parameter::INITIALIZED_WRITE);
    codecType->add(EnumDescription(Enum(codecTypePhaseShift2x3), L_("Phase shift 2x3")));
    codecType->add(EnumDescription(Enum(codecTypePhaseShift3), L_("Phase shift 3")));
    codecType->add(EnumDescription(Enum(codecTypePhaseShift3FastWrap), L_("Phase shift 3 fast wrap")));
    codecType->add(EnumDescription(Enum(codecTypePhaseShift3Unwrap), L_("Phase shift 3 unwrap")));
    codecType->add(EnumDescription(Enum(codecTypePhaseShift4), L_("Phase shift 4")));
    codecType->add(EnumDescription(Enum(codecTypeGrayCode), L_("Gray code")));
    codecType->add(EnumDescription(Enum(codecTypePhaseShift2p1), L_("Phase shift 2p1")));
    codecType->add(EnumDescription(Enum(codecTypeFastRatio), L_("Fast ratio")));
    codecType->add(EnumDescription(Enum(codecTypePhaseShiftModulated), L_("Phase shift modulated")));
    codecType->add(EnumDescription(Enum(codecTypePhaseShiftMicro), L_("Phase shift micro")));
    codecType->add(EnumDescription(Enum(codecTypePhaseShiftNStep), L_("Phase shift N step")));
    parameters.push_back(codecType);
    
    NumericParameter<UInt32>* width = new NumericParameter<UInt32>(WIDTH);
    width->setTitle(L_("Width"));
    width->setAccessMode(Parameter::INITIALIZED_WRITE);
    parameters.push_back(width);
    
    NumericParameter<UInt32>* height = new NumericParameter<UInt32>(HEIGHT);
    height->setTitle(L_("Height"));
    height->setAccessMode(Parameter::INITIALIZED_WRITE);
    parameters.push_back(height);
    
    EnumParameter* direction = new EnumParameter(DIRECTION);
    direction->setTitle(L_("Direction"));
    direction->setAccessMode(Parameter::INITIALIZED_WRITE);
    direction->add(EnumDescription(Enum(CodecDirHorizontal), L_("Horizontal")));
    direction->add(EnumDescription(Enum(CodecDirVertical), L_("Vertical")));
    direction->add(EnumDescription(Enum(CodecDirBoth), L_("Both directions")));
    parameters.push_back(direction);
                                
    return parameters;
}

} 
}
