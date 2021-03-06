#ifndef HITSERVOONC
#define HITSERVOONC
#include "HIT_servoon.h"
#include"iodefine.h"
extern unsigned short HIT_run_time;
extern unsigned short HIT_run_time_2;
extern unsigned int HIT_run_time_int;
extern unsigned int HIT_run_time_2_int;
extern char HIT_ready_go;
int HIT_speed_run_time = 0;
char HIT_pos_count = 0;
extern int HIT_position1_fb_16_int;
extern int HIT_new_angle_int;
extern float HIT_id_ref;
extern float HIT_run_mode;
unsigned short HIT_ceshi = 0;
unsigned short HIT_ceshi_1 = 2048;
unsigned short HIT_DA_chnl = 0;
unsigned int tx = 1;
unsigned int qwe = 1;
float HIT_speed_con_time[40];
float HIT_speed_time[40];
float HIT_speed_a[40];
float HIT_speed_command[40];
unsigned short V_comm_i = 0;
float HIT_speed_rond_v0 = 0;
//unsigned short HIT_speed_rond_num = 0;
float HIT_speed_rond_a;
unsigned short i;
unsigned short HIT_mode_5_i = 0;
float HIT_speed_command_ref = 0;
float HIT_speed_command_0 = 0;
extern unsigned short V_comm_i_max;
unsigned char HIT_enable_mode_5 = 1;
float HIT_speed_rond_num_f;
float HIT_speed_command_f;
float HIT_speed_a_f;
float HIT_speed_command_ref_out;
float HIT_sudu_jian_val = 0;
extern float HIT_WLw_ref_in;
extern unsigned char HIT_pwm_mode_choose;
union {
		unsigned short HIT_send_sci_DA;
		struct {
			unsigned short low_8:8;//最低位
			unsigned short high_8:8;//最位
		} BYTE;
		struct {
			unsigned short BIT_1:1;//最低位
			unsigned short BIT_2:1;//最位
			unsigned short BIT_3:1;//最位
			unsigned short BIT_4:1;//最位
			unsigned short BIT_5:1;//最位
			unsigned short BIT_6:1;//最位
			unsigned short BIT_7:1;//最位
			unsigned short BIT_8:1;//最高位
			unsigned short BIT_9:1;//最高位
			unsigned short BIT_10:1;//最高位
			unsigned short BIT_11:1;//最高位
			unsigned short BIT_12:1;//最高位
			unsigned short BIT_13:1;//最高位
			unsigned short BIT_14:1;//最高位
			unsigned short BIT_15:1;//最高位
			unsigned short BIT_16:1;//最高位
		} BIT;
	} HIT_send_sci_DA_buff;
unsigned short HIT_DA_data_trans = 0;
extern float HIT_iq_fb;
extern float HIT_OBC_iq;
int HIT_M_12_count = 0;
extern float HIT_M_12_r_time_num;
extern float HIT_M_12_k_time_num;
extern float HIT_M_12_it_time_num;
extern float HIT_M_12_w_ref;
extern float HIT_M_12_speed_step;
float HIT_M_12_w_ref = 0;
float HIT_M_12_w_out = 0 ;
float HIT_M_12_pos_sum = 0;
extern int HIT_virtual_ps_int;
extern float HIT_pos_org_f;
extern float HIT_M_12_max_speed;
float HIT_M_12_w_ref_1 = 0;
float HIT_M_12_w_ref_2 = 0;
float HIT_M_12_w_ref_err;
extern float HIT_sita_M_8_w;
extern float HIT_v_ref_f_out;
extern float HIT_s_ref_f_out;
extern float HIT_a_ref_f_out;
extern float HIT_U_FF;
extern float HIT_I_FF_ref;
extern float HIT_w_F_FF;
extern float HIT_I_FF_ref;
extern float HIT_I_FF;
extern float HIT_U_F;
extern float HIT_w_F_ref;
float HIT_w_F_FF_out = 0;
extern int HIT_virtual_ps_int_err_f_org_int;
extern float HIT_speedlpf_out;
extern int HIT_pos_org_int ;
extern int HIT_M_12_w_out_org_int;
extern float HIT_DA_one_out;
extern float HIT_DA_two_out;
extern float HIT_DA_one_full;
extern float HIT_DA_two_full;
extern float HIT_DA_out;
int HIT_run_mode_10_int = 0;
float HIT_mode_10_sita;
float HIT_mode_10_enc_mag;
char HIT_mode_10_first_time = 1;
float HIT_mode_10_enc_mag_fir;
char HIT_mode_10_jump = 0;
float HIT_mode_10_sita_err[1024];
signed short HIT_err_10_i=0;
extern float HIT_sita_mode_10_f;
float HIT_mode_10_enc_mag_err;
float HIT_mode_10_enc_mag_1;
float HIT_mode_10_enc_mag_2;
signed short HIT_mode_10_enc_mag_fir_short;
unsigned short HIT_mode_factor_num = 1;
int HIT_start_bd_int_num =0;
float HIT_mode_10_err_ser;
int run_run_time = 0;
float HIT_DA_float_1 = 2150;
float HIT_DA_float_2 = 2150;
unsigned short HIT_cur_test = 1;
extern float HIT_WLw_ref_mode_2;
extern float HIT_WLw_ref_mode_2_step;
extern float HIT_WLw_ref_mode_2_max;
#include"HIT_mechanicalpi.h"
extern float HIT_alarm ;
extern int HIT_alarm_num;
extern float HIT_gyo_n_da;
float HIT_wone_re = 0;
float HIT_we_re = 0;
float HIT_speedlpf_re = 0;
float HIT_wtwo_re = 0;
extern float fpPC_to_motor_angle;
void HIT_servoon()
{

//		PORTA.DR.BIT.B4=1
        

		if(HIT_pos_count == 1)
		{
			HIT_servo_on_first();
		}
		else
		{
			if((HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 14)||(HIT_run_mode == 15)||(HIT_run_mode == 18))
			{
				HIT_M_12_count++;
				if(HIT_M_12_count <= HIT_M_12_r_time_num)
				{
					HIT_M_12_w_ref = HIT_M_12_w_ref + HIT_M_12_speed_step;	
				}	
				if((HIT_M_12_count >= HIT_M_12_r_time_num)&&(HIT_M_12_count <= HIT_M_12_r_time_num + HIT_M_12_k_time_num))
				{
					
				}
				if((HIT_M_12_count > HIT_M_12_r_time_num + HIT_M_12_k_time_num)&&(HIT_M_12_count <= 2*HIT_M_12_r_time_num + HIT_M_12_k_time_num))
				{
					HIT_M_12_w_ref = HIT_M_12_w_ref - HIT_M_12_speed_step;	
				}
				if((HIT_M_12_count > 2*HIT_M_12_r_time_num + HIT_M_12_k_time_num)&&(HIT_M_12_count < 2*HIT_M_12_r_time_num + HIT_M_12_k_time_num + HIT_M_12_it_time_num))
				{
					HIT_M_12_w_ref = 0;
				}
				if(HIT_M_12_count == 2*HIT_M_12_r_time_num + HIT_M_12_k_time_num + HIT_M_12_it_time_num)
				{
					HIT_M_12_count = 0;	
					if((HIT_run_mode == 13)||(HIT_run_mode == 14)||(HIT_run_mode == 15)||(HIT_run_mode == 18))
					{
						HIT_M_12_speed_step = HIT_M_12_speed_step*(-1);	
					}
				}
				
				HIT_M_12_w_ref_1 = HIT_M_12_w_ref;///HIT_M_12_w_ref: v_ref
				HIT_M_12_w_ref_err = HIT_M_12_w_ref_1 - HIT_M_12_w_ref_2;//HIT_M_12_w_ref_err:a_ref
				HIT_M_12_w_ref_2 = HIT_M_12_w_ref_1;
				
				HIT_M_12_w_out = HIT_M_12_w_ref; 
				HIT_M_12_w_out = HIT_M_12_w_out/20000; 
				HIT_M_12_w_out = HIT_M_12_w_out/2/HIT_PIE*65536;//////HIT_M_12_w_out:s_ref
				
				if((HIT_run_mode == 15)||(HIT_run_mode == 12))
				{
					HIT_ref_lpf_fuc();
				}
				
/*				HIT_M_12_pos_sum = HIT_M_12_w_out + HIT_M_12_pos_sum;
				if(HIT_M_12_pos_sum > 65535)
				{
					HIT_M_12_pos_sum = 0;	
				}*/
			}

/*			if(HIT_run_mode == 12)
			{
				HIT_virtual_ps_int = (int)HIT_M_12_pos_sum;
			}*/
//			if((HIT_run_mode == 3)||(HIT_run_mode == 4)||(HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 15))
			
			if((HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 15)||(HIT_run_mode == 38))
			{
				if((HIT_run_mode == 15)||(HIT_run_mode == 12))
				{
					HIT_w_F_FF_out = HIT_w_F_FF; 
					HIT_w_F_FF_out = HIT_w_F_FF_out/20000; 
					HIT_w_F_FF_out = HIT_w_F_FF_out/2/HIT_PIE*65536;//////HIT_M_12_w_out:s_ref
					
				}
				HIT_positioncontrol();//////////////////////////////////////////////////////////
			}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////		
		/*		HIT_speed_run_time++;
				if(HIT_speed_run_time > 50000)
				{
					HIT_WLw_ref = HIT_WLw_ref - 0.105;	
				}
				if(HIT_WLw_ref < 0.3)
				{
					HIT_WLw_ref = 0;	
				}*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////					
//			if((HIT_run_mode == 3)||(HIT_run_mode == 2)||(HIT_run_mode == 4)||(HIT_run_mode == 5)||(HIT_run_mode == 7)||(HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 15))

		HIT_sitafir = HIT_sita;
/*		if(HIT_lpfcount < 3)
		{
			HIT_sita1 = HIT_sitafir;
			HITlpf_count++;	
		}*/
		HIT_sitaerr = HIT_sitafir - HIT_sita1;//HIT_sitafir - HIT_sita1;//HIT_sita1 - HIT_sitafir;//HITsitafir - HITsita1;
		HIT_sita1 = HIT_sitafir;
	
		
		if(HIT_sitaerr>HIT_PIE)//avoid happen the jump of the sitaerr
		{
			HIT_sitaerr = HIT_sitaerr-HIT_TWOPIE;	
		}
		if(HIT_sitaerr<-HIT_PIE)
		{
			HIT_sitaerr = HIT_TWOPIE+HIT_sitaerr;
		}
//		HIT_we = HIT_sitaerr/HIT_Tsa;//*HIT_speedpar;//////* calculate speed rad/s */
		HIT_we = HIT_sitaerr/HIT_Tsa;//*HIT_speedpar;//////* calculate speed rad/s */
//		HIT_OBW_state();
//		HIT_OBW_we = HIT_we;
		
		HIT_wone = HIT_we;/*speed filter*/
//		HIT_wone = HIT_gyo_n_da;
		HIT_speedlpf = HIT_lpfv1A * HIT_speedlpf;
		HIT_speedlpf = HIT_speedlpf + HIT_lpfv1B * HIT_wone;
		HIT_speedlpf = HIT_speedlpf + HIT_lpfv1B * (HIT_wtwo-HIT_speedlpf);
		HIT_wtwo = HIT_wone;/*filter end*/ 
		HIT_speedlpf_out = HIT_speedlpf;    // 速度转换
 

			if((HIT_run_mode == 2)||(HIT_run_mode == 5)||(HIT_run_mode == 7)||(HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 15)||(HIT_run_mode == 18)||(HIT_run_mode == 28)||(HIT_run_mode == 38))
			{
/*				if(HIT_run_mode == 7)
				{
					HIT_speed_run_time++;
					if(HIT_speed_run_time > 3000)
					{
						HIT_WLw_ref = HIT_WLw_ref - HIT_sudu_jian_val;	
					}
					if(HIT_WLw_ref < 0.3)
					{
						HIT_WLw_ref = HIT_WLw_ref_in;//109;//52;	
						HIT_speed_run_time = 0;
					}
				//	HIT_WLw_ref = 20;
				}*/
/*				if(HIT_run_mode == 5)
				{
//					HIT_run_mode_5_fnc();
				}*/
				
				if(HIT_run_mode == 2)
				{
					HIT_WLw_ref_mode_2 = HIT_WLw_ref_mode_2 + HIT_WLw_ref_mode_2_step;	
					if(HIT_WLw_ref_mode_2 > HIT_WLw_ref_mode_2_max)
					{
						HIT_WLw_ref_mode_2 = HIT_WLw_ref_mode_2_max;	
					}
					
					HIT_WLw_ref = HIT_WLw_ref_mode_2;
				}
				if(HIT_run_mode == 18)
				{	
					HIT_WLw_ref = HIT_M_12_w_ref;
				}
				
				if(HIT_run_mode == 28)
				{
					if((fpPC_to_motor_angle < 18) && (fpPC_to_motor_angle > -18) )
					{
						HIT_wone_re = fpPC_to_motor_angle;//HIT_we_re;
						HIT_wone_re = HIT_wone_re/360*2*3.1415;
					}//xg
					
					
/*					HIT_speedlpf_re = HIT_lpfv1A * HIT_speedlpf_re;
					HIT_speedlpf_re = HIT_speedlpf_re + HIT_lpfv1B * HIT_wone_re;
					HIT_speedlpf_re = HIT_speedlpf_re + HIT_lpfv1B * (HIT_wtwo_re-HIT_speedlpf_re);
					HIT_wtwo_re = HIT_wone_re;*/ 
					HIT_WLw_ref = HIT_wone_re;//HIT_speedlpf_re;//xg	
//					HIT_WLw_ref = HIT_gyo_n_da;
				}
				HIT_mechanicalpi();
				
			}
//				HIT_releasepowernew();
			if((HIT_run_mode == 1)||(HIT_run_mode == 8)||(HIT_run_mode == 14)||(HIT_run_mode == 10)||(HIT_run_mode == 19))
			{
				//HIT_id_ref = 5;
				HIT_iq_ref = 0;
			}
			if((HIT_run_mode == 6)||(HIT_run_mode == 2)||(HIT_run_mode == 12)||(HIT_run_mode == 13)||(HIT_run_mode == 15)||(HIT_run_mode == 18)||(HIT_run_mode == 28)||(HIT_run_mode == 38))
			{
				HIT_id_ref = 0;
//				HIT_fluxwenkingcontrol();
			//	HIT_iq_ref = 1;
			}
		
	//	if(HIT_speedlpf_out>500) 
	//	{
	//		HIT_alarm = 1;
	//		HIT_alarm_num = 1;	
	//	}//超速度停止
		
		
				HIT_current_pi();
			
	
	if((HIT_run_mode == 10)&&(HIT_ready_go == 1))
//	if(HIT_ready_go == 1)
	{
		HIT_mode_10_bd();
/*		HIT_run_mode_10_int++;
		if((HIT_run_mode_10_int > 100000))//&&(HIT_run_mode_10_int <= 120480))//20480个周期
		{
			HIT_mode_10_enc_mag = HIT_sita_mode_10_f*10430.219;//当前角度值

			HIT_mode_10_enc_mag_1 = HIT_mode_10_enc_mag;
			HIT_mode_10_enc_mag_err = HIT_mode_10_enc_mag_1 - HIT_mode_10_enc_mag_2;//HIT_sitafir - HIT_sita1;//HIT_sita1 - HIT_sitafir;//HITsitafir - HITsita1;
//			HIT_mode_10_enc_mag_save = HIT_mode_10_enc_mag_2;
			HIT_mode_10_enc_mag_2 = HIT_mode_10_enc_mag_1;
//			if(HIT_mode_10_enc_mag_err < -60000)//磁电过零点
			if((HIT_mode_10_enc_mag > 0)&&(HIT_mode_10_enc_mag < 20))
			{
				HIT_mode_10_jump = 1;	
			}
			
			if(HIT_mode_10_jump == 1)
			{
				if(HIT_mode_factor_num == 1)
				{
//					HIT_mode_10_factor_f = HIT_mode_10_enc_mag_save/65535;
					HIT_mode_factor_num = 0;
				}
				HIT_start_bd_int_num++;
				if((HIT_start_bd_int_num > 0)&&(HIT_start_bd_int_num <= 327680))
				{
					HIT_mode_10_sita = 	HIT_mode_10_sita + 0.199996;//3.6621;//3.19*HIT_mode_10_factor_f;//20480周期 1.024s 3.6rpm
					if(HIT_mode_10_sita > 65535)
					{
						HIT_mode_10_sita = 0;	
					}	
					
//					HIT_mode_10_err_sum = HIT_mode_10_sita - HIT_mode_10_enc_mag;
					
//					HIT_mode_10_err_org = HIT_mode_10_err_org + HIT_mode_10_err_sum;
					
					if((HIT_start_bd_int_num%320==0))//词典角度归零
					{
						
						HIT_mode_10_err_ser = HIT_mode_10_sita - HIT_mode_10_enc_mag;
						
//						HIT_mode_10_errone = HIT_mode_10_err_ser;
//						HIT_mode_10_err_lpf = HIT_lpfmode_10_1A*HIT_mode_10_err_lpf+HIT_lpfmode_10_1B*HIT_mode_10_errone+HIT_lpfmode_10_1B*(HIT_mode_10_errtwo-HIT_mode_10_err_lpf);
//						HIT_mode_10_errtwo = HIT_mode_10_errone;
						
						
						HIT_mode_10_sita_err[HIT_err_10_i] = HIT_mode_10_err_ser;//HIT_mode_10_err_ser;//HIT_mode_10_sita - HIT_mode_10_enc_mag;//HIT_mode_10_enc_mag;//HIT_mode_10_sita ;//- HIT_new_angle_f;//HIT_mode_10_enc_mag;//- HIT_mode_10_enc_mag_fir - HIT_mode_10_sita;
						
//						HIT_mode_10_sita_err[1023] = HIT_mode_10_err_ser;
						
						HIT_err_10_i++;
					}
					run_run_time++;
				}
				if(HIT_start_bd_int_num > 327680)
				{
					HIT_start_bd_int_num = 	327685;
				}
			}
		
		}
		if(HIT_run_mode_10_int > 620480)
		{
			HIT_run_mode_10_int = 	620485;
		}*/
	}
//////////////DA//////////////////////////////////////////////////////////////////////////////
//		PORT3.DR.BIT.B3 = 1;
//		PORTA.DR.BIT.B4 = 1;
 //       PORTB.DDR.BIT.B4 = 1;
//		PORTB.DR.BIT.B4 = 1;

	    PORT3.DR.BIT.B1 = 1;
		HIT_ceshi = HIT_ceshi+10;
		HIT_ceshi_1 = HIT_ceshi_1 +10;
		if(HIT_ceshi > 1047)
		{
			HIT_ceshi = 100;	
		}
		if(HIT_ceshi_1 > 1047)
		{
			HIT_ceshi_1 = 100;	
		}		
		
		HIT_DA_chnl++;
		if(HIT_DA_chnl == 3)
		{
			HIT_DA_chnl = 1;	
		}
//		HIT_DA_chnl = 1;
//		HIT_ceshi = HIT_speed_command_ref/65535*2048 + 2048;
		HIT_DA_out_fuc();
		
        HIT_DA_float_1 = (HIT_DA_out/HIT_DA_one_full*2150+2150);
		HIT_DA_float_2 = (HIT_DA_out/HIT_DA_two_full*2150+2150);//add20141230
////////DA测试/////////////////////////////////////////////////////////////////
//		HIT_DA_float_1 = HIT_ceshi;
//		HIT_DA_float_2 = HIT_ceshi_1;
/////////////////////////////////////////////////////////////////		
		if(HIT_DA_float_1 > 4095)
		{
			HIT_DA_float_1 = 4095;	
		}
		if(HIT_DA_float_1 < 0)
		{
			HIT_DA_float_1 = 1;	
		}
		if(HIT_DA_float_2 > 4095)
		{
			HIT_DA_float_2 = 4095;	
		}
		if(HIT_DA_float_2 < 0)
		{
			HIT_DA_float_2 = 1;	
		}
		
		HIT_ceshi = (unsigned short)HIT_DA_float_1;//HIT_M_12_w_out_org_int(unsigned short)(HIT_virtual_ps_int_err_f_org_int/16384*2048+2048);//(unsigned short)(HIT_M_12_w_ref/2/HIT_PIE*60/1250*2048+2048);//(unsigned short)(HIT_U_F/37.5*2048+2048);;//(HIT_M_12_w_ref/2/HIT_PIE*60/1250*2048+2048);//(unsigned short)(HIT_sita_M_8_w/315*2048+2048);             (unsigned short)(HIT_iq_fb/2*4095);
		HIT_ceshi_1 = (unsigned short)HIT_DA_float_2;//HIT_pos_org_f(unsigned short)(HIT_I_FF/15*2048 + 2048);;//(HIT_pos_org_f/30000*2048 + 2048);//(unsigned short)(500/1500*2048 + 2048);// (unsigned short)(HIT_OBC_iq/2*4095);
		
		
			
		switch(HIT_DA_chnl)
		{
			case 1:
				tx = 0x0000+HIT_ceshi;//HIT_WLw_ref/188*2048+2048;//HIT_ceshi;//HIT_speed_command_ref_out/5000*2048+2048;//HIT_ceshi;
				tx = 65535 - tx;
				HIT_DA_trans_fuc();
			break;	
			case 2:
				tx = 0x8000+HIT_ceshi_1;//HIT_speedlpf/188*2048+2048;//HIT_ceshi_1;
				tx = 65535 - tx;
				HIT_DA_trans_fuc();
			break;	
		}
	//		tx = 0x0000+HIT_ceshi;
	//		RSPI0.SPDR.WORD.L = tx;//0X8000;//tx;//0X8F51;//tx;//0XFFFF;//0x0001;
//		if(RSPI0.SPSR.BIT.SPTEF == 1)//20130511
//		if(SCI1.SSR.BIT.TDRE == 1)
		{
//			PORTA.DR.BIT.B4 = 0;
//		PORTB.DR.BIT.B4 = 0;

		}
//		PORT3.DR.BIT.B3 = 0;	
       PORT3.DR.BIT.B1 = 0;
		 
	qwe++;
//	RSPI0.SPSR.BIT.SPTEF = 0;//20130511
	SCI1.SSR.BIT.TEND = 0;
//	RSPI0.SPSR.BIT.SPRF = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    		if(HIT_qa ==  11112000)//15550020140107//155804)//1553)//288000000//36000000//106500///////20  1ms
			{
			//	if(HIT_cur_test == 2)
				{
					HIT_ready_go = 0;
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
					HIT_qa=0;
					HIT_ready_go=0;
					HIT_pwm_mode_choose=2;
					
				}
			}
			if(HIT_qa>=  11112001)//155805)//288000001//36000001//106501
			{
				PORT7.DR.BIT.B1 = 0;    //20121030 night 20:31 add pingbi
				PORT7.DR.BIT.B2 = 0;
				PORT7.DR.BIT.B3 = 0;
				PORT7.DR.BIT.B4 = 0;
				PORT7.DR.BIT.B5 = 0;
				PORT7.DR.BIT.B6 = 0;
				PORT7.DR.BIT.B0 = 0;
				GPT0.GTONCR.WORD = 0X0000;
				GPT1.GTONCR.BIT.OAE = 0;    ////modify20141214
				GPT1.GTONCR.BIT.OBE = 0;   ////modify20141214
				GPT1.GTONCR.WORD = 0X0000;
				GPT2.GTONCR.BIT.OAE = 0;   ////modify20141214
				GPT2.GTONCR.BIT.OBE = 0;   ////modify20141214
				GPT2.GTONCR.WORD = 0X0000;
				HIT_qa = 11112000;//155804;//288000001;//36000001;//106501;	
			}
			else
			{
				HIT_qa++;			
			}
		}
}
#endif