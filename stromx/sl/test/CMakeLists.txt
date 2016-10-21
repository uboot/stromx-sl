add_test(NAME stromx_sl_test COMMAND stromx_sl_test)
set_tests_properties(stromx_sl_test PROPERTIES ENVIRONMENT "${TEST_ENVIRONMENT}")

if(MSVC)
    add_definitions(/DSTROMX_SL_STATIC)
endif(MSVC)

include_directories (
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CPPUNIT_INCLUDE_DIR}
)

set (SOURCES 
    ../Encode.cpp
    ../Sl.cpp
    main.cpp
    EncodeTest.cpp
)

add_executable(stromx_sl_test ${SOURCES})

set_target_properties(stromx_sl_test PROPERTIES FOLDER "test")

target_link_libraries (stromx_sl_test
    ${CPPUNIT_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${stromx_RUNTIME_LIB}
    ${stromx_CVSUPPORT_LIB}
    slalgorithm
)

