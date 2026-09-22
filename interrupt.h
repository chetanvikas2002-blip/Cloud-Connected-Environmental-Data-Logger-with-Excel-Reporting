#include<lpc21xx.h>

/* External interrupt channel definitions */
#define EINT0_CH 14
#define EINT0_PIN 16

#define EINT3_CH 17
#define EINT3_PIN 30

/* Function declarations */

/* Initialize switch interrupt */
void init_interrupt(void);

/* ISR for switch press */
void sw_pressed(void) __irq;

/* Initialize MQ2 interrupt */
void init_mq2_int(void);

/* ISR for smoke alert */
void smoke_alert(void) __irq;
