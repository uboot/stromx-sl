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

#include "stromx/sl/EncodeBase.h"

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

const std::string EncodeBase::PACKAGE(STROMX_SL_PACKAGE_NAME);
const runtime::Version EncodeBase::VERSION(0, 1, 0);
    
EncodeBase::EncodeBase(const std::string & type)
    : OperatorKernel(type, PACKAGE, VERSION)
    , m_encoder(0)
    , m_currentPattern(0)
{
}

const runtime::DataRef EncodeBase::getParameter(const unsigned int id) const
{
    switch(id)
    {
    case WIDTH:
        return m_width;
    case HEIGHT:
        return m_height;
    default:
        throw WrongParameterId(id, *this);
    }
}

void EncodeBase::setParameter(const unsigned int id, const runtime::Data& value)
{
    try
    {
        switch(id)
        {
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

void EncodeBase::initialize()
{
    OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
}

void EncodeBase::activate()
{
    m_encoder = createEncoder();
    m_currentPattern = 0;
}

void EncodeBase::deactivate()
{
    delete m_encoder;
}

void EncodeBase::execute(runtime::DataProvider& provider)
{
    cv::Mat pattern = m_encoder->getEncodingPattern(m_currentPattern);
    runtime::DataContainer out(new cvsupport::Image(pattern));
    runtime::Id2DataPair patternPair(PATTERN, out);
    provider.sendOutputData(patternPair);
    
    m_currentPattern += 1;
    m_currentPattern %= m_encoder->getNPatterns();
}

const std::vector<const runtime::Input*> EncodeBase::setupInputs()
{
    std::vector<const Input*> inputs;
                    
    return inputs;
}

const std::vector<const runtime::Output*> EncodeBase::setupOutputs()
{
    std::vector<const runtime::Output*> outputs;
    
    Output* pattern = new Output(PATTERN, runtime::Variant::RGB_24_IMAGE);
    pattern->setTitle(L_("Pattern"));
    outputs.push_back(pattern);
    
    return outputs;
}

const std::vector<const runtime::Parameter*> EncodeBase::setupParameters()
{
    std::vector<const Parameter*> parameters;
    
    NumericParameter<UInt32>* width = new NumericParameter<UInt32>(WIDTH);
    width->setTitle(L_("Width"));
    width->setAccessMode(Parameter::INITIALIZED_WRITE);
    parameters.push_back(width);
    
    NumericParameter<UInt32>* height = new NumericParameter<UInt32>(HEIGHT);
    height->setTitle(L_("Height"));
    height->setAccessMode(Parameter::INITIALIZED_WRITE);
    parameters.push_back(height);
                                
    return parameters;
}

} 
}
