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

#ifndef STROMX_SL_CALIBRATE_H
#define STROMX_SL_CALIBRATE_H

#include <stromx/runtime/OperatorKernel.h>

#include "stromx/sl/DecodeBase.h"
#include "stromx/sl/Sl.h"

class Decoder;

namespace stromx
{
namespace sl
{

class STROMX_SL_API Calibrate : public DecodeBase
{   
public:    
    Calibrate();
    
    virtual OperatorKernel* clone() const { return new Calibrate; }
    
private:
    static const std::string TYPE;
}; 
      
}
}

#endif // STROMX_SL_CALIBRATE_H
