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
		int HIT_Rx_Tr;
			struct {
				unsigned char HIT_Rx_Da:8;//最低位
				unsigned char HIT_Rx_M:5;//中间位
				unsigned char HIT_Rx_H_3:1;//倒数3最高位
				unsigned char HIT_Rx_H_1:2;//最高位
			}BIT;
		}HIT_Rx_int;
int HIT_enc_L;
int HIT_enc_H;
int HIT_enc_fin;
int HIT_gyo_w_H;
int HIT_gyo_w_L;
int HIT_gyo_w_fin;
int HIT_gyo_fin;
int HIT_gyo_H;
int HIT_gyo_L;
char HIT_gyo_w_z[2] = {0};
//#pragma interrupt Cmt3IntFunc(vect=169)
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
			HIT_RX = RSPI0.SPDR.LONG;
/////////////////////////////////////////////////////////			
			HIT_Rx_int.HIT_Rx_Tr = HIT_RX;
/*			if(HIT_Rx_int.BIT.HIT_Rx_H_1 == 0)
			{
				if(HIT_Rx_int.BIT.HIT_Rx_H_2 == 0)
				{
					HIT_enc_H = HIT_Rx_int.BIT.HIT_Rx_Da;
				}
				if(HIT_Rx_int.BIT.HIT_Rx_H_2 == 1)
				{
				 	HIT_enc_L = HIT_Rx_int.BIT.HIT_Rx_Da;
				}	
				HIT_enc_fin = (HIT_enc_H<<8) + HIT_enc_L;
			}*/
			
			if((HIT_Rx_int.BIT.HIT_Rx_H_1 == 0)&&(HIT_Rx_int.BIT.HIT_Rx_Da != 0))
			{
				HIT_enc_H = HIT_Rx_int.BIT.HIT_Rx_Da;
			}
			if(HIT_Rx_int.BIT.HIT_Rx_H_1 == 1)
			{
			 	HIT_enc_L = HIT_Rx_int.BIT.HIT_Rx_Da;
			}	
				HIT_enc_fin = (HIT_enc_H<<8) + HIT_enc_L;
			
			
			if(HIT_Rx_int.BIT.HIT_Rx_H_1 == 2)
			{
				if(HIT_Rx_int.BIT.HIT_Rx_H_3 == 0)
				{
					HIT_gyo_w_H = HIT_Rx_int.BIT.HIT_Rx_Da;
				}	
				if(HIT_Rx_int.BIT.HIT_Rx_H_3 == 1)
				{
					HIT_gyo_w_L = HIT_Rx_int.BIT.HIT_Rx_Da;
				}
				HIT_gyo_w_fin = (HIT_gyo_w_H<<8) + HIT_gyo_w_L;		
			}		
					
				
				
			if(HIT_Rx_int.BIT.HIT_Rx_H_1 == 3)
			{
				if(HIT_Rx_int.BIT.HIT_Rx_H_3 == 0)
				{
					HIT_gyo_H = HIT_Rx_int.BIT.HIT_Rx_Da;
					
				}	
				if(HIT_Rx_int.BIT.HIT_Rx_H_3 == 1)
				{
					HIT_gyo_L = HIT_Rx_int.BIT.HIT_Rx_Da;
					
				}		
				HIT_gyo_fin = (HIT_gyo_H<<8) + HIT_gyo_L;
			}		
					
				
			
			
			
/////////////////////////////////////////////////////////////			
		}
	if(RSPI0.SPSR.BIT.OVRF == 1)
	{
		RSPI0.SPSR.BIT.OVRF = 0;
	}

	HIT_sita_spi_rec_short = HIT_RX;
	HIT_sita = (float)HIT_sita_spi_rec_short/65536*HITtwopie;
	
//	HIT_sita = HIT_sita;
	
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

//	PORT3.DR.BIT.B1=0;
//	PORT7.DR.BIT.B0=0;//modify 20131115
	PORTA.DR.BIT.B4=0;//20140711
}