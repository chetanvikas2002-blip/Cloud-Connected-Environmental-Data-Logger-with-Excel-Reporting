#ifndef _ESP01_H_

#define _ESP01_H_


//int init_esp01(void);

void esp01_sendToThingspeak(int field,char val);
void init_esp01(void);
void update_data(int field,char val);
int esp01_connectAP(void);

#endif
