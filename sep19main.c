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
#define TEMP_BUZZER        30
#define GAS_BUZZER         24

/* EEPROM definitions */
#define EEPROM_ADDR        0x50
#define SETPOINT_ADDRESS   0x0000

/* Default and valid set-point limits */
#define DEFAULT_SETPOINT   32
#define MIN_SETPOINT       10
#define MAX_SETPOINT       100

/* Temperature upload interval in minutes */
#define TIME               3

/* Global status variables */
static int last_minute = -1;
static int previous_smoke = 1;
static int smoke_state = 0;

int adc_value;
int interrupt_flag = 0;
int minute_backup = 0;

unsigned int set_point = DEFAULT_SETPOINT;
float temperature;

/*---------------------------------------------------------
MAIN FUNCTION
---------------------------------------------------------*/
int main()
{
/* RTC variables */
int sec;
int min;
int hour;
int date;
int month;
int year;
int week;


unsigned char stored_setpoint;


/*-----------------------------------------------------
  Configure buzzer pins as GPIO
-----------------------------------------------------*/

PINSEL1 &= ~(3 << (2 * (TEMP_BUZZER - 16)));
PINSEL2 &= ~(3 << (2 * (GAS_BUZZER - 16)));


/* Configure buzzer pins as output */

IODIR0 |= (1 << TEMP_BUZZER);
IODIR1 |= (1 << GAS_BUZZER);


/* Turn OFF buzzers initially */

IOCLR0 = (1 << TEMP_BUZZER);
IOCLR1 = (1 << GAS_BUZZER);


/*-----------------------------------------------------
  Initialize peripherals
-----------------------------------------------------*/

init_interrupt();

init_lcd();
init_uart();
init_adc();
init_rtc();
cust_lcd();

init_i2c();

init_inter();
init_keypad();
init_mq2();


/*-----------------------------------------------------
  Read initial RTC values
-----------------------------------------------------*/

set_time_info(&sec, &min, &hour);
set_date_info(&date, &month, &year);
set_week(&week);


/*
   Initialize last_minute AFTER reading RTC.

   Do NOT do:
       last_minute = min;
   before min has been initialized.
*/

last_minute = min;


/*-----------------------------------------------------
  Read SET POINT from EEPROM
-----------------------------------------------------*/

stored_setpoint = byte_read(EEPROM_ADDR,SETPOINT_ADDRESS);


/*
   EEPROM normally contains 0xFF when the location
   has never been programmed.

   Also check whether the stored value is within the
   allowed temperature range.
*/

if((stored_setpoint == 0xFF) ||
   (stored_setpoint < MIN_SETPOINT) ||
   (stored_setpoint > MAX_SETPOINT))
{
    /*
       EEPROM does not contain a valid set point.

       Use default value = 32°C
    */

    set_point = DEFAULT_SETPOINT;

    /*
       Store default value in EEPROM so that a valid
       value is available from the next power-up.
    */

    byte_write(EEPROM_ADDR,SETPOINT_ADDRESS,(char)set_point);
}
else
{
    /*
       Valid set point found in EEPROM.
       Restore it.
    */

    set_point = stored_setpoint;
}


/*-----------------------------------------------------
  Initial LCD
-----------------------------------------------------*/

cmd_lcd(0x01);
delay_ms(5);


/*-----------------------------------------------------
  Initial ADC reading
-----------------------------------------------------*/

read_adc(1, &adc_value, &temperature);

cmd_lcd(0x01);
delay_ms(5);


/*-----------------------------------------------------
  Connect to ESP01
-----------------------------------------------------*/

string_lcd("Connecting");

delay_ms(500);

cmd_lcd(0xC0);

string_lcd("To ESP01");

delay_ms(500);


/* Initialize ESP01 */

init_esp01();

cmd_lcd(0x01);
delay_ms(5);


/*-----------------------------------------------------
  MAIN LOOP
-----------------------------------------------------*/

while(1)
{
    /*-------------------------------------------------
      Read RTC values
    -------------------------------------------------*/

    get_info(&sec,&min,&hour,&date,&month,&year,&week);


    /*-------------------------------------------------
      Display RTC information
    -------------------------------------------------*/

    display_info(sec,min,hour,date,month,year,week);


    /*-------------------------------------------------
      Read temperature
    -------------------------------------------------*/

    read_adc(1,&adc_value,&temperature);


    /*-------------------------------------------------
      Display temperature
    -------------------------------------------------*/

    temp_display(temperature);


    /*-------------------------------------------------
      Upload temperature every 3 minutes
    -------------------------------------------------*/

    if((((min - last_minute + 60) % 60) >= TIME))
    {
        last_minute = min;

        cmd_lcd(0x01);
        delay_ms(5);

        update_data(1, (temperature * 100));
    }


    /*-------------------------------------------------
      MENU / SWITCH INTERRUPT
    -------------------------------------------------*/

    if(interrupt_flag == 1)
    {
        /*
           Clear interrupt flag before entering menu.
        */

        interrupt_flag = 0;


        /*
           Store current minute.

           This is used to determine whether the menu
           changed the RTC minute.
        */

        minute_backup = min;


        /*---------------------------------------------
          Open menu

          The menu can modify set_point.
        ---------------------------------------------*/

        menu(&set_point,&sec,&min,&hour,&date,&month,&year,&week);


        /*---------------------------------------------
          IMPORTANT:

          Save the newly selected set point to EEPROM.

          Therefore it survives power OFF/ON.
        ---------------------------------------------*/

        if((set_point >= MIN_SETPOINT) &&
           (set_point <= MAX_SETPOINT))
        {
            byte_write(EEPROM_ADDR,SETPOINT_ADDRESS,(char)set_point);
        }
        else
        {
            /*
               Safety check.

               If menu somehow produces an invalid value,
               restore the default set point.
            */

            set_point = DEFAULT_SETPOINT;

            byte_write(EEPROM_ADDR,SETPOINT_ADDRESS,(char)set_point);
        }


        /* Clear LCD after returning from menu */

        cmd_lcd(0x01);
        delay_ms(5);


        /*
           If menu changed the RTC minute, update
           last_minute so that temperature is not
           immediately uploaded unnecessarily.
        */

        if(minute_backup != min)
        {
            last_minute = min;
        }
    }


    /*-------------------------------------------------
      TEMPERATURE BUZZER CONTROL
    -------------------------------------------------*/

    /*
       If temperature is greater than the stored
       set point, turn ON temperature buzzer.

       Otherwise turn it OFF.
    */

    if(temperature > set_point)
    {
        IOSET0 = (1 << TEMP_BUZZER);

        /*
           Send temperature alert to ESP01/server.
        */

        update_data(2, (temperature * 100));
    }
    else
    {
        IOCLR0 = (1 << TEMP_BUZZER);
    }


    /*-------------------------------------------------
      SMOKE / GAS DISPLAY
    -------------------------------------------------*/

    cmd_lcd(0xC8);

    string_lcd(" G:");


    /*
       P0.29 is the smoke/gas digital output.
    */

    smoke_state = ((IOPIN0 >> 29) & 1);


    /*-------------------------------------------------
      GAS CLEARED EVENT
    -------------------------------------------------*/

    if((smoke_state == 1) &&
       (previous_smoke == 0))
    {
        data_lcd('0');

        cmd_lcd(0x01);
        delay_ms(5);

        cmd_lcd(0xC0);

        string_lcd("Gas Cleared");

        delay_ms(1000);

        cmd_lcd(0x01);
        delay_ms(5);

        /*
           Send gas-cleared status.
        */

        update_data(3, 0);
    }


    /*-------------------------------------------------
      GAS DETECTED EVENT
    -------------------------------------------------*/

    if((smoke_state == 0) && (previous_smoke == 1))
    {
        data_lcd('1');

        cmd_lcd(0x01);
        delay_ms(5);

        cmd_lcd(0xC0);

        string_lcd("Gas alert");

        delay_ms(1000);

        cmd_lcd(0x01);
        delay_ms(5);

        /*
           Send gas-alert status.
        */

        update_data(3, 1);
    }


    /*-------------------------------------------------
      GAS BUZZER CONTROL
    -------------------------------------------------*/

    if(smoke_state == 0)
    {
        /*
           Gas detected -> buzzer ON
        */

        IOSET1 = (1 << GAS_BUZZER);

        data_lcd('1');
    }
    else
    {
        /*
           Gas not detected -> buzzer OFF
        */

        IOCLR1 = (1 << GAS_BUZZER);

        data_lcd('0');
    }


    /*
       Save current gas state for edge detection
       during the next loop.
    */

    previous_smoke = smoke_state;
}

}

/*---------------------------------------------------------
EXTERNAL INTERRUPT SERVICE ROUTINE
---------------------------------------------------------*/

void sw_pressed(void) __irq
{
/*
Set flag.

```
   The actual menu processing is done inside main()
   rather than inside the interrupt service routine.
*/

interrupt_flag = 1;


/*
   Clear external interrupt flag.
*/

EXTINT = (1 << 0);


/*
   Signal end of interrupt to VIC.
*/

VICVectAddr = 0;

}

