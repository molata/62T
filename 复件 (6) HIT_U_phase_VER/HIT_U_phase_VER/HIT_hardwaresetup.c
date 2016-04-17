#ifndef HITHARDWARESETUPC
#define HITHARDWARESETUPC
#include "iodefine.h"
#include "HIT_hardwaresetup.h"
void HIT_hardwaresetup()
{
	R_PG_Clock_Set();
	
	SYSTEM.MSTPCRA.BIT.MSTPA17 = 0;//////////////////////////////////S12AD
	SYSTEM.MSTPCRA.BIT.MSTPA16 = 0;
	SYSTEM.MSTPCRA.BIT.MSTPA23 = 0;//10 BIT
	
	S12AD0.ADCSR.BIT.CKS = 0X03;
	S12AD1.ADCSR.BIT.CKS = 0X03;
	S12AD0.ADCSR.BIT.ADCS = 0X01;//Continuous scan mode
	S12AD1.ADCSR.BIT.ADCS = 0X01;
	
//	R_PG_SCI_Set_C0();//SET UP SCI
	
	S12AD0.ADANS.BIT.CH=0X03;
	S12AD1.ADANS.BIT.CH=0X03;
	S12AD0.ADCER.BIT.ADRFMT = 1;
	S12AD1.ADCER.BIT.ADRFMT = 1;
	S12AD0.ADSSTR = 20;/////////////SAMPLING REGISTER
	S12AD1.ADSSTR = 20;
	
	S12AD0.ADCSR.BIT.ADST=1;
	S12AD1.ADCSR.BIT.ADST=1;
	
	AD0.ADCSR.BIT.CH = 0X01;//CH0 AND CH1
	AD0.ADCR.BIT.MODE = 0X02;//Continuous scan mode
	AD0.ADCR.BIT.CKS = 0X03;//1  1: PCLK
	AD0.ADDPR.BIT.DPSEL =1;//high 10 bit
	AD0.ADDPR.BIT.DPPRC = 0;//10 bit jing du
	AD0.ADCSR.BIT.ADST = 1;//10BIT START
//	R_PG_SCI_Set_C2();

	HIT_pwm=0;
	HIT_tgr_d_val3=500-HIT_pwm;
	HIT_tgr_b_val3=500-HIT_pwm;
	HIT_tgr_c_val4=500-HIT_pwm;
	HIT_tgr_a_val4=500-HIT_pwm;
	HIT_tgr_b_val4=500-HIT_pwm;
	HIT_tgr_d_val4=500-HIT_pwm;
	R_PG_Timer_Set_GPT_U0();///////////GPT
	R_PG_Timer_Set_GPT_U0_C0();
	R_PG_Timer_SetCounterValue_GPT_U0_C0(HIT_counter_val0);
	R_PG_Timer_SetGTCCR_A_GPT_U0_C0(HIT_tgr_b_val3);
	R_PG_Timer_SetGTCCR_B_GPT_U0_C0(HIT_tgr_d_val3);

	R_PG_Timer_Set_GPT_U0_C1();
	R_PG_Timer_SetCounterValue_GPT_U0_C1(HIT_counter_val1);
	R_PG_Timer_SetGTCCR_A_GPT_U0_C1(HIT_tgr_a_val4);
	R_PG_Timer_SetGTCCR_B_GPT_U0_C1(HIT_tgr_c_val4);
	R_PG_Timer_Set_GPT_U0_C2();
	R_PG_Timer_SetCounterValue_GPT_U0_C2(HIT_counter_val2);
	R_PG_Timer_SetGTCCR_A_GPT_U0_C2(HIT_tgr_b_val4);
	R_PG_Timer_SetGTCCR_B_GPT_U0_C2(HIT_tgr_d_val4);

	R_PG_Timer_Start_CMT_U0_C0();//CMT module start(1ms interrupt)
//	R_PG_Timer_Start_CMT_U1_C2();//	GPT0.GTONCR.BIT.OAE = 0;
	GPT.GTSTR.WORD = 0X07;//////START SYNCROSCOLLY

//	GPT0.GTONCR.BIT.OBE = 0;
//	GPT1.GTONCR.BIT.OAE = 0;
//	GPT1.GTONCR.BIT.OBE = 0;
//	GPT2.GTONCR.BIT.OAE = 0;
//	GPT2.GTONCR.BIT.OBE = 0;
	PORT9.DDR.BIT.B5=1;	
}

#endif