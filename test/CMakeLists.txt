cmake_minimum_required( VERSION 3.3 )

if( BUILD_TESTING )

    include( CommonTestTargets.cmake )

    set( PROD_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../lib )
    set( PROD_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/../lib )
    set( MOCKS_DIR ${CMAKE_CURRENT_LIST_DIR}/Mocks )
    set( HELPERS_DIR ${CMAKE_CURRENT_LIST_DIR}/TestHelpers )

    #
    # Test modules
    #

    if( WIN32 )
        add_subdirectory( ColorConsole_Win32 )
        add_subdirectory( ColorConsole_Init_Win32 )
        add_subdirectory( ColorConsoleW_Win32 )
        add_subdirectory( ColorConsoleW_Init_Win32 )
    else()
        add_subdirectory( ColorConsole_ANSI )
        add_subdirectory( ColorConsole_Init_ANSI )
        add_subdirectory( ColorConsoleW_ANSI )
        add_subdirectory( ColorConsoleW_Init_ANSI )
    endif()

    add_subdirectory( ColorConsole_Custom )
    add_subdirectory( ColorConsoleW_Custom )

endif()
