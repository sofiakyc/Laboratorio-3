#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "driverlib/systick.h"
#include "driverleds.h" // Projects/drivers

void ledsInit();
void setLeds (int pos1, int pos2, int pos3);

typedef enum {g_000=0, g_001, g_011, g_010, g_110, g_111, g_101, g_100} state_t;

volatile uint8_t Evento = 0, memoria;

void SysTick_Handler(void){
  Evento =1;
} // SysTick_Handler

void main(void){
  ledsInit();
  static state_t Estado = g_000; // estado inicial da MEF
  SysTickPeriodSet(12000000); // f = 1Hz para clock = 24MHz
  SysTickIntEnable();
  SysTickEnable();

  while(1){
      switch(Estado){
        case g_000:
          setLeds (0, 0, 0);
          if(Evento)
          {
            Evento = 0;
            Estado = g_001;
          }
          break;
        case g_001:
          setLeds (1, 0, 0);
          if(Evento)
          {
            Evento = 0;
            Estado = g_011;
          }
          break;
        case g_011:
          setLeds (1, 1, 0);
          if(Evento)
          {
            Evento = 0;
            Estado = g_010;
          }
          break;
        case g_010:
          setLeds (0, 1, 0);
          if(Evento)
          {
            Evento = 0;
            Estado = g_110;
          }
          break;
        case g_110:
          setLeds (0, 1, 1);
          if(Evento)
          {
            Evento = 0;
            Estado = g_111;
          }
          break;
        case g_111:
          setLeds (1, 1, 1);
          if(Evento)
          {
            Evento = 0;
            Estado = g_101;
          }
          break;
        case g_101:
          setLeds (1, 0, 1);
          if(Evento)
          {
            Evento = 0;
            Estado = g_100;
          }
          break;
        case g_100:
          setLeds (0, 0, 1);
          if(Evento)
          {
            Evento = 0;
            Estado = g_000;
          }
          break;
      } // switch
  }
} // main

void setLeds (int pos1, int pos2, int pos3)
{
  if (pos1)
    LEDOn(LED1);
  else
    LEDOff(LED1);
  
  if (pos2)
    LEDOn(LED2);
  else
    LEDOff(LED2);
  
  if (pos3)
    LEDOn(LED3);
  else
    LEDOff(LED3);
}

void ledsInit()
{
  LEDInit(LED1);
  LEDInit(LED2);
  LEDInit(LED3);
}