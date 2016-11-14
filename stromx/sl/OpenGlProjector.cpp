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

#include <thread>
#include <chrono>   

#include <stromx/runtime/DataProvider.h>
#include <stromx/runtime/EnumParameter.h>
#include <stromx/runtime/Id2DataPair.h>
#include <stromx/runtime/Image.h>
#include <stromx/runtime/NumericParameter.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/Matrix.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/String.h>
#include <stromx/runtime/TriggerData.h>
#include <stromx/runtime/Variant.h>

#include <stromx/cvsupport/Image.h>

#include <projector/Projector.h>

#include "stromx/sl/Locale.h"

using namespace stromx::runtime;
    
namespace stromx
{
namespace sl
{        

const std::string OpenGlProjector::TYPE("OpenGlProjector");
const std::string OpenGlProjector::PACKAGE(STROMX_SL_PACKAGE_NAME);
const runtime::Version OpenGlProjector::VERSION(0, 1, 0);
const int OpenGlProjector::DISPLAY_SLEEP_MS = 100;
    
OpenGlProjector::OpenGlProjector()
    : OperatorKernel(TYPE, PACKAGE, VERSION, setupInputs(), setupOutputs(), setupParameters())
    , m_projector(0)
{
}

const runtime::DataRef OpenGlProjector::getParameter(const unsigned int id) const
{
    switch(id)
    {
    default:
        throw WrongParameterId(id, *this);
    }
}

void OpenGlProjector::setParameter(const unsigned int id, const runtime::Data& /*value*/)
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

void OpenGlProjector::activate()
{
    m_projector = Projector::NewProjector(projectorTypeOpenGL, 0);
}

void OpenGlProjector::deactivate()
{
    delete m_projector;
}

void OpenGlProjector::execute(runtime::DataProvider& provider)
{
    Id2DataPair inputMap(IMAGE);
    provider.receiveInputData(inputMap);
    
    ReadAccess access(inputMap.data());
    const runtime::Image & image = access.get<runtime::Image>();
    m_projector->displayTexture(image.data(), image.width(), image.height());
    std::this_thread::sleep_for(std::chrono::milliseconds(DISPLAY_SLEEP_MS)); 
    
    Id2DataPair outputMap(TRIGGER, DataContainer(new TriggerData()));
    provider.sendOutputData(outputMap);
}

const std::vector<const runtime::Input*> OpenGlProjector::setupInputs()
{
    std::vector<const Input*> inputs;
    
    Input* image = new Input(IMAGE, runtime::Variant::RGB_24_IMAGE);
    image->setTitle(L_("Image"));
    inputs.push_back(image);
                    
    return inputs;
}

const std::vector<const runtime::Output*> OpenGlProjector::setupOutputs()
{
    std::vector<const runtime::Output*> outputs;
    
    Output* trigger = new Output(TRIGGER, runtime::Variant::TRIGGER);
    trigger->setTitle(L_("Trigger"));
    outputs.push_back(trigger);
    
    return outputs;
}

const std::vector<const runtime::Parameter*> OpenGlProjector::setupParameters()
{
    std::vector<const Parameter*> parameters;
                                
    return parameters;
}

} 
}
