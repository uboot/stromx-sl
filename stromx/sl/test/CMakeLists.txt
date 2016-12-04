add_test(NAME stromx_sl_test COMMAND stromx_sl_test)
set_tests_properties(stromx_sl_test PROPERTIES ENVIRONMENT "${TEST_ENVIRONMENT}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mask_200x100.png ${CMAKE_CURRENT_BINARY_DIR}/mask_200x100.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/grid_200x100_x.npy ${CMAKE_CURRENT_BINARY_DIR}/grid_200x100_x.npy COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/grid_200x100_y.npy ${CMAKE_CURRENT_BINARY_DIR}/grid_200x100_y.npy COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/coordinates.npy ${CMAKE_CURRENT_BINARY_DIR}/coordinates.npy COPYONLY)

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


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_0.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_0.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_1.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_1.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_2.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_2.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_3.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_3.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_4.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_4.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_5.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_5.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_6.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_6.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_7.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_7.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_8.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_8.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_9.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_9.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_10.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_10.png COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/phase_shift_2x3_11.png ${CMAKE_CURRENT_BINARY_DIR}/phase_shift_2x3_11.png COPYONLY)
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
    ../RbfInterpolate.cpp
    ../Sl.cpp
    DecodeTest.cpp
    EncodeTest.cpp
    main.cpp
    OpenGlProjectorTest.cpp
    RbfInterpolateTest.cpp
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

