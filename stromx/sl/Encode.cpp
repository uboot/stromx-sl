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
#include <stromx/runtime/List.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/Matrix.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/String.h>
#include <stromx/runtime/Variant.h>

#include "stromx/sl/Locale.h"


using namespace stromx::runtime;
    
namespace stromx
{
namespace sl
{        

const std::string Encode::TYPE("Encode");

const std::string Encode::PACKAGE(STROMX_SL_PACKAGE_NAME);
const runtime::Version Encode::VERSION(0, 1, 0);
    
Encode::Encode()
  : OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters())
{
}

Encode::~Encode()
{
}

const runtime::DataRef Encode::getParameter(const unsigned int id) const
{
    switch(id)
    {
    default:
        throw WrongParameterId(id, *this);
    }
}

void Encode::setParameter(const unsigned int id, const runtime::Data& value)
{
    try
    {
        switch(id)
        {
        default:
            throw WrongParameterId(id, *this);
        }
    }
    catch(std::bad_cast&)
    {
        throw WrongParameterType(parameter(id), *this);
    }
}

void Encode::execute(runtime::DataProvider& provider)
{
}

const std::vector<const runtime::Input*> Encode::setupInputs()
{
    std::vector<const Input*> inputs;
                    
    return inputs;
}

const std::vector<const runtime::Output*> Encode::setupOutputs()
{
    std::vector<const runtime::Output*> outputs;
    
    return outputs;
}

const std::vector<const runtime::Parameter*> Encode::setupParameters()
{
    std::vector<const Parameter*> parameters;                                
                                
    return parameters;
}

} 
}
