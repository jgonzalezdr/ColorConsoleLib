cmake_minimum_required( VERSION 3.3 )

project( Test.ColorConsoleW.Custom )

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
     ColorConsoleW_Custom_test.cpp
     ${HELPERS_DIR}/TestHelpers.cpp
)

if( WIN32 )
     set( TEST_SRC_FILES ${TEST_SRC_FILES}
          ${MOCKS_DIR}/Win32_mock.cpp
     )
endif()


# Generate test target
include( ../GenerateTest.cmake )
