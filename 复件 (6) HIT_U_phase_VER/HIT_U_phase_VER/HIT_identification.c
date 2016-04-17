#ifndef IDENTIFICATIONC
#define IDENTIFICATIONC
#include "iodefine.h"
#include "HIT_identification.h"
void HIT_identification()
{
	if(HIT_qa_iden_L< 20000)//小于2s
	{	
/*return to motor zero point*/
		if(HIT_qa_iden_L < 4000)//0~0.4s
		{
			HIT_gpton();
		}
		/*get Ld Lq*/
		else
		{
			if(HIT_qa_iden_L < 6000)//turn off GPT 0.4s~0.6s	
			{
				HIT_gptoff();
				if(HIT_qa_iden_L == 5999)
				{
					HIT_gpton();	
				}	
			}
			else
			{
				if(HIT_qa_iden_L<6500)//growing 0.6s~0.65s
				{
					HIT_id_fb_iden_L = HIT_id_fb_iden;
					HIT_iq_fb_iden_L = HIT_iq_fb_iden;
					HIT_id_fb_iden_org_L = HIT_id_fb_iden_L * HIT_Ts_iden;
					HIT_id_fb_orgin_iden_L = HIT_id_fb_iden_org_L + HIT_id_fb_orgin_iden_L;
					HIT_id_fb_iden_L_end = HIT_id_fb_iden_L;
					HIT_qa_iden_L_end = HIT_qa_iden_L-6000;
				}	
				else
				{
					if(HIT_qa_iden_L < 16000)//steady 0.9s~1.6s
					{
						HIT_R_iden = HIT_iden_Ud/HIT_id_fb_iden;	
						HIT_L_iden = (HIT_Ts_iden*HIT_qa_iden_L_end*HIT_iden_Ud - HIT_id_fb_orgin_iden_L*HIT_R_iden)/HIT_id_fb_iden_L_end;
					}
					else//1.6s~
					{
						HIT_gptoff();
						S12AD0.ADCSR.BIT.ADST=1;
						S12AD1.ADCSR.BIT.ADST=1;
						AD0.ADCSR.BIT.ADST=1;
						HIT_p_getad[3] = S12AD0.ADDR3 ;
						HIT_n_getad[3] = S12AD1.ADDR3 ;
						HIT_v_sensor_10wei = AD0.ADDRA;
						HIT_u_sensor = (HIT_p_getad[3]>>4); //current signal u
						HIT_w_sensor = (HIT_n_getad[3]>>4);//current signal	w
						HIT_v_sensor_10wei = (HIT_v_sensor_10wei>>6);
						HIT_iu_fbad = HIT_u_sensor;
						HIT_iw_fbad = HIT_w_sensor;
						HIT_v_sensor_10weiad = HIT_v_sensor_10wei;
						HIT_iu_fbadf = (float)HIT_iu_fbad;
						HIT_iw_fbadf = (float)HIT_iw_fbad;
						HIT_v_sensor_10weiadf = (float)HIT_v_sensor_10weiad;
						HIT_iu_fb = (HIT_iu_fbadf*HIT_adad-HIT_VOLCENTER)*HIT_curr;
						HIT_iw_fb = (HIT_iw_fbadf*HIT_adad-HIT_VOLCENTER)*HIT_curr;
						HIT_iv_fb_10wei = (HIT_v_sensor_10weiadf*HIT_adad_10wei-HIT_VOLCENTER)*HIT_curr;
	
						HIT_iu_fb_sum = HIT_iu_fb_sum+HIT_iu_fb;
						HIT_iw_fb_sum = HIT_iw_fb_sum+HIT_iw_fb;
						HIT_iv_fb_sum = HIT_iv_fb_sum+HIT_iv_fb_10wei;
						if(HIT_qa_iden_L == 19999)
						{
							HIT_iu_fb_avg =	HIT_iu_fb_sum/4000;
							HIT_iw_fb_avg =	HIT_iw_fb_sum/4000;
							HIT_iv_fb_avg =	HIT_iv_fb_sum/4000;
							HIT_gpton();	
							HIT_WLw_ref = HIT_WLw_ref_iden;
						}	
					}
				}
			}
		}
/*get ad*/
			HIT_p_getad_iden[3] = S12AD0.ADDR3 ;
			HIT_n_getad_iden[3] = S12AD1.ADDR3 ;
			HIT_Uad_iden = AD0.ADDRB;
			S12AD0.ADCSR.BIT.ADST=1;
			S12AD1.ADCSR.BIT.ADST=1;
			AD0.ADCSR.BIT.ADST=1;
/*get Um */	
			HIT_Umsensor_iden = (HIT_Uad_iden>>6); //get Um ad
			HIT_Umsensor_iden_f = (float)HIT_Umsensor_iden;/*calculate voltage*/
			HIT_Um_standard_iden = 37;//27.2;//modify on 20120415
			HIT_Umsensor_iden_f_standard = HIT_Umsensor_f_standard;
			HIT_now_voltage_iden_f = (HIT_Um_standard_iden/HIT_Umsensor_iden_f_standard)* HIT_Umsensor_iden_f;
		
			//HIT_Vol_adj_fac_iden = HITUm_standard_iden/HIT_now_voltage_iden_f;//pwm adjust factor//modify on 20120415
			//HIT_iden_Um = HIT_now_voltage_iden_f;//modify on 20120415
			HIT_iden_Um = 27.2;//modify on 20120415
			HIT_Vol_adj_fac_iden = HIT_Um_standard_iden/HIT_iden_Um;//pwm adjust factor
/*out put  pwm*/
			HIT_iden_Uu = 4;//v
			HIT_iden_Uv = 0;
			HIT_iden_Uw = 0;
	
			HIT_pwm_iden_u_f = HIT_iden_Uu/HIT_iden_Um*4000+2400;
			HIT_pwm_iden_v_f = 2400;
			HIT_pwm_iden_w_f = 2400;
	
			HIT_pwm_iden_u_int = (int)HIT_pwm_iden_u_f;
			HIT_pwm_iden_v_int = (int)HIT_pwm_iden_v_f;
			HIT_pwm_iden_w_int = (int)HIT_pwm_iden_w_f;
	
			HIT_tgr_d_val3_iden = (unsigned short)(HIT_pwm_full_iden-HIT_pwm_iden_u_int);
			HIT_tgr_b_val3_iden = (unsigned short)(HIT_pwm_full_iden-HIT_pwm_iden_u_int);
			HIT_tgr_c_val4_iden = (unsigned short)(HIT_pwm_full_iden-HIT_pwm_iden_v_int);
			HIT_tgr_a_val4_iden = (unsigned short)(HIT_pwm_full_iden-HIT_pwm_iden_v_int);
			HIT_tgr_b_val4_iden = (unsigned short)(HIT_pwm_full_iden-HIT_pwm_iden_w_int);
			HIT_tgr_d_val4_iden = (unsigned short)(HIT_pwm_full_iden-HIT_pwm_iden_w_int);
		
			GPT0.GTCCRC = HIT_tgr_d_val3_iden;
			GPT0.GTCCRE = HIT_tgr_b_val3_iden;
			GPT1.GTCCRC = HIT_tgr_c_val4_iden;
			GPT1.GTCCRE = HIT_tgr_a_val4_iden;
			GPT2.GTCCRC = HIT_tgr_b_val4_iden;
			GPT2.GTCCRE = HIT_tgr_d_val4_iden;	
/*end*/		
/*Ud Uq 3->2*/
			HIT_iden_Ud = HIT_iden_Uu-0.5*(HIT_iden_Uv+HIT_iden_Uw);
			HIT_iden_Uq = 0.866025*(HIT_iden_Uv-HIT_iden_Uw);
/*get current*/		
			HIT_u_sensor_iden = (HIT_p_getad_iden[3]>>4); //current signal
			HIT_w_sensor_iden = (HIT_n_getad_iden[3]>>4);//current signal
				
			HIT_iu_fbad_iden = HIT_u_sensor_iden;
			HIT_iw_fbad_iden = HIT_w_sensor_iden;
			HIT_iu_fbadf_iden = (float)HIT_iu_fbad_iden;
			HIT_iw_fbadf_iden = (float)HIT_iw_fbad_iden;
			HIT_curr_sen_iden = HIT_curr_sen;
			HIT_curr_iden = (float)1000/HIT_curr_sen_iden;
		
			HIT_adad_iden = (float)HIT_volfive_iden/HIT_ad12_iden;
			HIT_iu_fb_iden = HIT_iu_fbadf_iden*HIT_adad_iden-HIT_volcenter_iden;
			HIT_iu_fb_iden = HIT_iu_fb_iden*HIT_curr_iden;//calculate Iu

			HIT_iw_fb_iden = HIT_iw_fbadf_iden*HIT_adad_iden-HIT_volcenter_iden;
			HIT_iw_fb_iden = HIT_iw_fb_iden*HIT_curr_iden;//calculate Iw
			HIT_iv_fb_iden = -(HIT_iu_fb_iden+HIT_iw_fb_iden);//-HIT_iv_fb_avg;
/*get off the drain current*/
			HIT_drain_iden = HIT_iu_fb_iden + HIT_iv_fb_iden + HIT_iw_fb_iden;
			HIT_drain_iden = HIT_drain_iden/3;
			HIT_iu_fb_iden = HIT_iu_fb_iden - HIT_drain_iden;
			HIT_iv_fb_iden = HIT_iv_fb_iden - HIT_drain_iden;
			HIT_iw_fb_iden = HIT_iw_fb_iden - HIT_drain_iden;
/*end*/
/*Id Iq 3->2*/
			HIT_id_fb_iden = HIT_iu_fb_iden-0.5*(HIT_iv_fb_iden+HIT_iw_fb_iden);
			HIT_iq_fb_iden = 0.866025*(HIT_iv_fb_iden-HIT_iw_fb_iden);
	}
	else//大于2s
	{
		if(HIT_qa_iden_L == 20000)
		{
			HIT_servofirst();	
		}
		else
		{
			if(HIT_qa_iden_L < 150000)
			{
				HIT_make_angle();
				HIT_mechanicalpi();
				HIT_current_pi();
				HIT_speedlpf_iden_fai = HIT_speedlpf;
				HIT_iq_fb_iden_fai = HIT_iq_fb;
				HIT_id_fb_iden_fai = HIT_id_fb;
				HIT_Uq_iden_fai = HIT_Uq;
				HIT_spe_id_iden_fai = HIT_speedlpf_iden_fai*HIT_id_fb_iden_fai;
				HIT_iq_fb_iden_fai_org = HIT_iq_fb_iden_fai_org + HIT_iq_fb_iden_fai * HIT_Ts_iden;//iq org
				HIT_id_fb_iden_fai_org = HIT_id_fb_iden_fai_org + HIT_id_fb_iden_fai * HIT_Ts_iden;//iq org
			//	HIT_spe_id_iden_fai_org = HIT_spe_id_iden_fai_org + HIT_spe_id_iden_fai * HITTs_iden;//w*id org
				HIT_Uq_iden_fai_org = HIT_Uq_iden_fai_org  + HIT_Uq_iden_fai * HIT_Ts_iden;//Uq org
				HIT_fai_iden = HIT_Uq_iden_fai_org ;
				HIT_fai_iden = HIT_fai_iden - HIT_L_iden*HIT_iq_fb_iden_fai;
				HIT_fai_iden = HIT_fai_iden - HIT_R_iden*HIT_iq_fb_iden_fai_org;
				HIT_fai_iden = HIT_fai_iden - HIT_L_iden*HIT_id_fb_iden_fai_org*HIT_WLw_ref_iden;
				HIT_fai_iden = HIT_fai_iden/HIT_WLw_ref_iden/13;
			//	HIT_fai_iden = HIT_fai_iden/376.99152;
			}
			else// 大于15s
			{
				HIT_gptoff();
				GPT0.GTONCR.BIT.OAE = 0;	
			}
		}

	}
		HIT_qa_iden_L++;
	if(HIT_qa_iden_L>150050)
	{
		HIT_qa_iden_L = 150050;	
	}
}
#endif