#include<lpc21xx.h>
#include "interrupt.h"

/* Function to initialize external interrupt */
void init_interrupt()
{
        /* Configure EINT0 pin function */
        PINSEL1 = PINSEL1 & ~(3<<(16-EINT0_PIN));

        PINSEL1 = PINSEL1 | (1<<(16-EINT0_PIN));

        /* Enable EINT0 interrupt */
        VICIntEnable |= (1<<EINT0_CH);

        /* Configure vector control register */
        VICVectCntl1 = (EINT0_CH) | (1<<5);

        /* Load ISR   address */
        VICVectAddr1 = (unsigned int)sw_pressed;

        /* Clear pending interrupt */
         EXTINT = 1<<0;

        /* Configure edge sensitive mode */
        EXTMODE = 1<<0;

        /* Configure falling edge trigger */
        EXTPOLAR = 0<<0;
}

/* MQ2 interrupt initialization */
/*
void init_mq2_int()
{
        PINSEL1 = PINSEL1 & ~(3<<(2*(30-16)));

        PINSEL1 = PINSEL1 | (2<<28);

        VICIntEnable |= (1<<EINT3_CH);

        VICVectCntl2 = (EINT3_CH) | (1<<5);

        VICVectAddr2 = (unsigned)smoke_alert;

        EXTINT = 1<<3;

        EXTMODE = 1<<3;

        EXTPOLAR = 1<<3;
}
*/
