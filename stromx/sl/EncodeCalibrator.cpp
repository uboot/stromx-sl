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

#include "stromx/sl/EncodeCalibrator.h"

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

#include <codec/CodecCalibration.h>

#include "stromx/sl/Locale.h"

using namespace stromx::runtime;
    
namespace stromx
{
namespace sl
{        

const std::string EncodeCalibrator::TYPE("EncodeCalibrator");
    
EncodeCalibrator::EncodeCalibrator()
    : EncodeBase(TYPE)
{
}

Encoder* EncodeCalibrator::createEncoder()
{
    return new EncoderCalibration(width(), height(), CodecDirBoth);
}

} 
}
