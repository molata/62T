#ifndef POSITIONCONTROLC
#define POSITIONCONTROLC
#include"HIT_positioncontrol.h"
#include<math.h>
#include<mathf.h>
void HIT_positioncontrol()
{
	
	HIT_virtualphotoeletric();//get photoeletric angle older
	HIT_virtual_ps_int_fir = HIT_virtual_ps_int;	
	HIT_virtual_ps_int_err = HIT_virtual_ps_int_fir-HIT_virtual_ps_int_sec;//get virtual_ps err
	HIT_virtual_ps_int_sec = HIT_virtual_ps_int_fir;
	if(HIT_virtual_ps_int_err>HIT_angle_zero_pass_lim)//virtual_ps zero pass offset
	{
		HIT_virtual_ps_int_err = HIT_virtual_ps_int_err - HIT_ANGLE_16;	
	}
	if(HIT_virtual_ps_int_err<-HIT_angle_zero_pass_lim)
	{
		HIT_virtual_ps_int_err = HIT_virtual_ps_int_err + HIT_ANGLE_16;	
	}
/*digital gear*/
	HIT_virtual_ps_int_err_f = (float)HIT_virtual_ps_int_err;
	HIT_virtual_ps_int_err_sum_f  = HIT_virtual_ps_int_err_sum_f + HIT_virtual_ps_int_err_f * HIT_ANGLE_16; 
	HIT_position_client_f = (float)HIT_position_client_int;
	HIT_virtual_ps_int_err_int_f =  HIT_virtual_ps_int_err_sum_f/HIT_position_client_f;
	HIT_virtual_ps_int_err_int_int = (int)HIT_virtual_ps_int_err_int_f; //get int part
	HIT_virtual_ps_int_err_float_f = HIT_virtual_ps_int_err_int_f - (float)HIT_virtual_ps_int_err_int_int;//get float part
	HIT_virtual_ps_int_err_sum_f = HIT_virtual_ps_int_err_float_f;
/*calculate end*/	

	HIT_position_fb_f = HIT_sita;//add on 2012.4.13
	HIT_positionfir_fb_16_int = (int)(HIT_position_fb_f * HIT_POSITIONERR_16WEI);//get position_fb_int 1
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
	HIT_position_err_int = HIT_virtual_ps_int_err_int_int - HIT_position_fb_err_16_int;//get position err
	HIT_pos_org_int = HIT_pos_org_int + HIT_position_err_int;
	HIT_pos_org_f = (float)HIT_pos_org_int;
	
//	HIT_WLw_ref = HIT_pos_org_f * HIT_positon_Kp_f;
}
#endif