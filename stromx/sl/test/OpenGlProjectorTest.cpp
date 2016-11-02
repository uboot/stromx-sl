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

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>

#include <stromx/runtime/DataContainer.h>
#include <stromx/runtime/OperatorTester.h>
#include <stromx/cvsupport/Image.h>

#include "stromx/sl/OpenGlProjector.h"

using namespace stromx::runtime;

namespace stromx
{
namespace sl
{


class OpenGlProjectorTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (OpenGlProjectorTest);
    CPPUNIT_TEST (testExecuteImage);
    CPPUNIT_TEST_SUITE_END ();

    public:
        OpenGlProjectorTest() : m_operator(0) {}
        
        void setUp();
        void tearDown();

    protected:
        void testExecuteImage();
        
    private:
        OperatorTester* m_operator;
};

CPPUNIT_TEST_SUITE_REGISTRATION (OpenGlProjectorTest);

void OpenGlProjectorTest::setUp ( void )
{
    m_operator = new OperatorTester(new OpenGlProjector());
    m_operator->initialize();
}

void OpenGlProjectorTest::testExecuteImage()
{
    m_operator->activate();
    
    cvsupport::Image* image = new cvsupport::Image(300, 200, runtime::Image::RGB_24);
    for (unsigned int i = 0; i < image->rows(); ++i)
    {
        for(unsigned int j = 0; j < image->cols(); ++j)
        {
            image->at<char>(i, j) = j % 3 ? 0 : 255;
        }
    }
    DataContainer container(image);
    m_operator->setInputData(OpenGlProjector::IMAGE, container);
    m_operator->setInputData(OpenGlProjector::IMAGE, container);
}

void OpenGlProjectorTest::tearDown ( void )
{
    delete m_operator;
}

}
}

