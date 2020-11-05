#include <CppUTestExt/MockSupport.h>

#include "windows.h"

HANDLE UT_GetStdHandle( DWORD nStdHandle )
{
    return (HANDLE) mock().actualCall("UT_GetStdHandle").withParameter("nStdHandle", nStdHandle).returnPointerValue();
}

BOOL UT_GetConsoleScreenBufferInfo( HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo )
{
    return mock().actualCall("UT_GetConsoleScreenBufferInfo").withParameter("hConsoleOutput", hConsoleOutput)
                 .withOutputParameter("lpConsoleScreenBufferInfo", lpConsoleScreenBufferInfo).returnIntValue();
}

BOOL UT_SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes )
{
    return mock().actualCall("UT_SetConsoleTextAttribute").withParameter("hConsoleOutput", hConsoleOutput)
                 .withParameter("wAttributes", wAttributes).returnIntValue();
}

BOOL UT_SetConsoleOutputCP( UINT wCodePageID )
{
    return mock().actualCall("UT_SetConsoleOutputCP").withParameter("wCodePageID", wCodePageID)
                 .returnIntValue();
}

int UT_setmode( int _FileHandle, int _Mode )
{
    return mock().actualCall("UT_setmode").withParameter("_FileHandle", _FileHandle)
                 .withParameter("_Mode", _Mode).returnIntValue();
}

int UT_fileno( FILE* _Stream )
{
    return mock().actualCall("UT_fileno").withPointerParameter("_Stream", _Stream)
                 .returnIntValue();
}
