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

#include <stromx/runtime/ConstDataRef.h>
#include <stromx/runtime/DataContainer.h>
#include <stromx/runtime/List.h>
#include <stromx/runtime/OperatorTester.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/String.h>
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
    CPPUNIT_TEST (testExecuteGrayCode);
    CPPUNIT_TEST_SUITE_END ();

    public:
        OpenGlProjectorTest() : m_operator(0) {}
        
        void setUp();
        void tearDown();

    protected:
        void testExecuteGrayCode();
        
    private:
        OperatorTester* m_operator;
};

CPPUNIT_TEST_SUITE_REGISTRATION (OpenGlProjectorTest);

void OpenGlProjectorTest::setUp ( void )
{
    m_operator = new OperatorTester(new OpenGlProjector());
    m_operator->initialize();
}

void OpenGlProjectorTest::testExecuteGrayCode()
{
    m_operator->setParameter(EncoderBase::WIDTH, UInt32(100));
    m_operator->setParameter(EncoderBase::HEIGHT, UInt32(50));
    m_operator->activate();
    
    for (int i = 0; i < 18; ++i)
    {
        DataContainer trigger = m_operator->getOutputData(EncoderBase::TRIGGER);
        m_operator->clearOutputData(EncoderBase::TRIGGER);
    }
}

void OpenGlProjectorTest::tearDown ( void )
{
    delete m_operator;
}

}
}

