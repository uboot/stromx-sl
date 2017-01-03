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

#ifndef STROMX_SL_DECODEBASE_H
#define STROMX_SL_DECODEBASE_H

#include <stromx/runtime/OperatorKernel.h>

#include "stromx/sl/Sl.h"

class Decoder;

namespace stromx
{
namespace sl
{

class DecodeBase : public runtime::OperatorKernel
{   
public:      
    enum DataId
    {
        WIDTH,
        HEIGHT,
        PATTERN,
        NUM_DATA_IDS
    };
    
    enum OperatorThread
    {
        INPUT_THREAD,
        OUTPUT_THREAD
    };
    
    DecodeBase(const std::string & type);
    
    virtual const runtime::DataRef getParameter(const unsigned int id) const;
    virtual void setParameter(const unsigned int id, const runtime::Data& value);
    
protected:
    virtual void initialize();
    virtual const std::vector<const runtime::Output*> setupOutputs();
    virtual const std::vector<const runtime::Parameter*> setupParameters();
    
    runtime::UInt32 width() const { return m_width; }
    runtime::UInt32 height() const { return m_height; }
    
private:
    static const std::string PACKAGE;
    static const runtime::Version VERSION; 
    
    static const std::vector<const runtime::Input*> setupInputs();
    
    runtime::UInt32 m_width;
    runtime::UInt32 m_height;
}; 
      
}
}

#endif // STROMX_SL_DECODEBASE_H
