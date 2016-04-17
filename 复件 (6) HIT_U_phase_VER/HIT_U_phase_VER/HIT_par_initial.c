#include "HIT_par_initial.h"
#include<math.h>
#include<mathf.h>
unsigned char HIT_star_R_ee_buff[20];
unsigned char HIT_star_R_ee;
unsigned char HIT_star_R_ee_i = 0;
extern unsigned char HIT_iic_word_send[];
extern unsigned short HIT_change_num;
extern unsigned char HIT_iic_word_rec_ad;
unsigned int HIT_ee_delay = 0;

unsigned char HIT_run_time_L;
unsigned char HIT_run_time_H;
unsigned short HIT_run_time;
unsigned char HIT_id_sc_H;
unsigned char HIT_id_sc_L;
unsigned short HIT_id_sc;
unsigned char HIT_Kp_sc_H;
unsigned char HIT_Kp_sc_L;
unsigned short HIT_Kp_sc;

unsigned short HIT_run_time_H_short;
unsigned short HIT_run_time_L_short;
unsigned short HIT_run_time_2;
unsigned int HIT_run_time_int;
unsigned int HIT_run_time_2_int;
void HIT_par_initial(void)
{
	
	HIT_adad = (float)HIT_VOLFIVE/HIT_AD12;//use for calculat current
	HIT_curr = (float)1000/HIT_curr_sen;//trans current sensity to Voltage

	HIT_adad_10wei = (float)HIT_VOLFIVE/HIT_AD10;//use for calculat current
		

	HIT_kv=HIT_kv*HIT_lm;//use for control mode-calculate Kv
	
	HIT_ki = 1/HIT_Ti;//calculate the ki
	HIT_Ki = HIT_ki*HIT_Ts; //use for jifen Ki   change HITki from 1/HITTs to 1/HITTi 2012.3.26 wl
	
	HIT_WLMech_Ki = HIT_WLMechki*HIT_Ts;//add 2012.4.1
	
	HIT_pwm_center = HIT_pwm_tcbr/2;///pwm center
	
	
	HIT_Tsa = HIT_Ts;//use for calculate speed control cycle time
	HIT_lpfv1A = (2*HIT_tal)/(2*HIT_tal+HIT_Ts);//the factor of speed filter  of NUM 1_A
	HIT_lpfv1B = HIT_Ts/(2*HIT_tal+HIT_Ts);//the factor of speed filter  of NUM 1_B
	
	HIT_lpfcurr_1A = (2*HIT_curr_tal)/(2*HIT_curr_tal+HIT_Ts);//the factor of current filter  of NUM 1_A
	HIT_lpfcurr_1B = HIT_Ts/(2*HIT_curr_tal+HIT_Ts);//the factor of current filter of NUM 1_B
	
	HIT_lpfUm_standard_1A = (2*HIT_Um_standard_tal)/(2*HIT_Um_standard_tal+HIT_Ts);//the factor of Um_now filter of NUM 1_A
	HIT_lpfUm_standard_1B = HIT_Ts/(2*HIT_Um_standard_tal+HIT_Ts);//the factor of Um_now filter of NUM 1_B
	

	
	HIT_current_inte_mode_select = 0.001/HIT_Ts;//0.001(1ms-interrupt)
	HIT_WLMechki= 1/HIT_MechTi;
	HIT_WLMech_Ki  = HIT_WLMechki*HIT_Ts;
	
	HIT_faif = HIT_faif*6.2832/60;//rpm==>rad/s
	for(HIT_star_R_ee_i=0;HIT_star_R_ee_i<20;HIT_star_R_ee_i++)
	{
		HIT_iic_word_send[0] = 2 + HIT_star_R_ee_i;/////the address iic send
		HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
	
		HIT_iic_word_rec_ad = HIT_iic_word_send[0];
	
		R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
		R_PG_I2C_MasterReceive_C0(0xa3,&HIT_star_R_ee,1);
		switch(HIT_star_R_ee_i)
		{
			case 0://Fn001
				HIT_star_R_ee_buff[0] = HIT_star_R_ee;
			break;	
			case 1://Fn002
				HIT_star_R_ee_buff[1] = HIT_star_R_ee;
			break;	
			case 2://Fn003
				HIT_star_R_ee_buff[2] = HIT_star_R_ee;
			break;	
			case 3://Fn004
				HIT_star_R_ee_buff[3] = HIT_star_R_ee;
			break;	
			case 4://Fn005
				HIT_star_R_ee_buff[4] = HIT_star_R_ee;
			break;	
			case 5://Fn006
				HIT_star_R_ee_buff[5] = HIT_star_R_ee;
			break;
			case 6://Fn007
				HIT_star_R_ee_buff[6] = HIT_star_R_ee;
			break;	
			case 7://Fn008
				HIT_star_R_ee_buff[7] = HIT_star_R_ee;
			break;	
			case 8://Fn009
				HIT_star_R_ee_buff[8] = HIT_star_R_ee;
			break;	
			case 9://Fn00A
				HIT_star_R_ee_buff[9] = HIT_star_R_ee;
			break;
			case 10://Fn001
				HIT_star_R_ee_buff[10] = HIT_star_R_ee;
			break;	
			case 11://Fn002
				HIT_star_R_ee_buff[11] = HIT_star_R_ee;
			break;	
			case 12://Fn003
				HIT_star_R_ee_buff[12] = HIT_star_R_ee;
			break;	
			case 13://Fn004
				HIT_star_R_ee_buff[13] = HIT_star_R_ee;
			break;	
			case 14://Fn005
				HIT_star_R_ee_buff[14] = HIT_star_R_ee;
			break;	
			case 15://Fn006
				HIT_star_R_ee_buff[15] = HIT_star_R_ee;
			break;
			case 16://Fn007
				HIT_star_R_ee_buff[16] = HIT_star_R_ee;
			break;	
			case 17://Fn008
				HIT_star_R_ee_buff[17] = HIT_star_R_ee;
			break;	
			case 18://Fn009
				HIT_star_R_ee_buff[18] = HIT_star_R_ee;
			break;	
			case 19://Fn00A
				HIT_star_R_ee_buff[19] = HIT_star_R_ee;
			break;
		}

		for(HIT_ee_delay=0;HIT_ee_delay<200000;HIT_ee_delay++)
		{
			;
		}
		
//		(unsigned char)(HIT_int_send&0x000f) + 64;	
		
		HIT_run_time_H = HIT_star_R_ee_buff[0];
		HIT_run_time_L = HIT_star_R_ee_buff[1];
		HIT_run_time = ((unsigned short)HIT_run_time_H)<<8 + (unsigned short)HIT_run_time_L;
		HIT_run_time_H_short = (unsigned short)HIT_run_time_H<<8;
		HIT_run_time_L_short = (unsigned short)HIT_run_time_L;
		HIT_run_time = HIT_run_time_L_short + HIT_run_time_H_short;
		HIT_run_time_int = (unsigned int)HIT_run_time;
		HIT_run_time_2 = HIT_run_time + 1;
		HIT_run_time_2_int = (unsigned int)HIT_run_time_2;
		
	//	HIT_run_time = HIT_run_time/1000;	
		
		HIT_id_sc_H = HIT_star_R_ee_buff[2];
		HIT_id_sc_L = HIT_star_R_ee_buff[3];
		HIT_id_sc = (((unsigned short)HIT_id_sc_H)<<8) + HIT_id_sc_L;
		HIT_id_sc = (HIT_id_sc/1000)*2/3;	
		
		HIT_Kp_sc_H = HIT_star_R_ee_buff[4];
		HIT_Kp_sc_L = HIT_star_R_ee_buff[5];
		HIT_Kp_sc = (((unsigned short)HIT_Kp_sc_H)<<8) + HIT_Kp_sc_L;	
	}
	
	
}