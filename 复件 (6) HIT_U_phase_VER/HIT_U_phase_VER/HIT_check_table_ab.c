#include "HIT_check_table_ab.h"
#include <math.h>
#include <mathf.h>

void HIT_check_table_ab(void)
{
		if(HIT_sitacheck_ab<1024)/*find table calculat sin(sita)and cos(sita) add process of zone line*/
		{
			HIT_sinzhi_a_ab = HIT_y[HIT_sitacheck_ab];
			HIT_sitacheck_cos_ab = 1023-HIT_sitacheck_ab;
			HIT_coszhi_a_ab = HIT_y[HIT_sitacheck_cos_ab];
			HIT_xw=1;	
		}
		else 
		{
	
			if(HIT_sitacheck_ab<2048)
			{
				HIT_sitacheck_sin_ab = 2047 - HIT_sitacheck_ab;
				HIT_sinzhi_a_ab = HIT_y[HIT_sitacheck_sin_ab];
				HIT_sitacheck_cos_ab = HIT_sitacheck_ab-1024;
				HIT_coszhi_a_ab = -HIT_y[HIT_sitacheck_cos_ab];
				HIT_xw=2;	
			}
			else
			{
				if(HIT_sitacheck_ab<3072)
				{
					HIT_sitacheck_sin_ab = HIT_sitacheck_ab-2048;
					HIT_sinzhi_a_ab =( -HIT_y[HIT_sitacheck_sin_ab]);
					HIT_sitacheck_cos_ab = 3071 - HIT_sitacheck_ab;
					HIT_coszhi_a_ab = -HIT_y[HIT_sitacheck_cos_ab];
					HIT_xw=3;
				}	
				else
				{
					HIT_sitacheck_sin_ab = 4095 - HIT_sitacheck_ab;
					HIT_sinzhi_a_ab = (-HIT_y[HIT_sitacheck_sin_ab]);
					HIT_sitacheck_cos_ab = HIT_sitacheck_ab - 3072;
					HIT_coszhi_a_ab = HIT_y[HIT_sitacheck_cos_ab];
					HIT_xw=4;	
				}	
			}
		}

/*end*/
		
		HIT_sinzhi_b_ab = HIT_KR*HIT_coszhi_a_ab - HIT_KHALF*HIT_sinzhi_a_ab;//sin(120+sita)
		HIT_sinzhi_c_ab = -HIT_KR*HIT_coszhi_a_ab - HIT_KHALF*HIT_sinzhi_a_ab;//sin(240+sita)
		HIT_coszhi_b_ab = -HIT_KHALF*HIT_coszhi_a_ab - HIT_KR*HIT_sinzhi_a_ab;//cos(120+sita)
		HIT_coszhi_c_ab = -HIT_KHALF*HIT_coszhi_a_ab + HIT_KR*HIT_sinzhi_a_ab;//cos(240+sita)
		if(HIT_sinzhi_b_ab > 1)
		{
			HIT_sinzhi_b_ab = 0.99999;	
		}
		if(HIT_sinzhi_c_ab > 1)
		{
			HIT_sinzhi_c_ab = 0.99999;	
		}
		if(HIT_sinzhi_b_ab < -1)
		{
			HIT_sinzhi_b_ab = -0.99999;	
		}
		if(HIT_sinzhi_c_ab < -1)
		{
			HIT_sinzhi_c_ab = -0.99999;	
		}
		if(HIT_coszhi_b_ab > 1)
		{
			HIT_coszhi_b_ab = 0.99999;	
		}
		if(HIT_coszhi_c_ab > 1)
		{
			HIT_coszhi_c_ab = 0.99999;	
		}
		if(HIT_coszhi_b_ab < -1)
		{
			HIT_coszhi_b_ab = -0.99999;	
		}
		if(HIT_coszhi_c_ab < -1)
		{
			HIT_coszhi_c_ab = -0.99999;	
		}
}