/**
 * @file
 * @brief      Example of the usage of ColorConsoleW
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#include "ColorConsoleW.hpp"

using namespace ColorConsole;

#ifdef WIN32
int wmain( int argc, const wchar_t* argv[] )
#else
int main( int argc, const char* argv[] )
#endif
{
    ConsoleW::Init();

    wcout << "wcout: Initial color (non-colored)" << endl << endl;

    wcout << Color::FG_LIGHT_BLUE;
    wcout << "wcout: Light blue" << endl;
    wcout << Color::FG_LIGHT_GREEN;
    wcout << "wcout: Light green" << endl;
    wcout << Color::FG_LIGHT_RED;
    wcout << "wcout: Light red" << endl;
    wcout << Color::FG_LIGHT_CYAN;
    wcout << "wcout: Light cyan" << endl;
    wcout << Color::FG_LIGHT_MAGENTA;
    wcout << "wcout: Light magenta" << endl;
    wcout << Color::FG_YELLOW;
    wcout << "wcout: Yellow" << endl;

    wcout << Color::FG_DARK_BLUE;
    wcout << "wcout: Dark blue" << endl;
    wcout << Color::FG_DARK_GREEN;
    wcout << "wcout: Dark green" << endl;
    wcout << Color::FG_DARK_RED;
    wcout << "wcout: Dark red" << endl;
    wcout << Color::FG_DARK_CYAN;
    wcout << "wcout: Dark cyan" << endl;
    wcout << Color::FG_DARK_MAGENTA;
    wcout << "wcout: Dark magenta" << endl;
    wcout << Color::FG_BROWN;
    wcout << "wcout: Brown" << endl;

    wcerr << Color::FG_BLACK;
    wcerr << "wcerr: Black" << endl;
    wcout << Color::FG_DARK_GREY;
    wcout << "wcout: Dark grey" << endl;
    wcout << Color::FG_LIGHT_GREY;
    wcout << "wcout: Light grey" << endl;
    wcout << Color::FG_WHITE;
    wcout << "wcout: White" << endl;

    wcerr << endl;

    wcerr << (Color::FG_LIGHT_BLUE | Color::BG_WHITE);
    wcerr << "wcerr: Light blue over white" << endl;
    wcerr << (Color::FG_WHITE | Color::BG_LIGHT_BLUE);
    wcerr << "wcerr: White over light blue" << endl;
    wcerr << (Color::FG_BLACK | Color::BG_LIGHT_GREEN);
    wcerr << "wcerr: Black over light green" << endl;
    wcerr << (Color::FG_YELLOW | Color::BG_LIGHT_RED);
    wcerr << "wcerr: Yellow over light red" << endl;
    wcerr << (Color::FG_BLACK | Color::BG_LIGHT_CYAN);
    wcerr << "wcerr: Black over light cyan" << endl;
    wcerr << (Color::FG_WHITE | Color::BG_LIGHT_MAGENTA);
    wcerr << "wcerr: White over light magenta" << endl;
    wcerr << (Color::FG_BLACK | Color::BG_YELLOW);
    wcerr << "wcerr: Black over yellow" << endl;
    wcerr << (Color::FG_BLACK | Color::BG_LIGHT_GREY);
    wcerr << "wcerr: Black over light grey" << endl;

    wcerr << (Color::FG_WHITE | Color::BG_DARK_BLUE);
    wcerr << "wcerr: White over dark blue" << endl;
    wcerr << (Color::FG_WHITE | Color::BG_DARK_GREEN);
    wcerr << "wcerr: White over dark green" << endl;
    wcerr << (Color::FG_YELLOW | Color::BG_DARK_RED);
    wcerr << "wcerr: Yellow over dark red" << endl;
    wcerr << (Color::FG_LIGHT_GREEN | Color::BG_DARK_CYAN);
    wcerr << "wcerr: Light green over dark cyan" << endl;
    wcerr << (Color::FG_LIGHT_CYAN | Color::BG_DARK_MAGENTA);
    wcerr << "wcerr: Light cyan over dark magenta" << endl;
    wcerr << (Color::FG_YELLOW | Color::BG_BROWN);
    wcerr << "wcerr: Yellow over brown" << endl;
    wcerr << (Color::FG_DARK_BLUE | Color::BG_DARK_GREY);
    wcerr << "wcerr: Dark blue over dark grey" << endl;
    wcerr << (Color::FG_LIGHT_GREEN | Color::BG_BLACK);
    wcerr << "cerr: Light green over black" << endl;
    wcerr << (Color::FG_LIGHT_BLUE | Color::BG_NONE);
    wcerr << "cerr: Light blue over none" << endl;

    wcout << Color::RESET;
    wcout << endl;
    wcout << L"wcout: Reset to initial color (non-colored)";
    wcout << endl;

    wcout << endl;
    wcerr << L"wcerr: Unicode chars \u2192 \u00AE \u00B6 \u00C6 \u00DF \u00F8 \u03A3 \u03FE \u2021 àêé·çÇñÑ" << endl;
    wcout << L"wcout: Unicode chars → ® ¶ Æ ß ø Σ Ͼ ‡ àêé·çÇñÑ" << endl;

    return 0;
}