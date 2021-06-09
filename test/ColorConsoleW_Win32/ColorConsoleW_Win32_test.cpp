/**
 * @file
 * @brief      Unit tests for the ColorConsoleW class
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/

#include <string>
#include <vector>

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "ColorConsoleW.hpp"

#include "Win32_expect.hpp"

#include <fcntl.h>
#include <io.h>
#include <stdio.h>

#include "TestHelpers.hpp"

/*===========================================================================
 *                      COMMON TEST DEFINES & MACROS
 *===========================================================================*/

/*===========================================================================
 *                          TEST GROUP DEFINITION
 *===========================================================================*/

// To avoid false memleak warnings
#if defined(_MSC_VER) || ( defined(__GNUC__) && ( __GNUC__ < 9 ) )
std::wstringbuf outBuffer;
std::wstringbuf errBuffer;
#endif

TEST_GROUP( ColorConsoleW )
{
    std::wstreambuf *oldOutBuffer;
    std::wstreambuf *oldErrBuffer;

// To avoid false memleak warnings
#if defined(__GNUC__) && !( __GNUC__ < 9 )
    std::wstringbuf outBuffer;
    std::wstringbuf errBuffer;
#endif

    void setup()
    {
        oldOutBuffer = std::wcout.rdbuf();
        oldErrBuffer = std::wcerr.rdbuf();

#if defined(_MSC_VER)
        IGNORE_ALL_LEAKS_IN_TEST();
#endif
    }

    void teardown()
    {
        RestoreRealConsole();

        // To avoid false memleak warnings
        outBuffer.str(L"");
        errBuffer.str(L"");
    }

    void RedirectRealConsole()
    {
        std::wcout.rdbuf( &outBuffer );
        std::wcerr.rdbuf( &errBuffer );
    }

    void RestoreRealConsole()
    {
        std::wcout.rdbuf( oldOutBuffer );
        std::wcerr.rdbuf( oldErrBuffer );
    }

    ColorConsole::ConsoleW* ConstructConsoleW( ColorConsole::ConsoleType consoleType )
    {
        ColorConsole::ConsoleW* newConsole;

        RedirectRealConsole();
        newConsole = new ColorConsole::ConsoleW( consoleType );
        RestoreRealConsole();

        return newConsole;
    }
};

/*===========================================================================
 *                    TEST CASES IMPLEMENTATION
 *===========================================================================*/

TEST( ColorConsoleW, Output )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare
    const int fd = 999773378;
    const HANDLE handle = (HANDLE) 0x1233214;
    const WORD initAttrs = 0xFEAD;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { {0, 0}, {0, 0}, initAttrs };

    expect::UT_fileno( stdout, fd );
    expect::UT_setmode( fd, _O_U16TEXT, 0 );
    expect::UT_GetStdHandle( STD_OUTPUT_HANDLE, handle );
    expect::UT_GetConsoleScreenBufferInfo( handle, &consoleInfo, true );

    // Exercise
    ColorConsole::ConsoleW* out = ConstructConsoleW( ColorConsole::ConsoleType::STD_OUTPUT );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( static_cast<int>( ColorConsole::ConsoleType::STD_OUTPUT ), static_cast<int>( out->get_console_type() ) );
    CHECK_EQUAL( true, out->is_coloring_enabled() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light red
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, FOREGROUND_RED|FOREGROUND_INTENSITY, true );

    // Exercise
    *out << ColorConsole::Color::FG_LIGHT_RED;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write something
    //

    // Prepare

    // Exercise
    *out << "Something";

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "Something", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color dark cyan and background color yellow
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, FOREGROUND_GREEN|FOREGROUND_BLUE|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY, true );

    // Exercise
    *out << (ColorConsole::Color::FG_DARK_CYAN | ColorConsole::Color::BG_YELLOW);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light magenta and background color light green
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_GREEN|BACKGROUND_INTENSITY, true );

    // Exercise
    *out << (ColorConsole::Color::FG_LIGHT_MAGENTA | ColorConsole::Color::BG_LIGHT_GREEN);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color brown and background color dark magenta
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, FOREGROUND_RED|FOREGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE, true );

    // Exercise
    *out << (ColorConsole::Color::FG_BROWN | ColorConsole::Color::BG_DARK_MAGENTA);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Reset color
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, initAttrs, true );

    // Exercise
    *out << ColorConsole::Color::RESET;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color black and background color white
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY, true );

    // Exercise
    *out << (ColorConsole::Color::FG_BLACK | ColorConsole::Color::BG_WHITE);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Reset color combined with color definition
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, initAttrs, true );

    // Exercise
    *out << (ColorConsole::Color::RESET|ColorConsole::Color::FG_LIGHT_GREEN);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color white and background color none
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY, true );

    // Exercise
    *out << (ColorConsole::Color::FG_WHITE | ColorConsole::Color::BG_NONE);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Destruction
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, initAttrs, true );

    // Exercise
    delete out;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
}

TEST( ColorConsoleW, Error )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare
    const int fd = 12967493;
    const HANDLE handle = (HANDLE) 0xFE33214;
    const WORD initAttrs = 0x12AF;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { {0, 0}, {0, 0}, initAttrs };

    expect::UT_fileno( stderr, fd );
    expect::UT_setmode( fd, _O_U16TEXT, 0 );
    expect::UT_GetStdHandle( STD_ERROR_HANDLE, handle );
    expect::UT_GetConsoleScreenBufferInfo( handle, &consoleInfo, true );

    // Exercise
    ColorConsole::ConsoleW* err = ConstructConsoleW( ColorConsole::ConsoleType::STD_ERROR );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );
    CHECK_EQUAL( static_cast<int>( ColorConsole::ConsoleType::STD_ERROR ), static_cast<int>( err->get_console_type() ) );
    CHECK_EQUAL( true, err->is_coloring_enabled() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light red
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, FOREGROUND_RED|FOREGROUND_INTENSITY, true );

    // Exercise
    *err << ColorConsole::Color::FG_LIGHT_RED;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write something
    //

    // Prepare

    // Exercise
    *err << "Something";

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "Something", readFromStringBuf(errBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write end-of-line
    //

    // Prepare

    // Exercise
    *err << ColorConsole::endl;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "\n", readFromStringBuf(errBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Destruction
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, initAttrs, true );

    // Exercise
    delete err;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
}

TEST( ColorConsoleW, Output_ColoringDisabled )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare
    const int fd = 999773378;
    const HANDLE handle = (HANDLE) 0x1233214;
    const WORD initAttrs = 0xFEAD;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { {0, 0}, {0, 0}, initAttrs };

    expect::UT_fileno( stdout, fd );
    expect::UT_setmode( fd, _O_U16TEXT, 0 );
    expect::UT_GetStdHandle( STD_OUTPUT_HANDLE, handle );
    expect::UT_GetConsoleScreenBufferInfo( handle, &consoleInfo, true );

    // Exercise
    ColorConsole::ConsoleW* out = ConstructConsoleW( ColorConsole::ConsoleType::STD_OUTPUT );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( static_cast<int>( ColorConsole::ConsoleType::STD_OUTPUT ), static_cast<int>( out->get_console_type() ) );
    CHECK_EQUAL( true, out->is_coloring_enabled() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Disable coloring
    //

    // Prepare

    // Exercise
    out->disable_coloring();

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( false, out->is_coloring_enabled() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light red
    //

    // Prepare

    // Exercise
    *out << ColorConsole::Color::FG_LIGHT_RED;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write something
    //

    // Prepare

    // Exercise
    *out << "Something";

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "Something", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color dark cyan and background color yellow
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_DARK_CYAN | ColorConsole::Color::BG_YELLOW);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light magenta and background color light green
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_LIGHT_MAGENTA | ColorConsole::Color::BG_LIGHT_GREEN);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color brown and background color dark magenta
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_BROWN | ColorConsole::Color::BG_DARK_MAGENTA);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Reset color
    //

    // Prepare

    // Exercise
    *out << ColorConsole::Color::RESET;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color black and background color white
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_BLACK | ColorConsole::Color::BG_WHITE);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Reset color combined with color definition
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::RESET|ColorConsole::Color::FG_LIGHT_GREEN);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color white and background color none
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_WHITE | ColorConsole::Color::BG_NONE);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Destruction
    //

    // Prepare

    // Exercise
    delete out;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
}

TEST( ColorConsoleW, Error_ColoringDisabled )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare
    const int fd = 12967493;
    const HANDLE handle = (HANDLE) 0xFE33214;
    const WORD initAttrs = 0x12AF;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { {0, 0}, {0, 0}, initAttrs };

    expect::UT_fileno( stderr, fd );
    expect::UT_setmode( fd, _O_U16TEXT, 0 );
    expect::UT_GetStdHandle( STD_ERROR_HANDLE, handle );
    expect::UT_GetConsoleScreenBufferInfo( handle, &consoleInfo, true );

    // Exercise
    ColorConsole::ConsoleW* err = ConstructConsoleW( ColorConsole::ConsoleType::STD_ERROR );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );
    CHECK_EQUAL( static_cast<int>( ColorConsole::ConsoleType::STD_ERROR ), static_cast<int>( err->get_console_type() ) );
    CHECK_EQUAL( true, err->is_coloring_enabled() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Disable coloring
    //

    // Prepare

    // Exercise
    err->disable_coloring();

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );
    CHECK_EQUAL( false, err->is_coloring_enabled() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light red
    //

    // Prepare

    // Exercise
    *err << ColorConsole::Color::FG_LIGHT_RED;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write something
    //

    // Prepare

    // Exercise
    *err << "Something";

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "Something", readFromStringBuf(errBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write end-of-line
    //

    // Prepare

    // Exercise
    *err << ColorConsole::endl;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "\n", readFromStringBuf(errBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Destruction
    //

    // Prepare

    // Exercise
    delete err;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
}
