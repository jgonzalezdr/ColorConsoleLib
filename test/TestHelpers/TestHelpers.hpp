/**
 * @file
 * @brief      Header for test helper functions
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#ifndef COLORCONSOLE_TESTHELPERS_HPP
#define COLORCONSOLE_TESTHELPERS_HPP

#include <string>
#include <sstream>

std::string readFromStringBuf( std::stringbuf& buf );
std::string readFromStringBuf( std::wstringbuf& buf );

#endif // header guard