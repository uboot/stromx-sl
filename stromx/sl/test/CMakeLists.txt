add_test(NAME stromx_sl_test COMMAND stromx_sl_test)
set_tests_properties(stromx_sl_test PROPERTIES ENVIRONMENT "${TEST_ENVIRONMENT}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_0.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_0.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_1.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_1.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_2.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_2.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_3.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_3.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_4.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_4.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_5.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_5.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_6.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_6.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_7.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_7.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_8.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_8.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_9.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_9.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_10.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_10.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_11.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_11.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_12.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_12.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_13.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_13.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_14.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_14.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_15.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_15.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_16.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_16.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/gray_code_17.png ${CMAKE_CURRENT_BINARY_DIR}/gray_code_17.png COPYONLY)

if(MSVC)
    add_definitions(/DSTROMX_SL_STATIC)
endif(MSVC)

include_directories (
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CPPUNIT_INCLUDE_DIR}
)

set (SOURCES 
    ../Decode.cpp
    ../Encode.cpp
    ../OpenGlProjector.cpp
    ../Sl.cpp
    DecodeTest.cpp
    EncodeTest.cpp
    main.cpp
    OpenGlProjectorTest.cpp
)

add_executable(stromx_sl_test ${SOURCES})

set_target_properties(stromx_sl_test PROPERTIES FOLDER "test")

target_link_libraries (stromx_sl_test
    ${CPPUNIT_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${stromx_RUNTIME_LIB}
    ${stromx_CVSUPPORT_LIB}
    slalgorithm
    slprojector
)

