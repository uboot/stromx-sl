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

#include <thread>

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
    CPPUNIT_TEST (testExecuteRow);
    CPPUNIT_TEST (testExecuteColumn);
    CPPUNIT_TEST (testExecutePixel);
    CPPUNIT_TEST_SUITE_END ();

    public:
        OpenGlProjectorTest() : m_operator(0) {}
        
        void setUp();
        void tearDown();

    protected:
        void testExecuteImage();
        void testExecuteRow();
        void testExecuteColumn();
        void testExecutePixel();
        
    private:
        const static int SLEEP_MS;
        const static int IMAGE_SIZE;
        const static int PATTERN_SIZE;
        
        static void fillWithPattern(runtime::Image* image);
        
        OperatorTester* m_operator;
};

CPPUNIT_TEST_SUITE_REGISTRATION (OpenGlProjectorTest);

const int OpenGlProjectorTest::SLEEP_MS = 100;
const int OpenGlProjectorTest::IMAGE_SIZE = 200;
const int OpenGlProjectorTest::PATTERN_SIZE = 100;

void OpenGlProjectorTest::fillWithPattern(runtime::Image* image)
{
    for (unsigned int i = 0; i < image->rows(); ++i)
    {
        for(unsigned int j = 0; j < image->cols(); ++j)
        {
            int isRowSquare = (j / PATTERN_SIZE + 1) % 2;
            int isColSquare = (i / PATTERN_SIZE) % 2;
            image->at<char>(i, j) = j % 3 ? 0 : 255 * (isRowSquare ^ isColSquare);
        }
    }
}

void OpenGlProjectorTest::setUp ( void )
{
    m_operator = new OperatorTester(new OpenGlProjector());
    m_operator->initialize();
}

void OpenGlProjectorTest::testExecuteImage()
{
    m_operator->activate();
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS)); 
    
    cvsupport::Image* image = new cvsupport::Image(IMAGE_SIZE, IMAGE_SIZE, 
                                                   runtime::Image::RGB_24);
    fillWithPattern(image);
    DataContainer container(image);
    m_operator->setInputData(OpenGlProjector::IMAGE, container);
    m_operator->setInputData(OpenGlProjector::IMAGE, container);
}

void OpenGlProjectorTest::testExecuteRow()
{
    m_operator->activate();
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS)); 
    
    cvsupport::Image* image = new cvsupport::Image(IMAGE_SIZE, 1, runtime::Image::RGB_24);
    fillWithPattern(image);
    DataContainer container(image);
    m_operator->setInputData(OpenGlProjector::IMAGE, container);
    m_operator->setInputData(OpenGlProjector::IMAGE, container);
}

void OpenGlProjectorTest::testExecuteColumn()
{
    m_operator->activate();
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS)); 
    
    cvsupport::Image* image = new cvsupport::Image(1, IMAGE_SIZE, runtime::Image::RGB_24);
    fillWithPattern(image);
    DataContainer container(image);
    m_operator->setInputData(OpenGlProjector::IMAGE, container);
    m_operator->setInputData(OpenGlProjector::IMAGE, container);
}

void OpenGlProjectorTest::testExecutePixel()
{
    m_operator->activate();
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    
    cvsupport::Image* image = new cvsupport::Image(1, 1, runtime::Image::RGB_24);
    fillWithPattern(image);
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

