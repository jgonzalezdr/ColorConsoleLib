/**
 * @file
 * @brief      Example of the usage of ColorConsole
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

    cout << "cout: Initial color (non-colorized)" << endl << endl;

    cout << Color::FG_LIGHT_BLUE;
    cout << "cout: Light blue" << endl;
    cout << Color::FG_LIGHT_GREEN;
    cout << "cout: Light green" << endl;
    cout << Color::FG_LIGHT_RED;
    cout << "cout: Light red" << endl;
    cout << Color::FG_LIGHT_CYAN;
    cout << "cout: Light cyan" << endl;
    cout << Color::FG_LIGHT_MAGENTA;
    cout << "cout: Light magenta" << endl;
    cout << Color::FG_YELLOW;
    cout << "cout: Yellow" << endl;

    cout << Color::FG_DARK_BLUE;
    cout << "cout: Dark blue" << endl;
    cout << Color::FG_DARK_GREEN;
    cout << "cout: Dark green" << endl;
    cout << Color::FG_DARK_RED;
    cout << "cout: Dark red" << endl;
    cout << Color::FG_DARK_CYAN;
    cout << "cout: Dark cyan" << endl;
    cout << Color::FG_DARK_MAGENTA;
    cout << "cout: Dark magenta" << endl;
    cout << Color::FG_BROWN;
    cout << "cout: Brown" << endl;

    cout << Color::FG_DARK_GREY;
    cout << "cout: Dark grey" << endl;
    cout << Color::FG_LIGHT_GREY;
    cout << "cout: Light grey" << endl;
    cout << Color::FG_WHITE;
    cout << "cout: White" << endl;

    cerr << endl;
    
    cerr << (Color::FG_LIGHT_BLUE | Color::BG_WHITE);
    cerr << "cerr: Light blue over white" << endl;
    cerr << (Color::FG_WHITE | Color::BG_LIGHT_BLUE);
    cerr << "cerr: White over light blue" << endl;
    cerr << (Color::FG_BLACK | Color::BG_LIGHT_GREEN);
    cerr << "cerr: Black over light green" << endl;
    cerr << (Color::FG_YELLOW | Color::BG_LIGHT_RED);
    cerr << "cerr: Yellow over light red" << endl;
    cerr << (Color::FG_BLACK | Color::BG_LIGHT_CYAN);
    cerr << "cerr: Black over light cyan" << endl;
    cerr << (Color::FG_WHITE | Color::BG_LIGHT_MAGENTA);
    cerr << "cerr: White over light magenta" << endl;
    cerr << (Color::FG_BLACK | Color::BG_YELLOW);
    cerr << "cerr: Black over yellow" << endl;
    cerr << (Color::FG_BLACK | Color::BG_LIGHT_GREY);
    cerr << "cerr: Black over light grey" << endl;

    cerr << (Color::FG_WHITE | Color::BG_DARK_BLUE);
    cerr << "cerr: White over dark blue" << endl;
    cerr << (Color::FG_WHITE | Color::BG_DARK_GREEN);
    cerr << "cerr: White over dark green" << endl;
    cerr << (Color::FG_YELLOW | Color::BG_DARK_RED);
    cerr << "cerr: Yellow over dark red" << endl;
    cerr << (Color::FG_LIGHT_GREEN | Color::BG_DARK_CYAN);
    cerr << "cerr: Light green over dark cyan" << endl;
    cerr << (Color::FG_LIGHT_CYAN | Color::BG_DARK_MAGENTA);
    cerr << "cerr: Light cyan over dark magenta" << endl;
    cerr << (Color::FG_YELLOW | Color::BG_BROWN);
    cerr << "cerr: Yellow over brown" << endl;
    cerr << (Color::FG_DARK_BLUE | Color::BG_DARK_GREY);
    cerr << "cerr: Dark blue over dark grey" << endl;

    cerr << Color::FG_BLACK;
    cerr << "cerr: Black" << endl;

    cout << Color::RESET;
    cout << endl;
    cout << "cout: Reset to initial color (non-colorized)";
    cout << endl;

    cout << endl;
    cerr << "cerr: Extended chars àêé·çÇñÑ" << endl;
    cout << "cout: Extended chars ® ¶ Æ ß ø ‡ àêé·çÇñÑ";

    return 0;
}