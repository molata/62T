#include "iodefine.h"
void HIT_highimp(void)
{
	POE.OCSR1.BIT.OCE1 = 1;
	POE.SPOER.BIT.GPT01HIZ = 1;
	POE.SPOER.BIT.GPT23HIZ = 1;
	POE.ALR1.WORD = 0X0000;
}