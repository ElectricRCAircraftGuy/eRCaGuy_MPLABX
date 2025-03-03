/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_user_input_thread.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app_user_input_thread.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_USER_INPUT_THREAD_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_USER_INPUT_THREAD_DATA app_user_inputData;
QueueHandle_t eventQueue;
// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_USER_INPUT_THREAD_Initialize ( void )

  Remarks:
    See prototype in app_user_input_thread.h.
 */

void APP_USER_INPUT_THREAD_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_user_inputData.isInitDone = false;

    eventQueue = xQueueCreate( 3, sizeof(EVENT_INFO) );
    if (eventQueue == NULL)
    {
        /* Handle error condition. Not sufficient memory to create Queue */
    }      
}


/******************************************************************************
  Function:
    void APP_USER_INPUT_THREAD_Tasks ( void )

  Remarks:
    See prototype in app_user_input_thread.h.
 */

void APP_USER_INPUT_THREAD_Tasks ( void )
{
    uint8_t usartData;   
    
    /* Open the drivers if not already opened */
    if (app_user_inputData.isInitDone == false)
    {
        /* Open the USART driver to read user key press */

        
        if (app_user_inputData.usartHandle == DRV_HANDLE_INVALID)
        {
            /* Handle Error */
        }    
        else
        {
            /* All drivers opened successfully */
            app_user_inputData.isInitDone = true;
        }
    }
                        
    /* Submit a blocking USART read request (user input). */    

    {
        app_user_inputData.eventInfo.eventType = EVENT_TYPE_TEMP_READ_REQ;
        app_user_inputData.eventInfo.eventData = usartData;

        /* Use FreeRTOS queue to notify the EEPROM task to print the logged temperature values */

    }
    else
    {
        /* Handle error condition */
    }
}


/*******************************************************************************
 End of File
 */
