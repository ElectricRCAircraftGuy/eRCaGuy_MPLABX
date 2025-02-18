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

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdio.h>                      // GS: snprintf()
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

#define MHZ     80              /* CPU clock in MHz. */
#define PIC32_USTA_TRMT		0x00000100 /* Transmit shift register is empty (read-only) */
#define C0_COUNT	9	/* Processor cycle count */

/*
 * Read C0 coprocessor register.
 */
#define mfc0(reg, sel) ({ int __value;				\
	asm volatile (						\
	"mfc0	%0, $%1, %2"					\
	: "=r" (__value) : "K" (reg), "K" (sel));		\
	__value; })

/*
GS borrowed from: "vak-opensource/microcontrollers/pic32-max32/uart.c"

 * Delay for a given number of microseconds.
 * The processor has a 32-bit hardware Count register,
 * which increments at half CPU rate.
 * We use it to get a precise delay.
 */
void udelay(unsigned usec)
{
    unsigned now = mfc0(C0_COUNT, 0);
    unsigned final = now + usec * MHZ / 2;

    for (;;) {
        now = mfc0(C0_COUNT, 0);

        /* This comparison is valid only when using a signed type. */
        if ((int) (now - final) >= 0)
            break;
    }
}

/*
 * Send a byte to the UART transmitter, with interrupts disabled.
 */
void putch(unsigned char c)
{
    /* Wait for transmitter shift register empty. */
    while (! (U1STA & PIC32_USTA_TRMT))
    {
        continue;
    }

again:
    /* Send byte. */
    U1TXREG = c;

    /* Wait for transmitter shift register empty. */
    while (! (U1STA & PIC32_USTA_TRMT))
        continue;

    if (c == '\n') {
        c = '\r';
        goto again;
    }
}

/*
 * Send a string to UART.
 */
void putstr(const char *str)
{
    while (*str)
        putch(*str++);
}

void setup()
{
    // printf("hello\n");

    const char str[] = "\nRunning setup()...\n";
    putstr(str);
    // UART1_Write((char*)str, sizeof(str));
}

void loop()
{
    static uint32_t loop_counter = -1;
    loop_counter++;
    // const char str[] = ".";
    // putstr(str);

    char buf[100]; 
    snprintf(buf, sizeof(buf), "hello world %i\n", loop_counter);

    putstr(buf);
    // UART1_Write((char*)str, sizeof(str));
    
    udelay(1000000);  // 1 second

}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    setup();

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

        loop();
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

