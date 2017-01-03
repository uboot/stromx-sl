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

#include "stromx/sl/Calibrate.h"

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

const std::string Calibrate::TYPE("Calibrate");
    
Calibrate::Calibrate()
    : DecodeBase(TYPE)
{
}

void Calibrate::execute(runtime::DataProvider& provider)
{
}

const std::vector<const runtime::Output*> Calibrate::setupOutputs()
{
    std::vector<const runtime::Output*> outputs = DecodeBase::setupOutputs();
    
    runtime::Output* cameraMatrix = new runtime::Output(CAMERA_MATRIX, runtime::Variant::FLOAT_64_MATRIX);
    cameraMatrix->setTitle(L_("Camera matrix"));
    cameraMatrix->setRows(3);
    cameraMatrix->setCols(3);
    outputs.push_back(cameraMatrix);
    
    runtime::Output* cameraDistCoeffs = new runtime::Output(CAMERA_DIST_COEFFS, runtime::Variant::FLOAT_64_MATRIX);
    cameraDistCoeffs->setTitle(L_("Camera distortion coefficients"));
    cameraDistCoeffs->setRows(1);
    cameraDistCoeffs->setCols(5);
    outputs.push_back(cameraDistCoeffs);
                
    runtime::Output* projectorMatrix = new runtime::Output(PROJECTOR_MATRIX, runtime::Variant::FLOAT_64_MATRIX);
    projectorMatrix->setTitle(L_("Projector matrix"));
    projectorMatrix->setRows(3);
    projectorMatrix->setCols(3);
    outputs.push_back(projectorMatrix);
    
    runtime::Output* projectorDistCoeffs = new runtime::Output(PROJECTOR_DIST_COEFFS, runtime::Variant::FLOAT_64_MATRIX);
    projectorDistCoeffs->setTitle(L_("Projector distortion coefficients"));
    projectorDistCoeffs->setRows(1);
    projectorDistCoeffs->setCols(5);
    outputs.push_back(projectorDistCoeffs);
                    
    runtime::Output* rvec = new runtime::Output(RVEC, runtime::Variant::FLOAT_64_MATRIX);
    rvec->setTitle(L_("Rotation"));
    rvec->setRows(3);
    rvec->setCols(1);
    outputs.push_back(rvec);
    
    runtime::Output* tvec = new runtime::Output(TVEC, runtime::Variant::FLOAT_64_MATRIX);
    tvec->setTitle(L_("Translation"));
    tvec->setRows(3);
    tvec->setCols(1);
    outputs.push_back(tvec);
    
    return outputs;
}

const std::vector<const runtime::Parameter*> Calibrate::setupParameters()
{
    std::vector<const Parameter*> parameters = DecodeBase::setupParameters();
    
    NumericParameter<UInt32>* patternSizeXParameter = new NumericParameter<UInt32>(PARAMETER_PATTERN_SIZE_X);
    patternSizeXParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
    patternSizeXParameter->setTitle(L_("Pattern size X"));
    patternSizeXParameter->setMin(UInt32(1));
    parameters.push_back(patternSizeXParameter);
    
    NumericParameter<UInt32>* patternSizeYParameter = new NumericParameter<UInt32>(PARAMETER_PATTERN_SIZE_Y);
    patternSizeYParameter->setAccessMode(Parameter::ACTIVATED_WRITE);
    patternSizeYParameter->setTitle(L_("Pattern size Y"));
    patternSizeYParameter->setMin(UInt32(1));
    parameters.push_back(patternSizeYParameter);
    
    NumericParameter<UInt32>* squareSizeParameter = new NumericParameter<UInt32>(PARAMETER_SQUARE_SIZE);
    squareSizeParameter->setAccessMode(Parameter::ACTIVATED_WRITE);
    squareSizeParameter->setTitle(L_("Square size"));
    squareSizeParameter->setMin(UInt32(0));
    parameters.push_back(squareSizeParameter);
                                
    return parameters;
}

} 
}
