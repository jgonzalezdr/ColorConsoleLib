cmake_minimum_required( VERSION 3.3 )

option( ENABLE_TEST "Enable building tests" ON )
option( COVERAGE_VERBOSE "Coverage analysis is performed in verbose mode" OFF )

if( ENABLE_TEST )

    enable_testing()

    add_custom_target( build_tests )

    include( CommonTestTargets.cmake )

    #
    # Test modules
    #

    if( WIN32 )
        add_subdirectory( ColorConsole_Win32 )
        add_subdirectory( ColorConsoleW_Win32 )
    endif()

endif()