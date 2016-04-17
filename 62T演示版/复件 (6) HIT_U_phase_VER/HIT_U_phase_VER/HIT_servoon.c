#ifndef HITSERVOONC
#define HITSERVOONC
#include "HIT_servoon.h"
#include"iodefine.h"
extern unsigned short HIT_run_time;
extern unsigned short HIT_run_time_2;
extern unsigned int HIT_run_time_int;
extern unsigned int HIT_run_time_2_int;

void HIT_servoon()
{

//		PORTA.DR.BIT.B4=1;
	/*speed limit*/
/*		HIT_speed_err = HIT_v_max - HIT_speedlpf ; 
		if((HIT_v_max - HIT_speedlpf < HIT_max_speed_err)||(HIT_v_max - HIT_speedlpf < HIT_max_speed_err_neg))
		{
			HIT_mech_sita1 = HIT_sita;
			HIT_mech_err = HIT_mech_sita1 - HIT_mech_sita2;
			HIT_mech_sita2 = HIT_mech_sita1;
			if(HIT_mech_err < -HIT_PIE)
			{
				HIT_rot_num++;
				if(HIT_rot_num == 1000)//////////////////////////////////////////////////////////////////
				{
					GPT0.GTONCR.BIT.OAE = 0;
					GPT0.GTONCR.BIT.OBE = 0;
					GPT1.GTONCR.BIT.OAE = 0;
					GPT1.GTONCR.BIT.OBE = 0;
					GPT2.GTONCR.BIT.OAE = 0;
					GPT2.GTONCR.BIT.OBE = 0;
					HIT_pwm_stop = 0;
				}	
			}	
		}
		HIT_WLw_ref = HIT_WLw_ref + HIT_WL_A*HIT_Ts;
		if(HIT_WLw_ref > HIT_v_max)
		{
			HIT_WLw_ref = HIT_v_max;
			HIT_WL_A = 0;
		}	*/
		HIT_make_angle();///////////////////////make angle
		HIT_positioncontrol();//////////////////////////////////////////////////////////		
		HIT_mechanicalpi();
		HIT_current_pi();

//		if(HIT_DA_channel == 1)
/*		{
			HIT_DA_t = (unsigned short)HIT_sitadian;
			HIT_DA_t = HIT_DA_t + 0x8000;
			HIT_DA_channel = 0;	
		}
//		else
		{
//			HIT_DA_t = (unsigned short)HIT_sitadian;
//			HIT_DA_t = HIT_DA_t + 0x8000;
//			HIT_DA_channel = 1;	
		}
//		HIT_DA_t = 500; 
//		HIT_DA_t = (unsigned short)HIT_sitadian;//HIT_ele_sita_int_out;//sitaintf_pole_int;//HITsitadianab;//HIT_zone*600;//(unsigned short)(HITsita*652);
		HIT_sci_16 = (HIT_DA_t&(0x01))<<15;
		HIT_sci_15 = (HIT_DA_t&(0x02))<<13;
		HIT_sci_14 = (HIT_DA_t&(0x04))<<11;
		HIT_sci_13 = (HIT_DA_t&(0x08))<<9;
		HIT_sci_12 = (HIT_DA_t&(0x10))<<7;
		HIT_sci_11 = (HIT_DA_t&(0x20))<<5;
		HIT_sci_10 = (HIT_DA_t&(0x40))<<3;
		HIT_sci_9 = (HIT_DA_t&(0x80))<<1;
		HIT_sci_8 = (HIT_DA_t&(0x100))>>1;
		HIT_sci_7 = (HIT_DA_t&(0x200))>>3;
		HIT_sci_6 = (HIT_DA_t&(0x400))>>5;
		HIT_sci_5 = (HIT_DA_t&(0x800))>>7;
		HIT_sci_4 = (HIT_DA_t&(0x1000))>>9;
		HIT_sci_3 = (HIT_DA_t&(0x2000))>>11;
		HIT_sci_2 = (HIT_DA_t&(0x4000))>>13;
		HIT_sci_1 = (HIT_DA_t&(0x8000))>>15;
		HIT_sci = HIT_sci_1+ HIT_sci_2 +HIT_sci_3 +HIT_sci_4 +HIT_sci_5 +HIT_sci_6 +HIT_sci_7 +HIT_sci_8 +HIT_sci_9 +HIT_sci_10 +HIT_sci_11 +HIT_sci_12 +HIT_sci_13 +HIT_sci_14 +HIT_sci_15 +HIT_sci_16;
		PORTA.DR.BIT.B4 = 0;
		PORTA.DR.BIT.B5 = 1;
		R_PG_SCI_StartSending_C2(&HIT_sci, 2);//(uint8_t * data, uint16_t count)*/


//		PORTA.DR.BIT.B4=0;		

	if(HIT_qa == HIT_run_time_int)//1553)//288000000//36000000//106500
	{
	//	highimp();	/////////////////////////////////////high impedence
		HIT_pwm_stop = 0;///////PWM stop output
	}
	if(HIT_qa>=HIT_run_time_2_int)//288000001//36000001//106501
	{
//		GPT0.GTONCR.BIT.OAE = 0;
//		GPT0.GTONCR.BIT.OBE = 0;
		GPT0.GTONCR.WORD = 0X0000;
//		GPT1.GTONCR.BIT.OAE = 0;
//		GPT1.GTONCR.BIT.OBE = 0;
		GPT1.GTONCR.WORD = 0X0000;
//		GPT2.GTONCR.BIT.OAE = 0;
//		GPT2.GTONCR.BIT.OBE = 0;
		GPT2.GTONCR.WORD = 0X0000;
		HIT_qa = HIT_run_time_2_int;//288000001;//36000001;//106501;	
	}
	else
	{
		HIT_qa++;			
	}
}
#endif