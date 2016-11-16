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

#include <codec/Codec.h>

#include <stromx/runtime/DataContainer.h>
#include <stromx/runtime/OperatorTester.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/cvsupport/Image.h>

#include "stromx/sl/Encode.h"

using namespace stromx::runtime;

namespace stromx
{
namespace sl
{


class EncodeTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (EncodeTest);
    CPPUNIT_TEST (testExecuteGrayCode);
    CPPUNIT_TEST (testExecutePhaseShift2x3);
    CPPUNIT_TEST_SUITE_END ();

    public:
        EncodeTest() : m_operator(0) {}
        
        void setUp();
        void tearDown();

    protected:
        void testExecuteGrayCode();
        void testExecutePhaseShift2x3();
        
    private:
        OperatorTester* m_operator;
};

CPPUNIT_TEST_SUITE_REGISTRATION (EncodeTest);

void EncodeTest::setUp ( void )
{
    m_operator = new OperatorTester(new Encode());
    m_operator->initialize();
}

void EncodeTest::testExecuteGrayCode()
{
    m_operator->setParameter(Encode::WIDTH, UInt32(100));
    m_operator->setParameter(Encode::HEIGHT, UInt32(50));
    m_operator->activate();
    
    for (int i = 0; i < 18; ++i)
    {
        DataContainer pattern = m_operator->getOutputData(Encode::PATTERN);
        const Image & image = ReadAccess(pattern).get<Image>();
        std::string filename = "EncodeTest_testExecuteGrayCode_" + std::to_string(i) + ".png";
        cvsupport::Image::save(filename, image);
        m_operator->clearOutputData(Encode::PATTERN);
    }
}

void EncodeTest::testExecutePhaseShift2x3()
{
    m_operator->setParameter(Encode::WIDTH, UInt32(100));
    m_operator->setParameter(Encode::HEIGHT, UInt32(50));
    m_operator->setParameter(Encode::CODEC_TYPE, Enum(codecTypePhaseShift2x3));
    m_operator->activate();
    
    for (int i = 0; i < 12; ++i)
    {
        DataContainer pattern = m_operator->getOutputData(Encode::PATTERN);
        const Image & image = ReadAccess(pattern).get<Image>();
        std::string filename = "EncodeTest_testExecutePhaseShift2x3_" + std::to_string(i) + ".png";
        cvsupport::Image::save(filename, image);
        m_operator->clearOutputData(Encode::PATTERN);
    }
}

void EncodeTest::tearDown ( void )
{
    delete m_operator;
}

}
}

