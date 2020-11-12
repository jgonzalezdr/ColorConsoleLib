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

#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>

#include "ColorConsoleW.hpp"

#include <sstream>

/*===========================================================================
 *                      COMMON TEST DEFINES & MACROS
 *===========================================================================*/

/*===========================================================================
 *                          TEST GROUP DEFINITION
 *===========================================================================*/

TEST_GROUP( ColorConsoleW )
{
    wchar_t tmpBuf[100] = L"\0";

    std::wstringbuf outBuffer;

    void setup()
    {
#if defined(_MSC_VER)
        IGNORE_ALL_LEAKS_IN_TEST();
#endif
    }

    void CallInitialize( ColorConsole::ConsoleW* console )
    {
        console->Initialize();
    }

    const wchar_t* readFromStringBuf( std::wstringbuf& buf )
    {
        std::streamsize n = buf.sgetn( tmpBuf, 100 );
        tmpBuf[n] = L'\0';
        return tmpBuf;
    }
};

/*===========================================================================
 *                    TEST CASES IMPLEMENTATION
 *===========================================================================*/

TEST( ColorConsoleW, Custom_Color )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare

    // Exercise
    ColorConsole::ConsoleW* out = new ColorConsole::ConsoleW( &outBuffer, true );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[49;1;31m", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"Something", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[103;36m", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[102;1;35m", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[45;33m", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[0m", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[107;30m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color dark green and background color dark red
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_DARK_GREEN | ColorConsole::Color::BG_DARK_RED);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[41;32m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light cyan and background color dark cyan
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_LIGHT_CYAN | ColorConsole::Color::BG_DARK_CYAN);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[46;1;36m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color dark red and background color light grey
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_DARK_RED | ColorConsole::Color::BG_LIGHT_GREY);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[47;31m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color dark magenta and background color light blue
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_DARK_MAGENTA | ColorConsole::Color::BG_LIGHT_BLUE);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[104;35m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light blue and background color light magenta
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_LIGHT_BLUE | ColorConsole::Color::BG_LIGHT_MAGENTA);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[105;1;34m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color yellow and background color dark green
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_YELLOW | ColorConsole::Color::BG_DARK_GREEN);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[42;1;33m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color dark grey and background color dark blue
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_DARK_GREY | ColorConsole::Color::BG_DARK_BLUE);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[44;1;30m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light grey and background color light red
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_LIGHT_GREY | ColorConsole::Color::BG_LIGHT_RED);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[101;37m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light red and background color light cyan
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_LIGHT_RED | ColorConsole::Color::BG_LIGHT_CYAN);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[106;1;31m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color light green and background color dark grey
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_LIGHT_GREEN | ColorConsole::Color::BG_DARK_GREY);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[100;1;32m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color dark blue and background color brown
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_DARK_BLUE | ColorConsole::Color::BG_BROWN);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[43;34m", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[0m", readFromStringBuf(outBuffer) ) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color white and background color black
    //

    // Prepare

    // Exercise
    *out << (ColorConsole::Color::FG_WHITE | ColorConsole::Color::BG_BLACK);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, wcscmp( L"\033[40;1;37m", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[49;1;37m", readFromStringBuf(outBuffer) ) );

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
    CHECK_EQUAL( 0, wcscmp( L"\033[0m", readFromStringBuf(outBuffer) ) );

    // Cleanup
}

TEST( ColorConsoleW, Custom_NoColor )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare

    // Exercise
    ColorConsole::ConsoleW* out = new ColorConsole::ConsoleW( &outBuffer, false );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

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
    CHECK_EQUAL( 0, wcscmp( L"Something", readFromStringBuf(outBuffer) ) );

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

    // Cleanup
}


TEST( ColorConsoleW, Custom_Init )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare

    // Exercise
    ColorConsole::ConsoleW* out = new ColorConsole::ConsoleW( &outBuffer, false );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Initialization
    //

    // Prepare

    // Exercise
    CallInitialize( out );

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

    // Cleanup
}
