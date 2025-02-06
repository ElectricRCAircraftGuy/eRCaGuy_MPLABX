/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdbool.h>                    // Defines true
#include <stddef.h>                     // Defines NULL
#include <stdint.h>                     // uint32_t, etc.
#include <stdio.h>                      // snprintf
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
/*

GS notes

Board:
1. The dev kit is "PIC32MZ EF Starter Kit with Crypto Engine" DM320007-C
    1. https://www.microchip.com/en-us/development-tool/dm320007-c 
    1. Mouser - https://mou.sr/41nGuBJ
    1. DigiKey - https://www.digikey.com/short/009p3pbq 
1. The debugger is "MPLAB PICKIT5 in-circuit debugger"
    1. https://www.microchip.com/en-us/development-tool/PG164150 
    1. Mouser - https://mou.sr/3uVoHpE 
    1. DigiKey - https://www.digikey.com/short/m0db14nd 
1. And the "PICKIT5 target adapter" (so nobody needs to make a cable)
    1. https://www.microchip.com/en-us/development-tool/ac102015 
    1. Mouser - https://mou.sr/47VxPJo
    1. DigiKey - https://www.digikey.com/short/mv259545

References:
1. [Starter Guide] PIC32MZ Embedded Connectivity with Floating Point Unit (EF) Starter Kit User’s Guide:
   https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/UserGuides/70005230B.pdf

Pinout:
See Starter Guide p20: J12 conections. 
1. J12 pin 6 (GND)      --> UART GND
1. J12 pin 8 (UART6 Tx) --> UART Rx

Baud rate: 115200

*/


// 1 second is 50M clock cycles, so 1 us is 50 clock cycles
// TODO: read the clock speed from the device somehow and use this to calculate the clock cycles per
// us, so that this automatically works even if we change the clock speed. 
const uint32_t CLOCK_CYCLES_PER_US = 50;
const uint32_t MAX_DELAY_ALLOWED_US = UINT32_MAX/CLOCK_CYCLES_PER_US;

// Delay (busy wait) this number of microseconds. 
// - the max delay allowed is `MAX_DELAY_ALLOWED_US` = (2^32 - 1) / 50 = 85899345 us = 85.899 sec.
// - Returns the actual delay in microseconds.
uint32_t delay_us(uint32_t delay_us)
{
    if (delay_us > MAX_DELAY_ALLOWED_US)
    {
        // TODO: log error

        delay_us = MAX_DELAY_ALLOWED_US;
    }

    uint32_t delay_ticks = delay_us * CLOCK_CYCLES_PER_US;

    for (uint32_t i = 0; i < delay_ticks; i++)
    {
        __asm__("nop");
    }

    return delay_us;
}

#define US_PER_MS 1000

// Delay (busy wait) this number of milliseconds.
// - the max delay allowed is (2^32 - 1) ms = 4294967295 ms = 4294967.295 sec = 49.71 days.
void delay_ms(uint32_t delay_ms)
{
    for (uint32_t i = 0; i < delay_ms; i++)
    {
        delay_us(US_PER_MS);
    }
}

int main (void)
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    char str[] = "Hello World!\n";
    char buf[100];

    size_t i = 0;
    while ( true )
    {
        int num_chars = snprintf(buf, sizeof(buf), "%u: Hello World!\n", i);
        i++;
        UART6_Write(buf, num_chars);

        // UART6_Write(str, sizeof(str)); 
        (void)str; // prevent compiler "unused" error

        // Use nops to busy wait ~1 second
        delay_ms(1000);

        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

/*
EXAMPLE OUTPUT:

1639: Hello World!
1640: Hello World!
1641: Hello World!
1642: Hello World!
1643: Hello World!
1644: Hello World!
1645: Hello World!
1646: Hello World!
1647: Hello World!
1648: Hello World!
1649: Hello World!
*/
