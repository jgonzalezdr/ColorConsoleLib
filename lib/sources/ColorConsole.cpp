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
ColorConsole &cout = ColorConsole::cout;
ColorConsole &cerr = ColorConsole::cerr;

ColorConsole ColorConsole::cout( ConsoleType::STD_OUTPUT );
ColorConsole ColorConsole::cerr( ConsoleType::STD_ERROR );
#endif

ColorConsole::ColorConsole( ConsoleType consoleType )
: std::ostream( ( consoleType == ConsoleType::STD_ERROR ) ? std::cerr.rdbuf() : std::cout.rdbuf() )
{
#ifdef WIN32
    SetConsoleOutputCP( 65001 );

    m_handle = GetStdHandle( ( consoleType == ConsoleType::STD_ERROR ) ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE );

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo( m_handle, &consoleInfo );

    m_origConsoleAttrs = consoleInfo.wAttributes;
#endif
}

ColorConsole::~ColorConsole() noexcept
{
#ifdef WIN32
    flush();
    SetConsoleTextAttribute( m_handle, m_origConsoleAttrs );
#endif
}

ColorConsole& ColorConsole::operator<<( Color color ) noexcept
{
    set_color( color );
    return *this;
}

void ColorConsole::set_color( Color color ) noexcept
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
