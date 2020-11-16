cmake_minimum_required( VERSION 3.13 )

project( ColorConsole VERSION 1.0.0 )

if( NOT CMAKE_PROJECT_NAME MATCHES "${PROJECT_NAME}.*" )

    # Seems like we are being imported into another project

    if( TARGET_NAMESPACE )
        set( TARGET_NAMESPACE "${TARGET_NAMESPACE}." )
    endif()

    add_custom_target( ${TARGET_NAMESPACE}build )

    unset( CMAKE_MODULE_PATH )

endif()

option( BUILD_STATIC_LIB "Build static library" ON )
option( BUILD_SHARED_LIB "Build shared library" ON )
option( REQUIRE_INITIALIZATION "Make initialization mandatory" OFF )
option( FORCE_ANSI_ESCAPE_CODES "Force using ANSI escape codes in Windows" OFF )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/Modules/" )

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
     sources/ColorConsoleHelpers.hpp
)

#
# Project information
#

if( NOT PROJECT_VERSION_BUILD )
    set( PROJECT_VERSION_BUILD ${PROJECT_VERSION_TWEAK} )
endif()

include( GenerateProductVersion )

if( WIN32 )
    set( PROJECT_NAME_SUFFIX "-${CMAKE_CXX_COMPILER_ID}" )
endif()

generate_product_version(
    PRODUCT_VERSION_FILES
    NAME ${PROJECT_NAME}${PROJECT_NAME_SUFFIX}
    FILE_DESCRIPTION "Color Console Library"
    VERSION_MAJOR ${PROJECT_VERSION_MAJOR}
    VERSION_MINOR ${PROJECT_VERSION_MINOR}
    VERSION_PATCH ${PROJECT_VERSION_PATCH}
    VERSION_BUILD ${PROJECT_VERSION_BUILD}
    VERSION_SUFFIX "${PROJECT_VERSION_SUFFIX}"
    COMPANY_NAME "www.gdr-sistemas.com"
    COMPANY_COPYRIGHT "(C) Copyright 2018-2020 Jesus Gonzalez"
    PRIVATE_BUILD "${PRIVATE_BUILD_INFO}"
    SPECIAL_BUILD "${SPECIAL_BUILD_INFO}"
    PRERELEASE "${PRERELEASE}"
    PATCHED "${PATCHED_RELEASE}"
    HOMEPAGE "https://github.com/jgonzalezdr/ColorConsoleLib"
    MAINTAINER "Jesús González <jgonzalez@gdr-sistemas.com>"
    EXPORT_TO_PARENT_SCOPE
)

#
# Common library definitions
#

if( MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc" )
endif()

if ( BUILD_SHARED_LIB )
    #
    # Shared library definition
    #

    add_library( ${PROJECT_NAME} SHARED ${SRC_LIST} ${INC_LIST} ${PRODUCT_VERSION_FILES} )
    target_compile_definitions( ${PROJECT_NAME} PUBLIC "COLORCONSOLE_SHARED_LIB" )

    target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

    add_dependencies( ${TARGET_NAMESPACE}build ${PROJECT_NAME} )

    if( REQUIRE_INITIALIZATION OR WIN32 )
        target_compile_definitions( ${PROJECT_NAME} PRIVATE "COLORCONSOLE_REQUIRE_INITIALIZATION" )
    endif()

    if( FORCE_ANSI_ESCAPE_CODES )
        target_compile_definitions( ${PROJECT_NAME} PRIVATE "COLORCONSOLE_FORCE_ANSI_ESCAPE_CODES" )
    endif()

    #
    # Shared library properties
    #

    set_target_properties( ${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "_dbg" )
    set_target_properties( ${PROJECT_NAME} PROPERTIES COVERAGE_POSTFIX "_cov" )
    set_target_properties( ${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} )
endif()

if ( BUILD_STATIC_LIB )
    #
    # Static library definition
    #

    add_library( ${PROJECT_NAME}_static STATIC ${SRC_LIST} ${INC_LIST} ${PRODUCT_VERSION_FILES} )

    target_include_directories( ${PROJECT_NAME}_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

    add_dependencies( ${TARGET_NAMESPACE}build ${PROJECT_NAME}_static )

    if( REQUIRE_INITIALIZATION )
        target_compile_definitions( ${PROJECT_NAME}_static PRIVATE "COLORCONSOLE_REQUIRE_INITIALIZATION" )
    endif()

    if( FORCE_ANSI_ESCAPE_CODES )
        target_compile_definitions( ${PROJECT_NAME}_static PRIVATE "COLORCONSOLE_FORCE_ANSI_ESCAPE_CODES" )
    endif()

    #
    # Static library properties
    #

    set_target_properties( ${PROJECT_NAME}_static PROPERTIES DEBUG_POSTFIX "_dbg" )
    set_target_properties( ${PROJECT_NAME}_static PROPERTIES COVERAGE_POSTFIX "_cov" )
    set_target_properties( ${PROJECT_NAME}_static PROPERTIES VERSION ${PROJECT_VERSION} )
endif()

#
# Install
#

include( InstallersSetup.cmake )

if ( BUILD_SHARED_LIB )
    if( WIN32 )
        install( TARGETS ${PROJECT_NAME} RUNTIME DESTINATION lib )
        install( TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib )
    else()
        install( TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib )
    endif()
endif()
if ( BUILD_STATIC_LIB )
    install( TARGETS ${PROJECT_NAME}_static ARCHIVE DESTINATION lib )
endif()

install( DIRECTORY include/ DESTINATION include )
