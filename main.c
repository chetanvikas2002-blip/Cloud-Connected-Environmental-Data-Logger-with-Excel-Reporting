//Header files
#include <lpc21xx.h>
#include "adc.h"
#include "lcd_defines.h"
#include "delay.h"
#include "rtc.h"
#include "cust_lcd.h"
#include "interrupt.h"
#include "keypad_defines.h"
#include "menu.h"
#include "i2c.h"
#include "eeprom.h"
#include "uart.h"
#include "mq2.h"
#include "esp01.h"

/* Buzzer pin definitions */
#define TEMP_BUZZER 30
#define GAS_BUZZER  24
 
/* Global status variables */
static int last_minute = -1;
static int previous_smoke = 1;
static int smoke_state = 0;
#define TIME 3

int adc_value;
int interrupt_flag = 0;
int minute_backup = 0;

//char set_point = 32;
unsigned int  set_point = 32;
float temperature;

/* Main function starts here */
int main()
{       
/*variables of RTC*/
		int sec;
        int min;
        int hour;
        int date;
        int month;
        int year;
        int week; 
        last_minute = min;
/* Configure buzzer pins as GPIO */
        PINSEL1 &= ~(3 << (2 * (TEMP_BUZZER - 16)));
        PINSEL2 &= ~(3 << (2 * (GAS_BUZZER - 16)));
/* Configure buzzer pins as output */
        IODIR0 |= (1 << TEMP_BUZZER);
        IODIR1 |= (1 << GAS_BUZZER);
   	   init_interrupt();
/* Initialize all peripherals */							                      
        init_lcd();
        init_uart();
        init_adc();
        init_rtc();
        cust_lcd();
        init_i2c();
        init_inter();
        init_keypad();
        init_mq2();
/* Set initial RTC values */
       set_time_info(&sec, &min, &hour);
       set_date_info(&date, &month, &year);
       set_week(&week);
/* Read stored setpoint from EEPROM */
   	   set_point=32;
       cmd_lcd(0x01);
/* Initial ADC reading */
        read_adc(1, &adc_value, &temperature); //F1
        cmd_lcd(0x01);
        delay_ms(5);
/*Connecting to the ESP01*/
        string_lcd("Connecting");
		delay_ms(500);
        cmd_lcd(0xC0);
        string_lcd("To ESP01");
		delay_ms(500);
/* Initialize ESP01 */
        init_esp01();
        cmd_lcd(0x01);
        delay_ms(5);
/*while loop begins here*/
        while(1)
        {
/* Read RTC values */
                get_info(&sec, &min, &hour, &date, &month, &year, &week);
/* Display RTC info */
				display_info(sec, min, hour, date, month, year, week);
/* Read temperature */
                read_adc(1, &adc_value, &temperature);	
/* Display temperature */
                temp_display(temperature);
/* Upload temperature for every 3 minutes */
          if((((min - last_minute + 60) % 60) >= (unsigned int)TIME))
	    	{
                  last_minute = min;
				  cmd_lcd(0x01);
                  delay_ms(5);
				  update_data(1, (temperature * 100));
            }
/* Interrupt switch pressed */
			if(interrupt_flag == 1)
			{
                  interrupt_flag = 0;
				  minute_backup = min;
				  menu(&set_point,&sec,&min,&hour,&date,&month,&year,&week);
				  cmd_lcd(0x01);
                  delay_ms(5);
			      if(minute_backup != min)
                        {
                                last_minute = min;
                        }
             } 
/* Temperature threshold condition :
if Temperature value exits more than set point then the buzzer should on 
otherwise it should off  */																 
			if(temperature>set_point)
			{
			      IOSET0 = (1 << TEMP_BUZZER);
    		       update_data(2, (temperature * 100));
			
            }
            else
            {
                   IOCLR0 = (1 << TEMP_BUZZER);
            }
/* Smoke display */
                cmd_lcd(0xC8);
                string_lcd(" G:");
//SETTING PO.29 HAS SMOKE DIGITAL OUTPUT PIN
				smoke_state = ((IOPIN0 >> 29) & 1);
/* Smoke released :
This function is used to represents wheather the gas is released or not*/
                if((smoke_state == 1) && (previous_smoke == 0))
                {
                        data_lcd('0');
						cmd_lcd(0x01);
                        delay_ms(5);
                        cmd_lcd(0xC0);
                        string_lcd("Gas Cleared");
						delay_ms(1000);
						cmd_lcd(0x01);
						update_data(3,0);
                }		 
/* Smoke detected :
This function is used to represents wheather the gasis released or not*/
                if((smoke_state == 0) && (previous_smoke == 1))
                {
                        data_lcd('1');
						cmd_lcd(0x01);
                        delay_ms(5);
                        cmd_lcd(0xC0);
                        string_lcd("Gas alert");
						delay_ms(1000);
						cmd_lcd(0x01);
						update_data(3,1);
                }
/* Smoke buzzer control :
If the smoke released then the smoke buzzer will turn on
otherwise it should be in off state*/
                if(smoke_state == 0)
                {
                        IOSET1 = (1 << GAS_BUZZER);
						data_lcd('1');
                }
                else
                {
                        IOCLR1 = (1 << GAS_BUZZER);
						data_lcd('0');
                }
                previous_smoke = smoke_state;
        }	  
}
/* MAIN  function ends here	 */

/* External interrupt service routine */
void sw_pressed(void) __irq
{
        interrupt_flag = 1;

        /* Clear interrupt flag */
        EXTINT = (1 << 0);

        /* End of interrupt */
        VICVectAddr = 0;
}
