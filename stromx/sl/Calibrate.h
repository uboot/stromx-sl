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
#include <stromx/runtime/ReadAccess.h>

#include "stromx/sl/DecodeBase.h"
#include "stromx/sl/Sl.h"

class Calibrator;

namespace stromx
{
namespace sl
{

class STROMX_SL_API Calibrate : public DecodeBase
{   
public:
    enum DataId
    {
        CALIBRATOR_TYPE = NUM_DATA_IDS,
        PARAMETER_PATTERN_SIZE_X,
        PARAMETER_PATTERN_SIZE_Y,
        PARAMETER_SQUARE_SIZE,
        CAMERA_MATRIX,
        CAMERA_DIST_COEFFS,
        PROJECTOR_MATRIX,
        PROJECTOR_DIST_COEFFS,
        RVEC,
        TVEC
    };
    
    Calibrate();
    
    virtual OperatorKernel* clone() const { return new Calibrate; }
    
    virtual void execute(runtime::DataProvider& provider);
    virtual void activate();
    virtual void deactivate();
    
protected:
    virtual const std::vector<const runtime::Output*> setupOutputs();
    virtual const std::vector<const runtime::Parameter*> setupParameters();
    
private:
    static const std::string TYPE;
    
    Calibrator* m_calibrator;
    unsigned int m_currentPattern;
    std::vector<runtime::ReadAccess> m_patternSequence;
    std::vector< std::vector<runtime::ReadAccess> > m_patternSequences;
}; 
      
}
}

#endif // STROMX_SL_CALIBRATE_H
