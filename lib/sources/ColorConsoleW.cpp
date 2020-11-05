/**
 * @file
 * @brief      Implementation of ColorConsoleW class
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#include "ColorConsoleW.hpp"

#ifdef WIN32
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#endif

#ifdef UNIT_TEST

#define GetStdHandle UT_GetStdHandle
HANDLE UT_GetStdHandle( DWORD nStdHandle );

#define GetConsoleScreenBufferInfo UT_GetConsoleScreenBufferInfo
BOOL UT_GetConsoleScreenBufferInfo( HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo );

#define SetConsoleTextAttribute UT_SetConsoleTextAttribute
BOOL UT_SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes );

#define _setmode UT_setmode
int UT_setmode( int _FileHandle, int _Mode );

#define _fileno UT_fileno
int UT_fileno( FILE* _Stream );

#endif // UNIT_TEST

namespace ColorConsole
{

#ifndef UNIT_TEST
ColorConsoleW &wcout = ColorConsoleW::wcout;
ColorConsoleW &wcerr = ColorConsoleW::wcerr;

ColorConsoleW ColorConsoleW::wcout( ConsoleType::STD_OUTPUT );
ColorConsoleW ColorConsoleW::wcerr( ConsoleType::STD_ERROR );
#endif

ColorConsoleW::ColorConsoleW( ConsoleType consoleType )
: std::wostream( ( consoleType == ConsoleType::STD_ERROR ) ? std::wcerr.rdbuf() : std::wcout.rdbuf() )
{
#ifdef WIN32
    _setmode( _fileno( ( consoleType == ConsoleType::STD_ERROR ) ? stderr : stdout ), _O_U16TEXT );

    m_handle = GetStdHandle( ( consoleType == ConsoleType::STD_ERROR ) ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE );

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo( m_handle, &consoleInfo );

    m_origConsoleAttrs = consoleInfo.wAttributes;
#endif
}

ColorConsoleW::~ColorConsoleW() noexcept
{
#ifdef WIN32
    flush();
    SetConsoleTextAttribute( m_handle, m_origConsoleAttrs );
#endif
}

ColorConsoleW& ColorConsoleW::operator<<( Color color ) noexcept
{
    set_color( color );
    return *this;
}

void ColorConsoleW::set_color( Color color ) noexcept
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
