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

#include "stromx/sl/OpenGlProjector.h"

#include <stromx/runtime/DataProvider.h>
#include <stromx/runtime/Id2DataPair.h>
#include <stromx/runtime/TriggerData.h>

#include <codec/Codec.h>

namespace stromx
{
namespace sl
{
    
const std::string OpenGlProjector::TYPE("OpenGlProjector");
    
OpenGlProjector::OpenGlProjector()
    : EncoderBase(TYPE)
    , m_currentPattern(0)
{
}

void OpenGlProjector::execute(runtime::DataProvider& provider)
{
    cv::Mat pattern = currentEncoder()->getEncodingPattern(m_currentPattern);
    runtime::DataContainer out(new runtime::TriggerData());
    provider.sendOutputData(runtime::Id2DataPair(TRIGGER, out));
    
    m_currentPattern += 1;
    m_currentPattern %= currentEncoder()->getNPatterns();
}

}
}

