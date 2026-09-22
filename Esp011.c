//
#include <string.h>
#include "uart.h"
#include "delay.h"
#include "lcd_defines.h"
#include"esp011.h"
extern char buff[200];
extern unsigned char i;
int time=0;
void init_esp01(void)
{
esp01_connectAP();
}
void update_data(int field,char val)
{
	esp01_sendToThingspeak(field,val);
} 
int esp01_connectAP()
{
	cmd_lcd(0x01);
	cmd_lcd(0x80);
	string_lcd("AT");
	delay_ms(1000);
	string_uart("AT\r\n");
	i=0;memset(buff,'\0',200);
	while((i<4)&&(time<200))
	{
	delay_ms(10);
	time++;
	}
	if(time>=200)
	{
	return -1;
	}
	delay_ms(100);
    buff[i] = '\0';
	cmd_lcd(0x01);
	cmd_lcd(0x80);
	delay_ms(100);
   if(strstr(buff,"OK"))
	{   cmd_lcd(0x01);
		cmd_lcd(0x80);
		string_lcd("OK");
		delay_ms(1000);		
	}

	else

	{
			 	cmd_lcd(0x01);

		cmd_lcd(0x80);

		string_lcd("ERROR");

		delay_ms(1000);		

	//	return;

	}

	

	

	cmd_lcd(0x01);

	cmd_lcd(0x80);

	string_lcd("ATE0");

	delay_ms(1000);

	string_uart("ATE0\r\n");

	i=0;memset(buff,'\0',200);

//	while(i<4);
while((i<4)&&(time<200))
	{
	delay_ms(10);
	time++;
	}
	if(time>=200)
	{
	return -1;
	}

	delay_ms(500);

	buff[i] = '\0';

	cmd_lcd(0x01);

	cmd_lcd(0x80);
	 

	//string_lcd(buff);

	delay_ms(500);

	if(strstr(buff,"OK"))

	{
		   	cmd_lcd(0x01);
		cmd_lcd(0x80);

		string_lcd("OK");

		delay_ms(1000);		

	}

	else

	{
				cmd_lcd(0x01);
		cmd_lcd(0x80);

		string_lcd("ERROR");

		delay_ms(1000);		

	//	return;

	}

	cmd_lcd(0x01);

	cmd_lcd(0x80);

	string_lcd("AT+CIPMUX");

	delay_ms(1000);

	string_uart("AT+CIPMUX=0\r\n");

	i=0;memset(buff,'\0',200);

	//while(i<4);
	while((i<4)&&(time<200))
	{
	delay_ms(10);
	time++;
	}
	if(time>=200)
	{
	return -1;
	}

	delay_ms(500);

	buff[i] = '\0';

	cmd_lcd(0x01);

	cmd_lcd(0x80);
	 //memset(buff,'\0',200);//line

	//string_lcd(buff);

	delay_ms(500);

	if(strstr(buff,"OK"))

	{
							  	cmd_lcd(0x01);
		cmd_lcd(0x80);

		string_lcd("OK");

		delay_ms(1000);		

	}

	else

	{

		cmd_lcd(0x01);

		cmd_lcd(0x80);

		string_lcd("ERROR");

		delay_ms(1000);		

//		return;

	}

	

	cmd_lcd(0x01);

	cmd_lcd(0x80);

	string_lcd("AT+CWQAP");

	delay_ms(1000);

	string_uart("AT+CWQAP\r\n");

	i=0;memset(buff,'\0',200);

//	while(i<4);
while((i<4)&&(time<200))
	{
	delay_ms(10);
	time++;
	}
	if(time>=200)
	{
	return -1;
	}

	delay_ms(1500);

	buff[i] = '\0';

	cmd_lcd(0x01);

	cmd_lcd(0x80);

	//string_lcd(buff);

	delay_ms(500);

	if(strstr(buff,"OK"))

	{
		cmd_lcd(0x01);

		cmd_lcd(0x80);

		string_lcd("OK");

		delay_ms(1000);		

	}

	else

	{

		cmd_lcd(0x01);
		cmd_lcd(0x80);

		string_lcd("ERROR");

		delay_ms(1000);		

//		return;

	}
	cmd_lcd(0x01);

	cmd_lcd(0x80);

	string_lcd("AT+CWJAP");
	delay_ms(1000);
	string_uart("AT+CWJAP=\"moto g85 5G\",\"123456789\"\r\n");
	i=0;memset(buff,'\0',200);

//	while(i<4);
while((i<4)&&(time<200))
	{
	delay_ms(10);
	time++;
	}
	if(time>=200)
	{
	return -1;
	}

	delay_ms(2500);

	buff[i] = '\0';

	cmd_lcd(0x01);

	cmd_lcd(0x80);

	//string_lcd(buff);

	delay_ms(500);

	if(strstr(buff,"WIFI CONNECTED"))

	{
		cmd_lcd(0x01);

		cmd_lcd(0x80);

		string_lcd("CONNECTED");

		delay_ms(1000);		

	}

	else

	{
		cmd_lcd(0x01);

		cmd_lcd(0x80);

		string_lcd("ERROR");

		delay_ms(1000);		

		//return;

	}
	return 1;
}


void esp01_sendToThingspeak(int field,char val)

{

	cmd_lcd(0x01);

	cmd_lcd(0x80);

	string_lcd("AT+CIPSTART");

	delay_ms(1000);


	string_uart("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

	i=0;memset(buff,'\0',200);

	while(i<5);

	delay_ms(2500);

	buff[i] = '\0';

	cmd_lcd(0x01);

	cmd_lcd(0x80);

//	string_lcd(buff);

	delay_ms(500);

if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))

{
		cmd_lcd(0x01);

		cmd_lcd(0x80);

		string_lcd("CONNECTED");

		delay_ms(1000);

		

		cmd_lcd(0x01);

		cmd_lcd(0x80);

		string_lcd("AT+CIPSEND");

		delay_ms(1000);

		string_uart("AT+CIPSEND=48\r\n");

		i=0;memset(buff,'\0',200);
		delay_ms(500);
		if(field==1)
		{
			string_uart("GET /update?api_key=B5EHEM6FKQQNIERQ&field1=");
			cmd_lcd(0x01);
			cmd_lcd(0x80);
			string_lcd("uploading temp..");
		}

		else if(field==2)
		{
	string_uart("GET /update?api_key=B5EHEM6FKQQNIERQ&field2=");//LUCKY API KEY
		cmd_lcd(0x01);
	
               cmd_lcd(0x80);
            string_lcd("uploading FILED2");
			cmd_lcd(0xc0);
			string_lcd("setpoint..");
			//return;

		}

		else if(field==3)
		{
	string_uart("GET /update?api_key=B5EHEM6FKQQNIERQ&field3=");
				  	  cmd_lcd(0x01);
             cmd_lcd(0x80);
              string_lcd("uploading smoke..");

		}

		 // string_lcd("val");
		  delay_ms(200);
		int_uart(val);

		string_uart("\r\n");
		delay_ms(100);
		string_uart("AT+CIPCLOSE\r\n");
		delay_ms(1000);
		
		buff[i] = '\0';

		cmd_lcd(0x01);
		if(strstr(buff,"OK"))

		{

			cmd_lcd(0x01);

			cmd_lcd(0x80);//line
			string_lcd("DATA UPDATED");
			

			delay_ms(1000);	
			cmd_lcd(0x01);		

		}


		else

		{

			cmd_lcd(0x01);
			cmd_lcd(0x80);

			string_lcd("DATA NOT UPDATED");

			delay_ms(1000);	

		}

		

}

else

{

		cmd_lcd(0x01);
		cmd_lcd(0x80);

		string_lcd("ERROR0");

		delay_ms(1000);		

		return;

}

}












