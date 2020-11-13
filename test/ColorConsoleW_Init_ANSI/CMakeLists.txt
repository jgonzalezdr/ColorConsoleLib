cmake_minimum_required( VERSION 3.3 )

project( Test.ColorConsoleW_Init.ANSI )

#
# Test configuration
#

set( PROD_DIR ${CMAKE_SOURCE_DIR}/lib )
set( MOCKS_DIR ${CMAKE_SOURCE_DIR}/test/Mocks )
set( HELPERS_DIR ${CMAKE_SOURCE_DIR}/test/TestHelpers )

include_directories(
    ${PROD_DIR}/sources
    ${PROD_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${MOCKS_DIR}
    ${HELPERS_DIR}
)

#
# Add your production source files to the following list
#
set( PROD_SRC_FILES
     ${PROD_DIR}/sources/ColorConsoleW.cpp
)

#
# Add your test source files to the following list
#
set( TEST_SRC_FILES
     ColorConsoleW_Init_ANSI_test.cpp
     ${HELPERS_DIR}/TestHelpers.cpp
)

add_definitions( "-DCOLORCONSOLE_REQUIRE_INITIALIZATION" )

# Generate test target
include( ../GenerateTest.cmake )
