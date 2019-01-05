/* ========================================
 * V0.1
 * Author: Robert Barron
 * WIP, not functional
 * Use at own risk
 *
 * Functional monitoring: VBATT, Shunt amps, thermistor temperatures
 * Does not currently protect
 *
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "math.h"
//#include <stdlib.h>

#define BUFFER_LEN  128
// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// the value of the 'other' resistor for the thermistors
#define SERIESRESISTOR 10000    

#define VBATT_DIVIDER 0.01038 //voltage divider measured value for vbat readings. VBATT = mV*VDIVIDER/10. Resistors ~350k and ~50k

int TS1_counts = 0;
int TS2_counts = 0;
float TS1_volts = 0;
float TS2_volts = 0;
float TS1_res = 0;
float TS2_res = 0;
float TS1_temp = 0; // degrees F
float TS2_temp = 0;

int v_bat = 0;//mVolts
float v_amps = 0.0;//Amps

uint8 fault_status = 0;
//bool fault = false;
uint8 buffer[BUFFER_LEN];

long mapCoor(long x, long in_min, long in_max, long out_min, long out_max);

void checkTemperature();//TODO: Check battery temperature and temperature rate of change

//check for fault conditions
void faultStatus()
{
    uint32 ov_fault = 0;
    uint32 uv_fault = 0;
    uint32 oc_fault = 0;
    uint32 temp_fault = 0;
    fault_status = PowerMonitor_GetFaultSource(); 
    
    if(fault_status)
    {
        pgood_Write(0);//TODO: pgood will disable charger and load mosfet pins
    }

    ov_fault = PowerMonitor_GetOVFaultStatus();
    uv_fault = PowerMonitor_GetUVFaultStatus();
    oc_fault = PowerMonitor_GetOCFaultStatus();
    if(v_amps < -50.0 || v_amps > 50.0)
    {
        oc_fault = 1;   
    }
    
    if(ov_fault || uv_fault || oc_fault || temp_fault)
    {
        pgood_Write(0);   
    }

    //Display fault status on lcd screen
    TFTSHIELD_1_SetCursor(0,120);
    //TFTSHIELD_1_FillRect(0, 120, 100,40, YELLOW);
    TFTSHIELD_1_PrintString("STATUS");
    TFTSHIELD_1_Write('\n');
    TFTSHIELD_1_PrintString("OV   UV   OC  TEMP");

    if(ov_fault)
    {
        TFTSHIELD_1_FillRect(220, 160, 20,20, RED);
    }
    else
    {
        TFTSHIELD_1_FillRect(220, 160, 20,20, GREEN);
    }
    if(uv_fault)
    {
        TFTSHIELD_1_FillRect(185, 160, 20,20, RED);
    }
    else
    {
        TFTSHIELD_1_FillRect(185, 160, 20,20, GREEN);
    }
    if(oc_fault)
    {
        TFTSHIELD_1_FillRect(145, 160, 20,20, RED);
    }
    else
    {
        TFTSHIELD_1_FillRect(145, 160, 20,20, GREEN);
    }
    if(temp_fault)
    {
        TFTSHIELD_1_FillRect(105, 160, 20,20, RED);
    }
    else
    {
       TFTSHIELD_1_FillRect(105, 160, 20,20, GREEN);   
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Thermistor_ADC_Start();
    Thermistor_ADC_StartConvert();
    //CalDAC_Start();
    Clock_1_SetDividerValue(24);
    CyDelay(10);
    //TFTSHIELD_1_StartTouch();
    bool touch_en = 0;
    uint16_t x, y;
    uint8_t z, buf;
    
    PowerMonitor_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    /* The size of the buffer is equal to maximum packet size of the 
    *  IN and OUT bulk endpoints. 
    */
    while(!TFTSHIELD_1_StartTouch())
    {
       
    }
    //touch_en = 1;
    Clock_1_SetDividerValue(1);
    CyDelay(10);
    TFTSHIELD_1_Start();
    
    TFTSHIELD_1_FillScreen(BLACK);
    //start at 0,0 for text
    TFTSHIELD_1_SetCursor(0,0);
    TFTSHIELD_1_SetTextColor(WHITE);  
    TFTSHIELD_1_SetTextSize(2);
    
    //landscape orientation
    TFTSHIELD_1_SetRotation(0);
    TFTSHIELD_1_PrintString("GnarV Battery Monitor 1.0\n");
    CyDelay(100);
    PowerMonitor_Calibrate();
    char8 *parity[] = { "None", "Odd", "Even", "Mark", "Space" };
    char8 *stop[] = { "1", "1.5", "2" };
    
    uint16 count_str;
    uint8 temp_buffer[10];
    char8 lineStr[20];
    uint8 state;
    int i = 0;
    
    /* Start USBFS Operation with 5V operation */
    //USBUART_2_Start(0u, USBUART_2_5V_OPERATION);

    /* Wait for Device to enumerate */
    //while(!USBUART_2_GetConfiguration());

    /* Enumeration is done, enable OUT endpoint for receive data from Host */
    //USBUART_2_CDC_Init();

    
    //CyDelay(10000);
    count_str = sprintf(buffer, "Power on \n\r");
    //while(USBUART_2_CDCIsReady() == 0u);    /* Wait till component is ready to send more data to the PC */ 
    //USBUART_2_PutData(buffer, count_str);       /* Send data back to PC */
    
    PWM_1_Start();
    
    for(;;)
    {
        //Get thermistor adc values. Convert Counts -> Volts -> Resistance -> Temp
        Thermistor_ADC_IsEndConversion(Thermistor_ADC_WAIT_FOR_RESULT); //wait for adc result
        TS1_counts = Thermistor_ADC_GetResult16(0);//get counts
        TS2_counts = Thermistor_ADC_GetResult16(1);
        TS1_volts = Thermistor_ADC_CountsTo_Volts(TS1_counts);//get volts
        TS2_volts = Thermistor_ADC_CountsTo_Volts(TS2_counts);
        
        TS1_res = (2800 / (float)TS1_counts)  - 1.0;     // (4095/ADC - 1) get resistance. 3.3V Ref = ~2800 max counts
        TS1_res = SERIESRESISTOR / TS1_res;  // 10K / (4095/ADC - 1)
        
        TS2_res = (2800 / (float)TS2_counts)  - 1.0;     // (4095/ADC - 1) get resistance
        TS2_res = SERIESRESISTOR / TS2_res;  // 10K / (4095/ADC - 1)
        
        //get temperature, C/100
        TS1_temp = Thermistor_1_GetTemperature((int)TS1_res);
        TS2_temp = Thermistor_1_GetTemperature((int)TS2_res);
        
        TS1_temp = TS1_temp/100; // convert to degrees C
        TS1_temp = (TS1_temp*9/5) + 32; // convert to degrees F
        TS2_temp = TS2_temp/100;
        TS2_temp = (TS2_temp*9/5) + 32;
        
        //power monitor. Measure battery voltage and charge/discharge amps
        v_bat = PowerMonitor_GetConverterVoltage(1);
        v_amps = PowerMonitor_GetConverterCurrent(2);
        
        //dtostrf( TS1_volts, 3, 4, temp_buffer);
        //count_str = sprintf(buffer, "float:  %.2f", TS1_volts);
        
        //print values to lcd screen
        //temperature
        TFTSHIELD_1_SetCursor(0,40);
        TFTSHIELD_1_FillRect(0, 35, 120,40, BLACK); //Clear section of screen to print to
        count_str = sprintf(buffer, "TS1 Temp: %.1f",TS1_temp); //print thermistor voltages
        TFTSHIELD_1_PrintString(buffer);
        TFTSHIELD_1_Write('\n');
        count_str = sprintf(buffer, "TS2 Temp: %.1f",TS2_temp); //print thermistor voltages
        TFTSHIELD_1_PrintString(buffer);
        
        
        //while(USBUART_2_CDCIsReady() == 0u);
        //USBUART_2_PutData(buffer, count_str);
        CyDelay(10);
        
        count_str = sprintf(buffer, "Batt Volts: %.1f   Batt Amps: %.1f \n",(float)v_bat*VBATT_DIVIDER,v_amps); //print battery voltage and current
        TFTSHIELD_1_SetCursor(0,80);
        TFTSHIELD_1_FillRect(0, 75, 110,40, BLACK);
        TFTSHIELD_1_PrintString(buffer);
        
        //while(USBUART_2_CDCIsReady() == 0u);
        //USBUART_2_PutData(buffer, count_str);
        
        faultStatus();//check fault status
        
        CyDelay(500);
    }
}

/* [] END OF FILE */
