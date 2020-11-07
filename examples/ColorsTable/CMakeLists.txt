cmake_minimum_required( VERSION 3.3 )

project( Example.ColorsTable VERSION 1.0.0 )

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
     sources/Example.ColorsTable.cpp
)

#
# Project information
#

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

if( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" )
endif()

add_executable( ${PROJECT_NAME} ${SRC_LIST} )

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

if( BUILD_SHARED_LIBS )
    add_custom_target( ${PROJECT_NAME}_CopyLibs ALL
                       DEPENDS ColorConsoleLib
                       COMMAND cmake -E copy "$<TARGET_FILE:ColorConsoleLib>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>" )
    add_dependencies( build ${PROJECT_NAME}_CopyLibs ) 
endif()

#
# Install
#

install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION examples )
