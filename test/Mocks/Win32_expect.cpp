#include "Win32_expect.hpp"

namespace expect {

MockExpectedCall& UT_GetStdHandle( DWORD nStdHandle, HANDLE __return__ )
{
    return mock().expectOneCall("UT_GetStdHandle").withParameter("nStdHandle", nStdHandle).andReturnValue(__return__);

}

MockExpectedCall& UT_GetConsoleScreenBufferInfo( HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo, BOOL __return__ )
{
    return mock().expectOneCall("UT_GetConsoleScreenBufferInfo").withParameter("hConsoleOutput", hConsoleOutput)
                 .withOutputParameterReturning("lpConsoleScreenBufferInfo", lpConsoleScreenBufferInfo, sizeof(*lpConsoleScreenBufferInfo))
                 .andReturnValue(__return__);

}

MockExpectedCall& UT_SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes, BOOL __return__ )
{
    return mock().expectOneCall("UT_SetConsoleTextAttribute").withParameter("hConsoleOutput", hConsoleOutput)
                 .withParameter("wAttributes", wAttributes).andReturnValue(__return__);

}

MockExpectedCall& UT_SetConsoleOutputCP( UINT wCodePageID, BOOL __return__ )
{
    return mock().expectOneCall("UT_SetConsoleOutputCP").withParameter("wCodePageID", wCodePageID)
                 .andReturnValue(__return__);
}

MockExpectedCall& UT_setmode( int _FileHandle, int _Mode, int __return__)
{
    return mock().expectOneCall("UT_setmode").withParameter("_FileHandle", _FileHandle)
                 .withParameter("_Mode", _Mode).andReturnValue(__return__);
}

MockExpectedCall& UT_fileno( FILE* _Stream, int __return__)
{
    return mock().expectOneCall("UT_fileno").withPointerParameter("_Stream", _Stream)
                 .andReturnValue(__return__);
}

}
