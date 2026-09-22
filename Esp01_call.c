#include "delay.h"
#include "lcd_defines.h"
#include "esp01.h"
#include "uart.h"
/* External variables */
extern char buff[300],store;
extern unsigned char ch,r_flag;
extern int i;

/* Function to initialize ESP01 module */
void init_esp01()
{
                int cnt=0,ret,ncnt=0,tot=0;

                /* Check AT communication */
                while(1)
                {
                        ret=esp01_connectAP_AT();

                        if(ret==1)
                        {
                                break;
                        }
                        else if(ret==0)
                        {
                                cnt++;
                                tot++;

                                if(cnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        delay_ms(2000);
                                        continue;
                                }
                        }
                        else if(ret==-1)
                        {
                                ncnt++;
                                tot++;

                                delay_ms(2000);

                                if(ncnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }

                        if(tot==5)
                        {
                                if(cnt>ncnt)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }
                }

                /* Reset counters */
                ret=0;
                cnt=0;
                ncnt=0;
                tot=0;

                /* Disable echo */
                while(1)
                {
                        ret=esp01_connectAP_ATE0();

                        if(ret==1)
                        {
                                break;
                        }
                        else if(ret==0)
                        {
                                cnt++;
                                tot++;

                                if(cnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        delay_ms(2000);
                                        continue;
                                }
                        }
                        else if(ret==-1)
                        {
                                ncnt++;
                                tot++;

                                delay_ms(2000);

                                if(ncnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }

                        if(tot==5)
                        {
                                if(cnt>ncnt)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }
                }

                /* Reset counters */
                ret=0;
                cnt=0;
                ncnt=0;
                tot=0;

                /* Configure TCP mode */
                while(1)
                {
                        ret=esp01_connectAP_TCP_MODE();

                        if(ret==1)
                        {
                                break;
                        }
                        else if(ret==0)
                        {
                                cnt++;
                                tot++;

                                if(cnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);																																								
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        delay_ms(2000);
                                        continue;
                                }
                        }
                        else if(ret==-1)
                        {
                                ncnt++;
                                tot++;

                                delay_ms(2000);

                                if(ncnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }

                        if(tot==5)
                        {
                                if(cnt>ncnt)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }
                }

                /* Reset counters */
                ret=0;
                cnt=0;
                ncnt=0;
                tot=0;

                /* Disconnect previous WiFi */
                while(1)
                {
                        ret=esp01_connectAP_QUIT_AP();

                        if(ret==1)
                        {
                                break;
                        }
                        else if(ret==0)
                        {
                                cnt++;
                                tot++;

                                if(cnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        delay_ms(2000);
                                        continue;
                                }
                        }
                        else if(ret==-1)
                        {
                                ncnt++;
                                tot++;

                                delay_ms(2000);

                                if(ncnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }

                        if(tot==5)
                        {
                                if(cnt>ncnt)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }
                }

                /* Reset counters */
                ret=0;
                cnt=0;
                ncnt=0;
                tot=0;

                /* Join WiFi network */
                while(1)
                {
                        ret=esp01_connectAP_JOIN_AP();

                        if(ret==1)
                        {
                                break;
                        }
                        else if(ret==0)
                        {
                                cnt++;
                                tot++;

                                if(cnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        delay_ms(2000);
                                        continue;
                                }
                        }
                        else if(ret==-1)
                        {
                                ncnt++;
                                tot++;

                                delay_ms(2000);

                                if(ncnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }

                        if(tot==5)
                        {
                                if(cnt>ncnt)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }
                }
}

/* Function to upload data to cloud */
void update_data(int field,int num)
{
                int cnt=0,ret,ncnt=0,tot=0;

                cmd_lcd(0x01);

                /* Display uploading status */
                if(field==1)
                {
                        string_lcd("uploading...");

                        cmd_lcd(0xc0);
                        string_lcd("Temperature");
                }
                else if(field==2)
                {
                        string_lcd("uploading...");

                        cmd_lcd(0xc0);
                        string_lcd("set point");
                }
                else if((field==3)&&(num==1))
                {
                        string_lcd("uploading...");

                        cmd_lcd(0xc0);
                        string_lcd("SMOKE ALERT");
                }
                else if((field==3)&&(num==0))
                {
                         string_lcd("uploading...");

                         cmd_lcd(0xc0);
                         string_lcd("SMOKE RELEASE");
                }
                else if(field==4)
                {
                        string_lcd("uploading...");

                        cmd_lcd(0xc0);
                        string_lcd("Temp>set point");
                }

                /* Upload retry loop */
                while(1)
                {
                        ret=esp01_sendToThingspeak(field,num);

                        if(ret==1)
                        {
                                break;
                        }
                        else if(ret==0)
                        {
                                cnt++;
                                tot++;

                                if(cnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        delay_ms(2000);
                                        continue;
                                }
                        }
                        else if(ret==-1)
                        {
                                ncnt++;
                                tot++;

                                delay_ms(2000);

                                if(ncnt==5)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }

                        if(tot==5)
                        {
                                if(cnt>ncnt)
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 connecting");

                                        cmd_lcd(0xc0);
                                        string_lcd("failed");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                                else
                                {
                                        cmd_lcd(0x01);
                                        string_lcd("esp01 not");

                                        cmd_lcd(0xc0);
                                        string_lcd("responding");

                                        delay_ms(5000);

                                        cmd_lcd(0x01);

                                        return ;
                                }
                        }
                }

                cmd_lcd(0x01);

                return ;
}
