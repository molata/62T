#ifndef HIT2HUNDREDTO3HUNDREDMSC
#define HIT2HUNDREDTO3HUNDREDMSC
#include"iodefine.h"
#include"HIT_2hundredto3hundredms.h"
void HIT_2hundredto3hundredms()
{
	if(HIT_system_count == 20001)
	{
		GPT0.GTONCR.BIT.OAE = 1;
		GPT0.GTONCR.BIT.OBE = 1;
		GPT1.GTONCR.BIT.OAE = 1;
		GPT1.GTONCR.BIT.OBE = 1;
		GPT2.GTONCR.BIT.OAE = 1;
		GPT2.GTONCR.BIT.OBE = 1;
	}
	
	
	
	//	HIT_p_getad[0] = S12AD0.ADDR0A ;/*get ad*///20131216//
//		HIT_p_getad[1] = S12AD0.ADDR1 ;//20131216//20140110
		HIT_p_getad[2] = S12AD0.ADDR0A;////////////////////////////////////////
		HIT_p_getad[3] = S12AD1.ADDR0A ;//////////////////////////////////////////
	//	HIT_n_getad[0] = S12AD1.ADDR0A ;//20131216//
//		HIT_n_getad[1] = S12AD1.ADDR1 ;
		HIT_n_getad[2] = S12AD0.ADDR1 ;////////////////////////////////////////////
//		HIT_n_getad[3] = S12AD1.ADDR3 ;
	HIT_Uad = AD0.ADDRB;
//	S12AD0.ADCSR.BIT.ADST=1;
//	S12AD1.ADCSR.BIT.ADST=1;
	AD0.ADCSR.BIT.ADST=1;

	HIT_u_sensor = (HIT_p_getad[2]>>4 );//current U
	HIT_w_sensor = (HIT_p_getad[3]>>4); //current W
	HIT_v_sensor = (HIT_n_getad[2]>>4  );//current V
		
		HIT_iu_fbad = HIT_u_sensor;
		HIT_iw_fbad = HIT_w_sensor;
		HIT_iv_fbad = HIT_v_sensor;
	
		HIT_iu_fbadf = (float)HIT_iu_fbad;
		HIT_iw_fbadf = (float)HIT_iw_fbad;
		HIT_iv_fbadf = (float)HIT_iv_fbad;
		
		HIT_iu_fb = -(HIT_iu_fbadf*HIT_adad-HIT_VOLCENTER);
		HIT_iu_fb = HIT_iu_fb*HIT_curr;//calculate Iu

		HIT_iw_fb = -(HIT_iw_fbadf*HIT_adad-HIT_VOLCENTER);
		HIT_iw_fb = HIT_iw_fb*HIT_curr;//calculate Iw

		HIT_iv_fb = -(HIT_iv_fbadf*HIT_adad-HIT_VOLCENTER);
		HIT_iv_fb = HIT_iv_fb*HIT_curr;//calculate Iv
		
/*get off the drain current*/
	//	HIT_drain = HIT_iu_fb + HIT_iv_fb + HIT_iw_fb;
	//	HIT_drain = HIT_drain/3;
	//	HIT_iu_fb = HIT_iu_fb - HIT_drain;
	//	HIT_iv_fb = HIT_iv_fb - HIT_drain;
	//	HIT_iw_fb = HIT_iw_fb - HIT_drain;/*end*/
				
	HIT_iu_fb_sum = HIT_iu_fb_sum+HIT_iu_fb;
	HIT_iw_fb_sum = HIT_iw_fb_sum+HIT_iw_fb;
	HIT_iv_fb_sum = HIT_iv_fb_sum+HIT_iv_fb;
	if(HIT_system_count == 30000)
	{
		HIT_iu_fb_avg =	HIT_iu_fb_sum/10000;
		HIT_iw_fb_avg =	HIT_iw_fb_sum/10000;
		HIT_iv_fb_avg =	HIT_iv_fb_sum/10000;
//		GPT0.GTONCR.BIT.OAE = 1;
//		GPT0.GTONCR.BIT.OBE = 1;
//		GPT1.GTONCR.BIT.OAE = 1;
//		GPT1.GTONCR.BIT.OBE = 1;
//		GPT2.GTONCR.BIT.OAE = 1;
//		GPT2.GTONCR.BIT.OBE = 1;
	}
		HIT_pwm_aint = 10;/////////////////////////
		HIT_pwm_bint = 10;/////////////////////////
		HIT_pwm_cint = 10;/////////////////////////
		
		HIT_tgr_d_val3=(unsigned short)(HIT_PWM_FULL-HIT_pwm_aint);
		HIT_tgr_b_val3=(unsigned short)(HIT_PWM_FULL-HIT_pwm_aint);
		HIT_tgr_c_val4=(unsigned short)(HIT_PWM_FULL-HIT_pwm_bint);
		HIT_tgr_a_val4=(unsigned short)(HIT_PWM_FULL-HIT_pwm_bint);
		HIT_tgr_b_val4=(unsigned short)(HIT_PWM_FULL-HIT_pwm_cint);
		HIT_tgr_d_val4=(unsigned short)(HIT_PWM_FULL-HIT_pwm_cint);
		
		GPT0.GTCCRC = HIT_tgr_d_val3;
		GPT0.GTCCRE = HIT_tgr_b_val3;
		
		GPT1.GTCCRC = HIT_tgr_c_val4;
		GPT1.GTCCRE = HIT_tgr_a_val4;
		
		GPT2.GTCCRC = HIT_tgr_b_val4;
		GPT2.GTCCRE = HIT_tgr_d_val4;
	HIT_system_count++;
}
#endif