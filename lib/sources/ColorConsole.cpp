/**
 * @file
 * @brief      Implementation of ColorConsole class
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#include "ColorConsole.hpp"

#include "ColorConsoleHelpers.hpp"

#if defined(WIN32) && defined(UNIT_TEST)

#define GetStdHandle UT_GetStdHandle
HANDLE UT_GetStdHandle( DWORD nStdHandle );

#define GetConsoleScreenBufferInfo UT_GetConsoleScreenBufferInfo
BOOL UT_GetConsoleScreenBufferInfo( HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo );

#define SetConsoleTextAttribute UT_SetConsoleTextAttribute
BOOL UT_SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes );

#define SetConsoleOutputCP UT_SetConsoleOutputCP
BOOL UT_SetConsoleOutputCP( UINT wCodePageID );

#endif // WIN32 && UNIT_TEST

namespace ColorConsole
{

#ifndef UNIT_TEST
Console &cout = Console::cout;
Console &cerr = Console::cerr;

Console Console::cout( ConsoleType::STD_OUTPUT );
Console Console::cerr( ConsoleType::STD_ERROR );
#endif

// LCOV_EXCL_START
void Console::Init()
{
#if defined(COLORCONSOLE_REQUIRE_INITIALIZATION) && !defined(UNIT_TEST)
    cout.initialize();
    cerr.initialize();
#endif
}
// LCOV_EXCL_STOP

Console::Console( ConsoleType consoleType )
#ifdef COLORCONSOLE_REQUIRE_INITIALIZATION
: std::ostream( NULL ), m_coloringEnabled( true )
#else
: std::ostream( ( consoleType == ConsoleType::STD_ERROR ) ? std::cerr.rdbuf() : std::cout.rdbuf() ), m_coloringEnabled( true )
#endif
{
    m_consoleType = consoleType;

#ifdef WIN32
    m_handle = INVALID_HANDLE_VALUE;
#endif

#ifndef COLORCONSOLE_REQUIRE_INITIALIZATION
    initialize();
#endif
}

Console::Console( std::streambuf *sb, bool enableColoring )
: std::ostream( sb ), m_coloringEnabled( enableColoring )
{
    m_consoleType = ConsoleType::CUSTOM;

#ifdef WIN32
    m_handle = INVALID_HANDLE_VALUE;
#endif
}

Console::~Console()
{
#if defined(WIN32) && !defined(COLORCONSOLE_FORCE_ANSI_ESCAPE_CODES)
    if( m_consoleType <= ConsoleType::STD_ERROR )
    {
        flush();

        if( ( m_handle != INVALID_HANDLE_VALUE ) && m_coloringEnabled )
        {
            SetConsoleTextAttribute( m_handle, m_origConsoleAttrs );
        }
    }
    else if( m_coloringEnabled )
    {
        setAnsiColor( this, Color::RESET );
    }
#else
    if( m_coloringEnabled )
    {
        setAnsiColor( this, Color::RESET );
    }
#endif
}

void Console::initialize()
{
#ifdef COLORCONSOLE_REQUIRE_INITIALIZATION
    if( rdbuf() == NULL )
    {
        init( ( m_consoleType == ConsoleType::STD_ERROR ) ? std::cerr.rdbuf() : std::cout.rdbuf() );
    }
#endif

#ifdef WIN32
    if( ( m_handle == INVALID_HANDLE_VALUE ) && ( m_consoleType <= ConsoleType::STD_ERROR ) )
    {
        if( m_consoleType == ConsoleType::STD_OUTPUT )
        {
            SetConsoleOutputCP( 65001 );
        }

        m_handle = GetStdHandle( ( m_consoleType == ConsoleType::STD_ERROR ) ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE );

        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo( m_handle, &consoleInfo );

        m_origConsoleAttrs = consoleInfo.wAttributes;
    }
#endif
}

Console& Console::operator<<( Color color )
{
    set_color( color );
    return *this;
}

void Console::set_color( Color color )
{
    if( m_coloringEnabled )
    {
#if defined(WIN32) && !defined(COLORCONSOLE_FORCE_ANSI_ESCAPE_CODES)
        if( m_consoleType <= ConsoleType::STD_ERROR )
        {
            flush();

            if( color >= Color::RESET )
            {
                SetConsoleTextAttribute( m_handle, m_origConsoleAttrs );
            }
            else
            {
                SetConsoleTextAttribute( m_handle, static_cast<WORD>(color) );
            }
        }
        else
        {
            setAnsiColor( this, color );
        }
#else
        setAnsiColor( this, color );
#endif
    }
}

} // namespace
