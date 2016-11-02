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

#include "stromx/sl/Encode.h"

#include <stromx/runtime/DataProvider.h>
#include <stromx/runtime/EnumParameter.h>
#include <stromx/runtime/Id2DataPair.h>
#include <stromx/runtime/Image.h>
#include <stromx/runtime/NumericParameter.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/Matrix.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/String.h>
#include <stromx/runtime/Variant.h>

#include <stromx/cvsupport/Image.h>

#include <codec/Codec.h>

#include "stromx/sl/Locale.h"

using namespace stromx::runtime;
    
namespace stromx
{
namespace sl
{        

const std::string Encode::TYPE("Encode");

const std::string Encode::PACKAGE(STROMX_SL_PACKAGE_NAME);
const runtime::Version Encode::VERSION(0, 1, 0);
    
Encode::Encode()
  : OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters())
  , m_encoder(0)
  , m_codecType(codecTypeGrayCode)
  , m_direction(CodecDirBoth)
  , m_currentPattern(0)
{
}

const runtime::DataRef Encode::getParameter(const unsigned int id) const
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

void Encode::setParameter(const unsigned int id, const runtime::Data& value)
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

void Encode::activate()
{
    m_encoder = Encoder::NewEncoder(CodecType(int(m_codecType)), m_width,
                                    m_height, CodecDir(int(m_direction)));
    m_currentPattern = 0;
}

void Encode::deactivate()
{
    delete m_encoder;
}

void Encode::execute(runtime::DataProvider& provider)
{
    cv::Mat pattern = m_encoder->getEncodingPattern(m_currentPattern);
    runtime::DataContainer out(new cvsupport::Image(pattern));
    runtime::Id2DataPair patternPair(PATTERN, out);
    provider.sendOutputData(patternPair);
    
    m_currentPattern += 1;
    m_currentPattern %= m_encoder->getNPatterns();
}

const std::vector<const runtime::Input*> Encode::setupInputs()
{
    std::vector<const Input*> inputs;
                    
    return inputs;
}

const std::vector<const runtime::Output*> Encode::setupOutputs()
{
    std::vector<const runtime::Output*> outputs;
    
    Output* pattern = new Output(PATTERN, runtime::Variant::BGR_24_IMAGE);
    pattern->setTitle(L_("Pattern"));
    outputs.push_back(pattern);
    
    return outputs;
}

const std::vector<const runtime::Parameter*> Encode::setupParameters()
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
    direction->add(EnumDescription(Enum(CodecDirBoth), L_("Both direction")));
    parameters.push_back(direction);
                                
    return parameters;
}

} 
}
