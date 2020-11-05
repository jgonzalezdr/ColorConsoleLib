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

#include <iostream>

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
class ColorConsoleW : public std::wostream
{
public:
    /**
     * Destructor.
     */
    ~ColorConsoleW() noexcept;

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
     * @return The ColorConsoleW object (*this)
     */
    ColorConsoleW& operator<<( Color color ) noexcept;

    /**
     * Inserter for ostream manipulators.
     * 
     * @param pf [in] Manipulator
     * @return The ColorConsoleW object (*this)
     */
    ColorConsoleW& operator<<( std::wostream& (*pf)(std::wostream&) )
    {
        (*pf)(*this);
        return *this;
    }

    /**
     * Inserter for text strings.
     * 
     * @param text [in] Text string
     * @return The ColorConsoleW object (*this)
     */
    ColorConsoleW& operator<<( const wchar_t* text )
    {
        *(static_cast<std::wostream*>(this)) << text;
        return *this;
    }

    /**
     * Color-enabled standard output stream (wide characters oriented).
     */
    static ColorConsoleW wcout;

    /**
     * Color-enabled standard output stream for errors (wide characters oriented).
     */
    static ColorConsoleW wcerr;

private:
    /**
     * Constructor.
     *
     * @param consoleType [in] Console to colorize
     */
    ColorConsoleW( ConsoleType consoleType );

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
extern ColorConsoleW &wcout;

/**
 * Color-enabled standard output stream for errors (wide characters oriented).
 */
extern ColorConsoleW &wcerr;

} // namespace

#endif // header guard
