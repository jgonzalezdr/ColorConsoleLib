cmake_minimum_required( VERSION 3.3 )

project( Test.ColorConsoleW.ANSI )

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
     ${PROD_SOURCE_DIR}/sources/ColorConsoleW.cpp
)

#
# Add your test source files to the following list
#
set( TEST_SRC_FILES
     ColorConsoleW_ANSI_test.cpp
     ${HELPERS_DIR}/TestHelpers.cpp
)

# Generate test target
include( ../GenerateTest.cmake )
