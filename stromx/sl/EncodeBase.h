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

#ifndef STROMX_SL_ENCODEBASE_H
#define STROMX_SL_ENCODEBASE_H

#include <stromx/runtime/OperatorKernel.h>

#include "stromx/sl/Sl.h"

class Encoder;

namespace stromx
{
namespace sl
{

class EncodeBase : public runtime::OperatorKernel
{   
public:      
    enum DataId
    {
        PATTERN,
        WIDTH,
        HEIGHT,
        NUM_DATA_IDS
    };
    
    EncodeBase(const std::string & type);
    
    virtual const runtime::DataRef getParameter(const unsigned int id) const;
    virtual void setParameter(const unsigned int id, const runtime::Data& value);
    virtual void activate();
    virtual void deactivate();
    virtual void execute(runtime::DataProvider& provider);
    
protected:
    virtual const std::vector<const runtime::Parameter*> setupParameters();
    virtual Encoder* createEncoder() = 0;
    virtual void initialize();
    
    unsigned int width() const { return m_width; }
    unsigned int height() const { return m_height; }
    
private:
    static const std::string PACKAGE;
    static const runtime::Version VERSION; 
    
    static const std::vector<const runtime::Input*> setupInputs();
    static const std::vector<const runtime::Output*> setupOutputs();
    
    Encoder* m_encoder;
    runtime::UInt32 m_width;
    runtime::UInt32 m_height;
    unsigned int m_currentPattern;
}; 
      
}
}

#endif // STROMX_SL_ENCODEBASE_H
