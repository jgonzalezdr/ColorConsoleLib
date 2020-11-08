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

#include "Win32_expect.hpp"

#include <sstream>

/*===========================================================================
 *                      COMMON TEST DEFINES & MACROS
 *===========================================================================*/

/*===========================================================================
 *                          TEST GROUP DEFINITION
 *===========================================================================*/

TEST_GROUP( ColorConsole )
{
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
    CHECK_EQUAL( 0, outBuffer.str().length() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Initialization
    //

    // Prepare
    const HANDLE handle = (HANDLE) 0x1233214;
    const WORD initAttrs = 0xFEAD;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { {0, 0}, {0, 0}, initAttrs };

    expect::UT_SetConsoleOutputCP( 65001, true );
    expect::UT_GetStdHandle( STD_OUTPUT_HANDLE, handle );
    expect::UT_GetConsoleScreenBufferInfo( handle, &consoleInfo, true );

    // Exercise
    CallInitialize( out );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    STRCMP_EQUAL( "Something", outBuffer.str().c_str() );

    // Cleanup
    mock().clear();
    outBuffer.str("");

    //////////////////////////////////////////////////////////////////////////
    // Set foreground color dark cyan and background color yellow
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, FOREGROUND_GREEN|FOREGROUND_BLUE|BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY, true );

    // Exercise
    *out << (ColorConsole::Color::FG_DARK_CYAN | ColorConsole::Color::BG_YELLOW);

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );
    CHECK_EQUAL( 0, errBuffer.str().length() );

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
    CHECK_EQUAL( 0, errBuffer.str().length() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Initialization
    //

    // Prepare
    const HANDLE handle = (HANDLE) 0xFE33214;
    const WORD initAttrs = 0x12AF;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { {0, 0}, {0, 0}, initAttrs };

    expect::UT_GetStdHandle( STD_ERROR_HANDLE, handle );
    expect::UT_GetConsoleScreenBufferInfo( handle, &consoleInfo, true );

    // Exercise
    CallInitialize( err );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.str().length() );

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
    CHECK_EQUAL( 0, errBuffer.str().length() );

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
    STRCMP_EQUAL( "Something", errBuffer.str().c_str() );

    // Cleanup
    mock().clear();
    errBuffer.str("");

    //////////////////////////////////////////////////////////////////////////
    // Destruction
    //

    // Prepare
    expect::UT_SetConsoleTextAttribute( handle, initAttrs, true );

    // Exercise
    delete err;

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.str().length() );
    CHECK_EQUAL( 0, errBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // First Initialization
    //

    // Prepare
    const HANDLE handle = (HANDLE) 0x1233214;
    const WORD initAttrs = 0xFEAD;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { {0, 0}, {0, 0}, initAttrs };

    expect::UT_SetConsoleOutputCP( 65001, true );
    expect::UT_GetStdHandle( STD_OUTPUT_HANDLE, handle );
    expect::UT_GetConsoleScreenBufferInfo( handle, &consoleInfo, true );

    // Exercise
    CallInitialize( out );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );
    CHECK_EQUAL( 0, errBuffer.str().length() );

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
    CHECK_EQUAL( 0, errBuffer.str().length() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // First Initialization
    //

    // Prepare
    const HANDLE handle = (HANDLE) 0xFE33214;
    const WORD initAttrs = 0x12AF;
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo = { {0, 0}, {0, 0}, initAttrs };

    expect::UT_GetStdHandle( STD_ERROR_HANDLE, handle );
    expect::UT_GetConsoleScreenBufferInfo( handle, &consoleInfo, true );

    // Exercise
    CallInitialize( err );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, errBuffer.str().length() );

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
    CHECK_EQUAL( 0, errBuffer.str().length() );

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
    CHECK_EQUAL( 0, outBuffer.str().length() );
    CHECK_EQUAL( 0, errBuffer.str().length() );

    // Cleanup
}
