/**
 * @file
 * @brief      Helper functions declarations for ColorConsole and ColorConsoleW
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2017-2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#ifndef COLORCONSOLEHELPERS_HPP_
#define COLORCONSOLEHELPERS_HPP_

#include "ColorConsoleCommon.hpp"

namespace ColorConsole
{

inline Color operator&( Color a, Color b )
{
    return static_cast<Color>( static_cast<int>(a) & static_cast<int>(b) );
}

inline bool cast_bool( Color color )
{
    return static_cast<bool>( color );
}

template<class Stream>
void setAnsiColor( Stream *out, Color color )
{
    if( color >= Color::RESET )
    {
        *out << "\033[0m";
    }
    else
    {
        *out << "\033[";

        Color bg_color = ( color & (Color::BG_LIGHT_RED|Color::BG_LIGHT_GREEN|Color::BG_LIGHT_BLUE) );

        switch( bg_color )
        {
            default:
            case Color::BG_NONE:
                if( cast_bool( color & Color::BG_BLACK ) )
                {
                    *out << "40";
                }
                else
                {
                    *out << "49";
                }
                break;
            case Color::BG_DARK_RED:
                *out << "41";
                break;
            case Color::BG_DARK_GREEN:
                *out << "42";
                break;
            case Color::BG_BROWN:
                *out << "43";
                break;
            case Color::BG_DARK_BLUE:
                *out << "44";
                break;
            case Color::BG_DARK_MAGENTA:
                *out << "45";
                break;
            case Color::BG_DARK_CYAN:
                *out << "46";
                break;
            case Color::BG_LIGHT_GREY:
                *out << "47";
                break;
            case Color::BG_DARK_GREY:
                *out << "100";
                break;
            case Color::BG_LIGHT_RED:
                *out << "101";
                break;
            case Color::BG_LIGHT_GREEN:
                *out << "102";
                break;
            case Color::BG_YELLOW:
                *out << "103";
                break;
            case Color::BG_LIGHT_BLUE:
                *out << "104";
                break;
            case Color::BG_LIGHT_MAGENTA:
                *out << "105";
                break;
            case Color::BG_LIGHT_CYAN:
                *out << "106";
                break;
            case Color::BG_WHITE:
                *out << "107";
                break;
        }
        *out << ";";

        switch( color & (Color::FG_LIGHT_RED|Color::FG_LIGHT_GREEN|Color::FG_LIGHT_BLUE) )
        {
            case Color::FG_BLACK:
                *out << "30";
                break;
            case Color::FG_DARK_RED:
                *out << "31";
                break;
            case Color::FG_DARK_GREEN:
                *out << "32";
                break;
            case Color::FG_BROWN:
                *out << "33";
                break;
            case Color::FG_DARK_BLUE:
                *out << "34";
                break;
            case Color::FG_DARK_MAGENTA:
                *out << "35";
                break;
            case Color::FG_DARK_CYAN:
                *out << "36";
                break;
            case Color::FG_LIGHT_GREY:
                *out << "37";
                break;
            case Color::FG_DARK_GREY:
                *out << "1;30";
                break;
            case Color::FG_LIGHT_RED:
                *out << "1;31";
                break;
            case Color::FG_LIGHT_GREEN:
                *out << "1;32";
                break;
            case Color::FG_YELLOW:
                *out << "1;33";
                break;
            case Color::FG_LIGHT_BLUE:
                *out << "1;34";
                break;
            case Color::FG_LIGHT_MAGENTA:
                *out << "1;35";
                break;
            case Color::FG_LIGHT_CYAN:
                *out << "1;36";
                break;
            default:
            case Color::FG_WHITE:
                *out << "1;37";
                break;
        }
        *out << "m";
    }
}

} // namespace

#endif // header guard
