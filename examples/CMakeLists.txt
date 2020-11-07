option( BUILD_EXAMPLES "Enable building tests" ON )

if( BUILD_EXAMPLES AND (BUILD_SHARED_LIB OR BUILD_STATIC_LIB) )

    add_subdirectory( ColorConsole )
    add_subdirectory( ColorConsoleW )
    add_subdirectory( ColorsTable )

endif()