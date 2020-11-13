/**
 * @file
 * @brief      Unit tests for the ColorConsole class
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

#include "ColorConsole.hpp"

#include <sstream>

/*===========================================================================
 *                      COMMON TEST DEFINES & MACROS
 *===========================================================================*/

/*===========================================================================
 *                          TEST GROUP DEFINITION
 *===========================================================================*/

TEST_GROUP( ColorConsole )
{
    char tmpBuf[100] = "\0";

    std::streambuf *oldOutBuffer;
    std::streambuf *oldErrBuffer;

    std::stringbuf outBuffer;
    std::stringbuf errBuffer;

    void setup()
    {
        oldOutBuffer = std::cout.rdbuf();
        oldErrBuffer = std::cerr.rdbuf();
    }

    void teardown()
    {
        RestoreRealConsole();
    }

    void RedirectRealConsole()
    {
        std::cout.rdbuf( &outBuffer );
        std::cerr.rdbuf( &errBuffer );
    }

    void RestoreRealConsole()
    {
        std::cout.rdbuf( oldOutBuffer );
        std::cerr.rdbuf( oldErrBuffer );
    }

    ColorConsole::Console* ConstructConsole( ColorConsole::ConsoleType consoleType )
    {
        ColorConsole::Console* newConsole;

        RedirectRealConsole();
        newConsole = new ColorConsole::Console( consoleType );
        RestoreRealConsole();

        return newConsole;
    }

    const char* readFromStringBuf( std::stringbuf& buf )
    {
        std::streamsize n = buf.sgetn( tmpBuf, 100 );
        tmpBuf[n] = '\0';
        return tmpBuf;
    }
};

/*===========================================================================
 *                    TEST CASES IMPLEMENTATION
 *===========================================================================*/

TEST( ColorConsole, Output )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare

    // Exercise
    ColorConsole::Console* out = ConstructConsole( ColorConsole::ConsoleType::STD_OUTPUT );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( static_cast<int>( ColorConsole::ConsoleType::STD_OUTPUT ), static_cast<int>( out->get_console_type() ) );

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
    STRCMP_EQUAL( "\033[49;1;31m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "Something", readFromStringBuf(outBuffer) );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write end-of-line
    //

    // Prepare

    // Exercise
    *out << ColorConsole::endl;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "\033[K\n", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[103;36m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[102;1;35m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[45;33m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[0m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[107;30m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[41;32m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[46;1;36m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[47;31m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[104;35m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[105;1;34m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[42;1;33m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[44;1;30m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[101;37m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[106;1;31m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[100;1;32m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[43;34m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[0m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[40;1;37m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[49;1;37m", readFromStringBuf(outBuffer) );

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
    STRCMP_EQUAL( "\033[0m", readFromStringBuf(outBuffer) );
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
}

TEST( ColorConsole, Error )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare

    // Exercise
    ColorConsole::Console* err = ConstructConsole( ColorConsole::ConsoleType::STD_ERROR );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );
    CHECK_EQUAL( static_cast<int>( ColorConsole::ConsoleType::STD_ERROR ), static_cast<int>( err->get_console_type() ) );

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
    STRCMP_EQUAL( "\033[49;1;31m", readFromStringBuf(errBuffer)  );

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
    STRCMP_EQUAL( "Something", readFromStringBuf(errBuffer) );

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
    STRCMP_EQUAL( "\033[0m", readFromStringBuf(errBuffer) );

    // Cleanup
}
