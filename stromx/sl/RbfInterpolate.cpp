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

#include "stromx/sl/RbfInterpolate.h"

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

#include <calibrator/RBFInterpolator.h>

#include "stromx/sl/Locale.h"

using namespace stromx::runtime;
    
namespace stromx
{
namespace sl
{        

const std::string RbfInterpolate::TYPE("RbfInterpolate");

const std::string RbfInterpolate::PACKAGE(STROMX_SL_PACKAGE_NAME);
const runtime::Version RbfInterpolate::VERSION(0, 1, 0);
    
RbfInterpolate::RbfInterpolate()
    : OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters())
    , m_decoder(0)
    , m_currentPattern(0)
{
}

const runtime::DataRef RbfInterpolate::getParameter(const unsigned int id) const
{
    switch(id)
    {
    default:
        throw WrongParameterId(id, *this);
    }
}

void RbfInterpolate::setParameter(const unsigned int id, const runtime::Data& value)
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

void RbfInterpolate::activate()
{
}

void RbfInterpolate::deactivate()
{
}

void RbfInterpolate::execute(runtime::DataProvider& provider)
{

}

const std::vector<const runtime::Input*> RbfInterpolate::setupInputs()
{
    std::vector<const Input*> inputs;
    
    Input* inputData = new Input(INPUT_DATA, runtime::Variant::FLOAT_MATRIX);
    inputData->setTitle(L_("Input data"));
    inputData->setVisualization(Variant::IMAGE);
    inputs.push_back(inputData);
    
    Input* inputPoints = new Input(INPUT_POINTS, runtime::Variant::FLOAT_MATRIX);
    inputPoints->setTitle(L_("Input points"));
    inputPoints->setCols(2);
    inputs.push_back(inputPoints);

    return inputs;
}

const std::vector<const runtime::Output*> RbfInterpolate::setupOutputs()
{
    std::vector<const runtime::Output*> outputs;
    
    Output* dataAtPoints = new Output(DATA_AT_POINTS, runtime::Variant::FLOAT_MATRIX);
    dataAtPoints->setTitle(L_("Interpolated data"));
    dataAtPoints->setCols(1);
    outputs.push_back(dataAtPoints);
    
    return outputs;
}

const std::vector<const runtime::Parameter*> RbfInterpolate::setupParameters()
{
    std::vector<const Parameter*> parameters;
    
                                
    return parameters;
}

} 
}
