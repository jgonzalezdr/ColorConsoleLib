cmake_minimum_required( VERSION 3.3 )

project( Test.ColorConsole_Init.Win32 )

#
# Test configuration
#

include_directories(
    ${PROD_SOURCE_DIR}/sources
    ${PROD_SOURCE_DIR}/include
    ${MOCKS_DIR}
    ${HELPERS_DIR}
)

#
# Add your production source files to the following list
#
set( PROD_SRC_FILES
     ${PROD_SOURCE_DIR}/sources/ColorConsole.cpp
)

#
# Add your test source files to the following list
#
set( TEST_SRC_FILES
     ColorConsole_Init_Win32_test.cpp
     ${MOCKS_DIR}/Win32_mock.cpp
     ${MOCKS_DIR}/Win32_expect.cpp
     ${HELPERS_DIR}/TestHelpers.cpp
)

add_definitions( "-DCOLORCONSOLE_REQUIRE_INITIALIZATION" )

# Generate test target
include( ../GenerateTest.cmake )
