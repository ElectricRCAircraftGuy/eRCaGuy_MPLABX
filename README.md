
# References

1. YouTube - Create Your First Project with PIC32MZ EF using MPLAB® Harmony v3 - https://www.youtube.com/watch?v=sW-yS2FHI54
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

    Under pin settings, the UART pin should be pin 14: RG6: set it to `U6TX`. 

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
