This file is part of eRCaGuy_MPLABX: https://github.com/ElectricRCAircraftGuy/eRCaGuy_MPLABX

See: 
1. https://www.microchip.com/en-us/development-tool/dm320007-c
1. [../ChipKIT_Max32_PIC32MX795F512L](../ChipKIT_Max32_PIC32MX795F512L)


# Steps

For more details, see also: [../ChipKIT_Max32_PIC32MX795F512L](../ChipKIT_Max32_PIC32MX795F512L)

1. Open CM (MCC _Content Manager_) and update to latest. 
    1. Click "Select Latest Versions", then Apply. 
    1. Close the MCC Content Manager.
1. Create new project.
    1. Microchip Embedded --> Application Project(s). 
    1. Device: PIC32MZ2048EFM144.
    1. Tool: Simulator
    1. Compiler: XC32 v4.45
    1. Project Name: basic_uart
    1. Encoding: UTF-8
    1. Click "Finish". 
1. Open MCC and configure the project. 
    1. Reference [pg. 20 here for the board pinout](https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/blob/main/Datasheets/Microchip/Starter_Kits_and_Boards/PIC32MZ_Embedded_Connectivity_w_FPU/PIC32MZ%20Embedded%20Connectivity%20with%20Floating%20Point%20Unit%20(EF)%20Starter%20Kit%20User%E2%80%99s%20Guide-70005230B_GS_edit%20(qpdf%20--decrypt).pdf)
    1. Device Resources --> Libraries --> Harmony --> Peripherals --> UART --> click the "+" next to UART4 to add it.
    1. Open Pin Configuration: "Pin Settings" tab: 
        1. Assign Pin 61, RB14, to U4RX. 
        1. Assign Pin 14, RG6, to U4TX.
    1. Generate the code.
1. Close MCC: Tools --> Embedded --> "MPLAB Code Configurator v5: Open/Close"
    1. It will probably freeze. Use `xkill` to kill it: type `xkill` in another terminal, then click the window to kill it. 
