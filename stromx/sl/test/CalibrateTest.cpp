/* 
*  Copyright 2017 Matthias Fuchs
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

#include <codec/Codec.h>

#include <stromx/runtime/DataContainer.h>
#include <stromx/runtime/OperatorTester.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/cvsupport/Image.h>
#include <stromx/cvsupport/Matrix.h>

#include "stromx/sl/Calibrate.h"

using namespace stromx::runtime;

namespace stromx
{
namespace sl
{


class CalibrateTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (CalibrateTest);
    CPPUNIT_TEST (testExecute);
    CPPUNIT_TEST_SUITE_END ();

    public:
        CalibrateTest() : m_operator(0) {}
        
        void setUp();
        void tearDown();

    protected:
        void testExecute();
        
    private:
        OperatorTester* m_operator;
};

CPPUNIT_TEST_SUITE_REGISTRATION (CalibrateTest);

void CalibrateTest::setUp ( void )
{
    m_operator = new OperatorTester(new Calibrate());
    m_operator->initialize();
}

void CalibrateTest::testExecute()
{
    m_operator->setParameter(Calibrate::WIDTH, UInt32(100));
    m_operator->setParameter(Calibrate::HEIGHT, UInt32(50));
    m_operator->activate();
    
    for (int i = 0; i < 12; ++i)
    {
        std::string fileName = "phase_shift_2x3_" + std::to_string(i) + ".png";
        DataContainer image(new cvsupport::Image(fileName));
        m_operator->setInputData(Calibrate::PATTERN, image);
    }
}

void CalibrateTest::tearDown ( void )
{
    delete m_operator;
}

}
}


