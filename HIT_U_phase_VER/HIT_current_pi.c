#ifndef CURRENT
#define CURRENT

#include "HIT_current_pi.h"
#include "HIT_check_table.h"
#include "HIT_make_angle.h"
#include "iodefine.h"
#include <math.h>
#include <mathf.h>
extern unsigned short  pwm;
extern unsigned char HIT_pwm_mode_choose ;
extern char HIT_ready_go;
extern int HIT_pos_org_int ;
extern char HIT_pos_count;
extern unsigned short HIT_xi_d_count;
//extern float HIT_i_vector_fb;
extern float HIT_run_mode;
extern float HIT_bf_u_open;
//float HIT_i_vector_err;
//float HIT_i_vector_ref = 0.5;
//float HIT_i_vector_org;
//float HIT_U_vector;
extern float HIT_U_FF;
extern float HIT_U_F;
 extern float HIT_bf_c;
 extern float HIT_bf_c_open;
 extern float HIT_I_FF;
 extern float HIT_bf_b;
 int countf=0;
 float HIT_iq_ft_max = 25;
 float HIT_ft = 0.86;
 float HIT_Ud_Uq_sqrt;
void HIT_current_pi()
{
//////////////////////////////////////////////PWM part///////////////////////////////////////////

			
		if(HIT_pwm_stop == 0)
		{
			PORT7.DR.BIT.B1 = 0;
			PORT7.DR.BIT.B2 = 0;
			PORT7.DR.BIT.B3 = 0;
			PORT7.DR.BIT.B4 = 0;
			PORT7.DR.BIT.B5 = 0;
			PORT7.DR.BIT.B6 = 0;
			PORT7.DR.BIT.B0 = 0;
			GPT0.GTONCR.WORD = 0X0000;
			GPT1.GTONCR.WORD = 0X0000;
			GPT2.GTONCR.WORD = 0X0000;
				
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
		HIT_iu_fb = HIT_iu_fb - HIT_iu_fb_avg;//calculate Iu  //20140708
		HIT_iw_fb = -(HIT_iw_fbadf*HIT_adad - HIT_VOLCENTER);
		HIT_iw_fb = HIT_iw_fb*HIT_curr;
		HIT_iw_fb = HIT_iw_fb - HIT_iw_fb_avg;//calculate Iw  //20140708
		
		HIT_iv_fb = -(HIT_iv_fbadf*HIT_adad - HIT_VOLCENTER);
		HIT_iv_fb = HIT_iv_fb*HIT_curr;
		HIT_iv_fb = HIT_iv_fb - HIT_iv_fb_avg;//calculate Iv  //20140708
		//HIT_iw_fb=HIT_iw_fb*40/42;
		//HIT_iw_fb=HIT_iw_fb*37/36;
	//	if(HIT_iu_fb>0) HIT_iu_fb=HIT_iu_fb*36/37;
	//	if(HIT_iv_fb>0) HIT_iv_fb=HIT_iv_fb*36/37;
	//	if(HIT_iw_fb>0) HIT_iw_fb=HIT_iw_fb*36/37;
////////////////////////////////////Y用其中两相求出另一相//////////////////////////////modify20141231//////////////////
//HIT_iu_fb=-HIT_iv_fb-HIT_iw_fb;
//HIT_iv_fb=-HIT_iu_fb-HIT_iw_fb;
//HIT_iw_fb=-HIT_iu_fb-HIT_iv_fb;
//////////////////////////////////////////////////////////////////////////////

/*get off the drain current*/
		HIT_drain = HIT_iu_fb + HIT_iv_fb + HIT_iw_fb;
		HIT_drain = HIT_drain/3;
		HIT_iu_fb = HIT_iu_fb - HIT_drain;
		HIT_iv_fb = HIT_iv_fb - HIT_drain;
		HIT_iw_fb = HIT_iw_fb - HIT_drain;/*end*/
		
		HIT_alarmnew();
				
		HIT_sitadian_check = HIT_sitadian;
		HIT_check_table();/////////////////////////check table

/*3==>2*/	
//countf++;
//if (countf==1000)
//{
//	countf =888;
//	}

		HIT_id_fb = HIT_coszhi_a*HIT_iu_fb;
		HIT_id_fb = HIT_id_fb+HIT_coszhi_c*HIT_iv_fb;
		HIT_id_fb = HIT_id_fb+HIT_coszhi_b*HIT_iw_fb;
		HIT_id_fb = HIT_id_fb*0.6667;//20141226
		
		HIT_iq_fb = -HIT_sinzhi_a*HIT_iu_fb-HIT_sinzhi_c*HIT_iv_fb;
		HIT_iq_fb = HIT_iq_fb-HIT_sinzhi_b*HIT_iw_fb;
		HIT_iq_fb = HIT_iq_fb*0.6667;//20141226
/*i vector*/
/*		if(HIT_run_mode == 9)
		{
			HIT_id_fb = HIT_iu_fb;
			HIT_id_fb = HIT_id_fb-0.5*HIT_iv_fb;
			HIT_id_fb = HIT_id_fb-0.5*HIT_iw_fb;
		
			HIT_iq_fb = 0.866025*HIT_iv_fb;
			HIT_iq_fb = HIT_iq_fb-0.866025*HIT_iw_fb;	
		}*/
//		HIT_i_vector_fb = sqrt(HIT_id_fb*HIT_id_fb + HIT_iq_fb*HIT_iq_fb);		
/*integral lim calculate*/
    HIT_now_voltage_f_out= 24;//300;20151114
//		if(HIT_system_count > HIT_current_inte_mode_select)
//		{
//			HIT_curren_aa_q_max = HIT_curren_aa_q_max_cmt0; 	
//		}
//		else
//		{
//			HIT_curren_aa_q_max = HIT_now_voltage_f_out/HIT_kv+HIT_iq_ft_max;//20141226//*1.2;//*1.2;	//20140430
//		}
		
		
		HIT_curren_aa_q_max = HIT_now_voltage_f_out/HIT_kv+HIT_iq_ft_max;
		
				
		
/*d-PI*/
		
		HIT_id_err = HIT_id_ref-HIT_id_fb;////iu_fb 12nit AD
		HIT_id_err = HIT_id_err*HIT_Ki;
		HIT_id_org = HIT_id_org+HIT_id_err;

//		HIT_curren_aa_q_max = HIT_curren_aa_q_max;///100;
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
		if(HIT_bf_u_open == 2)
		{
//			HIT_Ud = HIT_Ud + HIT_U_FF;		
		}

/*q-PI*/

        HIT_iq_one = HIT_iq_ref;// current filter
        HIT_iq_ref_out = HIT_lpfcurr_1A*HIT_iq_ref_out;
        HIT_iq_ref_out = HIT_iq_ref_out + HIT_lpfcurr_1B*HIT_iq_one;
        HIT_iq_ref_out = HIT_iq_ref_out + HIT_lpfcurr_1B*(HIT_iq_two-HIT_iq_ref_out);
        HIT_iq_two = HIT_iq_one;//filter end
	
		if(HIT_bf_c_open == 2)
		{
			HIT_iq_ref_out = HIT_iq_ref_out + HIT_I_FF*HIT_bf_b;//HIT_iq_ref = HIT_iq_ref + HIT_I_FF*HIT_bf_b;//HIT_M_12_w_ref_err*HIT_WL_Jm/HIT_WL_T_factor*HIT_bf_b;	
		}
		HIT_iq_err = HIT_iq_ref_out-HIT_iq_fb;//HIT_iq_err = HIT_iq_ref-HIT_iq_fb;////iu_fb 12nit AD

		HIT_iq_err = HIT_iq_err*HIT_iq_Ki;
		HIT_iq_org = HIT_iq_org+HIT_iq_err;

//HIT_now_voltage_f_out=300;//20141227
//if(HIT_system_count > HIT_current_inte_mode_select)
//		{
//			HIT_curren_aa_q_max = HIT_curren_aa_q_max_cmt0; 	
//		}
//		else
//		{
//			HIT_curren_aa_q_max = HIT_now_voltage_f_out/HIT_iq_kv+HIT_iq_ft_max;;//20141226//*1.2;//*1.2;	//20140430
//		}	

		HIT_curren_aa_q_max = HIT_now_voltage_f_out/HIT_iq_kv+HIT_iq_ft_max;
		if(HIT_iq_org > HIT_curren_aa_q_max)
		{
			HIT_iq_org = HIT_curren_aa_q_max;	
		}
		if(HIT_iq_org < -HIT_curren_aa_q_max)
		{
			HIT_iq_org = -HIT_curren_aa_q_max;	
		}
		HIT_Uq = (HIT_iq_org + HIT_alfa * HIT_I_FF - HIT_iq_fb)*HIT_kv;
/*		if(HIT_bf_c_open == 2)
		{
			HIT_Uq = HIT_Uq + HIT_I_FF*HIT_bf_b;//HIT_M_12_w_ref_err*HIT_WL_Jm/HIT_WL_T_factor*HIT_bf_b;	
		}*/
		
//		HIT_iq_kv = HIT_kv;
//		HIT_Uq = HIT_Uq * HIT_iq_kv;
		HIT_Uq = HIT_Uq + HIT_Rs*HIT_iq_fb;//+HIT_speedlpf_pole*HIT_Lq*HIT_id_fb;

		HIT_Uq = HIT_Uq + HIT_speedlpf_pole*HIT_Lq*HIT_id_fb;				
		HIT_Uq = HIT_Uq + HIT_speedlpf_pole*HIT_faif;
		
		if(HIT_bf_u_open == 2)
		{
			HIT_Uq = HIT_Uq + HIT_U_F*HIT_bf_c;// + HIT_U_FF;	
		}
		
/*muxian dianliu kongzhi*/
/*	if (HIT_run_mode == 9)
	{
//		HIT_moth_line_vector();
	}*/
/*2==>3*/
		HIT_Vol_adj_fac = HIT_Um_standard/HIT_now_voltage_f_out;//calculate the PWM adjust factor
//		HIT_pwm_mode = HIT_Ud*HIT_Ud+HIT_Uq*HIT_Uq;
//		HIT_pwm_mode = sqrt(HIT_pwm_mode);
///////////////////20141227//////////////
	    HIT_Ud_Uq_sqrt = HIT_Ud*HIT_Ud+HIT_Uq*HIT_Uq;
		
		HIT_Ud_Uq_sqrt = sqrt(HIT_Ud_Uq_sqrt);


		if (HIT_Ud_Uq_sqrt > HIT_now_voltage_f_out*HIT_ft)
		{
			HIT_Ud = HIT_Ud*HIT_now_voltage_f_out*HIT_ft/HIT_Ud_Uq_sqrt;
			HIT_Uq = HIT_Uq*HIT_now_voltage_f_out*HIT_ft/HIT_Ud_Uq_sqrt;
		}
///////////////20141227//////////////////////		
		
//		HIT_pwm_mode_Um = HIT_now_voltage_f_out*0.01;
		
//		HIT_Um = HIT_now_voltage_f_out*0.5;
		HIT_Um = HIT_now_voltage_f_out;
		HIT_pwm_en_out = 1;
	
	
//	HIT_OBC_state();
	
	if(HIT_pwm_en_out == 1)
	{
//		if(HIT_pwm_mode < HIT_pwm_mode_Um)/////////////////////////////if 0.8mutiply///////////////////
//		{
			HIT_vectorcontrol();
//		}		
	/*2==>2*/
//		else
//		{
//			HIT_spacevectorcontrol();
//		}
		
/*			HIT_iuone = HIT_iu_fb;/*current filter u*/
/*			HIT_iulpf = HIT_lpfcurr_1A*HIT_iulpf+HIT_lpfcurr_1B*HIT_iuone+HIT_lpfcurr_1B*(HIT_iutwo-HIT_iulpf);
			HIT_iutwo = HIT_iuone;
		
			HIT_iwone = HIT_iw_fb;/*current filter w*/
/*			HIT_iwlpf = HIT_lpfcurr_1A*HIT_iwlpf+HIT_lpfcurr_1B*HIT_iwone+HIT_lpfcurr_1B*(HIT_iwtwo-HIT_iwlpf);
			HIT_iwtwo = HIT_iwone;
		
			HIT_ivone = HIT_iv_fb;/*current filter v*/
/*			HIT_ivlpf = HIT_lpfcurr_1A*HIT_ivlpf+HIT_lpfcurr_1B*HIT_ivone+HIT_lpfcurr_1B*(HIT_ivtwo-HIT_ivlpf);
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
			
	//		HIT_pwm_af = 1000;
	//		HIT_pwm_bf = 1000;
	//		HIT_pwm_cf = 1000;
			
			HIT_pwm_aint=(signed int)(HIT_pwm_af);
		
			HIT_pwm_bint=(signed int)(HIT_pwm_bf);
		
			HIT_pwm_cint=(signed int)(HIT_pwm_cf);
		
			if(HIT_pwm_aint>HIT_PWM_FULL)//dont over max
			{
				HIT_pwm_aint=HIT_PWM_FULL;	
			}
			if(HIT_pwm_bint>HIT_PWM_FULL)
			{
				HIT_pwm_bint=HIT_PWM_FULL;	
			}
			if(HIT_pwm_cint>HIT_PWM_FULL)
			{
				HIT_pwm_cint=HIT_PWM_FULL;	
			}
			
/*			
	     HIT_WJW_U1 = (unsigned short)HIT_PWM_FULL-HIT_pwm_aint;
	     HIT_WJW_U2 = (unsigned short)HIT_PWM_FULL-HIT_pwm_aint;
		 HIT_WJW_V1 = (unsigned short)HIT_PWM_FULL-HIT_pwm_bint;
		 HIT_WJW_V2 = (unsigned short)HIT_PWM_FULL-HIT_pwm_bint;
		 HIT_WJW_W1 = (unsigned short)HIT_PWM_FULL-HIT_pwm_cint;
	     HIT_WJW_W2 = (unsigned short)HIT_PWM_FULL-HIT_pwm_cint;*/
/*			
			HIT_tgr_d_val3= 0;
			HIT_tgr_b_val3= 0;
			HIT_tgr_c_val4= 0; 
			HIT_tgr_a_val4= 0;
			HIT_tgr_b_val4= 0;
			HIT_tgr_d_val4= 0;
		*/	
		
			HIT_tgr_d_val3= (unsigned short)(HIT_PWM_FULL-HIT_pwm_aint);//(unsigned short)HIT_WJW_U1;//(unsigned short)(HIT_PWM_FULL-HIT_pwm_aint);
			HIT_tgr_b_val3= (unsigned short)(HIT_PWM_FULL-HIT_pwm_aint);//(unsigned short)HIT_WJW_U2;//
			HIT_tgr_c_val4= (unsigned short)(HIT_PWM_FULL-HIT_pwm_bint);// (unsigned short)HIT_WJW_V1;//
			HIT_tgr_a_val4= (unsigned short)(HIT_PWM_FULL-HIT_pwm_bint);//(unsigned short)HIT_WJW_V2;//
			HIT_tgr_b_val4= (unsigned short)(HIT_PWM_FULL-HIT_pwm_cint);//(unsigned short)HIT_WJW_W1;//
			HIT_tgr_d_val4= (unsigned short)(HIT_PWM_FULL-HIT_pwm_cint);//(unsigned short)HIT_WJW_W2;//
		
/*			HIT_tgr_d_val3= 670;
			HIT_tgr_b_val3= 670;
			HIT_tgr_c_val4= 500; 
			HIT_tgr_a_val4= 500;
			HIT_tgr_b_val4= 500;
			HIT_tgr_d_val4= 500;*/
		switch(HIT_pwm_mode_choose)	
		{
			case 1:
			PORT7.DR.BIT.B0 = 1;
			GPT0.GTCCRC = HIT_tgr_d_val3;
			GPT0.GTCCRE = HIT_tgr_b_val3;
		
			GPT1.GTCCRC = HIT_tgr_c_val4;
			GPT1.GTCCRE = HIT_tgr_a_val4;
		
			GPT2.GTCCRC = HIT_tgr_b_val4;
			GPT2.GTCCRE = HIT_tgr_d_val4;
			break;
			case 2:
			
		//	HIT_pos_org_int = 0;
	     	PORT7.DR.BIT.B0 = 0;
			HIT_servo_on_first();
			HIT_pos_count = 1;
			HIT_ready_go = 0;
			PORT7.DR.BIT.B1 = 0;
			PORT7.DR.BIT.B2 = 0;
			PORT7.DR.BIT.B3 = 0;
			PORT7.DR.BIT.B4 = 0;
			PORT7.DR.BIT.B5 = 0;
			PORT7.DR.BIT.B6 = 0;
			//PORT7.DR.BIT.B0 = 0;
			GPT0.GTONCR.WORD = 0X0000;
			GPT1.GTONCR.WORD = 0X0000;
			GPT2.GTONCR.WORD = 0X0000;
			break;
			case 3:
			PORT7.DR.BIT.B0 = 0;
		//	HIT_pos_org_int = 0;
			HIT_servo_on_first();
			HIT_pos_count = 1;
			HIT_ready_go = 0;
			PORT7.DR.BIT.B1 = 0;
			PORT7.DR.BIT.B2 = 0;
			PORT7.DR.BIT.B3 = 0;
			PORT7.DR.BIT.B4 = 0;
			PORT7.DR.BIT.B5 = 0;
			PORT7.DR.BIT.B6 = 0;
			//PORT7.DR.BIT.B0 = 0;
			GPT0.GTONCR.WORD = 0X0000;
			GPT1.GTONCR.WORD = 0X0000;
			GPT2.GTONCR.WORD = 0X0000;
			break;
		}

	}
		
}
#endif
