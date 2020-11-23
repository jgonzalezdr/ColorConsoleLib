/**
 * @file
 * @brief      Header of ColorConsoleW class
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#ifndef COLORCONSOLEW_HPP_
#define COLORCONSOLEW_HPP_

#include "ColorConsoleCommon.hpp"

#ifdef WIN32
#include "windows.h"
#endif

#ifdef UNIT_TEST
struct TEST_GROUP_CppUTestGroupColorConsoleW;
#endif

namespace ColorConsole
{

/**
 * Output stream representing a console oriented to wide characters (of type wchar_t)
 * with text colorization capabilities.
 */
class COLORCONSOLE_API ConsoleW : public std::wostream
{
public:
    /**
     * Constructor for custom streams.
     *
     * Colorization of custom streams (if enabled) will be performed using ANSI color escape codes.
     *
     * Custom streams are mostly intended for testing software that writes on color consoles.
     *
     * param sb [in] Stream buffer where the strem will write to
     * param color [in] Indicates if colorization is enabled
     *
     * @param[inout] consoleType Console to colorize
     */
    ConsoleW( std::wstreambuf *sb, bool color = true );

    /**
     * Destructor.
     */
    ~ConsoleW();

    /**
     * Sets (or resets) the console color.
     *
     * @param[in] color Color to be set, or RESET to reset to default value
     */
    void set_color( Color color );

    /**
     * Sets (or resets) the console color.
     *
     * @param[in] color Color to be set, or RESET to reset to default value
     * @return The ColorConsoleW object (*this)
     */
    ConsoleW& operator<<( Color color );

    /**
     * Inserter for ostream manipulators.
     *
     * @param[in] pf Manipulator
     * @return The ColorConsoleW object (*this)
     */
    ConsoleW& operator<<( std::wostream& (*pf)(std::wostream&) )
    {
        (*pf)(*this);
        return *this;
    }

    /**
     * Inserter for ios manipulators.
     *
     * @param[in] pf Manipulator
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( std::wios& (*pf)(std::wios&) )
    {
        (*pf)(*this);
        return *this;
    }

    /**
     * Inserter for ios_base manipulators.
     *
     * @param[in] pf Manipulator
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( std::ios_base& (*pf)(std::ios_base&) )
    {
        (*pf)(*this);
        return *this;
    }

    /**
     * Inserter for longs.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( long n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for unsigned longs.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( unsigned long n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for bools.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( bool n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for shorts.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( short n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for unsigned shorts.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( unsigned short n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for ints.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( int n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for unsigned ints.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( unsigned int n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for long longs.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( long long n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for unsigned long longs.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( unsigned long long n )
    {
        *(static_cast<std::wostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for doubles.
     *
     * @param[in] f Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( double f )
    {
        *(static_cast<std::wostream*>(this)) << f;
        return *this;
    }

    /**
     * Inserter for floats.
     *
     * @param[in] f Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( float f )
    {
        *(static_cast<std::wostream*>(this)) << f;
        return *this;
    }

    /**
     * Inserter for long doubles.
     *
     * @param[in] f Number
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( long double f )
    {
        *(static_cast<std::wostream*>(this)) << f;
        return *this;
    }

    /**
     * Inserter for pointers.
     *
     * @param[in] p Pointer
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( const void *p )
    {
        *(static_cast<std::wostream*>(this)) << p;
        return *this;
    }

    /**
     * Inserter for chars.
     *
     * @param[in] c Character
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( char c )
    {
        *(static_cast<std::wostream*>(this)) << c;
        return *this;
    }

    /**
     * Inserter for unsigned chars.
     *
     * @param[in] c Character
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( unsigned char c )
    {
        *(static_cast<std::wostream*>(this)) << c;
        return *this;
    }

    /**
     * Inserter for signed chars.
     *
     * @param[in] c Character
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( signed char c )
    {
        *(static_cast<std::wostream*>(this)) << c;
        return *this;
    }

    /**
     * Inserter for wide chars.
     *
     * @param[in] c Character
     * @return The ColorConsole object (*this)
     */
    ConsoleW& operator<<( wchar_t c )
    {
        *(static_cast<std::wostream*>(this)) << c;
        return *this;
    }

    /**
     * Inserter for text strings.
     *
     * @param[in] text Text string
     * @return The ColorConsoleW object (*this)
     */
    ConsoleW& operator<<( const wchar_t *text )
    {
        *(static_cast<std::wostream*>(this)) << text;
        return *this;
    }

    /**
     * Inserter for text strings.
     *
     * @param[in] text Text string
     * @return The ColorConsoleW object (*this)
     */
    ConsoleW& operator<<( const char *text )
    {
        *(static_cast<std::wostream*>(this)) << text;
        return *this;
    }

    /**
     * Returns the console type.
     *
     * @return The console type
     */
    ConsoleType get_console_type() const noexcept
    {
        return m_consoleType;
    }

    /**
     * Color-enabled standard output stream (wide characters oriented).
     */
    static ConsoleW wcout;

    /**
     * Color-enabled standard output stream for errors (wide characters oriented).
     */
    static ConsoleW wcerr;

    /**
     * Initializes the consoles.
     */
    static void Init();

private:
    /**
     * Constructor for standard streams.
     *
     * @param[in] consoleType Console to colorize
     */
    ConsoleW( ConsoleType consoleType );

    void Initialize();

    ConsoleType m_consoleType;

#ifdef WIN32
    HANDLE m_handle;
    WORD m_origConsoleAttrs;
#endif

#ifdef UNIT_TEST
    friend struct ::TEST_GROUP_CppUTestGroupColorConsoleW;
#endif
};

/**
 * Color-enabled standard output stream (wide characters oriented).
 */
extern COLORCONSOLE_API ConsoleW &wcout;

/**
 * Color-enabled standard output stream for errors (wide characters oriented).
 */
extern COLORCONSOLE_API ConsoleW &wcerr;

} // namespace

#endif // header guard
