/**
 * @file
 * @brief      Common declarations for ColorConsole and ColorConsoleW
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#ifndef COLORCONSOLECOMMON_HPP_
#define COLORCONSOLECOMMON_HPP_

#include <iostream>

#if defined(WIN32) && defined(COLORCONSOLE_SHARED_LIB)
#   if defined(ColorConsole_EXPORTS)
#       define COLORCONSOLE_API __declspec(dllexport)
#   else
#       define COLORCONSOLE_API __declspec(dllimport)
#   endif
#else
#   define COLORCONSOLE_API
#endif

namespace ColorConsole
{

/**
 * Console type.
 */
enum class ConsoleType
{
    STD_OUTPUT, ///< Standard output
    STD_ERROR   ///< Standard error
};

/**
 * Console color.
 * 
 * One foreground and one background color can be combined ORing them.
 */
enum class Color
{
    FG_BLACK = 0,             ///< Black foreground
    FG_DARK_BLUE = 0x01,      ///< Dark blue foreground
    FG_DARK_GREEN = 0x02,     ///< Dark green foreground
    FG_DARK_CYAN = 0x03,      ///< Dark cyan foreground
    FG_DARK_RED = 0x04,       ///< Dark red foreground
    FG_DARK_MAGENTA = 0x05,   ///< Dark magenta foreground
    FG_BROWN = 0x06,          ///< Brown foreground
    FG_LIGHT_GREY = 0x07,     ///< Light grey foreground
    FG_LIGHT_GRAY = 0x07,     ///< Light gray foreground
    FG_DARK_GREY = 0x08,      ///< Dark grey foreground
    FG_DARK_GRAY = 0x08,      ///< Dark gray foreground
    FG_LIGHT_BLUE = 0x09,     ///< Light blue foreground
    FG_LIGHT_GREEN = 0x0A,    ///< Light green foreground
    FG_LIGHT_CYAN = 0x0B,     ///< Light cyan foreground
    FG_LIGHT_RED = 0x0C,      ///< Light red foreground
    FG_LIGHT_MAGENTA = 0x0D,  ///< Light magenta foreground
    FG_YELLOW = 0x0E,         ///< Yellow foreground
    FG_WHITE = 0x0F,          ///< White foreground
    BG_NONE = 0,              ///< Default background
    BG_DARK_BLUE = 0x10,      ///< Dark blue background
    BG_DARK_GREEN = 0x20,     ///< Dark green background
    BG_DARK_CYAN = 0x30,      ///< Dark cyan background
    BG_DARK_RED = 0x40,       ///< Dark red background
    BG_DARK_MAGENTA = 0x50,   ///< Dark magenta background
    BG_BROWN = 0x60,          ///< Brown background
    BG_LIGHT_GREY = 0x70,     ///< Light grey background
    BG_LIGHT_GRAY = 0x70,     ///< Light gray background
    BG_DARK_GREY = 0x80,      ///< Dark grey background
    BG_DARK_GRAY = 0x80,      ///< Dark gray background
    BG_LIGHT_BLUE = 0x90,     ///< Light blue background
    BG_LIGHT_GREEN = 0xA0,    ///< Light green background
    BG_LIGHT_CYAN = 0xB0,     ///< Light cyan background
    BG_LIGHT_RED = 0xC0,      ///< Light red background
    BG_LIGHT_MAGENTA = 0xD0,  ///< Light magenta background
    BG_YELLOW = 0xE0,         ///< Yellow background
    BG_WHITE = 0xF0,          ///< White background
    RESET = 0x10000           ///< Reset to initial setting
};

/**
 * Combines colors.
 */
inline Color operator|(Color a, Color b)
{
    return static_cast<Color>(static_cast<int>(a) | static_cast<int>(b));
}

/**
 * Newline and flush manipulator (redefined from std namespace for convenience).
 */
template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& endl( std::basic_ostream<_Elem, _Traits>& str )
{
    return std::endl( str );
}

//extern std::ostream& (*endl)(std::ostream&);

/**
 * End of string manipulator (redefined from std namespace for convenience).
 */
template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& ends( std::basic_ostream<_Elem, _Traits>& str )
{
    return std::ends( str );
}

/**
 * Flush manipulator (redefined from std namespace for convenience).
 */
template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>& flush( std::basic_ostream<_Elem, _Traits>& str )
{
    return std::flush( str );
}

} // namespace

#endif // header guard
