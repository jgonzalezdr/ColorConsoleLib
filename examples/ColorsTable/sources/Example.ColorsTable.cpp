/**
 * @file
 * @brief      Colors table app
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#include "ColorConsole.hpp"

using namespace ColorConsole;

int main( int argc, const char* argv[] )
{
    Console::Init();

    cout << Color::FG_WHITE;
    cout << "      FG_WHITE      ";
    cout << (Color::BG_WHITE|Color::FG_BLACK);
    cout << "      BG_WHITE      " << Color::RESET << endl;
    cout << Color::FG_LIGHT_BLUE;
    cout << "   FG_LIGHT_BLUE    ";
    cout << (Color::BG_LIGHT_BLUE|Color::FG_LIGHT_GREY);
    cout << "   BG_LIGHT_BLUE    " << Color::RESET << endl;
    cout << Color::FG_LIGHT_GREEN;
    cout << "   FG_LIGHT_GREEN   ";
    cout << (Color::BG_LIGHT_GREEN|Color::FG_BLACK);
    cout << "   BG_LIGHT_GREEN   " << Color::RESET << endl;
    cout << Color::FG_LIGHT_RED;
    cout << "    FG_LIGHT_RED    ";
    cout << (Color::BG_LIGHT_RED|Color::FG_LIGHT_GREY);
    cout << "    BG_LIGHT_RED    " << Color::RESET << endl;
    cout << Color::FG_LIGHT_CYAN;
    cout << "   FG_LIGHT_CYAN    ";
    cout << (Color::BG_LIGHT_CYAN|Color::FG_BLACK);
    cout << "   BG_LIGHT_CYAN    " << Color::RESET << endl;
    cout << Color::FG_LIGHT_MAGENTA;
    cout << "  FG_LIGHT_MAGENTA  ";
    cout << (Color::BG_LIGHT_MAGENTA|Color::FG_WHITE);
    cout << "  BG_LIGHT_MAGENTA  " << Color::RESET << endl;
    cout << Color::FG_YELLOW;
    cout << "     FG_YELLOW      ";
    cout << (Color::BG_YELLOW|Color::FG_BLACK);
    cout << "     BG_YELLOW      " << Color::RESET << endl;
    cout << Color::FG_LIGHT_GREY;
    cout << "   FG_LIGHT_GREY    ";
    cout << (Color::BG_LIGHT_GREY|Color::FG_BLACK);
    cout << "   BG_LIGHT_GREY    " << Color::RESET << endl;

    cout << Color::FG_DARK_GREY;
    cout << "    FG_DARK_GREY    ";
    cout << (Color::BG_DARK_GREY|Color::FG_WHITE);
    cout << "    BG_DARK_GREY    " << Color::RESET << endl;
    cout << (Color::FG_BROWN|Color::BG_NONE);
    cout << "      FG_BROWN      ";
    cout << (Color::BG_BROWN|Color::FG_WHITE);
    cout << "      BG_BROWN      " << Color::RESET << endl;
    cout << (Color::FG_DARK_BLUE|Color::BG_LIGHT_GREY);
    cout << "    FG_DARK_BLUE    ";
    cout << (Color::BG_DARK_BLUE|Color::FG_WHITE);
    cout << "    BG_DARK_BLUE    " << Color::RESET << endl;
    cout << (Color::FG_DARK_GREEN|Color::BG_LIGHT_GREY);
    cout << "   FG_DARK_GREEN    ";
    cout << (Color::BG_DARK_GREEN|Color::FG_WHITE);
    cout << "   BG_DARK_GREEN    " << Color::RESET << endl;
    cout << (Color::FG_DARK_RED|Color::BG_LIGHT_GREY);
    cout << "    FG_DARK_RED     ";
    cout << (Color::BG_DARK_RED|Color::FG_WHITE);
    cout << "    BG_DARK_RED     " << Color::RESET << endl;
    cout << (Color::FG_DARK_CYAN|Color::BG_LIGHT_GREY);
    cout << "    FG_DARK_CYAN    ";
    cout << (Color::BG_DARK_CYAN|Color::FG_WHITE);
    cout << "    BG_DARK_CYAN    " << Color::RESET << endl;
    cout << (Color::FG_DARK_MAGENTA|Color::BG_LIGHT_GREY);
    cout << "  FG_DARK_MAGENTA   ";
    cout << (Color::BG_DARK_MAGENTA|Color::FG_WHITE);
    cout << "  BG_DARK_MAGENTA   " << Color::RESET << endl;
    cout << (Color::FG_BLACK|Color::BG_WHITE);
    cout << "      FG_BLACK      ";
    cout << (Color::BG_NONE|Color::FG_WHITE);
    cout << "      BG_NONE       " << Color::RESET << endl;

    return 0;
}