/**
 * @file
 * @brief      Implementation of ColorConsoleW class
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#include "ColorConsoleW.hpp"

#include "ColorConsoleHelpers.hpp"

#ifdef WIN32
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#endif

#if defined(WIN32) && defined(UNIT_TEST)

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

#endif // WIN32 && UNIT_TEST

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
    wcout.initialize();
    wcerr.initialize();
#endif
}
// LCOV_EXCL_STOP

ConsoleW::ConsoleW( ConsoleType consoleType )
#ifdef COLORCONSOLE_REQUIRE_INITIALIZATION
: std::wostream( NULL ), m_coloringEnabled( true )
#else
: std::wostream( ( consoleType == ConsoleType::STD_ERROR ) ? std::wcerr.rdbuf() : std::wcout.rdbuf() ), m_coloringEnabled( true )
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

ConsoleW::ConsoleW( std::wstreambuf *sb, bool enableColoring )
: std::wostream( sb ), m_coloringEnabled( enableColoring )
{
    m_consoleType = ConsoleType::CUSTOM;

#ifdef WIN32
    m_handle = INVALID_HANDLE_VALUE;
#endif
}

ConsoleW::~ConsoleW()
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

void ConsoleW::initialize()
{
#ifdef COLORCONSOLE_REQUIRE_INITIALIZATION
    if( rdbuf() == NULL )
    {
        init( ( m_consoleType == ConsoleType::STD_ERROR ) ? std::wcerr.rdbuf() : std::wcout.rdbuf() );
    }
#endif

#ifdef WIN32
    if( ( m_handle == INVALID_HANDLE_VALUE ) && ( m_consoleType <= ConsoleType::STD_ERROR ) )
    {
        _setmode( _fileno( ( m_consoleType == ConsoleType::STD_ERROR ) ? stderr : stdout ), _O_U16TEXT );

        m_handle = GetStdHandle( ( m_consoleType == ConsoleType::STD_ERROR ) ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE );

        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo( m_handle, &consoleInfo );

        m_origConsoleAttrs = consoleInfo.wAttributes;
    }
#else
    if( m_consoleType <= ConsoleType::STD_ERROR )
    {
        std::setlocale(LC_ALL, "");
    }
#endif
}

ConsoleW& ConsoleW::operator<<( Color color )
{
    set_color( color );
    return *this;
}

void ConsoleW::set_color( Color color )
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
        else if( m_consoleType == ConsoleType::CUSTOM )
        {
            setAnsiColor( this, color );
        }
#else
        if( m_consoleType <= ConsoleType::CUSTOM )
        {
            setAnsiColor( this, color );
        }
#endif
    }
}

} // namespace
