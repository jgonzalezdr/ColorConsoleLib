/**
 * @file
 * @brief      Implementation of test helper functions
 * @project    ColorConsoleLib
 * @authors    Jesus Gonzalez <jgonzalez@gdr-sistemas.com>
 * @copyright  Copyright (c) 2020 Jesus Gonzalez. All rights reserved.
 * @license    See LICENSE.txt
 */

#include "TestHelpers.hpp"

#include <vector>

std::string readFromStringBuf( std::stringbuf& buf )
{
    char tmpNarrowBuf[100] = "\0";

    std::streamsize n = buf.sgetn( tmpNarrowBuf, 100 );
    tmpNarrowBuf[n] = '\0';
    return std::string( tmpNarrowBuf );
}

static std::string wideToNarrow( const wchar_t *t )
{
    std::mbstate_t state = std::mbstate_t();
    std::size_t len = 1 + std::wcsrtombs( nullptr, &t, 0, &state );
    std::vector<char> tmp_mbstr( len );
    std::wcsrtombs( &tmp_mbstr[0], &t, tmp_mbstr.size(), &state );
    return std::string( tmp_mbstr.data() );
}

std::string readFromStringBuf( std::wstringbuf& buf )
{
    wchar_t tmpWideBuf[100] = L"\0";

    std::streamsize n = buf.sgetn( tmpWideBuf, 100 );
    tmpWideBuf[n] = L'\0';
    return wideToNarrow( tmpWideBuf );
}
