/**
 * @file
 * @brief      Header of ColorConsole class
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#ifndef COLORCONSOLE_HPP_
#define COLORCONSOLE_HPP_

#include "ColorConsoleCommon.hpp"

#ifdef WIN32
#include "windows.h"
#endif

#ifdef UNIT_TEST
struct TEST_GROUP_CppUTestGroupColorConsole;
#endif

namespace ColorConsole
{

/**
 * Output stream representing a console oriented to narrow characters (of type char)
 * with text coloring capabilities.
 */
class COLORCONSOLE_API Console : public std::ostream
{
public:
    /**
     * Constructor for custom streams.
     *
     * Coloring of custom streams (if enabled) will be performed using ANSI color escape codes.
     *
     * Custom streams are mostly intended for testing software that writes on color consoles.
     *
     * param sb [in] Stream buffer where the strem will write to
     * param enableColoring [in] Indicates if coloring shall be enabled
     *
     * @param[in,out] consoleType Console to color
     */
    Console( std::streambuf *sb, bool enableColoring = true );

    /**
     * Destructor.
     */
    ~Console();

    /**
     * Sets (or resets) the console color.
     *
     * @param[in] color Color to be set, or RESET to reset to default value
     */
    void set_color( Color color );

    /**
     * Enables coloring.
     *
     * @param[in] value @c true to enable coloring, @c false to disable coloring
     */
    void enable_coloring( bool value = true )
    {
        m_coloringEnabled = value;
    }

    /**
     * Disables coloring.
     *
     * @param[in] value @c true to disable coloring, @c false to enable coloring
     */
    void disable_coloring( bool value = true )
    {
        m_coloringEnabled = !value;
    }

    /**
     * Indicates if coloring is enabled.
     *
     * @return @c true if coloring is enabled, @c false otherwise
     */
    bool is_coloring_enabled() const
    {
        return m_coloringEnabled;
    }

    /**
     * Sets (or resets) the console color.
     *
     * @param[in] color Color to be set, or RESET to reset to default value
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( Color color );

    /**
     * Inserter for ostream manipulators.
     *
     * @param[in] pf Manipulator
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( std::ostream& (*pf)(std::ostream&) )
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
    Console& operator<<( std::ios& (*pf)(std::ios&) )
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
    Console& operator<<( std::ios_base& (*pf)(std::ios_base&) )
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
    Console& operator<<( long n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for unsigned longs.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( unsigned long n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for bools.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( bool n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for shorts.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( short n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for unsigned shorts.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( unsigned short n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for ints.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( int n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for unsigned ints.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( unsigned int n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for long longs.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( long long n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for unsigned long longs.
     *
     * @param[in] n Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( unsigned long long n )
    {
        *(static_cast<std::ostream*>(this)) << n;
        return *this;
    }

    /**
     * Inserter for doubles.
     *
     * @param[in] f Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( double f )
    {
        *(static_cast<std::ostream*>(this)) << f;
        return *this;
    }

    /**
     * Inserter for floats.
     *
     * @param[in] f Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( float f )
    {
        *(static_cast<std::ostream*>(this)) << f;
        return *this;
    }

    /**
     * Inserter for long doubles.
     *
     * @param[in] f Number
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( long double f )
    {
        *(static_cast<std::ostream*>(this)) << f;
        return *this;
    }

    /**
     * Inserter for pointers.
     *
     * @param[in] p Pointer
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( const void *p )
    {
        *(static_cast<std::ostream*>(this)) << p;
        return *this;
    }

    /**
     * Inserter for chars.
     *
     * @param[in] c Character
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( char c )
    {
        *(static_cast<std::ostream*>(this)) << c;
        return *this;
    }

    /**
     * Inserter for unsigned chars.
     *
     * @param[in] c Character
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( unsigned char c )
    {
        *(static_cast<std::ostream*>(this)) << c;
        return *this;
    }

    /**
     * Inserter for signed chars.
     *
     * @param[in] c Character
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( signed char c )
    {
        *(static_cast<std::ostream*>(this)) << c;
        return *this;
    }

    /**
     * Inserter for text strings.
     *
     * @param[in] text Text string
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( const char *text )
    {
        *(static_cast<std::ostream*>(this)) << text;
        return *this;
    }

    /**
     * Inserter for text strings.
     *
     * @param[in] text Text string
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( const unsigned char *text )
    {
        *(static_cast<std::ostream*>(this)) << text;
        return *this;
    }

    /**
     * Inserter for text strings.
     *
     * @param[in] text Text string
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( const signed char *text )
    {
        *(static_cast<std::ostream*>(this)) << text;
        return *this;
    }

    /**
     * Inserter for text strings.
     *
     * @param[in] text Text string
     * @return The ColorConsole object (*this)
     */
    Console& operator<<( const std::string &text )
    {
        *(static_cast<std::ostream*>(this)) << text;
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
     * Color-enabled standard output stream (narrow characters oriented).
     */
    static Console cout;

    /**
     * Color-enabled standard output stream for errors (narrow characters oriented).
     */
    static Console cerr;

    /**
     * Initializes the consoles.
     */
    static void Init();

private:
    /**
     * Constructor for standard streams.
     *
     * @param[in] consoleType Console to color
     */
    Console( ConsoleType consoleType );

    void initialize();

    ConsoleType m_consoleType;

    bool m_coloringEnabled;

#ifdef WIN32
    HANDLE m_handle;
    WORD m_origConsoleAttrs;
#endif

#ifdef UNIT_TEST
    friend struct ::TEST_GROUP_CppUTestGroupColorConsole;
#endif
};

/**
 * Color-enabled standard output stream (narrow characters oriented).
 */
extern COLORCONSOLE_API Console &cout;

/**
 * Color-enabled standard output stream for errors (narrow characters oriented).
 */
extern COLORCONSOLE_API Console &cerr;

} // namespace

#endif // header guard
