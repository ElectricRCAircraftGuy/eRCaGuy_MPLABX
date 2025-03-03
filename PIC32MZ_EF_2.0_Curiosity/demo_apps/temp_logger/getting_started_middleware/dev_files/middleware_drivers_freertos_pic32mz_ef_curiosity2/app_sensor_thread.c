/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_sensor_thread.c

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

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "app_sensor_thread.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define APP_SENSOR_I2C_CLOCK_SPEED             100000
#define APP_SENSOR_I2C_SLAVE_ADDR              0x004B
#define APP_SENSOR_TEMPERATURE_REG_ADDR        0x00
#define APP_SENSOR_SAMPLING_RATE_IN_MSEC       1000
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_SENSOR_THREAD_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_SENSOR_THREAD_DATA app_sensorData;

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

/******************************************************************************
  Function:
    int8_t APP_SENSOR_CalcTemperature ( uint8_t* )

  Remarks:
    This function returns the temperature in degree Fahrenheit.
 */
int8_t APP_SENSOR_CalcTemperature(uint8_t* pRawValue)
{
    int16_t temp;
    
    temp = (pRawValue[0] << 8) | pRawValue[1];
    if ((temp & 0x8000) == 0)
    {
        temp = (temp >> 7) * 0.5;
    }
    else
    {
        temp = (~temp) + 1;
        temp = (temp >> 7);
        temp *= -0.5;
    }
        
    temp = (temp * (float)9/5) + 32;
    
    return (int8_t)temp;
}


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_SENSOR_THREAD_Initialize ( void )

  Remarks:
    See prototype in app_sensor_thread.h.
 */

void APP_SENSOR_THREAD_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_sensorData.isInitDone = false;
}


/******************************************************************************
  Function:
    void APP_SENSOR_THREAD_Tasks ( void )

  Remarks:
    See prototype in app_sensor_thread.h.
 */

void APP_SENSOR_THREAD_Tasks ( void )
{

    uint8_t registerAddr = APP_SENSOR_TEMPERATURE_REG_ADDR;                
    uint8_t strlen;                        
    
    /* Open the drivers if not already opened */
    if (app_sensorData.isInitDone == false)
    {
        /* Open I2C driver to interact with the temperature sensor */
        
        
        if (app_sensorData.i2cHandle != DRV_HANDLE_INVALID)
        {
            /* Got valid handle, now configure the I2C clock speed for sensor */
            app_sensorData.i2cSetup.clockSpeed = APP_SENSOR_I2C_CLOCK_SPEED;
            
            /* Setup I2C transfer @ 100 kHz to interface with Sensor */    
            
        }
        else
        {
            /* Handle error */
        }
                                                  
        /* Open the USART driver to print temperature values */
        
             
        if (app_sensorData.usartHandle != DRV_HANDLE_INVALID )
        {
            /* All drivers opened successfully */
            app_sensorData.isInitDone = true;
        }
        else
        {
            /* Handle Error */
        }
    }
                                                       
    /* Allow other threads to run until it's time to read temperature */
    

    LED1_Toggle();
    
    /* Submit a blocking I2C write-read request (for temperature). */           
     
    {            
        app_sensorData.temperature = APP_SENSOR_CalcTemperature(app_sensorData.i2cRxBuffer);

        app_sensorData.eventInfo.eventType = EVENT_TYPE_TEMP_WRITE_REQ;
        app_sensorData.eventInfo.eventData = app_sensorData.temperature;

        /* Use FreeRTOS Queue to notify the temperature write event and temperature 
         * value to EEPROM thread. */        
        
        
        strlen = sprintf((char*)app_sensorData.usartTxBuffer, "Temperature = %d F\r\n", app_sensorData.temperature);       
        
        /* Print the temperature value by submitting a blocking USART write request. */        
        
    }            

}
 

/*******************************************************************************
 End of File
 */
