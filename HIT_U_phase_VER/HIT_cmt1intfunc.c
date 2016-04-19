#include "iodefine.h"

#include "HIT_gpt0cmvintfunc.h"
#include "HIT_servoon.h"
#include "HIT_controlsystem_servoon.h"	
#include "HIT_vectorcontrol.h"
//#include "HIT_spacevectorcontrol.h"
#include "HIT_current_pi.h"
#include "HIT_check_table.h"
#include "HIT_make_angle.h"

extern char HIT_ready_go;
unsigned short HIT_RX;
union {
		unsigned short HIT_RX_buff_short;
		struct {
			unsigned short HIT_RX_buff_low:12;//×?μí??
			unsigned short HIT_RX_buff_high:4;//×?????
		} BIT;
	} HIT_RX_buff;
unsigned short HIT_RX_buff_high_1 = 0;
unsigned short HIT_first_spi = 1;
unsigned short HIT_RX_buff_high_2 = 0;
unsigned short HIT_first_spi_count = 0;
unsigned short HIT_spi_make_right = 0;
float HIT_RX_buff_high_err = 0;
extern int HIT_alarm_num;
unsigned short HIT_RX_sita_short = 0;
unsigned short HIT_sita_spi_rec_short = 0;
#define HITtwopie 6.28319
float HIT_sita_M_8_1;
float HIT_sita_M_8_2;
float HIT_sita_M_8_err;
float HIT_sita_M_8_w;
extern float HIT_run_mode;
extern float HIT_sita_mode_10_f;
int HIT_mode_10_mag_sita_int;
float HIT_sita_mode_15_run_first_f;
unsigned short HIT_DA_mode_15_angle = 1;
float HIT_sita_mode_15_run_err_f = 0;
extern float HIT_lpfmode_10_1A;
extern float HIT_lpfmode_10_1B;
float HIT_sita_mode_10_fone = 0.0;
float HIT_sita_mode_10_ftwo = 0.0;
float HIT_sita_mode_10_f_lpf = 0.0;
union {
		int HIT_Rx_re;
			struct {
				unsigned short HIT_Rx_data:16;//倒数3最高位
				unsigned short HIT_Rx_sel:16;//最高位
			}BIT;
		}HIT_Rx_union;
unsigned int HIT_RX_unsigned_int;
int HIT_enc_fin;
unsigned short HIT_gyo_w_fin;
unsigned short HIT_gyo_n_fin;
float HIT_gyo_w_fin_f = 0;
float HIT_gyo_w_da = 0;
float HIT_gyo_n_fin_f = 0;
float HIT_gyo_n_da = 0;
//#pragma interrupt Cmt3IntFunc(vect=169)
char HIT_run_start = 1;
float HIT_gry_x_hall_f_sum = 0;
float HIT_gry_x_hall_f_avg = 0;
unsigned short HIT_count_num = 0;
extern unsigned char HIT_pwm_mode_choose;
/********************* 串口接收 **********************************/
float fpPC_to_motor_angle = 0;    // 上位机发送给电机的角度指令
float fpMotor_to_pc_deg = 0;         // 
float fpMotor_to_pc_velo = 0;    // 向上位机发送
unsigned char ucMotor_send_flag = 0;    // 判断当前返回的速度还是角度：0： 发送角度； 1.发送速度
unsigned short usPC_to_motor_cmd = 0XFFFF;  // 上位机发送给电机的所有命令
unsigned short usMotor_to_PC_value = 0;    // 电机发送给上位机的查询角度
short usCount = 0;
unsigned short usMotor_angle = 0;
extern  int HIT_enc_fin;
unsigned short usMotor_pluse_count = 0;     // 计数脉冲，每500us请求发送一次数据， GPT的周期是25us
unsigned char ucPluse_send = 0;            // 是否发送脉冲，

extern  int HIT_enc_fin;    // 返回的角度值


void Cmt3IntFunc()//50us
{
	
//	PORT3.DR.BIT.B1=1;
//	PORT7.DR.BIT.B0=1;//modify 20131115
   PORTA.DR.BIT.B4=1;//20140711
/////////////////////////////////////////
//	HIT_ready_go = 1;
//	HIT_run_mode = 14;
///////////////////////////////////////////
	GPT0.GTST.BIT.TCFPO =0;//yuan shi ban ben	
/////////////////////////////////angle receive////////////////////////////////
		if(RSPI0.SPSR.BIT.SPRF == 1)
		{
		
			HIT_RX_unsigned_int =  RSPI0.SPDR.LONG;
			HIT_Rx_union.HIT_Rx_re = HIT_RX_unsigned_int;
			if(HIT_Rx_union.BIT.HIT_Rx_sel == 0xFFFF)
			{
				HIT_gyo_w_fin = HIT_Rx_union.BIT.HIT_Rx_data;
				HIT_gyo_w_fin_f = (float)HIT_gyo_w_fin;
				HIT_gyo_w_da = (HIT_gyo_w_fin_f - 32768)/5000;
			}
			else
			{
			 	HIT_enc_fin = HIT_Rx_union.BIT.HIT_Rx_sel;
				HIT_gyo_n_fin = HIT_Rx_union.BIT.HIT_Rx_data;
				HIT_gyo_n_fin_f = (float)HIT_gyo_n_fin;
				HIT_gyo_n_fin_f = HIT_gyo_n_fin_f;
				HIT_gyo_n_da = (HIT_gyo_n_fin_f - 32768)/5000;
				HIT_gyo_n_da = HIT_gyo_n_da - HIT_gry_x_hall_f_avg;
				
				if(HIT_run_start == 1)
				{
					HIT_count_num++;
					HIT_gry_x_hall_f_sum = HIT_gyo_n_da + HIT_gry_x_hall_f_sum;
					if(HIT_count_num == 50000)
					{
						HIT_gry_x_hall_f_avg = HIT_gry_x_hall_f_sum/50000;
						HIT_run_start = 0;
						HIT_ready_go = 1;
						HIT_pwm_mode_choose = 1;
					}	
				}				
			}
				
		}
	if(RSPI0.SPSR.BIT.OVRF == 1)
	{
		RSPI0.SPSR.BIT.OVRF = 0;
	}

	HIT_sita_spi_rec_short = HIT_enc_fin;//HIT_RX;
	HIT_sita = (float)HIT_sita_spi_rec_short/65536*HITtwopie;
	HIT_sita_mode_10_f = HIT_sita;
	
	HIT_mode_10_mag_sita_int = (signed int)(HIT_sita_mode_10_f*HIT_MAKE16WEI_ANGLE);//add 20130530

/////////////////////////////////angle receive END////////////////////////////////
	HIT_make_angle();///////////////////////make angle
	HIT_virtualphotoeletric();//get photoeletric angle older
//	HIT_ready_go = 1;//20140105
	switch(HIT_systemcontrol_mode)
	{
		case 1:
		
		if(HIT_ready_go == 1)
		{
			HIT_controlsystem_servoon();
		}
		break;	
		case 2:
//			HIT_identification();
		break;	
		
		
	}
/*********** 串口程序 **************/
	if(ucPluse_send == 1)
	{
		R_PG_SCI_StartReceiving_C2(&usPC_to_motor_cmd, 2);	
		if(usPC_to_motor_cmd != 0x55AA)
		{
			fpPC_to_motor_angle = ((float)usPC_to_motor_cmd - 1800)/100;	
		}
		SCI2.SCR.BIT.RE = 0X01;  // 手动接收使能
		SCI2.SCR.BIT.RIE = 0X01; // 手动接收中断使能
		ucPluse_send = 0;
		PORT9.DR.BIT.B4 = 0x00;
	}
	usMotor_pluse_count++;
	if(usMotor_pluse_count > 19)
	{
		//usMotor_to_PC_angle = (unsigned short)HIT_enc_fin;
		usCount++;
		if(usCount >= 500)
		{
			usMotor_to_PC_value++;	
			usCount = 0;
		}
		if(ucMotor_send_flag == 0) // 发送角度
		{
			usMotor_to_PC_value = fpMotor_to_pc_deg * 100 + 1800 + 0XAA000000;	
			ucMotor_send_flag= 1;  // 下次发送速度
		}
		else if(ucMotor_send_flag == 1)
		{
			usMotor_to_PC_value	= fpMotor_to_pc_velo * 1000 + 6000 + 0X55000000;
		}
		R_PG_SCI_StartSending_C2(&usMotor_to_PC_value, 2);
		PORT9.DR.BIT.B4 = 0X01;
		ucPluse_send = 1;
		usMotor_pluse_count = 0;
		
	}
	SCI2.SCR.BIT.RE = 1;
//	PORT9.DDR.BIT.B4 = 0;

//	PORT3.DR.BIT.B1=0;
//	PORT7.DR.BIT.B0=0;//modify 20131115
	PORTA.DR.BIT.B4=0;//20140711
}