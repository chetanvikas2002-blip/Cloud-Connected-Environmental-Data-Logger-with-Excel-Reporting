#include "mq2.h"
void init_mq2()
{
        PINSEL1=PINSEL1&~(3<<(2*(29-16)));
}
