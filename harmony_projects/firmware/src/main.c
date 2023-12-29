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
#include <stdio.h>                      // snprintf
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
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
        for (int i = 0; i < 100000000; i++)
        {
            __asm__("nop");
        }

        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

