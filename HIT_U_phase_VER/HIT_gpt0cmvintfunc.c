#ifndef GPT0CMVINTFUNCC
#define GPT0CMVINTFUNCC
#include "iodefine.h"

extern unsigned short HIT_tgr_b_val3;
extern unsigned short HIT_tgr_d_val3;
extern unsigned short HIT_tgr_a_val4;
extern unsigned short HIT_tgr_c_val4;
extern unsigned short HIT_tgr_b_val4;
extern unsigned short HIT_tgr_d_val4;
extern unsigned char HIT_pwm_mode_choose;
extern char HIT_pos_count;
extern char HIT_ready_go;

//#pragma interrupt Gpt0CmVIntFunc(vect=178)
void Gpt0CmVIntFunc()
{
/*		HIT_tgr_d_val3= 100;
		HIT_tgr_b_val3= 100;
		HIT_tgr_c_val4= 500; 
		HIT_tgr_a_val4= 500;
		HIT_tgr_b_val4= 500;
		HIT_tgr_d_val4= 500;*/
	switch(HIT_pwm_mode_choose)	
	{
		case 1:
		GPT0.GTCCRC = HIT_tgr_d_val3;
		GPT0.GTCCRE = HIT_tgr_b_val3;
	
		GPT1.GTCCRC = HIT_tgr_c_val4;
		GPT1.GTCCRE = HIT_tgr_a_val4;
	
		GPT2.GTCCRC = HIT_tgr_b_val4;
		GPT2.GTCCRE = HIT_tgr_d_val4;
		break;
		case 2:
		
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
		GPT0.GTONCR.WORD = 0X0000;
		GPT1.GTONCR.WORD = 0X0000;
		GPT2.GTONCR.WORD = 0X0000;
		break;
		case 3:
		
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
		GPT0.GTONCR.WORD = 0X0000;
		GPT1.GTONCR.WORD = 0X0000;
		GPT2.GTONCR.WORD = 0X0000;
		break;
	}
}

#endif