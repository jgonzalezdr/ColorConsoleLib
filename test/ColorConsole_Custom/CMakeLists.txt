cmake_minimum_required( VERSION 3.3 )

project( Test.ColorConsole.Custom )

#
# Test configuration
#

set( PROD_DIR ${CMAKE_SOURCE_DIR}/lib )
set( MOCKS_DIR ${CMAKE_SOURCE_DIR}/test/Mocks )

include_directories(
    ${PROD_DIR}/sources
    ${PROD_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MOCKS_DIR}
)

#
# Add your production source files to the following list
#
set( PROD_SRC_FILES
     ${PROD_DIR}/sources/ColorConsole.cpp
)

#
# Add your test source files to the following list
#
set( TEST_SRC_FILES
     ColorConsole_Custom_test.cpp
)

if( WIN32 )
     set( TEST_SRC_FILES ${TEST_SRC_FILES}
          ${MOCKS_DIR}/Win32_mock.cpp
     )
endif()


# Generate test target
include( ../GenerateTest.cmake )
