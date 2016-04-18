#ifndef HITMAKE_ANGLEC
#define HITMAKE_ANGLEC
#include "HIT_make_angle.h"
#include "iodefine.h"
#include<math.h>
#include<mathf.h>
void HIT_make_angle(void)
{
		HIT_p_getad[0] = S12AD0.ADDR0A ;/*get ad*/
		HIT_p_getad[1] = S12AD0.ADDR1 ;
		HIT_p_getad[2] = S12AD0.ADDR2 ;
		HIT_p_getad[3] = S12AD0.ADDR3 ;
		HIT_n_getad[0] = S12AD1.ADDR0A ;
		HIT_n_getad[1] = S12AD1.ADDR1 ;
		HIT_n_getad[2] = S12AD1.ADDR2 ;
		HIT_n_getad[3] = S12AD1.ADDR3 ;
		HIT_Uad = AD0.ADDRB;

		S12AD0.ADCSR.BIT.ADST=1;
		S12AD1.ADCSR.BIT.ADST=1;
		AD0.ADCSR.BIT.ADST=1;
		
		HIT_a_p_hall = (HIT_p_getad[0]>>4 );//hall signal A
//		HIT_b_p_hall = (HIT_p_getad[1]>>4 );
		HIT_u_sensor = (HIT_p_getad[2]>>4 );//current U
		HIT_w_sensor = (HIT_p_getad[3]>>4); //current W
		HIT_a_n_hall = (HIT_n_getad[0]>>4  );//hall signal B
//		HIT_b_n_hall = (HITn_getad[1]>>4  );
		HIT_v_sensor = (HIT_n_getad[2]>>4  );//current V
		HIT_Umsensor = (HIT_n_getad[3]>>4);//VDTP
		
		
//		HIT_a_n_int = (signed int)HIT_a_phase_sum;
//		HIT_a_p_int = (signed int)HIT_b_phase_sum;	
		HIT_a_p_int = (signed int)HIT_a_p_hall;
		HIT_a_n_int = (signed int)HIT_a_n_hall;	
//		HIT_a_n_int = (signed int)HIT_a_n_hall;
//		HIT_a_p_int = (signed int)HIT_a_p_hall;	
		
//		HIT_s0TX_buffer1 = HIT_a_n_int - 2048;
//		HIT_s0TX_buffer2 = HIT_a_p_int - 2048;
		
		HIT_s0TX_buffer1 = HIT_a_p_int - 2048;
		HIT_s0TX_buffer2 = HIT_a_n_int - 2048;
		
		HIT_s0TX_buffer3 = -(HIT_s0TX_buffer1 + HIT_s0TX_buffer2);
		HIT_a_hall = (float)HIT_s0TX_buffer1 ;
		HIT_b_hall = (float)HIT_s0TX_buffer2 ;
		HIT_c_hall = (float)HIT_s0TX_buffer3 ;
		HIT_d_hall = HIT_a_hall-0.5*(HIT_b_hall+HIT_c_hall);/*angle 3->2*/
		HIT_q_hall = 0.866025*(HIT_b_hall-HIT_c_hall);

/*angle zone calculate*/
		if(HIT_q_hall >= 0)
		{
			if(HIT_d_hall >=0)
			{
				if(HIT_d_hall > HIT_q_hall)
				{
					HIT_make_angle_mode = 1;	
				}
				if(HIT_d_hall > 0)
				{
					if(HIT_d_hall <= HIT_q_hall)
					{
						HIT_make_angle_mode = 2;	
					}	
				}
				else
				{
					if(HIT_q_hall == 0)
					{
						HIT_make_angle_mode = 9;	
					}	
				}	
			}
			else
			{
				if(HIT_q_hall >= -HIT_d_hall)	
				{
					HIT_make_angle_mode = 3;	
				}
				else
				{
					HIT_make_angle_mode = 4;	
				}
			}	
		}
		else
		{
			if(HIT_d_hall >=0)
			{
				if(HIT_d_hall > -HIT_q_hall)
				{
					HIT_make_angle_mode = 8;	
				}
				if(HIT_d_hall >0)
				{
					if(HIT_d_hall <= -HIT_q_hall)	
					{
						HIT_make_angle_mode = 7;	
					}
				}	
			}
			else
			{
				if(HIT_d_hall < HIT_q_hall)
				{
					HIT_make_angle_mode = 5;	
				}	
				else
				{
					HIT_make_angle_mode = 6;	
				}
			}	
		}
		switch(HIT_make_angle_mode)
		{
			case 1:
				HIT_sita=atan(HIT_q_hall/HIT_d_hall);
			break;	
			case 2:
				HIT_sita=HIT_HALFPIE-atan(HIT_d_hall/HIT_q_hall);
			break;	
			case 3:
				HIT_sita=HIT_HALFPIE+atan(-HIT_d_hall/HIT_q_hall);
			break;	
			case 4:
				HIT_sita=HIT_PIE-atan(HIT_q_hall/-HIT_d_hall);
			break;
			case 5:
				HIT_sita=HIT_PIE+atan(HIT_q_hall/HIT_d_hall);	
			break;
			case 6:
				HIT_sita=HIT_TWOTHIRDPIE-atan(HIT_d_hall/HIT_q_hall);	
			break;
			case 7:
				HIT_sita=HIT_TWOTHIRDPIE+atan(HIT_d_hall/-HIT_q_hall);	
			break;
			case 8:
				HIT_sita=HIT_TWOPIE-atan(-HIT_q_hall/HIT_d_hall);		
			break;
		}

/*calculate end*/


		HIT_sitaintf_curr_mech_f = HIT_sita*HIT_MAKE16WEI_ANGLE;
		HIT_sitaintf_curr_mech_int = (signed int)HIT_sitaintf_curr_mech_f;
		HIT_sitaintf_curr_int = HIT_sitaintf_curr_mech_int;
///////////////////////////////////////////////////////////////////////////////////////////////////////		
	HIT_biaoding_int = HIT_sitaintf_curr_int;
	HIT_biaoding_int_bia = HIT_sitaintf_curr_int;// -13704;
	if(HIT_biaoding_int_bia>65535)
	{
		HIT_biaoding_int_bia = HIT_biaoding_int_bia - 65535;	
	}
	if(HIT_biaoding_int_bia<0)
	{
		HIT_biaoding_int_bia = HIT_biaoding_int_bia + 65535;	
	}
		
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
	if(HIT_new_angle_f > 65535)
	{
		HIT_new_angle_f = HIT_new_angle_f - 65535;	
	}
	if(HIT_new_angle_f < 0)
	{
		HIT_new_angle_f = HIT_new_angle_f + 65535;	
	}
	HIT_new_angle_int = (int)HIT_new_angle_f;
	HIT_new_angle_short = (unsigned short)HIT_new_angle_int;
	HIT_sitaintf_curr_int = HIT_new_angle_int;

////////check table end////////			
			
////////////////////////////////////////////////////////////////////////////////////////////////////////		
		HIT_sitaintf_curr_int = HIT_sitaintf_curr_int-HIT_sitadf_int;	
		if(HIT_sitaintf_curr_int < 0)
		{
			HIT_sitaintf_curr_int = HIT_AD16WEI+HIT_sitaintf_curr_int;///2012.3.25wl
		}
		HIT_sitaintf_pole_int = HIT_sitaintf_curr_int*((int)HIT_poles);
		HIT_sitadian_pole_max_int = HIT_AD16WEI*((int)HIT_poles);
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
		HIT_sitadian = 0;
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
}
#endif