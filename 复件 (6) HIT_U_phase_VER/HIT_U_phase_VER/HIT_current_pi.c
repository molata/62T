#ifndef CURRENT
#define CURRENT

#include "HIT_current_pi.h"
#include "HIT_check_table.h"
#include "HIT_make_angle.h"
#include "iodefine.h"
#include <math.h>
#include <mathf.h>
extern unsigned short  pwm;
void HIT_current_pi()
{
		//////////////////////////////////////////////PWM part
	
		if(HIT_pwm_stop == 0)
		{
			GPT0.GTONCR.BIT.OAE = 0;
			GPT0.GTONCR.BIT.OBE = 0;
			GPT1.GTONCR.BIT.OAE = 0;
			GPT1.GTONCR.BIT.OBE = 0;
			GPT2.GTONCR.BIT.OAE = 0;
			GPT2.GTONCR.BIT.OBE = 0;	
		}
		else
		{
			GPT0.GTONCR.BIT.OAE = 1;
			GPT0.GTONCR.BIT.OBE = 1;
			GPT1.GTONCR.BIT.OAE = 1;
			GPT1.GTONCR.BIT.OBE = 1;
			GPT2.GTONCR.BIT.OAE = 1;
			GPT2.GTONCR.BIT.OBE = 1;	
		}
		HIT_iu_fbad = HIT_u_sensor;
		HIT_iv_fbad = HIT_v_sensor;
		HIT_iw_fbad = HIT_w_sensor;
/*instance current alarm */		
		if((HIT_iu_fbad > HIT_CURRENT_INS_MAX)||(HIT_iu_fbad < HIT_CURRENT_INS_MIN))
		{
			//	HIT_pwm_stop = 0;	//current alam 1
		}
		if((HIT_iw_fbad > HIT_CURRENT_INS_MAX)||(HIT_iw_fbad < HIT_CURRENT_INS_MIN))
		{
			//	HIT_pwm_stop = 0;	//current alam 1
		}
		HIT_iu_fbadf = (float)HIT_iu_fbad;
		HIT_iw_fbadf = (float)HIT_iw_fbad;
		HIT_iv_fbadf = (float)HIT_iv_fbad;
/*calculate current ad averge*/		
		HIT_iu_fbadf = HIT_iu_fbadf;
		HIT_iw_fbadf = HIT_iw_fbadf;
		HIT_iv_fbadf = HIT_iv_fbadf;
/*calculate current ad averge end*/			
		HIT_iu_fb = -(HIT_iu_fbadf*HIT_adad - HIT_VOLCENTER);
		HIT_iu_fb = HIT_iu_fb*HIT_curr;
		HIT_iu_fb = HIT_iu_fb - HIT_iu_fb_avg;//calculate Iu
		HIT_iw_fb = -(HIT_iw_fbadf*HIT_adad - HIT_VOLCENTER);
		HIT_iw_fb = HIT_iw_fb*HIT_curr;
		HIT_iw_fb = HIT_iw_fb - HIT_iw_fb_avg;//calculate Iw
		
		HIT_iv_fb = -(HIT_iv_fbadf*HIT_adad - HIT_VOLCENTER);
		HIT_iv_fb = HIT_iv_fb*HIT_curr;
		HIT_iv_fb = HIT_iv_fb - HIT_iv_fb_avg;//calculate Iv
		
/*get off the drain current*/
		HIT_drain = HIT_iu_fb + HIT_iv_fb + HIT_iw_fb;
		HIT_drain = HIT_drain/3;
		HIT_iu_fb = HIT_iu_fb - HIT_drain;
		HIT_iv_fb = HIT_iv_fb - HIT_drain;
		HIT_iw_fb = HIT_iw_fb - HIT_drain;/*end*/
				
		HIT_sitadian_check = HIT_sitadian;
		HIT_check_table();/////////////////////////check table
	
/*3==>2*/	
		
		HIT_id_fb = HIT_coszhi_a*HIT_iu_fb;
		HIT_id_fb = HIT_id_fb+HIT_coszhi_c*HIT_iv_fb;
		HIT_id_fb = HIT_id_fb+HIT_coszhi_b*HIT_iw_fb;
		
		HIT_iq_fb = -HIT_sinzhi_a*HIT_iu_fb-HIT_sinzhi_c*HIT_iv_fb;
		HIT_iq_fb = HIT_iq_fb-HIT_sinzhi_b*HIT_iw_fb;
		
/*integral lim calculate*/
		if(HIT_system_count > HIT_current_inte_mode_select)
		{
			HIT_curren_aa_q_max = HIT_curren_aa_q_max_cmt0; 	
		}
		else
		{
			HIT_curren_aa_q_max = HIT_now_voltage_f_out/HIT_kv;	
		}		
		
/*d-PI*/
		
		HIT_id_err = HIT_id_ref-HIT_id_fb;////iu_fb 12nit AD
		HIT_id_err = HIT_id_err*HIT_Ki;
		HIT_id_org = HIT_id_org+HIT_id_err;

		HIT_curren_aa_q_max = HIT_curren_aa_q_max;///100;
		if(HIT_id_org > HIT_curren_aa_q_max)
		{
			HIT_id_org = HIT_curren_aa_q_max;
		}
		if(HIT_id_org < -HIT_curren_aa_q_max)
		{
			HIT_id_org = -HIT_curren_aa_q_max;	
		}
		
		HIT_Ud = (HIT_id_org+HIT_alfa*HIT_id_ref-HIT_id_fb)*HIT_kv;
		HIT_Ud = HIT_Ud + HIT_Rs*HIT_id_fb;
		HIT_Ud = HIT_Ud-HIT_speedlpf_pole*HIT_Lq*HIT_iq_fb;/*claculate Ud*/ 

/*q-PI*/

		HIT_iq_err = HIT_iq_ref-HIT_iq_fb;////iu_fb 12nit AD
		HIT_iq_err = HIT_iq_err*HIT_Ki;
		HIT_iq_org = HIT_iq_org+HIT_iq_err;


		
		if(HIT_iq_org > HIT_curren_aa_q_max)
		{
			HIT_iq_org = HIT_curren_aa_q_max;	
		}
		if(HIT_iq_org < -HIT_curren_aa_q_max)
		{
			HIT_iq_org = -HIT_curren_aa_q_max;	
		}
		HIT_Uq = (HIT_iq_org + HIT_alfa * HIT_iq_ref - HIT_iq_fb) * HIT_kv;
		HIT_Uq = HIT_Uq + HIT_Rs*HIT_iq_fb+HIT_speedlpf_pole*HIT_Lq*HIT_id_fb;
		HIT_Uq = HIT_Uq + HIT_speedlpf_pole*HIT_faif;	
/*2==>3*/
//		HIT_now_voltage_f = 37;//27.2;
		HIT_Vol_adj_fac = HIT_Um_standard/HIT_now_voltage_f_out;//calculate the PWM adjust factor
//		HIT_Um = HITnow_voltage_f_out;//give ad_now Voltage  modify on 20120414
//		HIT_Um = 37;//27.2;// modify on 20120414	
	    HIT_pwm_mode = HIT_Ud*HIT_Ud+HIT_Uq*HIT_Uq;
		HIT_pwm_mode = sqrt(HIT_pwm_mode);
		HIT_pwm_mode_Um = HIT_now_voltage_f_out*0.01;
		
		HIT_Um = HIT_now_voltage_f_out;
		HIT_pwm_en_out = 1;
		
	if(HIT_pwm_en_out == 1)
	{
		if(HIT_pwm_mode < HIT_pwm_mode_Um)/////////////////////////////if 0.8mutiply///////////////////
		{
			HIT_vectorcontrol();
		}		
	/*2==>2*/
		else
		{
			HIT_spacevectorcontrol();
		}
		
	/*		HIT_iuone = HIT_iu_fb;/*current filter u*/
	/*		HIT_iulpf = HIT_lpfcurr_1A*HIT_iulpf+HIT_lpfcurr_1B*HIT_iuone+HIT_lpfcurr_1B*(HIT_iutwo-HIT_iulpf);
			HIT_iutwo = HIT_iuone;
		
			HIT_iwone = HIT_iw_fb;/*current filter w*/
	/*		HIT_iwlpf = HIT_lpfcurr_1A*HIT_iwlpf+HIT_lpfcurr_1B*HIT_iwone+HIT_lpfcurr_1B*(HIT_iwtwo-HIT_iwlpf);
			HIT_iwtwo = HIT_iwone;
		
			HIT_ivone = HIT_iv_fb;/*current filter v*/
	/*		HIT_ivlpf = HIT_lpfcurr_1A*HIT_ivlpf+HIT_lpfcurr_1B*HIT_ivone+HIT_lpfcurr_1B*(HIT_ivtwo-HIT_ivlpf);
			HIT_ivtwo = HIT_ivone;
		
			HIT_iu_fb = HIT_iulpf;
			HIT_iw_fb = HIT_iwlpf;
			HIT_iv_fb = HIT_ivlpf;*//*end*/
	/*pwm dead zone offser*/		
	/*		if(HIT_iu_fb<0)
			{
				HIT_pwm_af = HIT_pwm_af-HITpwm_deadoff;
			}
			if(HIT_iv_fb<0)
			{
				HIT_pwm_bf = HIT_pwm_bf-HITpwm_deadoff;
			}
			if(HIT_iw_fb<0)
			{
				HIT_pwm_cf = HIT_pwm_cf-HITpwm_deadoff;
			}*/
//			HIT_pwm_af = 2000;
//			HIT_pwm_bf = 2000;
//			HIT_pwm_cf = 3300;			
			
			HIT_pwm_aint=(signed int)(HIT_pwm_af);
		
			HIT_pwm_bint=(signed int)(HIT_pwm_bf);
		
			HIT_pwm_cint=(signed int)(HIT_pwm_cf);
		
			if(HIT_pwm_aint>HIT_PWMOUTULIM)//dont over max
			{
				HIT_pwm_aint=HIT_PWMOUTULIM;	
			}
			if(HIT_pwm_bint>HIT_PWMOUTULIM)
			{
				HIT_pwm_bint=HIT_PWMOUTULIM;	
			}
			if(HIT_pwm_cint>HIT_PWMOUTULIM)
			{
				HIT_pwm_cint=HIT_PWMOUTULIM;	
			}
//			HIT_pwm_aint = 2500;
//			HIT_pwm_bint = 2000;
//			HIT_pwm_cint = 2000;
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

	}
		
}
#endif
