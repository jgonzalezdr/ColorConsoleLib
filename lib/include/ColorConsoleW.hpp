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
class COLORCONSOLE_API ConsoleW : public std::wostream
{
public:
    /**
     * Destructor.
     */
    ~ConsoleW() noexcept;

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
    ConsoleW& operator<<( Color color ) noexcept;

    /**
     * Inserter for ostream manipulators.
     * 
     * @param pf [in] Manipulator
     * @return The ColorConsoleW object (*this)
     */
    ConsoleW& operator<<( std::wostream& (*pf)(std::wostream&) )
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
    ConsoleW& operator<<( const wchar_t* text )
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
     * Constructor.
     *
     * @param consoleType [in] Console to colorize
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
