#ifndef POSITIONCONTROLC
#define POSITIONCONTROLC
#include"HIT_positioncontrol.h"
#include<math.h>
#include<mathf.h>
unsigned short HIT_filter_initial = 1;
extern unsigned short HIT_filter_depth;
unsigned short HIT_filter_i;
int HIT_a_phase_filter[16];
int HIT_a_phase_sum;
char HIT_speed_zero = 0;
extern int HIT_new_angle_int;
extern int HIT_sitaintf_curr_int;
extern float HIT_alarm;
extern float HIT_run_mode;
float HIT_gear_num_f = 65536;
extern int HIT_alarm_num;
extern float HIT_M_12_w_out;
extern unsigned short HIT_new_angle_short;
extern float HIT_M_12_w_ref;
extern float HIT_bf_m_open;
extern float HIT_bf_a;
extern float HIT_W_FF;
extern float HIT_w_F_FF_out;
extern float HIT_w_F_FF;
float  HIT_virtual_ps_int_err_f_org = 0;
int HIT_virtual_ps_int_err_f_org_int = 0;
int HIT_virtual_ps_int_err_f_org_int_1 = 0;
int HIT_virtual_ps_int_err_f_org_int_err = 0;
int HIT_virtual_ps_int_err_f_org_int_2 = 0;
int HIT_virtual_ps_int_err_int =0 ;
int HIT_virtual_ps_int_err_int_org = 0;
float HIT_OBW_Err_P_f = 0;
extern float HIT_OBW_Err;
float HIT_OBW_kc = 0;
#define HIT_PIE 3.1415926
float HIT_FF_REF_err_out_f = 0;
extern float HIT_M_12_w_out_org;
float HIT_mode_15_fb_angle_f_org = 0;
float HIT_FB_REF_err_out_f = 0;
float HIT_BF_REF_err_out_f = 0; //20140112 前馈与反馈差
void HIT_positioncontrol()
{
	if((HIT_run_mode != 12)&&(HIT_run_mode != 13)&&(HIT_run_mode != 15))
	{
		HIT_virtual_ps_int_fir = HIT_virtual_ps_int;	
		HIT_virtual_ps_int_err = HIT_virtual_ps_int_fir-HIT_virtual_ps_int_sec;//get virtual_ps err
		HIT_virtual_ps_int_sec = HIT_virtual_ps_int_fir;
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		if(HIT_virtual_ps_int_err>HIT_angle_zero_pass_lim)//virtual_ps zero pass offset
		{
			HIT_virtual_ps_int_err = HIT_virtual_ps_int_err - HIT_ANGLE_16;	
		}
		if(HIT_virtual_ps_int_err<-HIT_angle_zero_pass_lim)
		{
			HIT_virtual_ps_int_err = HIT_virtual_ps_int_err + HIT_ANGLE_16;	
		}
		if(HIT_filter_initial == 1)
		{
			HIT_filter_initial = 0;
			HIT_filter_depth = 0;
			for (HIT_filter_i=0;HIT_filter_i<16;HIT_filter_i++)
			{
				HIT_a_phase_filter[HIT_filter_i] = HIT_virtual_ps_int_err;
				HIT_a_phase_sum = HIT_virtual_ps_int_err << 4;
			}		
		}
	
		HIT_a_phase_sum -= HIT_a_phase_filter[HIT_filter_depth];
	
		HIT_a_phase_filter[HIT_filter_depth] = HIT_virtual_ps_int_err;
	
		HIT_a_phase_sum += HIT_virtual_ps_int_err;
	
		++HIT_filter_depth;
		if(HIT_filter_depth == 16)
		{
			HIT_filter_depth = 0;
		}
		
	//	HIT_virtual_ps_int_err = (int)(HIT_a_phase_sum/16);
		HIT_virtual_ps_int_err_f = (float)HIT_a_phase_sum;
	}
//	if((HIT_run_mode == 12)||(HIT_run_mode == 13))
	if((HIT_run_mode == 13))
	{
		HIT_virtual_ps_int_err_f = HIT_M_12_w_out;	
	}
	if((HIT_run_mode == 15)||(HIT_run_mode == 12))
	{
		HIT_virtual_ps_int_err_int_int = HIT_virtual_ps_int_err_f_org_int_err;

		HIT_virtual_ps_int_err_f = HIT_w_F_FF_out;//HIT_w_F_FF;
//		HIT_virtual_ps_int_err_int = (int)HIT_w_F_FF;
		HIT_virtual_ps_int_err_f_org = HIT_virtual_ps_int_err_f + HIT_virtual_ps_int_err_f_org	;
//		HIT_virtual_ps_int_err_int_org = HIT_virtual_ps_int_err_int + HIT_virtual_ps_int_err_int_org	;
		HIT_virtual_ps_int_err_f_org_int  = (int)HIT_virtual_ps_int_err_f_org;
//		HIT_virtual_ps_int_err_f_org_int  = (int)HIT_virtual_ps_int_err_int_org;
		HIT_virtual_ps_int_err_f_org_int_1 = HIT_virtual_ps_int_err_f_org_int;
		HIT_virtual_ps_int_err_f_org_int_err = HIT_virtual_ps_int_err_f_org_int_1 - HIT_virtual_ps_int_err_f_org_int_2;
		HIT_virtual_ps_int_err_f_org_int_2 = HIT_virtual_ps_int_err_f_org_int_1; 
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	HIT_FF_REF_err_out_f = HIT_M_12_w_out_org - HIT_virtual_ps_int_err_f_org;
	

/*digital gear*/
//	HIT_virtual_ps_int_err_f = (float)HIT_virtual_ps_int_err;
/*	if((HIT_run_mode == 3))
	{
		HIT_gear_num_f = 4096;	
	}
	if(HIT_run_mode == 4)
	{
		HIT_gear_num_f = 768;	
	}*/
	if((HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 15)||(HIT_run_mode == 21))
	{
		HIT_gear_num_f = 65536;	
	}
	HIT_virtual_ps_int_err_sum_f  = HIT_virtual_ps_int_err_sum_f + HIT_virtual_ps_int_err_f * HIT_gear_num_f;//4096;//768;//3072;//HIT_ANGLE_16; 
	HIT_position_client_f = (float)HIT_position_client_int;
//	HIT_position_client_f = 65536;//625;
//	if((HIT_run_mode == 3)||(HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 15))
	if((HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 15)||(HIT_run_mode == 21))
	{
		HIT_position_client_f = 65536;	
	}
/*	if(HIT_run_mode == 4)
	{
		HIT_position_client_f = 625;	
	}*/
	if(HIT_run_mode != 15)
	{
		HIT_virtual_ps_int_err_int_f =  HIT_virtual_ps_int_err_sum_f/HIT_position_client_f;
		HIT_virtual_ps_int_err_int_int = (int)HIT_virtual_ps_int_err_int_f; //get int part
		HIT_virtual_ps_int_err_float_f = HIT_virtual_ps_int_err_int_f - (float)HIT_virtual_ps_int_err_int_int;//get float part
		HIT_virtual_ps_int_err_sum_f = HIT_virtual_ps_int_err_float_f*HIT_position_client_f;
	}
/*	if(HIT_run_mode == 15)
	{
	}*/
/*calculate end*/	

//	HIT_position_fb_f = HIT_sita;//add on 2012.4.13
//	HIT_positionfir_fb_16_int = (int)(HIT_position_fb_f * HIT_POSITIONERR_16WEI);//get position_fb_int 1
		
	HIT_positionfir_fb_16_int = (int)HIT_new_angle_short;//HIT_new_angle_int;//get position_fb_int 1

	HIT_position_fb_err_16_int =  HIT_positionfir_fb_16_int - HIT_position1_fb_16_int;//HIT_position1_fb_16_int - HIT_positionfir_fb_16_int;//HITpositionfir_fb_16_int - HITposition1_fb_16_int;//get positon feed back err
	HIT_position1_fb_16_int = HIT_positionfir_fb_16_int;//get position_fb_int 2
	if(HIT_position_fb_err_16_int >HIT_angle_zero_pass_lim )//positon_fb zero pass offset
	{
		HIT_position_fb_err_16_int = HIT_position_fb_err_16_int-HIT_ANGLE_16;	
	}
	if(HIT_position_fb_err_16_int < -HIT_angle_zero_pass_lim )
	{
		HIT_position_fb_err_16_int = HIT_position_fb_err_16_int+HIT_ANGLE_16;	
	}

	HIT_mode_15_fb_angle_f_org = (float)HIT_position_fb_err_16_int + HIT_mode_15_fb_angle_f_org;

	HIT_position_err_int = HIT_virtual_ps_int_err_int_int - HIT_position_fb_err_16_int;//get position err
	HIT_pos_org_int = HIT_pos_org_int + HIT_position_err_int;
	HIT_pos_org_f = (float)HIT_pos_org_int;
	
	HIT_FB_REF_err_out_f = HIT_M_12_w_out_org -  HIT_mode_15_fb_angle_f_org;
//	HIT_FB_REF_err_out_f = HIT_virtual_ps_int_err_f_org -  HIT_mode_15_fb_angle_f_org;
	
	HIT_BF_REF_err_out_f = HIT_virtual_ps_int_err_f_org -  HIT_mode_15_fb_angle_f_org;// 20140112 前馈与反馈指令差
	
	
	HIT_OBW_Err_P_f = HIT_pos_org_f + HIT_OBW_Err/2/HIT_PIE*65536;
/*	
	if((HIT_pos_org_int > 165536)||(HIT_pos_org_int < -165536))
	{
		HIT_alarm = 1;
		HIT_alarm_num = 5;	
	}
	
	*/
//	HIT_WLw_ref = (HIT_pos_org_f*(1-HIT_OBW_kc) +  HIT_OBW_Err_P_f*HIT_OBW_kc)*HIT_positon_Kp_f/20000;//*20000;
	HIT_WLw_ref = (HIT_pos_org_f*(1-HIT_OBW_kc))*HIT_positon_Kp_f/65535*HIT_PIE*40000;//20000;//*20000;
	if(HIT_bf_m_open == 2) 
	{
		HIT_WLw_ref = HIT_WLw_ref + HIT_w_F_FF*HIT_bf_a;//HIT_M_12_w_ref*HIT_bf_a;	
	}
		
}
#endif