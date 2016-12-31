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
    
Encode::Encode()
    : EncodeBase(TYPE)
    , m_codecType(codecTypeGrayCode)
    , m_direction(CodecDirBoth)
{
}

const runtime::DataRef Encode::getParameter(const unsigned int id) const
{
    switch(id)
    {
    case CODEC_TYPE:
        return m_codecType;
    case DIRECTION:
        return m_direction;
    default:
        return EncodeBase::getParameter(id);
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
        default:
            EncodeBase::setParameter(id, value);
            break;
        }
    }
    catch(std::bad_cast&)
    {
        throw WrongParameterType(parameter(id), *this);
    }
}

Encoder* Encode::createEncoder()
{
    return Encoder::NewEncoder(CodecType(int(m_codecType)), width(), height(),
                               CodecDir(int(m_direction)));
}

const std::vector<const runtime::Parameter*> Encode::setupParameters()
{
    std::vector<const Parameter*> parameters = EncodeBase::setupParameters();
    
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
