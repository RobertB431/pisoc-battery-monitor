/* ========================================
 * V0.2
 * Author: Robert Barron
 * WIP, not functional
 * Use at own risk
 *
 * Functional monitoring: VBATT, Shunt amps, thermistor temperatures
 * Can cutoff load with an external mosfet during a fault condition with the fault pin(gate) between battery(source) and load(drain)
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

//Fault conditions
#define UNDER_VOLTAGE 20.0 //20
#define OVER_VOLTAGE 24 //24
#define UNDER_TEMP 45.0 //45
#define OVER_TEMP 90.0 //90
#define OVER_CURRENT 50.0 //50 - Discharging
#define UNDER_CURRENT -80.0 //-80 - Charging

//BATTERY State of charge(SOC)
#define VBAT_BOTTOM 19.2 //0% charge
#define VBAT_TOP 25.2 //100% charge

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

float v_bat_actual = 0;
float v_amps_actual = 0;

float charge_percent = 0;

uint32 temp_fault = 0;
uint8 fault_status = 0;
//bool fault = false;
char buffer[BUFFER_LEN];
char soc_gauge[10];
uint8 InterruptCnt;
uint32 ov_fault = 0;
uint32 uv_fault = 0;
uint32 oc_fault = 0;

float mapCoor(float x, float in_min, float in_max, float out_min, float out_max);

void checkTemperature();//TODO: Check battery temperature and temperature rate of change

float checkSOC();//Check state of charge. Will require manual calibration

void displaySOC();//Display SOC battery gauge

void displayStatus();//Push status over UART to bluetooth dongle for viewing on a phone

void faultStatus();//check for fault conditions

CY_ISR(timerHandler) //send status over uart
{
	/* Read Status register in order to clear the sticky Terminal Count (TC) bit 
	 * in the status register. */
   	Timer_1_STATUS;
    
	/* Increment the Counter to indicate the keep track of the number of 
     * interrupts received */
    InterruptCnt++;
    
    displayStatus();
    
}

CY_ISR(pmonitor_eoc) //All status checks here. Ensures no blocking functions like UART prevent status check and disconnect
{
    faultStatus();//Check battery status    
}

//check for fault conditions
void faultStatus()
{
    //Get thermistor adc values. Convert Counts -> Volts -> Resistance -> Temp
    TS1_counts = 0;
    TS2_counts = 0;
    for(int i = 0; i < 5; i++)//avg thermistor readings
    {
        Thermistor_ADC_IsEndConversion(Thermistor_ADC_WAIT_FOR_RESULT); //wait for adc result
        TS1_counts += Thermistor_ADC_GetResult16(0);//get counts
        TS2_counts += Thermistor_ADC_GetResult16(1);
    }
    TS1_counts /= 5;
    TS2_counts /= 5;
    
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
    
    if(TS1_temp < UNDER_TEMP || TS1_temp > OVER_TEMP)//check temperature status
    {
        temp_fault = 1;
        TempPin_Write(0);   
    }
    else
    {
        temp_fault = 0;
        TempPin_Write(1);    
    }
    if(TS2_temp < UNDER_TEMP || TS2_temp > OVER_TEMP)
    {
        temp_fault = 1;
        TempPin_Write(0);   
    }
    else
    {
        temp_fault = 0;
        TempPin_Write(1);    
    }
    
    //power monitor. Measure battery voltage and charge/discharge amps
    v_bat = PowerMonitor_GetConverterVoltage(1);
    v_amps = PowerMonitor_GetConverterCurrent(2);
    
    v_bat_actual = (float)v_bat*VBATT_DIVIDER;
    v_amps_actual = v_amps;
    
    //fault_status = PowerMonitor_GetFaultSource(); 

    //ov_fault = PowerMonitor_GetOVFaultStatus();
    //uv_fault = PowerMonitor_GetUVFaultStatus();
    //oc_fault = PowerMonitor_GetOCFaultStatus();
    
    if(v_bat_actual > OVER_VOLTAGE)//check OV status. OV -> disconnect charger
    {
        ov_fault = 1;   
    }
    else
    {
        ov_fault = 0;   
    }
    
    if(v_bat_actual < UNDER_VOLTAGE)//check UV status. UV -> disconnect load
    {
        uv_fault = 1;   
    }
    else
    {
        uv_fault = 0;   
    }
    
    if(v_amps < UNDER_CURRENT || v_amps > OVER_CURRENT) // check OC status. OC -> disconnect load and charger 
    {
        oc_fault = 1;   
    }
    else
    {
        oc_fault = 0;   
    }
    
    if(ov_fault || uv_fault || oc_fault || temp_fault)//Check temp, OV, UV, OC
    {
        fault_Write(0);   
    }   
    else
    {
        fault_Write(1); //For debugging. Could consider requiring a controller reset if there is a fault condition.   
    }
}

//Check state of charge. Will require manual calibration
float checkSOC()
{
    //Starting with a linear voltage slope to calculate SOC. 
    charge_percent = mapCoor(v_bat_actual,VBAT_BOTTOM,VBAT_TOP,0.0,100.0);
    return charge_percent;
}

void displaySOC()//Display SOC battery gauge
{
    sprintf(soc_gauge,""); //clear battery gauge
    for(int i = 0; i < charge_percent/10; i++)
    {
        sprintf(soc_gauge,"%s+",soc_gauge); //print battery SOC
    }
}

void displayStatus()
{   
    //Push status over uart bluetooth. First fill message then push combined message at the end
    sprintf(buffer,"TS1 Temp: %.1f\n",TS1_temp); //print thermistor voltages
    sprintf(buffer,"%sTS2 Temp: %.1f\n",buffer,TS2_temp); //print thermistor voltages
    sprintf(buffer,"%sBatt Volts: %.1f\n",buffer,v_bat_actual); //print battery voltage
    sprintf(buffer,"%sBatt Amps: %.1f\n",buffer,v_amps); //print battery current
    
    sprintf(buffer,"%sBatt SOC: %.1f%%\n\n",buffer,checkSOC()); //print battery SOC
    /*displaySOC();
    sprintf(buffer,"%s|----------|\n",buffer); //print battery SOC
    sprintf(buffer,"%s%s",buffer,soc_gauge); //print battery SOC
    sprintf(buffer,"%s\n|----------|",buffer); //print battery SOC*/
    
    if(v_amps > 0)
    {
        sprintf(buffer,"%sSTATUS - DISCHARGING\n",buffer);//statuses
    }
    else
    { 
        sprintf(buffer,"%sSTATUS - CHARGING\n",buffer);//statuses
    }
    
    sprintf(buffer,"%sOV   UV   OC  TEMP\n",buffer);//statuses
    
    if(ov_fault)
    {
        //TFTSHIELD_1_FillRect(220, 160, 20,20, RED);
        sprintf(buffer,"%s-X-",buffer);
        //UART_1_PutString("-X-");
    }
    else
    {
        //TFTSHIELD_1_FillRect(220, 160, 20,20, GREEN);
        sprintf(buffer,"%s-O-",buffer);
        //UART_1_PutString("-O-");
    }
    if(uv_fault)
    {
        //TFTSHIELD_1_FillRect(185, 160, 20,20, RED);
        sprintf(buffer,"%s---X-",buffer);
        //UART_1_PutString("---X-");
    }
    else
    {
        //TFTSHIELD_1_FillRect(185, 160, 20,20, GREEN);
        sprintf(buffer,"%s----O-",buffer);
        //UART_1_PutString("----O-");
    }
    if(oc_fault)
    {
        //TFTSHIELD_1_FillRect(145, 160, 20,20, RED);
        sprintf(buffer,"%s----X-",buffer);
        //UART_1_PutString("----X-");
    }
    else
    {
        //TFTSHIELD_1_FillRect(145, 160, 20,20, GREEN);
        sprintf(buffer,"%s----O-",buffer);
        //UART_1_PutString("----O-");
    }
    if(temp_fault)
    {
        //TFTSHIELD_1_FillRect(105, 160, 20,20, RED);
        sprintf(buffer,"%s----X-",buffer);
        //UART_1_PutString("----X-");
    }
    else
    {
       //TFTSHIELD_1_FillRect(105, 160, 20,20, GREEN);
        sprintf(buffer,"%s----O-",buffer);
        //UART_1_PutString("----O-");
    }
    if(!fault_Read())
    {
        sprintf(buffer,"%s\nFAULT\n\n",buffer);
        //UART_1_PutString("FAULT\n");   
        //while(1);//HALT if fault!!!
    }
    else
    {
        sprintf(buffer,"%s\nOK\n\n",buffer);
        //UART_1_PutString("OK\n");
    }
    UART_1_PutString(buffer); //Push message out over uart to bluetooth dongle
}

float mapCoor(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    timer_clock_Start();
    Timer_1_Start();
    
    Thermistor_ADC_Start();
    Thermistor_ADC_StartConvert();
    //CalDAC_Start();
    //Clock_1_SetDividerValue(24);
    CyDelay(10);
    //TFTSHIELD_1_StartTouch();
    //bool touch_en = 0;
    //uint16_t x, y;
    //uint8_t z, buf;
    
    PowerMonitor_Start();
    
    CyDelay(100);
    //PowerMonitor_Calibrate();
    //char8 *parity[] = { "None", "Odd", "Even", "Mark", "Space" };
    //char8 *stop[] = { "1", "1.5", "2" };
    
    //uint16 count_str;
    //uint8 temp_buffer[10];
    //char8 lineStr[20];
    //uint8 state;
    //int i = 0;
    /* Enable the Interrupt component connected to Timer interrupt */
    isr_1_StartEx(timerHandler);
    /* Enable the Interrupt component connected to Timer interrupt */
    pmonitor_eoc_isr_StartEx(pmonitor_eoc);
    
    UART_1_Start();
    UART_1_PutString("GnarV Battery Monitor 1.0\n");
    
    //count_str = sprintf(buffer, "Power on \n\r");
    //while(USBUART_2_CDCIsReady() == 0u);    /* Wait till component is ready to send more data to the PC */ 
    //USBUART_2_PutData(buffer, count_str);       /* Send data back to PC */
    
    //PWM_1_Start();
    
    
    for(;;)
    {
        //displayStatus();
        //CyDelay(500);
    }
}
/* [] END OF FILE */
