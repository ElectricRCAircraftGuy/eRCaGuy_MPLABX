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
    1. _Note: to see everything in the MCC, a large, 2k or 4k 32" monitor is recommended. The windowing layout isn't very friendly to lower-resolution monitors._ 
    1. Tools --> Embedded --> "MPLAB Code Configurator v5: Open/Close"
    1. Add and configure the UART:
        1. "Resource Management (MCC)" tab at far top-left, next to "Projects" and "Files" tabs --> "Project Resources" tab --> "Device Resources" section underneath that --> Libraries -> Harmony -> Peripherals -> UART -> click the "+" next to UART1. 
        1. In the "Project Graph" tab, there is now a UART1 box/block. Select it. Resize the right-hand pane to show everything. Check your baud rate and settings. I left the defaults, with 115200 baud, 8 data bits, no parity, 1 stop bit, no parity. 
    1. Configure the UART Tx and Rx pins in the pin manager: 
        1. "Project Graph" tab --> click the "Plugins" dropdown menu --> Pin Configuration. This opens the following new tabs: 
            - Pin Diagram
            - Pin Table
            - Pin Settings
        1. In the Pin Table tab: 
            1. In the top-left corner, click the "Package" drop-down and select the correct IC package for your chip. Ex: TQFP. 
            1. Look at the "Module" column on the left, and scroll down and find "UART1". Then look to the right to find the corresponding pins which can be used for the UART1 Tx (`U1TX`) and Rx (`U1RX`) pins. They will be blue boxes. Click them to make them green to select them. The only options in this case are pins `RF2` (which becomes `U1RX`) and `RF8` (which becomes `U1TX`).
        1. In the "Pin Diagram" tab, you can now see two green pins in the bottom-right of the TQFP IC package which are labeled `U1TX` and `U1RX`. These are the pins you just selected in the Pin Table tab.
        1. In the "Pin Settings" tab, check that the pin settings are configured as you desire: 
            1. _Note: there's nothing to do here in our case right now, so you can skip this section if you want. Or, even better, continue reading to learn with me how to use this tab!_
            1. Scroll down, looking at the "Function" column, until you see the `U1RX` and `U1TX` pins. They are pins `52` and `53`, respectively. You can click the `U1RX` and `U1TX` labels in the "Function" column to change them to something else if you want. We won't, however. The "Voltage Tolerance" columns shows these pins are 5V tolerant. See if any other columns allow you to edit the pin. 
            
            1. For example, we can also check the box for **"Open Drain"** if we want, for either of these pins. The Google Search AI for ["what is "open drain" on an mcu?"](https://www.google.com/search?q=what+is+%22open+drain%22+on+an+mcu%3F&oq=what+is+%22open+drain%22+on+an+mcu%3F&gs_lcrp=EgZjaHJvbWUyBggAEEUYOdIBCDQ4ODZqMGo0qAIAsAIB&sourceid=chrome&ie=UTF-8#vhid=IW__aZTmYBsr-M&vssid=l) tells us the following, which I know to be correct: 

                > An "open drain" on an MCU refers to a type of output pin configuration where the internal transistor connected to the pin can only pull the output voltage low to ground, meaning it can only actively drive a low signal, leaving the pin floating (high impedance) when not actively driven, requiring an external pull-up resistor to define a high logic state; essentially acting like a switch that can only connect the output to ground when activated, not to a high voltage. 
                > 
                > ### Key points about open drain:
                > 
                > #### Limited functionality:
                > Unlike a standard push-pull output, an open drain pin can only actively drive a low signal. 
                > 
                > #### Pull-up resistor needed:
                > To define a high logic state on an open drain pin, an external pull-up resistor is required, which pulls the pin high when the output is not actively driven low. 
                > 
                > #### Applications:
                > Open drain outputs are often used in situations where multiple devices need to share a single communication line, like in I2C or One-Wire protocols, as it prevents conflicts when multiple devices try to drive the line simultaneously. 

                Note that "Open Drain" refers to an MCU which uses MOSFET transistors internally. If the MCU uses BJT transistors internally, then the equivalent of "Open Drain" is called "Open Collector".

                Remember: 
                - MOSFET -> Gate, _Drain_, Source
                - BJT -> Base, _Collector_, Emitter

                My understanding is that each pin has an internal push-pull half-H-bridge mechanism, like this: 
                ```
                   INTERNAL CIRCUITRY                  EXTERNAL CIRCUITRY
                                           +V
                                            | 
                gate/base_driver----high_side_transistor
                                            | 
                                       external_pin-----your_circuitry
                                            | 
                gate/base_driver----low_side_transistor
                                            | 
                                           GND
                ```

                - In normal push-pull configuration, to drive the pin HIGH, the high-side transistor is turned on, which connects the pin to `+V`. This is an active drive HIGH.
                - In normal push-pull configuration, to drive the pin LOW, the low-side transistor is turned on, which connects the pin to `GND`.
                - If both transistors are off, then the pin is in a high-impedance "floating" state. 
                - In "open drain" configuration, the high-side transistor drain is disconnected from the pin (really, this just means they don't turn on this transistor when the pin is set to HIGH, I think), so that setting the pin to a HIGH state leaves it disconnected, or floating, while setting the pin to a LOW state drives it LOW by connecting it to GND. 
                    - Therefore, in "open drain" or "open collector" mode, the pin is a high-impedance, passive HIGH, and an active drive LOW.
                
    1. Generate the code:
        1. "Resource Management (MCC)" tab at far top-left, next to "Projects" and "Files" tabs --> click the "Generate" button to auto-generate the code.
1. Close MCC: 
    1. "Tools" --> "Embedded" --> "MPLAB Code Configurator v5: Open/Close"
    1. If it freezes (which happens a lot :(), type `xkill` in another terminal, then click the window to kill it. 
