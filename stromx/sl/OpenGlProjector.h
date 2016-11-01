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

#ifndef STROMX_SL_OPENGLPROJECTOR_H
#define STROMX_SL_OPENGLPROJECTOR_H

#include "stromx/sl/EncoderBase.h"

namespace stromx
{
namespace sl
{

class STROMX_SL_API OpenGlProjector : public EncoderBase
{   
public:     
    OpenGlProjector();
    
    virtual OperatorKernel* clone() const { return new OpenGlProjector; }
    virtual void execute(runtime::DataProvider& provider);
    
private:
    static const std::string TYPE;
    
    unsigned int m_currentPattern;
}; 
      
}
}

#endif // STROMX_SL_OPENGLPROJECTOR_H
