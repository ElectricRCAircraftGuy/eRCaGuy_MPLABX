This file is part of eRCaGuy_MPLABX: https://github.com/ElectricRCAircraftGuy/eRCaGuy_MPLABX


# How to set up VSCode to index and search the Microchip XC32 compiler's include files


# Quick summary

1. Add the `-v` flag to the compiler command-line to get verbose output. 
1. Build the project.
1. Find the include paths in the build output by searching for `#include`, which now show up because of `-v` above. 
1. Use `realpath` on all of the include paths to get a fixed-up path to each one. 
1. Add those paths to the `.vscode/settings.json` file in the `"C_Cpp.default.includePath"` list.


# Details

This process works for *any* gcc or clang-based compiler project, not just Microchip's XC32 compiler.

I will be testing this on the following project herein: `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/gs_pic32mx7_basic_uart/gs_pic32mx7.X`. When imported into the MPLAB X IDE, this project is called `gs_pic32mx7`. 

1. Create a `.vscode/settings.json` file at path `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/.vscode/settings.json`. 

1. Add the following entries: 
    ```jsonc
    {
        "C_Cpp.default.defines": [
        ],
        "C_Cpp.default.includePath": [
        ],
        "files.associations": {
        }
    }
    ```

1. Add the `-v` flag to the compiler command-line. 

    To do this in the MPLAB X IDE, right-click the project --> Properties --> find the target configuration of interest (ex: `default`) --> XC32 (Global Options) --> xc32-gcc --> in the "Additional options" field, add `-v`. 
    
    Do the same in the XC32 (Global Options) --> xc32-g++ section.

    Click "OK" to save the changes.

1. Build the project. 

1. Copy/paste the build output to a text editor like VSCode and search for the following lines: 
    ```
    #include "..." search starts here:
    ```
    and:
    ```
    #include <...> search starts here:
    ```

    I see the following output. It occurs exactly 9 times in my case:
    ```
    #include "..." search starts here:
    #include <...> search starts here:
    ../src
    ../src/config/default
    /opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259/include
    /opt/microchip/xc32/v4.45/bin/bin/../../lib/gcc/pic32mx/8.3.1/../../../../pic32mx/include
    /opt/microchip/xc32/v4.45/bin/bin/../../lib/gcc/pic32mx/8.3.1/include/../../../../../pic32mx//include/musl
    /opt/microchip/xc32/v4.45/bin/bin/../../lib/gcc/pic32mx/8.3.1/include
    /opt/microchip/xc32/v4.45/bin/bin/../../pic32mx/include/pic32m-libs
    ```

1. Based on the output above, resolve the paths using `realpath` and `realpath --relative-to`, as follows: 

    Run these commands in your terminal: 
    ```bash
    # 1. for the relative paths which are relative to 
    #    `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/gs_pic32mx7_basic_uart/gs_pic32mx7.X`, 
    #    make them relative to the root location in which the `.vscode/` dir is located
    cd path/to/eRCaGuy_MPLABX
    cd ChipKIT_Max32_PIC32MX795F512L/gs_pic32mx7_basic_uart/gs_pic32mx7.X
    realpath --relative-to=../.. ../src
    realpath --relative-to=../.. ../src/config/default
    
    # 2. for the absolute paths
    realpath /opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259/include
    realpath /opt/microchip/xc32/v4.45/bin/bin/../../lib/gcc/pic32mx/8.3.1/../../../../pic32mx/include
    realpath /opt/microchip/xc32/v4.45/bin/bin/../../lib/gcc/pic32mx/8.3.1/include/../../../../../pic32mx//include/musl
    realpath /opt/microchip/xc32/v4.45/bin/bin/../../lib/gcc/pic32mx/8.3.1/include
    realpath /opt/microchip/xc32/v4.45/bin/bin/../../pic32mx/include/pic32m-libs
    ```

    My output is as follows: 
    ```bash
    # from 1
    gs_pic32mx7_basic_uart/src
    gs_pic32mx7_basic_uart/src/config/default
    
    # from 2
    /opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259/include
    /opt/microchip/xc32/v4.45/pic32mx/include
    /opt/microchip/xc32/v4.45/pic32mx/include/musl
    /opt/microchip/xc32/v4.45/lib/gcc/pic32mx/8.3.1/include
    /opt/microchip/xc32/v4.45/pic32mx/include/pic32m-libs
    ```

1. Add those "fixed" `realpath`s to the `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/.vscode/settings.json` file as follows: 

    ```jsonc
    {
        "C_Cpp.default.defines": [
        ],
        "C_Cpp.default.includePath": [
        "gs_pic32mx7_basic_uart/src",
        "gs_pic32mx7_basic_uart/src/config/default",
        "/opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259/include",
        "/opt/microchip/xc32/v4.45/pic32mx/include",
        "/opt/microchip/xc32/v4.45/pic32mx/include/musl",
        "/opt/microchip/xc32/v4.45/lib/gcc/pic32mx/8.3.1/include",
        "/opt/microchip/xc32/v4.45/pic32mx/include/pic32m-libs",
        ],
        "files.associations": {
        }
    }
    ```

    Now, the VSCode indexer can find all of the include files in your project!

1. Open the project/directory in VSCode.

    ```bash
    code path/to/eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L
    ```

    This opens up "root" directory in which the `.vscode` folder we made is found, so that VSCode will find and use the `.vscode/settings.json` file we made.

1. Let's test it out now, and also delve a littler deeper to find some necessary `define`s/macros too. 

    Open up the `ChipKIT_Max32_PIC32MX795F512L/gs_pic32mx7_basic_uart/src/main.c` file in VSCode.

    Ctrl+click on `#include <stddef.h>`. Because we added the above include paths to the `.vscode/settings.json` file, VSCode will find and jump to this file here: `/opt/microchip/xc32/v4.45/pic32mx/include/musl/stddef.h`. 

    Use Alt + Left-arrow to go back to the main.c file. Ctrl+click on `#include <stdbool.h>`. It will find and jump to it here: `/opt/microchip/xc32/v4.45/pic32mx/include/musl/stdbool.h`. 

    Go back. 

    Ctrl+click on `#include "definitions.h"`. It will find it here: `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/gs_pic32mx7_basic_uart/src/config/default/definitions.h`. 

    From there, Ctrl+click on `#include "peripheral/uart/plib_uart1.h"`. It will find it here: `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/gs_pic32mx7_basic_uart/src/config/default/peripheral/uart/plib_uart1.h`.

    From there, Ctrl+click on `#include "device.h"`. It will go here: `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/gs_pic32mx7_basic_uart/src/config/default/device.h`. 

    This `device.h` file contains the following includes: 
    ```c
    #include <xc.h>
    #include <sys/attribs.h>
    #include "toolchain_specifics.h"
    ```

    Ctrl+click on `<xc.h>` and it will go here: `/opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259/include/xc.h`. 

    Ctrl+click on `#include <xc-pic32m.h>` and it will go here: `/opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259/include/xc-pic32m.h`. 

    This file contains lines like this: 
    ```c
    #elif defined(__32MX775F512H__)
    #  include <proc/p32mx775f512h.h>
    #elif defined(__32MX775F512L__)
    #  include <proc/p32mx775f512l.h>
    #elif defined(__32MX795F512H__)
    #  include <proc/p32mx795f512h.h>
    #elif defined(__32MX795F512L__)
    #  include <proc/p32mx795f512l.h>
    #elif defined(__32M4KCORE__)
    #  include <proc/p32m4kcore.h>
    #elif defined(__32MXGENERIC__)
    #  include <proc/p32mxgeneric.h>
    ```

    So, let's define the following macros for our chip: 
    ```c
    __32MX795F512L__     # the one I see just above in `xc-pic32m.h`
    __PIC32MX795F512L__  # one I've seen elsewhere
    ```

    Let's also define `__LANGUAGE_C__`. 

1. So, add the following defines to your `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/.vscode/settings.json` file as well: 
    ```jsonc
        "C_Cpp.default.defines": [
            // "GS_TEST=1",
            // "__cplusplus",
            // "__PIC32MZ__",
            // "__32MZ2048EFM144__",
            // "__LANGUAGE_ASSEMBLY__",
            "__LANGUAGE_C__",
            // "__LANGUAGE_C_PLUS_PLUS",
            // "__DEBUG",
            "__32MX795F512L__",
            "__PIC32MX795F512L__",
        ],
    ```

1. Now, your `eRCaGuy_MPLABX/ChipKIT_Max32_PIC32MX795F512L/.vscode/settings.json` file will have something like the following: 
    ```jsonc
    {
        "C_Cpp.default.defines": [
            "__LANGUAGE_C__",
            "__32MX795F512L__",
            "__PIC32MX795F512L__",
        ],
        "C_Cpp.default.includePath": [
        "gs_pic32mx7_basic_uart/src",
        "gs_pic32mx7_basic_uart/src/config/default",
        "/opt/microchip/mplabx/v6.20/packs/Microchip/PIC32MX_DFP/1.5.259/include",
        "/opt/microchip/xc32/v4.45/pic32mx/include",
        "/opt/microchip/xc32/v4.45/pic32mx/include/musl",
        "/opt/microchip/xc32/v4.45/lib/gcc/pic32mx/8.3.1/include",
        "/opt/microchip/xc32/v4.45/pic32mx/include/pic32m-libs",
        ],
        "files.associations": {
        }
    }
    ```

1. Done. 

    That's the idea of how to enable VSCode to index your system includes and all includes brought in by your compiler! 

    This works for *any* gcc or clang-based compiler, not just the Microchip XC32 PIC32 compiler. 
