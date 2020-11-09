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

    void CallInitialize( ColorConsole::Console* console )
    {
        RedirectRealConsole();
        console->Initialize();
        RestoreRealConsole();
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

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Initialization
    //

    // Prepare

    // Exercise
    CallInitialize( err );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );

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
    STRCMP_EQUAL( "\033[49;1;31m", readFromStringBuf(errBuffer) );

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

TEST( ColorConsole, Output_DoubleInit )
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

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // First Initialization
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
    // Second Initialization
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
    STRCMP_EQUAL( "\033[0m", readFromStringBuf(outBuffer) );
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
}

TEST( ColorConsole, Error_DoubleInit )
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

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // First Initialization
    //

    // Prepare

    // Exercise
    CallInitialize( err );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Second Initialization
    //

    // Prepare

    // Exercise
    CallInitialize( err );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.in_avail() );

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
