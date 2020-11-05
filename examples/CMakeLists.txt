option( BUILD_EXAMPLES "Enable building tests" ON )

if( BUILD_EXAMPLES )

    add_subdirectory( ColorConsole )
    add_subdirectory( ColorConsoleW )
    add_subdirectory( ColorsTable )

endif()