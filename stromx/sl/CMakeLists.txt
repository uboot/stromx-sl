configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Config.h
)

include_directories (
    ${CMAKE_SOURCE_DIR}/slstudio/src
    ${CMAKE_BINARY_DIR}/slstudio/src
    ${CMAKE_BINARY_DIR}/slstudio/src/projector
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

set (SOURCES 
    Decode.cpp
    DecodeBase.cpp
    Encode.cpp
    EncodeBase.cpp
    OpenGlProjector.cpp
    RbfInterpolate.cpp
    Sl.cpp
)

add_library (stromx_sl SHARED ${SOURCES})

set(VERSION_STRING "${STROMX_SL_VERSION_MAJOR}.${STROMX_SL_VERSION_MINOR}.${STROMX_SL_VERSION_PATCH}")

set_target_properties (stromx_sl PROPERTIES
    VERSION ${VERSION_STRING}
    SOVERSION ${VERSION_STRING}
    FOLDER "library"
)

target_link_libraries (stromx_sl
    ${stromx_RUNTIME_LIB}
    ${stromx_CVSUPPORT_LIB}
    slalgorithm
    slprojector
)

if(WIN32)
    install (TARGETS stromx_sl
        RUNTIME DESTINATION .
        LIBRARY DESTINATION ${LIB_DIR}
        ARCHIVE DESTINATION ${LIB_DIR}
    )
else(WIN32)
    install (TARGETS stromx_sl
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${LIB_DIR}
        ARCHIVE DESTINATION ${LIB_DIR}
    )
endif(WIN32)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/stromx/sl
    DESTINATION include/stromx
    FILES_MATCHING PATTERN "*.h"
    PATTERN "test" EXCLUDE
)

install(FILES ${CMAKE_BINARY_DIR}/stromx/sl/Config.h
    DESTINATION include/stromx/sl
)

if(BUILD_TESTS)
    add_subdirectory(test)
endif(BUILD_TESTS)
