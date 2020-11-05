#include <CppUTestExt/MockSupport.h>

#include "windows.h"

namespace expect {

MockExpectedCall& UT_GetStdHandle( DWORD nStdHandle, HANDLE __return__ );

MockExpectedCall& UT_GetConsoleScreenBufferInfo( HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo, BOOL __return__ );

MockExpectedCall& UT_SetConsoleTextAttribute( HANDLE hConsoleOutput, WORD wAttributes, BOOL __return__ );

MockExpectedCall& UT_SetConsoleOutputCP( UINT wCodePageID, BOOL __return__ );

MockExpectedCall& UT_setmode( int _FileHandle, int _Mode, int __return__);

MockExpectedCall& UT_fileno( FILE* _Stream, int __return__);

}
