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

#include "TestHelpers.hpp"

/*===========================================================================
 *                      COMMON TEST DEFINES & MACROS
 *===========================================================================*/

/*===========================================================================
 *                          TEST GROUP DEFINITION
 *===========================================================================*/

TEST_GROUP( ColorConsole )
{
    std::stringbuf outBuffer;

    void CallInitialize( ColorConsole::Console* console )
    {
        console->Initialize();
    }
};

/*===========================================================================
 *                    TEST CASES IMPLEMENTATION
 *===========================================================================*/

TEST( ColorConsole, Custom_Color )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare

    // Exercise
    ColorConsole::Console* out = new ColorConsole::Console( &outBuffer, true );

    // Verify
    mock().checkExpectations();
    CHECK_EQUAL( 0, outBuffer.in_avail() );
    CHECK_EQUAL( static_cast<int>( ColorConsole::ConsoleType::CUSTOM_COLOR ), static_cast<int>( out->get_console_type() ) );

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
    STRCMP_EQUAL( "\033[49;1;31m", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write string
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
    // Write string
    //

    // Prepare

    // Exercise
    *out << (unsigned char*) "Something unsigned";

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "Something unsigned", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write string
    //

    // Prepare

    // Exercise
    *out << (signed char*) "Something signed";

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "Something signed", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write int
    //

    // Prepare

    // Exercise
    *out << (int) -87736663;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "-87736663", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write unsigned int
    //

    // Prepare

    // Exercise
    *out << (unsigned int) 234905874u;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "234905874", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write short
    //

    // Prepare

    // Exercise
    *out << (short) -8763;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "-8763", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write unsigned short
    //

    // Prepare

    // Exercise
    *out << (unsigned short) 23874u;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "23874", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write long
    //

    // Prepare

    // Exercise
    *out << (long) -997646634l;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "-997646634", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write unsigned long
    //

    // Prepare

    // Exercise
    *out << (unsigned long) 779938934ul;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "779938934", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write long long
    //

    // Prepare

    // Exercise
    *out << (long long) -9976777677946634ll;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "-9976777677946634", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write unsigned long long
    //

    // Prepare

    // Exercise
    *out << (unsigned long long) 779786565449398934ull;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "779786565449398934", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write char
    //

    // Prepare

    // Exercise
    *out << (char) 'A';

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "A", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write unsigned char
    //

    // Prepare

    // Exercise
    *out << (unsigned char) '0';

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "0", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write signed char
    //

    // Prepare

    // Exercise
    *out << (signed char) '0';

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "0", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write bool
    //

    // Prepare

    // Exercise
    *out << true << "-" << false;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "1-0", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write float
    //

    // Prepare

    // Exercise
    *out << (float) -163.873f;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "-163.873", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write double
    //

    // Prepare

    // Exercise
    *out << std::fixed << (double) 877344.177654;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "877344.177654", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write long double
    //

    // Prepare

    // Exercise
    *out << (long double) 238489823163.87649918l;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "238489823163.876499", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
    mock().clear();

    //////////////////////////////////////////////////////////////////////////
    // Write pointer
    //

    // Prepare

    // Exercise
    *out << (void*) 0x01987674;

    // Verify
    mock().checkExpectations();
    STRCMP_EQUAL( "0x1987674", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[103;36m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[102;1;35m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[45;33m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[0m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[107;30m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[41;32m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[46;1;36m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[47;31m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[104;35m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[105;1;34m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[42;1;33m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[44;1;30m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[101;37m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[106;1;31m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[100;1;32m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[43;34m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[0m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[40;1;37m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[49;1;37m", readFromStringBuf(outBuffer).c_str() );

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
    STRCMP_EQUAL( "\033[0m", readFromStringBuf(outBuffer).c_str() );

    // Cleanup
}

TEST( ColorConsole, Custom_NoColor )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare

    // Exercise
    ColorConsole::Console* out = new ColorConsole::Console( &outBuffer, false );
    CHECK_EQUAL( static_cast<int>( ColorConsole::ConsoleType::CUSTOM_NOCOLOR ), static_cast<int>( out->get_console_type() ) );

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
    STRCMP_EQUAL( "Something", readFromStringBuf(outBuffer).c_str() );

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

TEST( ColorConsole, Custom_Init )
{
    //////////////////////////////////////////////////////////////////////////
    // Creation
    //

    // Prepare

    // Exercise
    ColorConsole::Console* out = new ColorConsole::Console( &outBuffer, false );

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
