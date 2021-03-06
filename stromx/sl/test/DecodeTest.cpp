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
#include <stromx/cvsupport/Matrix.h>

#include "stromx/sl/Decode.h"

using namespace stromx::runtime;

namespace stromx
{
namespace sl
{


class DecodeTest : public CPPUNIT_NS :: TestFixture
{
    CPPUNIT_TEST_SUITE (DecodeTest);
    CPPUNIT_TEST (testExecuteGrayCode);
    CPPUNIT_TEST (testExecutePhaseShift2x3);
    CPPUNIT_TEST_SUITE_END ();

    public:
        DecodeTest() : m_operator(0) {}
        
        void setUp();
        void tearDown();

    protected:
        void testExecuteGrayCode();
        void testExecutePhaseShift2x3();
        
    private:
        OperatorTester* m_operator;
};

CPPUNIT_TEST_SUITE_REGISTRATION (DecodeTest);

void DecodeTest::setUp ( void )
{
    m_operator = new OperatorTester(new Decode());
    m_operator->initialize();
}

void DecodeTest::testExecuteGrayCode()
{
    m_operator->setParameter(Decode::WIDTH, UInt32(100));
    m_operator->setParameter(Decode::HEIGHT, UInt32(50));
    m_operator->activate();
    
    for (int i = 0; i < 18; ++i)
    {
        std::string fileName = "gray_code_" + std::to_string(i) + ".png";
        DataContainer image(new cvsupport::Image(fileName));
        m_operator->setInputData(Decode::PATTERN, image);
    }
    
    DataContainer shading = m_operator->getOutputData(Decode::SHADING);
    cvsupport::Image::save("DecodeTest_testExecuteGrayCode_shading.png", ReadAccess(shading).get<Image>());
    
    DataContainer mask = m_operator->getOutputData(Decode::MASK);
    cvsupport::Image::save("DecodeTest_testExecuteGrayCode_mask.png", ReadAccess(mask).get<Image>());
    
    DataContainer horizontal = m_operator->getOutputData(Decode::HORIZONTAL);
    cvsupport::Matrix::save("DecodeTest_testExecuteGrayCode_horizontal.npy", ReadAccess(horizontal).get<Matrix>());
    
    DataContainer vertical = m_operator->getOutputData(Decode::VERTICAL);
    cvsupport::Matrix::save("DecodeTest_testExecuteGrayCode_vertical.npy", ReadAccess(vertical).get<Matrix>());
}

void DecodeTest::testExecutePhaseShift2x3()
{
    m_operator->setParameter(Decode::WIDTH, UInt32(100));
    m_operator->setParameter(Decode::HEIGHT, UInt32(50));
    m_operator->setParameter(Decode::CODEC_TYPE, Enum(codecTypePhaseShift2x3));
    m_operator->activate();
    
    for (int i = 0; i < 12; ++i)
    {
        std::string fileName = "phase_shift_2x3_" + std::to_string(i) + ".png";
        DataContainer image(new cvsupport::Image(fileName));
        m_operator->setInputData(Decode::PATTERN, image);
    }
    
    DataContainer shading = m_operator->getOutputData(Decode::SHADING);
    cvsupport::Image::save("DecodeTest_testExecutePhaseShift2x3_shading.png", ReadAccess(shading).get<Image>());
    
    DataContainer mask = m_operator->getOutputData(Decode::MASK);
    cvsupport::Image::save("DecodeTest_testExecutePhaseShift2x3_mask.png", ReadAccess(mask).get<Image>());
    
    DataContainer horizontal = m_operator->getOutputData(Decode::HORIZONTAL);
    cvsupport::Matrix::save("DecodeTest_testExecutePhaseShift2x3_horizontal.npy", ReadAccess(horizontal).get<Matrix>());
    
    DataContainer vertical = m_operator->getOutputData(Decode::VERTICAL);
    cvsupport::Matrix::save("DecodeTest_testExecutePhaseShift2x3_vertical.npy", ReadAccess(vertical).get<Matrix>());
}

void DecodeTest::tearDown ( void )
{
    delete m_operator;
}

}
}

