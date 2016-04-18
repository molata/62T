#ifndef MAKE_ANGLEABC
#define MAKE_ANGLEABC
#include "HIT_make_angleab.h"
#include<math.h>
void  HIT_make_angleab()
{
			
/*angle zone calculate*/		
		if((HIT_Ua>0)&&(HIT_Ua >= HIT_Ub))		
		{
			if(HIT_Ub < 0)
			{
				HIT_sitalfa=HIT_TWOPIE-atan(-HIT_Ub/HIT_Ua);	
			}
			else
			{
				HIT_sitalfa=atan(HIT_Ub/HIT_Ua);	
			}
		}
		else
		{
			if((HIT_Ub>0)&&(HIT_Ub >= HIT_Ua))
			{
				if(HIT_Ua<0)
				{
					HIT_sitalfa=HIT_HALFPIE+atan(-HIT_Ua/HIT_Ub);	
				}	
				else
				{
					HIT_sitalfa=HIT_HALFPIE-atan(HIT_Ua/HIT_Ub);	
				}
			}
			else
			{
				if((HIT_Ua<0)&&(HIT_Ub >= HIT_Ua))
				{
					if(HIT_Ub<0)
					{
						HIT_sitalfa=HIT_PIE+atan(HIT_Ub/HIT_Ua);	
					}
					else
					{
						HIT_sitalfa=HIT_PIE-atan(HIT_Ub/-HIT_Ua);		
					}	
				}
				else
				{
					if(HIT_Ua>0)
					{
						HIT_sitalfa=HIT_TWOTHIRDPIE+atan(HIT_Ua/-HIT_Ub);	
					}	
					else
					{
						HIT_sitalfa=HIT_TWOTHIRDPIE-atan(HIT_Ua/HIT_Ub);	
					}	
				}	
			}
		}

		/*calculate end*/
		HIT_sitaintab=HIT_sitalfa* HIT_MAKE16WEI_ANGLE;
		HIT_sitadianab =  HIT_sitaintab&0x0000ffff;
		HIT_sitadianab = HIT_sitadianab>>4;//get 12 wei AB-axis angle
}
#endif