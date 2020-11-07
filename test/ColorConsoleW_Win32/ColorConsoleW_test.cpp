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

#include "Win32_expect.hpp"

#include <fcntl.h>
#include <io.h>
#include <stdio.h>

/*===========================================================================
 *                      COMMON TEST DEFINES & MACROS
 *===========================================================================*/

/*===========================================================================
 *                          TEST GROUP DEFINITION
 *===========================================================================*/

TEST_GROUP( ColorConsoleW )
{
    ColorConsole::ConsoleW* ConstructConsoleW( ColorConsole::ConsoleType consoleType )
    {
        return new ColorConsole::ConsoleW( consoleType );
    }
};

/*===========================================================================
 *                    TEST CASES IMPLEMENTATION
 *===========================================================================*/

TEST( ColorConsoleW, ConstructorOutput )
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

    // Cleanup
}

TEST( ColorConsoleW, ConstructorError )
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

    // Cleanup
}
