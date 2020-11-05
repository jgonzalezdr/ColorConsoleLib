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
 * with text colorization capabilities.
 */
class ColorConsole : public std::ostream
{
public:
    /**
     * Destructor.
     */
    ~ColorConsole() noexcept;

    /**
     * Sets (or resets) the console color.
     *
     * @param color [in] Color to be set, or RESET to reset to default value
     */
    void set_color( Color color ) noexcept;

    /**
     * Sets (or resets) the console color.
     *
     * @param color [in] Color to be set, or RESET to reset to default value
     * @return The ColorConsole object (*this)
     */
    ColorConsole& operator<<( Color color ) noexcept;

    /**
     * Inserter for ostream manipulators.
     * 
     * @param pf [in] Manipulator
     * @return The ColorConsole object (*this)
     */
    ColorConsole& operator<<( std::ostream& (*pf)(std::ostream&) )
    {
        (*pf)(*this);
        return *this;
    }

    /**
     * Inserter for text strings.
     * 
     * @param text [in] Text string
     * @return The ColorConsole object (*this)
     */
    ColorConsole& operator<<( const char* text )
    {
        *(static_cast<std::ostream*>(this)) << text;
        return *this;
    }

    /**
     * Color-enabled standard output stream (narrow characters oriented).
     */
    static ColorConsole cout;

    /**
     * Color-enabled standard output stream for errors (narrow characters oriented).
     */
    static ColorConsole cerr;

private:
    /**
     * Constructor.
     *
     * @param consoleType [in] Console to colorize
     */
    ColorConsole( ConsoleType consoleType );

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
extern ColorConsole &cout;

/**
 * Color-enabled standard output stream for errors (narrow characters oriented).
 */
extern ColorConsole &cerr;

} // namespace

#endif // header guard
