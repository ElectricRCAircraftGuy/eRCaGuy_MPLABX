This file is part of eRCaGuy_MPLABX: https://github.com/ElectricRCAircraftGuy/eRCaGuy_MPLABX

See: 
1. https://chipkit.net/wiki/index.php?title=chipKIT_Max32
1. https://github.com/sergev/qemu/wiki
1. Serge Vakulenko's mcu work:
    1. https://github.com/sergev/vak-opensource/tree/master/microcontrollers/pic32-max32
    1. https://github.com/ElectricRCAircraftGuy/vak-opensource/tree/master/microcontrollers/pic32-max32


# Steps

Note: useful prompt for GitHub Copilot: 

> MCC configure UART on a newly-created project.

My steps: 

1. Create new project. 
1. Open "CM" "MCC Content Manager" and update to latest: 
    1. Click "Select Latest Versions", then Apply. 
    1. Close the MCC Content Manager.
1. Open MCC and configure the project: 
    1. Tools --> Embedded --> "MPLAB Code Configurator v5 Open/Close"
    1. Add and configure the UART:
        1. "Resource Management (MCC)" tab at far top-left, next to "Projects" and "Files" tabs --> "Project Resources" tab --> "Device Resources" section underneath that --> Libraries -> Harmony -> Peripherals -> UART -> click the "+" next to UART1. 
        1. In the "Project Graph" tab, there is now a UART1 box/block. Select it. Resize the right-hand pane to show everything. Check your baud rate and settings. I left the defaults, with 115200 baud, 8 data bits, no parity, 1 stop bit, no parity. 
    1. Configure the UART Tx and Rx pins in the pin manager: 
        1. "Project Graph" tab --> click the "Plugins" dropdown menu --> Pin Configuration. This opens the following new tabs: 
            - Pin Diagram
            - Pin Table
            - Pin Settings
        1. 


    1. Click the "Generate" button at the top. 

