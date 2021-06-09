
Color Console Library
===========

[![Build status](https://ci.appveyor.com/api/projects/status/7wi13ayrw0dn2oaq/branch/main?svg=true)](https://ci.appveyor.com/project/jgonzalezdr/colorconsolelib/branch/main)
[![codecov](https://codecov.io/gh/jgonzalezdr/ColorConsoleLib/branch/main/graph/badge.svg)](https://codecov.io/gh/jgonzalezdr/ColorConsoleLib)

## About

ColorConsoleLib is a library that adds text coloring capabilities to the C++ standard output and error streams ([cout](http://www.cplusplus.com/reference/iostream/cout/)/[wcout](http://www.cplusplus.com/reference/iostream/wcout/) and [cerr](http://www.cplusplus.com/reference/iostream/cerr/)/[wcerr](http://www.cplusplus.com/reference/iostream/cout/)).

## Usage

ColorConsoleLib provides compatible replacements for the C++ standard _cout_, _cerr_, _wcout_ and _wcerr_ output streams in the **ColorConsole** namespace that add text coloring capabilities by accepting **Color**s to the _insertion operator_ (`<<`).

``` CPP
#include "ColorConsole.hpp"

using namespace ColorConsole;

int main( int argc, const char* argv[] )
{
  cout << Color::FG_LIGHT_BLUE << "Hello World!" << endl;

  return 0;
}
```

There are 16 foreground **Color**s (which names start with `FG_`) that can be mixed with 17 background **Color**s (which names start with `BG_`) using the _OR_ operation (`|`).

![Color Table](https://github.com/jgonzalezdr/ColorConsoleLib/blob/gh-pages/images/ColorTable.png?raw=true)

> **Note**:
>
> The background **Color** `FG_BLACK` interpretation depends on the terminal. Some interpret it as black, others as transparent (showing the underlying console color).
>
> The background **Color** `FG_NONE` interpretation depends on the terminal. Some interpret it as transparent (showing the underlying console color), others as black.

The special **Color** `RESET` can be used to return the console to the original "non-colored" mode.

Alternatively, the **set_color()** member function can be used, which behaves just like inserting a **Color** in the stream.

### Example Output

![Example Output](https://github.com/jgonzalezdr/ColorConsoleLib/blob/gh-pages/images/ColorConsoleLib.png?raw=true)

## Building from Source

### Build Requirements

- [CMake](https://cmake.org/) (≥ v3.13, tested with v3.17.2)
- [CppUTest](http://cpputest.github.io/) [Optional, not needed if tests are disabled] (tested with [v3.9.alpha0](https://github.com/jgonzalezdr/cpputest/releases/download/v3.9.alpha0/cpputest-3.9.alpha0.zip))
- On Windows:
  - A C/C++ compiler, either:
    - [MinGW-w64](https://sourceforge.net/projects/mingw-w64/) (tested with v7.3.0, v8.1.0 and [TDM-GCC v9.2.0](https://jmeubank.github.io/tdm-gcc/download/))
    - [Microsoft Visual Studio](https://www.visualstudio.com/es/downloads/) (tested with Visual Studio Community 2019)
  - [LCOV for Windows](https://github.com/jgonzalezdr/lcov/releases) [Optional, needed if tests and coverage are enabled using MinGW] (tested with [v1.15.alpha1w](https://github.com/jgonzalezdr/lcov/releases/download/v1.15.alpha1w/lcov-v1.15.alpha1w.zip))
  - [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage) [Optional, needed if tests and coverage are enabled using Visual Studio 2019] (tested with v0.9.8.0)
- On Linux:
  - [GCC](https://gcc.gnu.org/) (tested with v7.5.0, v8.4.0 and v9.3.0)
  - [LCOV](http://ltp.sourceforge.net/coverage/lcov.php) [Optional, needed if tests and coverage are enabled using GCC] (tested with v1.14)

### CMake Project Options

| OPTION                | Description |
| -                     | - |
| `-DCMAKE_BUILD_TYPE`  | Selects build type<br>_(only for single-config generators)_<br>`Debug`<br>`Release`_(default)_<br>`RelWithDebInfo` (Release with debug info)<br>`MinSizeRel`(Release with size optimization)<br> `Coverage`(Debug with code coverage enabled) |
| `-DBUILD_SHARED_LIB`  | Enables generation of shared library<br>`ON`_(default)_<br>`OFF` |
| `-DBUILD_STATIC_LIB`  | Enables generation of static library<br>`ON`_(default)_<br>`OFF` |
| `-DENABLE_TEST`       | Enables compilation and execution of tests<br>`ON`_(default)_<br>`OFF` |
| `-DCPPUTEST_HOME`     | Path to your CppUTest installation directory<br>`<filesystem path>` |
| `-DLCOV_HOME`         | Path to your LCOV installation directory<br>`<filesystem path>` |
| `-DENABLE_INSTALLER`  | Enables generation of installer packages<br>`ON`_(default)_<br>`OFF` |
| `-DBUILD_EXAMPLES`    | Enables building examples<br>`ON`_(default)_<br>`OFF` |
| `-DCOVERAGE`          | Enables code coverage in tests<br>_(only for multi-config generators)_<br>`ON`_(default)_<br>`OFF` |
| `-DCOVERAGE_VERBOSE`  | Enables verbose code coverage<br>`ON`<br>`OFF`_(default)_ |
| `-DCI_MODE`           | Enables Continous Integration mode<br>`ON`<br>`OFF`_(default)_ |
