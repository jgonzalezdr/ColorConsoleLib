/**
 * @file
 * @brief      Implementation of ColorConsole class
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#include "ColorConsole.hpp"

#ifdef UNIT_TEST

#define GetStdHandle UT_GetStdHandle
HANDLE UT_GetStdHandle( DWORD nStdHandle );

#define GetConsoleScreenBufferInfo UT_GetConsoleScreenBufferInfo
BOOL UT_GetConsoleScreenBufferInfo( HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo );

#define SetConsoleTextAttribute UT_SetConsoleTextAttribute
BOOL UT_SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes );

#define SetConsoleOutputCP UT_SetConsoleOutputCP
BOOL UT_SetConsoleOutputCP( UINT wCodePageID );

#endif // UNIT_TEST

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
    cout.Initialize();
    cerr.Initialize();
#endif
}
// LCOV_EXCL_STOP

Console::Console( ConsoleType consoleType )
#ifdef COLORCONSOLE_REQUIRE_INITIALIZATION
: std::ostream( NULL )
#else
: std::ostream( ( consoleType == ConsoleType::STD_ERROR ) ? std::cerr.rdbuf() : std::cout.rdbuf() )
#endif
{
    m_consoleType = consoleType;

#ifdef WIN32
    m_handle = INVALID_HANDLE_VALUE;
#endif

#ifndef COLORCONSOLE_REQUIRE_INITIALIZATION
    Initialize();
#endif
}

Console::~Console()
{
#ifdef WIN32
    flush();
    SetConsoleTextAttribute( m_handle, m_origConsoleAttrs );
#endif
}

void Console::Initialize()
{
#ifdef COLORCONSOLE_REQUIRE_INITIALIZATION
    if( rdbuf() == NULL )
    {
        init( ( m_consoleType == ConsoleType::STD_ERROR ) ? std::cerr.rdbuf() : std::cout.rdbuf() );
    }
#endif

#ifdef WIN32
    if( m_handle == INVALID_HANDLE_VALUE )
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

Console& Console::operator<<( Color color ) noexcept
{
    set_color( color );
    return *this;
}

void Console::set_color( Color color ) noexcept
{
#ifdef WIN32
    flush();

    if( color >= Color::RESET )
    {
        SetConsoleTextAttribute( m_handle, m_origConsoleAttrs );
    }
    else
    {
        SetConsoleTextAttribute( m_handle, static_cast<WORD>(color) );
    }
#endif
}

} // namespace
