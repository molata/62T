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
/********************* 串口接收 **********************************/
float fpPC_to_motor_angle = 0;    // 上位机发送给电机的角度指令
float fpMotor_to_pc = 0;
unsigned short usPC_to_motor_cmd = 0XFFFF;  // 上位机发送给电机的所有命令
unsigned short usMotor_to_PC_angle = 0;    // 电机发送给上位机的查询角度
short usCount = 0;
unsigned short usMotor_angle = 0;
extern  int HIT_enc_fin;
unsigned short usMotor_pluse_count = 0;     // 计数脉冲，每500us请求发送一次数据， GPT的周期是25us
unsigned char ucPluse_send = 0;            // 是否发送脉冲，
extern  int HIT_enc_fin;
//#pragma interrupt Gpt0CmVIntFunc(vect=178)
char serial_receive(unsigned char * ucSerial_datas, unsigned int uiCount)
{

	char blResult = 0;
	int isCount = 0;
	R_PG_SCI_StartReceiving_C2(ucSerial_datas, uiCount);
	SCI2.SSR.BIT.RDRF = 0;
	
	for(isCount = 0 ; isCount < uiCount; isCount++)
	{
		if(ucSerial_datas[isCount] != 0XFF)
			blResult = 1;
			break;	
	}
	return blResult;
}
void Gpt0CmVIntFunc()
{
/*		HIT_tgr_d_val3= 600;
		HIT_tgr_b_val3= 600;
		HIT_tgr_c_val4= 500; 
		HIT_tgr_a_val4= 500;
		HIT_tgr_b_val4= 500;
		HIT_tgr_d_val4= 500;*/
	//PORT9.DR.BIT.B4 = !PORT9.DR.BIT.B4;
	PORTA.DR.BIT.B4 = !PORTA.DR.BIT.B4;
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
	if(ucPluse_send == 1)
	{
		//PORT9.DR.BIT.B4 = 0X00;
		ucPluse_send = 2;
	}
	if(ucPluse_send == 2)
	{
		
		//serial_receive(&usPC_to_motor_cmd, 2);
		R_PG_SCI_StartReceiving_C2(&usPC_to_motor_cmd, 2);	
		if(usPC_to_motor_cmd != 0x55AA)
		{
			//fpPC_to_motor_angle = ((float)usPC_to_motor_cmd - 1800)/100;	
		}
		SCI2.SSR.BIT.ORER = 0;   // 溢出标志量，清零
		SCI2.SSR.BIT.FER = 0; 
		ucPluse_send = 0;
	}
	usMotor_pluse_count++;
	if(usMotor_pluse_count > 19)
	{
		//usMotor_to_PC_angle = (unsigned short)HIT_enc_fin;
		usCount++;
		if(usCount >= 500)
		{
			usMotor_to_PC_angle++;	
			usCount = 0;
		}
		//SCI2.TDR = usMotor_to_PC_angle && 0x00FF;
		//SCI2.TDR = (usMotor_to_PC_angle && 0xFF00)>>8;
		R_PG_SCI_StartSending_C2(&usMotor_to_PC_angle, 2);
		ucPluse_send = 1;
		usMotor_pluse_count = 0;
		//PORT9.DR.BIT.B4 = 0X01;
	}
	SCI2.SCR.BIT.RE = 1;
	
}

#endif