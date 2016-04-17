#ifndef CMT0INTFUNCC
#define CMT0INTFUNCC
#include "iodefine.h"
#include "HIT_cmt0intfunc.h"

#include	<machine.h>
#include	<_h_c_lib.h>
//#include	<stddef.h>					// Remove the comment when you use errno
//#include 	<stdlib.h>					// Remove the comment when you use rand()
#include	"typedefine.h"		// Define Types
#include	"stacksct.h"		// Stack Sizes (Interrupt and User)


#include "math.h"
#include "mathf.h"

int psw_value;
char HIT_SERVO_PORT = 1;
extern unsigned char HIT_pwm_mode_choose ;
extern char HIT_ready_go;
extern float HIT_alarm;
extern float HIT_run_mode;
extern float HIT_WLw_ref;
extern float HIT_pos_org_f;
unsigned short HIT_baozha_num = 1;
extern int HIT_a_phase_sum;
extern int HIT_pos_org_int ;
void Cmt0IntFunc()
{

	PORT1.DR.BIT.B1 = 1;
	psw_value = get_psw();//////////////////////////
	psw_value |= 0x00010000;
	set_psw(psw_value);

	
//	HIT_now_voltage_f_out = 37;//27.2;
	HIT_curren_aa_q_max_cmt0 = HIT_now_voltage_f_out/HIT_kv;//calculate the current_sum_lim  MAX
/* short current alarm */
	HIT_id_fb_square = HIT_id_fb*HIT_id_fb;
	HIT_iq_fb_square = HIT_iq_fb*HIT_iq_fb;
	HIT_idq_square = HIT_id_fb_square+HIT_iq_fb_square;
	
	if(HIT_idq_square > HIT_IDQ_SPE_SQUARE)
	{
		HIT_shortime_cur_count++;
		if(HIT_shortime_cur_count > 9)//serial 10ms match
		{
			//HIT_shortime_curr_alam
			HIT_shortime_cur_count = 0;	
		}	
	}
	else
	{
		HIT_shortime_cur_count = 0;		
	}
/* short current alarm end */ 
	HIT_positon_Kp_trans_f = HIT_positon_Kp_int_float;//(float)HIT_positon_Kp_int;//HIT_positon_Kp_int_float;//(float)HIT_positon_Kp_int;//transfer to trsmit parameter
	HIT_positon_Kp_trans_f = HIT_positon_Kp_trans_f * HIT_TWOPIE/HIT_POSITION_16WEI;
	HIT_positon_Kp_f = HIT_positon_Kp_trans_f;//transfer to real register
	
	HIT_shouchaoqi();
/////////////////////////////////////////////////////////////////////////
/*if((HIT_run_mode == 3)||(HIT_run_mode == 4))//((HIT_run_mode == 2)||(HIT_run_mode == 3))
{
	HIT_SERVO_PORT = PORT1.PORT.BIT.B0;
	if(HIT_SERVO_PORT == 0)
	{
		HIT_pwm_mode_choose = 1;	
	}
	if(HIT_pwm_mode_choose == 1)
	{
		HIT_ready_go = 1;	
	}
	if(HIT_SERVO_PORT == 1)
	{
		HIT_pwm_mode_choose = 2;	
	}
}*/
/////////////////////////////////////////////////////////////////////////
	if(HIT_alarm == 1)// 报警输出
	{
		PORT9.DR.BIT.B2 = 0;//ALM 	
	}
	if((HIT_ready_go == 0)||(HIT_alarm == 1))//伺服准备未完成
	{
		PORT9.DR.BIT.B1 = 1;//S_RDY	
	}
	if((HIT_ready_go == 1)&&(HIT_alarm == 0))//伺服准备完成
	{
		HIT_baozha_num++;
		if(HIT_baozha_num > 500)
		{
			PORT9.DR.BIT.B1 = 0;//S_RDY	
			HIT_baozha_num = 501;
		}
	}
//	if((HIT_WLw_ref == 0)&&((HIT_pos_org_f > -0.5)&&(HIT_pos_org_f < 0.5)))//&&(HIT_speedlpf == 0))
	if(((HIT_a_phase_sum <= 3)&&(HIT_a_phase_sum >= -3))&&((HIT_pos_org_int <= 200)&&(HIT_pos_org_int > -200)))//&&(HIT_speedlpf == 0))
	{
		PORT2.DR.BIT.B4 = 0;//CUIN
	}
	else
	{
		PORT2.DR.BIT.B4 = 1;//CUIN	
	}
/////////////////////////////////////////////////////////////////////////
	PORT1.DR.BIT.B1 = 0;


}
#endif