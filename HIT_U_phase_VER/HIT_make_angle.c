#ifndef HITMAKE_ANGLEC
#define HITMAKE_ANGLEC
#include "HIT_make_angle.h"
#include "iodefine.h"
#include<math.h>
#include<mathf.h>
extern unsigned char HIT_pwm_mode_choose ;
signed int HIT_s0TX_buffer1_judge;
signed int HIT_s0TX_buffer2_judge;
extern float HIT_alarm;
extern float HIT_run_mode;
float HIT_xi_d_w = 2;
extern float HIT_Ts;
extern int HIT_sitadian;
float HIT_sita_d = 0;
extern char HIT_ready_go;
unsigned short HIT_xi_d_count = 1;
float HIT_xi_d_num_count = 0;
extern float HIT_xi_d_num;
float HIT_id_out = 0;
extern float HIT_xi_d_step;
extern float HIT_id_ref;
float HIT_xi_d_w_num_count = 0;
extern float HIT_xi_d_w_num;
float HIT_xi_d_w_out = 0;
extern float HIT_xi_d_w_step;
extern int HIT_alarm_num;
float HIT_sita_mode_10_f;
//extern float HIT_i_vector_ref;
extern int HIT_mode_10_check_en;
extern int HIT_mode_10_mag_sita_int;
extern float HIT_mode_10_sita_err[];
extern int HIT_M_12_count;
extern float HIT_M_12_r_time_num;
extern float HIT_M_12_w_ref;
extern float HIT_M_12_speed_step;
extern float HIT_M_12_k_time_num;
extern float HIT_M_12_it_time_num;


void HIT_make_angle(void)
{
	
	//	HIT_p_getad[0] = S12AD0.ADDR0A ;/*get ad*///20131216//
//		HIT_p_getad[1] = S12AD0.ADDR1 ;//20131216//20140110
		HIT_p_getad[2] = S12AD0.ADDR0A;////////////////////////////////////////
		HIT_p_getad[3] = S12AD1.ADDR0A ;//////////////////////////////////////////
	//	HIT_n_getad[0] = S12AD1.ADDR0A ;//20131216//
//		HIT_n_getad[1] = S12AD1.ADDR1 ;
		HIT_n_getad[2] = S12AD0.ADDR1 ;////////////////////////////////////////////
		HIT_n_getad[3] = S12AD1.ADDR3 ;
		HIT_Uad = AD0.ADDRB;

//		S12AD0.ADCSR.BIT.ADST=1;
//		S12AD1.ADCSR.BIT.ADST=1;
		AD0.ADCSR.BIT.ADST=1;
		
	//	HIT_a_p_hall = (HIT_p_getad[0]>>4 );//hall signal A//20131216//
		HIT_b_p_hall = (HIT_p_getad[1]>>4 );//hall signal C//20131216//20140110
		HIT_u_sensor = (HIT_p_getad[2]>>4 );//current U
		HIT_w_sensor = (HIT_p_getad[3]>>4); //current W
	//	HIT_a_n_hall = (HIT_n_getad[0]>>4  );//hall signal B//20131216//
		HIT_b_n_hall = (HIT_n_getad[1]>>4  );//20131216//20140110
		HIT_v_sensor = (HIT_n_getad[2]>>4  );//current V
		HIT_Umsensor = (HIT_n_getad[3]>>4);//VDTP
		

/*calculate end*/
		if(((HIT_run_mode == 8)||(HIT_run_mode == 9)||(HIT_run_mode == 10)||(HIT_run_mode == 19))&&(HIT_ready_go==1))
		{
			if(HIT_xi_d_num_count <= HIT_xi_d_num)
			{
				HIT_id_out = HIT_id_out + HIT_xi_d_step;
				HIT_xi_d_num_count++;
				if((HIT_run_mode == 8)||(HIT_run_mode == 10)||(HIT_run_mode == 19))
				{
					HIT_id_ref = HIT_id_out;
				}
/*				if(HIT_run_mode == 9)
				{
//					HIT_i_vector_ref = HIT_id_out;	
				}*/
			}
			
			if(HIT_xi_d_count == 1)
			{
				HIT_sita_d = HIT_sita;
				HIT_xi_d_count = 0;
			}
			if(HIT_xi_d_num_count > HIT_xi_d_num)
			{
				if(HIT_run_mode != 19)
				{
					if(HIT_xi_d_w_num_count <= HIT_xi_d_w_num)
					{
						HIT_xi_d_w_out = HIT_xi_d_w_out + HIT_xi_d_w_step; 
						HIT_xi_d_w_num_count++;	
						HIT_xi_d_w = HIT_xi_d_w_out;
					}
				}
				if(HIT_run_mode == 19)
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
						if((HIT_run_mode == 13)||(HIT_run_mode == 14)||(HIT_run_mode == 15)||(HIT_run_mode == 18)||(HIT_run_mode == 19))
						{
							HIT_M_12_speed_step = HIT_M_12_speed_step*(-1);	
						}
					}
					HIT_xi_d_w = HIT_M_12_w_ref;	
				}
				HIT_sita_d = HIT_sita_d +(HIT_xi_d_w*HIT_Ts);
				if(HIT_sita_d >= HIT_TWOPIE)
				{
					HIT_sita_d = HIT_sita_d - HIT_TWOPIE;	
				}
				if(HIT_sita_d<0)
				{
					HIT_sita_d = 0;	
				}
			}
			HIT_sita = HIT_sita_d;	
		}

		HIT_sitaintf_curr_mech_f = HIT_sita*HIT_MAKE16WEI_ANGLE;
		HIT_sitaintf_curr_mech_int = (signed int)HIT_sitaintf_curr_mech_f;
		HIT_sitaintf_curr_int = HIT_sitaintf_curr_mech_int;
///////////////////////////////////////////////////////////////////////////////////////////////////////		
	if((HIT_run_mode!=8)&&(HIT_run_mode!=9)&&(HIT_run_mode!=10))
	{	HIT_biaoding_int = HIT_sitaintf_curr_int;
		HIT_biaoding_int_bia = HIT_sitaintf_curr_int;// -13704;
		if(HIT_biaoding_int_bia >= 65536)
		{
			HIT_biaoding_int_bia = HIT_biaoding_int_bia - 65536;	
		}
		if(HIT_biaoding_int_bia < 0)
		{
			HIT_biaoding_int_bia = HIT_biaoding_int_bia + 65536;	
		}
/*		
	////////check table////////	
		HIT_check_area_int = HIT_biaoding_int_bia&0x0000ffc0;// high 10wei
		HIT_add_point_int = HIT_biaoding_int_bia&0x0000003f;//low 6wei
		HIT_check_area_bia_int = HIT_check_area_int>>6;
	

	
	//	HIT_check_area_bia_f = (float)HIT_check_area_bia_int;
		if(HIT_check_area_bia_int==1023)
		{
			HIT_y_a1_f = HIT_biaodingarry[1023];
			HIT_y_a2_f = HIT_biaodingarry[0];	
		}
		else
		{
			HIT_y_a1_f = HIT_biaodingarry[HIT_check_area_bia_int];
			HIT_y_a2_f = HIT_biaodingarry[HIT_check_area_bia_int+1];	
		}

	
		HIT_x_a1_f = (float)HIT_check_area_bia_int;
			
		HIT_k_f = HIT_y_a2_f - HIT_y_a1_f;
		HIT_b_f = HIT_y_a1_f - HIT_k_f * HIT_x_a1_f;
	
		HIT_add_point_f = (float)HIT_add_point_int/64;
		HIT_biaoding_ang_f = HIT_k_f*(HIT_x_a1_f +  HIT_add_point_f) + HIT_b_f;

		HIT_biaoding_f = (float)HIT_biaoding_int;
		HIT_new_angle_f = HIT_biaoding_ang_f + HIT_biaoding_f;
		if(HIT_new_angle_f >= 65536)
		{
			HIT_new_angle_f = HIT_new_angle_f - 65536;	
		}
		if(HIT_new_angle_f < 0)
		{
			HIT_new_angle_f = HIT_new_angle_f + 65536;	
		}
		HIT_sita = HIT_new_angle_f * HIT_TWOPIE/65536;/////////add 20121122
		HIT_new_angle_int = (int)HIT_new_angle_f;
		HIT_new_angle_short = (unsigned short)HIT_new_angle_int;
		HIT_sitaintf_curr_int = HIT_new_angle_int;*/
	}
////////check table end////////			
		if((HIT_mode_10_check_en == 1)&&(HIT_run_mode == 10))
		{
			HIT_biaoding_int = HIT_mode_10_mag_sita_int;
			HIT_biaoding_int_bia = HIT_mode_10_mag_sita_int;// -13704;
		
			
		////////check table////////	
			HIT_check_area_int = HIT_biaoding_int_bia&0x0000ffc0;// high 10wei
			HIT_add_point_int = HIT_biaoding_int_bia&0x0000003f;//low 6wei
			HIT_check_area_bia_int = HIT_check_area_int>>6;
	

	
		//	HIT_check_area_bia_f = (float)HIT_check_area_bia_int;
			if(HIT_check_area_bia_int==1023)
			{
				HIT_y_a1_f = HIT_mode_10_sita_err[1023];
				HIT_y_a2_f = HIT_mode_10_sita_err[0];	
			}
			else
			{
				HIT_y_a1_f = HIT_mode_10_sita_err[HIT_check_area_bia_int];
				HIT_y_a2_f = HIT_mode_10_sita_err[HIT_check_area_bia_int+1];	
			}

	
			HIT_x_a1_f = (float)HIT_check_area_bia_int;
			
			HIT_k_f = HIT_y_a2_f - HIT_y_a1_f;
			HIT_b_f = HIT_y_a1_f - HIT_k_f * HIT_x_a1_f;
	
			HIT_add_point_f = (float)HIT_add_point_int/64;
			HIT_biaoding_ang_f = HIT_k_f*(HIT_x_a1_f +  HIT_add_point_f) + HIT_b_f;

			HIT_biaoding_f = (float)HIT_biaoding_int;
			HIT_new_angle_f = HIT_biaoding_ang_f + HIT_biaoding_f;
			if(HIT_new_angle_f >= 65536)
			{
				HIT_new_angle_f = HIT_new_angle_f - 65536;	
			}
			if(HIT_new_angle_f < 0)
			{
				HIT_new_angle_f = HIT_new_angle_f + 65536;	
			}
			HIT_new_angle_int = (int)HIT_new_angle_f;
			HIT_new_angle_short = (unsigned short)HIT_new_angle_int;
			HIT_mode_10_mag_sita_int = HIT_new_angle_int;
		}	
////////////////////////////////////////////////////////////////////////////////////////////////////////
		HIT_new_angle_short = (unsigned short)HIT_sitaintf_curr_int;//add 20130512	
		HIT_new_angle_int = (int)HIT_sitaintf_curr_int;//add 20130607
		
		HIT_new_angle_int = HIT_new_angle_int;
				
		HIT_sitaintf_curr_int = HIT_sitaintf_curr_int - HIT_sitadf_int;// 20140731 ly 	
		if(HIT_sitaintf_curr_int < 0)
		{
			HIT_sitaintf_curr_int = HIT_AD16WEI+HIT_sitaintf_curr_int;///2012.3.25wl
		}
		
		
		HIT_sitaintf_pole_int = (int)((float)HIT_sitaintf_curr_int*HIT_poles);
		HIT_sitadian_pole_max_int = (int)(HIT_AD16WEI*HIT_poles);
		if(HIT_sitaintf_pole_int > HIT_sitadian_pole_max_int)//196606=65535*3
		{
			HIT_sitaintf_pole_int = HIT_sitadian_pole_max_int;	
		}
		if(HIT_sitaintf_pole_int < 0)
		{
			HIT_sitaintf_pole_int = 0;	
		}
		HIT_sitadian = HIT_sitaintf_pole_int;
		HIT_sitadian =  HIT_sitadian&0x0000ffff;
		HIT_sitadian = HIT_sitadian>>4;
//		HIT_sitadian = HIT_sitadian&0x0000ffff;///add20141224
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		HIT_sitadian = 0;////////////////////////////////////////////////////////////////////////////////////////
		if(HIT_run_mode == 1)
		{
			HIT_sitadian = 0;	
		}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*		 HIT_speedlpf= HIT_speedlpf*HITdirection;//use for test the rotate direction of the motor 
		if(HIT_speedlpf<0) 
		{
			HIT_dir = 0;	
			HIT_dircount++;
		}
		if(HIT_speedlpf >= 0)
		{
			HIT_dir = 1;
			HIT_dircount1++;	
		}*/
		HIT_Umsensor_f = (float)HIT_Umsensor;/*calculate voltage*/
		HIT_now_voltage_f = (HIT_Um_standard/HIT_Umsensor_f_standard)* HIT_Umsensor_f;
		
		HIT_now_voltage_one = HIT_now_voltage_f;/*voltage filter u*/
		HIT_now_voltage_f_out = HIT_lpfUm_standard_1A*HIT_now_voltage_f_out;
		HIT_now_voltage_f_out = HIT_now_voltage_f_out +HIT_lpfUm_standard_1B*HIT_now_voltage_one;
		HIT_now_voltage_f_out = HIT_now_voltage_f_out +HIT_lpfUm_standard_1B*(HIT_now_voltage_two-HIT_now_voltage_f_out);
		HIT_now_voltage_two = HIT_now_voltage_one;
		
		HIT_now_voltage_f = 24.0;
}
#endif