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
ConsoleW &wcout = ConsoleW::wcout;
ConsoleW &wcerr = ConsoleW::wcerr;

ConsoleW ConsoleW::wcout( ConsoleType::STD_OUTPUT );
ConsoleW ConsoleW::wcerr( ConsoleType::STD_ERROR );
#endif

// LCOV_EXCL_START
void ConsoleW::Init()
{
#if defined(COLORCONSOLE_REQUIRE_INITIALIZATION) && !defined(UNIT_TEST)
    wcout.Initialize();
    wcerr.Initialize();
#endif
}
// LCOV_EXCL_STOP

ConsoleW::ConsoleW( ConsoleType consoleType )
#ifdef COLORCONSOLE_REQUIRE_INITIALIZATION
: std::wostream( NULL )
#else
: std::wostream( ( consoleType == ConsoleType::STD_ERROR ) ? std::wcerr.rdbuf() : std::wcout.rdbuf() )
#endif
{
    m_handle = INVALID_HANDLE_VALUE;
    m_consoleType = consoleType;

#ifndef COLORCONSOLE_REQUIRE_INITIALIZATION
    Initialize();
#endif
}

ConsoleW::~ConsoleW() noexcept
{
#ifdef WIN32
    flush();
    SetConsoleTextAttribute( m_handle, m_origConsoleAttrs );
#endif
}

void ConsoleW::Initialize()
{
#ifdef COLORCONSOLE_REQUIRE_INITIALIZATION
    if( rdbuf() == NULL )
    {
        init( ( m_consoleType == ConsoleType::STD_ERROR ) ? std::wcerr.rdbuf() : std::wcout.rdbuf() );
    }
#endif

#ifdef WIN32
    if( m_handle == INVALID_HANDLE_VALUE )
    {
        _setmode( _fileno( ( m_consoleType == ConsoleType::STD_ERROR ) ? stderr : stdout ), _O_U16TEXT );

        m_handle = GetStdHandle( ( m_consoleType == ConsoleType::STD_ERROR ) ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE );

        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo( m_handle, &consoleInfo );

        m_origConsoleAttrs = consoleInfo.wAttributes;
    }
#endif
}

ConsoleW& ConsoleW::operator<<( Color color ) noexcept
{
    set_color( color );
    return *this;
}

void ConsoleW::set_color( Color color ) noexcept
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
