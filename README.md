This file is part of eRCaGuy_MPLABX: https://github.com/ElectricRCAircraftGuy/eRCaGuy_MPLABX


# See also

1. [vscode_settings_includes_for_indexing_PIC32_projects.md](vscode_settings_includes_for_indexing_PIC32_projects.md) - How to set up VSCode to index and search the Microchip XC32 compiler's include files.


# References

1. [How to Set up the Tools Required to Get Started with MPLAB® Harmony v3 and MCC](https://www.youtube.com/watch?v=0rNFSlsVwVw)
1. [Create Your First Project with PIC32MZ EF Using MPLAB® Harmony v3 and MCC](https://www.youtube.com/watch?v=Z-8srAI8jow)
    1. [CURIOSITY PIC32MZ EF 2.0 DEVELOPMENT BOARD](https://www.microchip.com/en-us/development-tool/dm320209)


## Specific references for the instructions below

1. YouTube - Create Your First Project with PIC32MZ EF using MPLAB® Harmony v3 - https://www.youtube.com/watch?v=sW-yS2FHI54
    Potential new videos to look at (posted as replies to [my comment](https://www.youtube.com/watch?v=sW-yS2FHI54&lc=UgxTfjXbYMmejhx1Hb54AaABAg)): 
    1. [NEW VIDEO!] https://www.youtube.com/watch?v=Z-8srAI8jow
1. https://www.microchip.com/en-us/tools-resources/configure/mplab-harmony
    1. Creating a "Hello World" Application on SAM Microcontrollers Using MPLAB Harmony Configurator (MHC) - http://ww1.microchip.com/downloads/en/DeviceDoc/Creating_Hello_World_%20Application_on_SAM_Using_MHC_DS90003231A.pdf
1. Some of my datasheets here: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/tree/main/Datasheets/Microchip
    1. Starter kit: https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/tree/main/Datasheets/Microchip/PIC32MZ2048EFM144/embedded_starter_kit

Using this dev kit: https://www.microchip.com/en-us/development-tool/dm320007-c, the `eRCaGuy_MPLABX/harmony_projects/firmware/harmony_test1.X` project works! 

Harmony is no longer supported. See: https://forum.microchip.com/s/topic/a5C3l000000BoKjEAK/t390653

Solution: 
1. Download this git repo manually: https://github.com/Microchip-MPLAB-Harmony/mhc

    Ex:
    ```bash
    mkdir -p ~/dev/Microchip-MPLAB-Harmony
    cd ~/dev/Microchip-MPLAB-Harmony
    git clone https://github.com/Microchip-MPLAB-Harmony/mhc.git
    ```

1. In MPLAB X IDE v6.15, go to Tools --> Options --> Plugins --> ensure that "Harmony Repository" is set to https://github.com/Microchip-MPLAB-Harmony, and that the "Harmony Content Path" is set to the path you just created above: `~/dev/Microchip-MPLAB-Harmony`.

1. Then, open the code configurator: Tools --> Embedded --> "MPLAB Code Configurator v5: Open/Close"

1. Then follow the steps in the video above (more or less--they don't match quite right).

    In the "Project Graph" tab --> click the "Plugins" dropdown menu near the top --> select "Pin Configuration". This opens up 3 new tabs: 
    1. Pin Settings
    1. Pin Table
    1. Pin Diagram

    In the "Pin Settings" tab, find Pin Number 14, Pin ID `RG6`, and change its "Function" dropdown setting from "Available" to `U6TX`. This is what assigns that `RG6` pin `14`, which is J12 pin `8` on the development board, to the UART6 TX function.

    In the "Resource Management (MCC)" tab in the far top-left (near the normal "Projects" and "Files" tabs), under the "Project Resources" tab section, click the "Generate" button. This will generate the source code for you.
    
    When done, close the code configurator: Tools --> Embedded --> "MPLAB Code Configurator v5: Open/Close".

    _Note:_ the tool is bad and freezes a lot when trying to open or close it. If this happens, type `xkill` in a new terminal window, then click on the MPLAB X IDE window to kill the frozen process.

    Connect a USB serial UART ("console cable") to the dev kit, and connect it to your computer. Refer to DS70005230B, the start kit User's Guide, Table 2-3 p20. 

    - UART GND to dev kit GND (pin 6)
    - UART Rx to dev kit Tx (pin 8)

    Now, program the dev kit from MPLAB X IDE v6.15, and open a serial terminal to your USB serial UART. I use the legacy Arduino IDE 1.8.19 Serial Monitor for this. 

    Here is the output!--with \~1 second delay between each line: 
    ```
    0: Hello World!
    1: Hello World!
    2: Hello World!
    3: Hello World!
    4: Hello World!
    5: Hello World!
    6: Hello World!
    7: Hello World!
    8: Hello World!
    9: Hello World!
    10: Hello World!
    11: Hello World!
    12: Hello World!
    13: Hello World!
    14: Hello World!
    15: Hello World!
    16: Hello World!
    17: Hello World!
    18: Hello World!
    19: Hello World!
    20: Hello World!
    21: Hello World!
    22: Hello World!
    23: Hello World!
    24: Hello World!
    ```


# TODO

Todo/next steps (not necessarily in this order): 

1. [ ] Get the device to blink some LEDs at fixed intervals too.
1. [ ] Study and configure the clocks. 
1. [ ] Obtain high-resolution timestamps via the core timer.
1. [ ] Study and configure some interrupts and ISRs. 
1. [ ] Study and configure the timers/counters, and use them for: 
    1. [ ] PWM
    1. [ ] Input capture
    1. [ ] Output compare
    1. [ ] driving servos
1. [ ] Study and configure some DMA.
1. [ ] Add C++. 
1. [ ] Configure the build flags; ex: `-std=gnu++20`, `-Wall -Wextra -Werror`, etc.
1. [ ] Add FreeRTOS. 
1. [ ] Add an interactive CLI over serial. 
1. [ ] Improve the UART control to be more like Arduino, except do it better by overwriting the `printf()` function. All prints will be passed to a buffer, and a UART ISR will continually send what's in the buffer, just like in Arduino. If the buffer is full, `printf()` will block until the data is all printed, just like Arduino. 
1. [ ] Add an interactive CLI over telnet over Ethernet. 
1. [ ] Add a web server and have it host a web page.
1. [ ] Add Arduino-like libraries and functions. 
1. [ ] Add a `Makefile` to build from the command line. See: https://github.com/brunoleppe/PIC32-Project-Template
1. [ ] Build it using a custom-compiled XC32 compiler. See: https://github.com/ElectricRCAircraftGuy/Microchip_XC32_Compiler
