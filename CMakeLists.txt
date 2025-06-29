cmake_minimum_required(VERSION 3.10)
project(FileRAII)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")

set(LIB_SRCS FileRAII.cpp)
set(TEST_SRC TestProgram.cpp)

add_library(FileRAII_static STATIC ${LIB_SRCS})
set_target_properties(FileRAII_static PROPERTIES OUTPUT_NAME "FileRAII")

add_library(FileRAII_shared SHARED ${LIB_SRCS})
set_target_properties(FileRAII_shared PROPERTIES 
    OUTPUT_NAME "FileRAII"
    POSITION_INDEPENDENT_CODE ON
)

if(APPLE)
    set_target_properties(FileRAII_shared PROPERTIES
        MACOSX_RPATH ON
        INSTALL_NAME_DIR "@executable_path"
    )
else()
    set_target_properties(FileRAII_shared PROPERTIES
        BUILD_WITH_INSTALL_RPATH TRUE
        INSTALL_RPATH "\$ORIGIN"
    )
endif()

add_executable(TestProgramStaticLinking ${TEST_SRC})
target_link_libraries(TestProgramStaticLinking PRIVATE FileRAII_static)

add_executable(TestProgramDynamicLinking ${TEST_SRC})
target_link_libraries(TestProgramDynamicLinking PRIVATE FileRAII_shared)

if(APPLE)
    set_target_properties(TestProgramDynamicLinking PROPERTIES
        INSTALL_RPATH "@executable_path"
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(TestProgramDynamicLinking PROPERTIES
        INSTALL_RPATH "$ORIGIN"
    )
endif()

add_custom_target(build_all
    DEPENDS TestProgramStaticLinking TestProgramDynamicLinking
    COMMENT "Building both static and dynamic versions"
)