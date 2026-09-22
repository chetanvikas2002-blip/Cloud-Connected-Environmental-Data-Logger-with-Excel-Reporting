#include <string.h>
#include "uart.h"
#include "delay.h"
#include "lcd_defines.h"
#define DEBUG_SIM 1

extern char buff[300];
extern int i;

/* Check ESP01 response using AT command */
int esp01_connectAP_AT()
{
        int timeout = 0;

       string_uart("AT\r\n");
		#if DEBUG_SIM
		  return 1;
		  #endif
	/*	 delay_ms(2000);
		 string_uart("BUFF=");
		 string_uart(buff);
		 string_uart("\r\n");	 */
        i = 0;
        memset(buff,'\0',300);

        while((i < 3) && (timeout < 20))
        {
                delay_ms(10);
                timeout++;
        }

        if(timeout >= 20)
        {
                return -1;
        }

        delay_ms(500);

        buff[i] = '\0';

        if(strstr(buff,"OK"))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

/* Disable echo */
int esp01_connectAP_ATE0()
{
        int timeout = 0;

        string_uart("ATE0\r\n");
			#if DEBUG_SIM
		  return 1;
		  #endif

        i = 0;
        memset(buff,'\0',300);

        while((i < 4) && (timeout < 20))
        {
                delay_ms(10);
                timeout++;
        }

        if(timeout >= 20)
        {
                return -1;
        }

        delay_ms(500);

        buff[i] = '\0';

        if(strstr(buff,"OK"))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

/* Configure single TCP connection mode */
int esp01_connectAP_TCP_MODE()
{
        int timeout = 0;

        string_uart("AT+CIPMUX=0\r\n");	
		#if DEBUG_SIM
		  return 1;
		  #endif


        i = 0;
        memset(buff,'\0',300);

        while((i < 4) && (timeout < 20))
        {
                delay_ms(10);
                timeout++;
        }

        if(timeout >= 20)
        {
                return -1;
        }

        delay_ms(500);

        buff[i] = '\0';

        if(strstr(buff,"OK"))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

/* Disconnect previous WiFi connection */
int esp01_connectAP_QUIT_AP()
{
        int timeout = 0;

        delay_ms(1000);

        string_uart("AT+CWQAP\r\n");
	  	#if DEBUG_SIM
		  return 1;
		  #endif

        i = 0;
        memset(buff,'\0',300);

        while((i < 4) && (timeout < 20))
        {
                delay_ms(10);
                timeout++;
        }

        if(timeout >= 20)
        {
                return -1;
        }

        delay_ms(1500);

        buff[i] = '\0';

        if(strstr(buff,"OK"))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

/* Connect ESP01 to OPPO A16 hotspot */
int esp01_connectAP_JOIN_AP()
{
        int timeout = 0;

        /* WiFi Name : OPPO A16 */
        /* Password  : 123456789 */

        string_uart("AT+CWJAP=\"OPPO A16\",\"12345678\"\r\n");
			#if DEBUG_SIM
		  return 1;
		  #endif

        i = 0;
        memset(buff,'\0',300);

        while((i < 4) && (timeout < 20))
        {
                delay_ms(10);
                timeout++;
        }

        if(timeout >= 20)
        {
                return -1;
        }

        delay_ms(2500);

        buff[i] = '\0';

        if(strstr(buff,"WIFI CONNECTED"))
        {
                return 1;
        }
        else
        {
                return 0;
        }
}

/* Upload data to ThingSpeak cloud */
int esp01_sendToThingspeak(int field,int num)
{
        int len = 0;
        int temp;
        int timeout = 0;		
			#if DEBUG_SIM
			string_uart("OK\r\n")'
			return 1;
			#endif
        string_uart("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

        i = 0;
        memset(buff,'\0',300);

        while((i < 5) && (timeout < 20))
        {
                delay_ms(10);
                timeout++;
        }

        if(timeout >= 20)
        {
                return -1;
        }

        timeout = 0;

        delay_ms(2500);

        buff[i] = '\0';

        if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
        {
                temp = num;

                while(temp != 0)
                {
                        len++;
                        temp /= 10;
                }

                if(num == 0)
                {
                        len = 1;
                }

                string_uart("AT+CIPSEND=");

                /* Correct data length */
                int_uart(len + 47);

                string_uart("\r\n");

                i = 0;
                memset(buff,'\0',300);

                delay_ms(500);

                /* Your ThingSpeak API key added */
                string_uart("GET /update?api_key=WZ9BGGE3ALNS0BH9&field");

                int_uart(field);

                tx_uart('=');

                int_uart(num);

                string_uart("\r\n\r\n");
					
	//	 return 1;
		//  #endif

                delay_ms(5000);

                buff[i] = '\0';

                delay_ms(2000);

                if(strstr(buff,"SEND OK"))
                {
                        return 1;
                }
                else
                {
                        return 0;
                }
        }
        else
        {
                return 0;
        }
}
