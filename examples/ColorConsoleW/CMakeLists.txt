cmake_minimum_required( VERSION 3.13 )

project( Example.ColorConsoleW VERSION 1.0.0 )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/" )

if( MSVC )
    include( VisualStudioHelper )

    generate_groups( ${CMAKE_CURRENT_SOURCE_DIR} sources )
    generate_groups( ${CMAKE_CURRENT_SOURCE_DIR} include )
endif( MSVC )

#
# Source files
#

set( SRC_LIST
     sources/Example.ColorConsoleW.cpp
)

#
# Project information
#

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

if( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" )
endif()

add_executable( ${PROJECT_NAME} ${SRC_LIST} )

if( WIN32 AND NOT MSVC )
    target_link_options( ${PROJECT_NAME} PRIVATE "-municode" )
endif()

add_dependencies( build ${PROJECT_NAME} )

#
# Executable properties
#

set_target_properties( ${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_dbg" )
set_target_properties( ${PROJECT_NAME} PROPERTIES COVERAGE_POSTFIX "_cov" )
set_target_properties( ${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} )

#
# External libraries
#

target_link_libraries( ${PROJECT_NAME} ColorConsoleLib )

#
# Install
#

install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION examples )