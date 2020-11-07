cmake_minimum_required( VERSION 3.13 )

project( ColorConsoleLib VERSION 1.0.0 )

option( BUILD_SHARED_LIBS "Build shared library" ON )
option( REQUIRE_INITIALIZATION "Make initialization mandatory" ON )

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
     sources/ColorConsole.cpp
     sources/ColorConsoleW.cpp
)

#
# Header files
#

set( INC_LIST
     include/ColorConsoleCommon.hpp
     include/ColorConsole.hpp
     include/ColorConsoleW.hpp
)

#
# Project information
#

if( NOT PROJECT_VERSION_BUILD )
    set( PROJECT_VERSION_BUILD ${PROJECT_VERSION_TWEAK} )
endif()

include( GenerateProductVersion )

generate_product_version(
    PRODUCT_VERSION_FILES
    NAME ${PROJECT_NAME}
    FILE_DESCRIPTION "Example app description"
    VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
    VERSION_MINOR ${PROJECT_VERSION_MINOR}
    VERSION_PATCH ${PROJECT_VERSION_PATCH}
    VERSION_BUILD ${PROJECT_VERSION_BUILD}
    VERSION_SUFFIX "${PROJECT_VERSION_SUFFIX}"
    COMPANY_NAME "www.example.com"
    COMPANY_COPYRIGHT "(C) Copyright YEAR Whatever"
    PRIVATE_BUILD "${PRIVATE_BUILD_INFO}"
    SPECIAL_BUILD "${SPECIAL_BUILD_INFO}"
    PRERELEASE "${PRERELEASE}"
    PATCHED "${PATCHED_RELEASE}"
    HOMEPAGE "http://example.com/yourproduct/"
    MAINTAINER "Your Name <yourname@example.com>"
    EXPORT_TO_PARENT_SCOPE
)

#
# Library definition
#

if( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" )
endif()

if ( BUILD_SHARED_LIBS )
    add_library( ${PROJECT_NAME} SHARED ${SRC_LIST} ${INC_LIST} ${PRODUCT_VERSION_FILES} )
    target_compile_definitions( ${PROJECT_NAME} PUBLIC "COLORCONSOLE_SHARED_LIB" )
else()
    add_library( ${PROJECT_NAME} STATIC ${SRC_LIST} ${INC_LIST} ${PRODUCT_VERSION_FILES} )
endif()

if( REQUIRE_INITIALIZATION OR (WIN32 AND BUILD_SHARED_LIBS) )
    target_compile_definitions( ${PROJECT_NAME} PRIVATE "COLORCONSOLE_REQUIRE_INITIALIZATION" )
endif()


target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

add_dependencies( build ${PROJECT_NAME} )

#
# Library properties
#

set_target_properties( ${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_dbg" )
set_target_properties( ${PROJECT_NAME} PROPERTIES COVERAGE_POSTFIX "_cov" )
set_target_properties( ${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} )

#
# Install
#

include( InstallersSetup.cmake )

install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION lib )
install( DIRECTORY include/ DESTINATION include ) 
