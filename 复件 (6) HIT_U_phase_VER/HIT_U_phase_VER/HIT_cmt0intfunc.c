#ifndef CMT0INTFUNCC
#define CMT0INTFUNCC
#include "iodefine.h"
#include "HIT_cmt0intfunc.h"

#include	<machine.h>
#include	<_h_c_lib.h>
//#include	<stddef.h>					// Remove the comment when you use errno
//#include 	<stdlib.h>					// Remove the comment when you use rand()
#include	"typedefine.h"		// Define Types
#include	"stacksct.h"		// Stack Sizes (Interrupt and User)


#include "math.h"
#include "mathf.h"

int psw_value;

extern unsigned char HIT_iic_word_send[2] ;/////// address and data to iic send
unsigned char HIT_iic_word_rec;
unsigned char HIT_iic_word_rec_ad = 0x02;// address of iic read ///////////////////////////////////
unsigned char HIT_iic_send_num = 0;
unsigned char HIT_iic_rec_num = 0;
unsigned int HIT_int_send = 0;
unsigned int HIT_rec_num = 0;
unsigned char rcvbuff_char_gr[8];
unsigned short HIT_cmt = 0;
unsigned char HIT_send_data;
unsigned char HIT_rec_i = 0;
unsigned char HIT_iic_send_buff_i=0;
unsigned char HIT_iic_send_buff[8];
unsigned char HIT_iic_send_count = 0;
unsigned char HIT_rewrite_eep = 0;
unsigned char HIT_iic_word_rec_judge;
unsigned char HIT_change_num_title_judge;

unsigned char HIT_angle_send_buff_i = 0;
unsigned char HIT_angle_send_buff[8];
unsigned char HIT_angle_send;
extern int HIT_sitaintf_curr_int;
extern char HIT_ready_go;
unsigned char HIT_iic_choose = 0;

unsigned char HIT_iic_word_rec_1;
unsigned char HIT_iic_word_rec_2;
unsigned short HIT_iic_word_rec_short;
unsigned short HIT_iic_word_rec_short_judge;
unsigned char HIT_iic_word_send_fir;
unsigned char HIT_iic_word_send_sec;
unsigned char HIT_iic_write_choose = 0;
unsigned short HIT_change_num_H;
unsigned short HIT_change_num_L;

unsigned short HIT_p_getad_cmt[4];
unsigned short HIT_n_getad_cmt[4]; 
int HIT_make_angle_mode_cmt;
unsigned short HIT_a_p_hall_cmt;
unsigned short HIT_a_n_hall_cmt;
float HIT_a_hall_cmt;
float HIT_b_hall_cmt;
float HIT_c_hall_cmt;
float HIT_d_hall_cmt;
float HIT_q_hall_cmt;
signed int HIT_a_n_int_cmt;
signed int HIT_a_p_int_cmt;
signed int HIT_s0TX_buffer1_cmt;
signed int HIT_s0TX_buffer2_cmt;
signed int HIT_s0TX_buffer3_cmt;
float HIT_sita_cmt;
float HIT_sitaintf_curr_mech_f_cmt;
signed int HIT_sitaintf_curr_mech_int_cmt;
unsigned short HIT_sitaintf_curr_mech_short_cmt;
unsigned char HIT_sitaintf_curr_mech_char_buff[8];
unsigned char HIT_enc_buff_i = 0;

unsigned char HIT_enc_count=0;
int HIT_sitaintf_curr_mech_int_cmt_bia;

int HIT_check_area_int_cmt;
int HIT_check_area_bia_int_cmt;
float HIT_y_a1_f_cmt;
float HIT_y_a2_f_cmt;
float HIT_x_a1_f_cmt;
float HIT_k_f_cmt ;
float HIT_b_f_cmt ;
float HIT_add_point_f_cmt;
int HIT_add_point_int_cmt;
extern float HIT_biaodingarry[1024];
float HIT_biaoding_ang_f_cmt ;
float HIT_biaoding_f_cmt;
float HIT_new_angle_f_cmt;
int HIT_new_angle_int_cmt;
signed int HIT_sitaintf_curr_int_cmt;
unsigned char HIT_iic_write_choose_U_phase = 0;
extern unsigned short HIT_new_angle_short;
unsigned short HIT_change_num_H_U_phase;
unsigned short HIT_change_num_L_U_phase;

#define HIT_HALFPIE 1.5708
#define HIT_PIE 3.1415926
#define HIT_TWOTHIRDPIE 4.71239
#define HIT_MAKE16WEI_ANGLE 10430.858//10420.6
void Sci2ReFunc()
{
//	psw_value = get_psw();//////////////////////////
//	psw_value |= 0x00010000;
//	set_psw(psw_value);
//		SCI2.SCR.BIT.RIE = 0;
//		SCI2.SSR.BIT.RDRF = 0;
}
void Sci2TrFunc()
{
//	psw_value = get_psw();//////////////////////////
//	psw_value |= 0x00010000;
//	set_psw(psw_value);
}

void Cmt0IntFunc()
{

	PORT2.DR.BIT.B2 = 1;
	psw_value = get_psw();//////////////////////////
	psw_value |= 0x00010000;
	set_psw(psw_value);

	
//	HIT_now_voltage_f_out = 37;//27.2;
	HIT_curren_aa_q_max_cmt0 = HIT_now_voltage_f_out/HIT_kv;//calculate the current_sum_lim  MAX
/* short current alarm */
	HIT_id_fb_square = HIT_id_fb*HIT_id_fb;
	HIT_iq_fb_square = HIT_iq_fb*HIT_iq_fb;
	HIT_idq_square = HIT_id_fb_square+HIT_iq_fb_square;
	
	if(HIT_idq_square > HIT_IDQ_SPE_SQUARE)
	{
		HIT_shortime_cur_count++;
		if(HIT_shortime_cur_count > 9)//serial 10ms match
		{
			//HIT_shortime_curr_alam
			HIT_shortime_cur_count = 0;	
		}	
	}
	else
	{
		HIT_shortime_cur_count = 0;		
	}
/* short current alarm end */ 
	HIT_positon_Kp_trans_f = (float)HIT_positon_Kp_int;//transfer to trsmit parameter
	HIT_positon_Kp_trans_f = HIT_positon_Kp_trans_f * HIT_TWOPIE/HIT_POSITION_16WEI;
	HIT_positon_Kp_f = HIT_positon_Kp_trans_f;//transfer to real register
	
/*disp encord angle*/	
/*	HIT_ceshi[2] = 1;
	HIT_ceshi[1] = (unsigned char)(HIT_sitaintf_curr_mech_int&0x000000ff);

	HIT_ceshi[0] = (unsigned char)((HIT_sitaintf_curr_mech_int&0x0000ff00)>>8);*/
/*disp encord angle end*/	
/*disp mother voltage */	
	HIT_sitaintf_curr_mech_int = 5;
	HIT_int_send++;
	if (HIT_int_send == 30000)
	{
		HIT_int_send = 0;	
	}
	HIT_ceshi[3] = (unsigned char)(HIT_int_send&0x000f) + 64;	
	HIT_ceshi[2] = (unsigned char)((HIT_int_send&0x00f0)>>4) +48;
	HIT_ceshi[1] = (unsigned char)((HIT_int_send&0x0f00)>>8) + 32;
	HIT_ceshi[0] = (unsigned char)((HIT_int_send&0xf000)>>12) + 16;
/*	
	HIT_ceshi[3] = (unsigned char)(HIT_sitaintf_curr_mech_int&0x000f) + 64;	
	HIT_ceshi[2] = (unsigned char)((HIT_sitaintf_curr_mech_int&0x00f0)>>4) +48;
	HIT_ceshi[1] = (unsigned char)((HIT_sitaintf_curr_mech_int&0x0f00)>>8) + 32;
	HIT_ceshi[0] = (unsigned char)((HIT_sitaintf_curr_mech_int&0xf000)>>12) + 16;*/
/*disp mother voltage end*/
//	HIT_send_data = 0x55;
//	R_PG_SCI_StartSending_C2(HIT_ceshi,4);
//	R_PG_SCI_StartSending_C2(&HIT_send_data,1);
	
//	if (HIT_cmt == 10)
	{
	//	R_PG_SCI_StartReceiving_C2(&rcvbuff_char,1);
		R_PG_SCI_StartReceiving_C2(rcvbuff_char_gr,8);
	}
//	if(SCI2.SSR.BIT.RDRF == 1)
	{
		SCI2.SSR.BIT.RDRF = 0;	
		
	}
	
//	R_PG_SCI_StartReceiving_C2(&rcvbuff_char,1);
	for(HIT_rec_i=0;HIT_rec_i<8;HIT_rec_i++)
	{
		HIT_judge = (rcvbuff_char_gr[HIT_rec_i]&0xf0)>>4;
		switch(HIT_judge)
			{
				case 1:
					rcvbuff_char_1 = (unsigned short)(rcvbuff_char_gr[HIT_rec_i]&0x0f)<<12;
				break;	
				case 2:
					rcvbuff_char_2 = (unsigned short)(rcvbuff_char_gr[HIT_rec_i]&0x0f)<<8;	
				break;	
				case 3:
					rcvbuff_char_3 = (unsigned short)(rcvbuff_char_gr[HIT_rec_i]&0x0f)<<4;
				break;	
				case 4:
					rcvbuff_char_4 = (unsigned short)(rcvbuff_char_gr[HIT_rec_i]&0x0f);	
				break;
				case 5:
					rcvbuff_char_5 = (unsigned short)(rcvbuff_char_gr[HIT_rec_i]&0x0f)<<12;	
				break;
				case 6:
					rcvbuff_char_6 = (unsigned short)(rcvbuff_char_gr[HIT_rec_i]&0x0f)<<8;
				break;
				case 7:
					rcvbuff_char_7 = (unsigned short)(rcvbuff_char_gr[HIT_rec_i]&0x0f)<<4;	
				break;
				case 8:
					rcvbuff_char_8 = (unsigned short)(rcvbuff_char_gr[HIT_rec_i]&0x0f);		
				break;
			}	
	}

			rcvbuff_short_title = rcvbuff_char_1 + rcvbuff_char_2 + rcvbuff_char_3 + rcvbuff_char_4;
			HIT_change_num_title = rcvbuff_short_title;
			rcvbuff_short_num = rcvbuff_char_5 + rcvbuff_char_6 + rcvbuff_char_7 + rcvbuff_char_8;
			HIT_change_num = rcvbuff_short_num;
//		}
//////////////////////////////////////////////////receive JUDGE Start/////////////////////////
		HIT_iic_choose++;
		if(HIT_iic_choose == 3)
		{
			HIT_iic_choose = 1;	
		}
		if(rcvbuff_short_title != 0x0c27)
		{
		 	switch(rcvbuff_short_title)
			{
				case 0x0c1d://Fn001
					if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 2;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 3;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}
				break;	
				case 0x0c1e://Fn002
					if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 4;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 5;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}

				break;	
				case 0x0c1f://Fn003
						if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 6;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 7;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}

				break;	
				case 0x0c20://Fn004
					if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 8;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 9;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}

				break;	
				case 0x0c21://Fn005
					if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 10;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 11;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}

				break;	
				case 0x0c22://Fn006
					if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 12;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 13;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}

				break;
				case 0x0c23://Fn007
					if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 16;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 17;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}

				break;	
				case 0x0c24://Fn008 /////////write U phase angle
			/*		if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 16;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 17;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}*/
						
															
						HIT_iic_write_choose_U_phase++;
						if(HIT_iic_write_choose_U_phase == 16)
						{
							HIT_iic_write_choose_U_phase = 1;	
						}	
					//	if((HIT_change_num_title == 0)&&(HIT_change_num != 0))////////////
						{
						//	HIT_iic_word_send[0] = 2;/////the address iic send
						HIT_change_num_H_U_phase = (HIT_new_angle_short&0xff00)>>8;
						HIT_change_num_L_U_phase = HIT_new_angle_short&0x00ff;
							if(HIT_iic_write_choose_U_phase == 1)
							{
								HIT_iic_word_send[0] = 16;
								HIT_iic_word_send[1] = 	(unsigned char)HIT_change_num_H_U_phase;
								R_PG_I2C_MasterSend_C0(0xa2, HIT_iic_word_send, 2);//block 1 dizhi 1 xie 2
							}
							if(HIT_iic_write_choose_U_phase == 8)
							{
								HIT_iic_word_send[0] = 17;
								HIT_iic_word_send[1] = 	(unsigned char)HIT_change_num_L_U_phase;
								R_PG_I2C_MasterSend_C0(0xa2, HIT_iic_word_send, 2);//block 1 dizhi 1 xie 2
							}
		
						}

				break;	
		/*		case 0x0c25://Fn009
					if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 18;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 19;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}

				break;	
				case 0x0c26://Fn00A 
					if(HIT_iic_choose == 1)
					{
						HIT_iic_word_send[0] = 20;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_1,1);
						HIT_iic_word_send_fir = HIT_iic_word_send[0];
					}
					if(HIT_iic_choose == 2)
					{
						HIT_iic_word_send[0] = 21;/////the address iic send
						HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
						HIT_iic_word_rec_ad = HIT_iic_word_send[0];
						R_PG_I2C_MasterSend_C0(0xa2, &HIT_iic_word_rec_ad, 1);
						R_PG_I2C_MasterReceive_C0(0xa3,&HIT_iic_word_rec_2,1);
						HIT_iic_word_send_sec = HIT_iic_word_send[0];
					}
				break;*/

			}

			
			HIT_iic_word_rec_short = (((unsigned short)(HIT_iic_word_rec_1))<<8) + HIT_iic_word_rec_2;
				
			
			for(HIT_iic_send_buff_i=0;HIT_iic_send_buff_i<4;HIT_iic_send_buff_i++)
			{
				HIT_iic_send_buff[HIT_iic_send_buff_i*2] = HIT_iic_word_rec_1;	
				HIT_iic_send_buff[HIT_iic_send_buff_i*2+1] = HIT_iic_word_rec_2;
			} 	

			if((HIT_iic_word_rec_short_judge != HIT_iic_word_rec_short))//||(HIT_change_num_title_judge != HIT_change_num_title))//make it send ee data if data different
			{
				HIT_iic_send_count = 0;	
			}
			HIT_iic_word_rec_short_judge = HIT_iic_word_rec_short;//////make it send ee data if data different END
	//		HIT_change_num_title_judge = HIT_change_num_title;
			if(HIT_iic_send_count < 150)
			{
				R_PG_SCI_StartSending_C2(HIT_iic_send_buff,8);	
			}
			HIT_iic_send_count++;
			if(HIT_iic_send_count > 150)
			{
				HIT_iic_send_count = 151;	
			}
		}
////////////////////////////////////////////////////////////////////ADD////////////////////////////////////////////////		
		if(rcvbuff_short_title == 0x0c26)//Fn014 servo off
		{
			HIT_p_getad_cmt[0] = S12AD0.ADDR0A ;/*get ad*/
			HIT_n_getad_cmt[0] = S12AD1.ADDR0A ;
			S12AD0.ADCSR.BIT.ADST=1;
			S12AD1.ADCSR.BIT.ADST=1;
			AD0.ADCSR.BIT.ADST=1;
			HIT_a_p_hall_cmt = (HIT_p_getad_cmt[0]>>4 );//hall signal A
			HIT_a_n_hall_cmt = (HIT_n_getad_cmt[0]>>4  );//hall signal B


			HIT_a_p_int_cmt = (signed int)HIT_a_p_hall_cmt;
			HIT_a_n_int_cmt = (signed int)HIT_a_n_hall_cmt;	

			HIT_s0TX_buffer1_cmt = HIT_a_p_int_cmt - 2048;
			HIT_s0TX_buffer2_cmt = HIT_a_n_int_cmt - 2048;
		
			HIT_s0TX_buffer3_cmt = -(HIT_s0TX_buffer1_cmt + HIT_s0TX_buffer2_cmt);
			HIT_a_hall_cmt = (float)HIT_s0TX_buffer1_cmt ;
			HIT_b_hall_cmt = (float)HIT_s0TX_buffer2_cmt ;
			HIT_c_hall_cmt = (float)HIT_s0TX_buffer3_cmt ;
			HIT_d_hall_cmt = HIT_a_hall_cmt-0.5*(HIT_b_hall_cmt+HIT_c_hall_cmt);/*angle 3->2*/
			HIT_q_hall_cmt = 0.866025*(HIT_b_hall_cmt-HIT_c_hall_cmt);

	/*angle zone calculate*/
			if(HIT_q_hall_cmt >= 0)
			{
				if(HIT_d_hall_cmt >=0)
				{
					if(HIT_d_hall_cmt > HIT_q_hall_cmt)
					{
						HIT_make_angle_mode_cmt = 1;	
					}
					if(HIT_d_hall_cmt > 0)
					{
						if(HIT_d_hall_cmt <= HIT_q_hall_cmt)
						{
							HIT_make_angle_mode_cmt = 2;	
						}	
					}
					else
					{
						if(HIT_q_hall_cmt == 0)
						{
							HIT_make_angle_mode_cmt = 9;	
						}	
					}	
				}
				else
				{
					if(HIT_q_hall_cmt >= -HIT_d_hall_cmt)	
					{
						HIT_make_angle_mode_cmt = 3;	
					}
					else
					{
						HIT_make_angle_mode_cmt = 4;	
					}
				}	
			}
			else
			{
				if(HIT_d_hall_cmt >=0)
				{
					if(HIT_d_hall_cmt > -HIT_q_hall_cmt)
					{
						HIT_make_angle_mode_cmt = 8;	
					}
					if(HIT_d_hall_cmt >0)
					{
						if(HIT_d_hall_cmt <= -HIT_q_hall_cmt)	
						{
							HIT_make_angle_mode_cmt = 7;	
						}
					}	
				}
				else
				{
					if(HIT_d_hall_cmt < HIT_q_hall_cmt)
					{
						HIT_make_angle_mode_cmt = 5;	
					}	
					else
					{
						HIT_make_angle_mode_cmt = 6;	
					}
				}	
			}
			switch(HIT_make_angle_mode_cmt)
			{
				case 1:
					HIT_sita_cmt=atan(HIT_q_hall_cmt/HIT_d_hall_cmt);
				break;	
				case 2:
					HIT_sita_cmt=HIT_HALFPIE-atan(HIT_d_hall_cmt/HIT_q_hall_cmt);
				break;	
				case 3:
					HIT_sita_cmt=HIT_HALFPIE+atan(-HIT_d_hall_cmt/HIT_q_hall_cmt);
				break;	
				case 4:
					HIT_sita_cmt=HIT_PIE-atan(HIT_q_hall_cmt/-HIT_d_hall_cmt);
				break;
				case 5:
					HIT_sita_cmt=HIT_PIE+atan(HIT_q_hall_cmt/HIT_d_hall_cmt);	
				break;
				case 6:
					HIT_sita_cmt=HIT_TWOTHIRDPIE-atan(HIT_d_hall_cmt/HIT_q_hall_cmt);	
				break;
				case 7:
					HIT_sita_cmt=HIT_TWOTHIRDPIE+atan(HIT_d_hall_cmt/-HIT_q_hall_cmt);	
				break;
				case 8:
					HIT_sita_cmt=HIT_TWOPIE-atan(-HIT_q_hall_cmt/HIT_d_hall_cmt);		
				break;
			}

	/*calculate end*/
			HIT_enc_count++;
			
			HIT_sitaintf_curr_mech_f_cmt = HIT_sita_cmt*HIT_MAKE16WEI_ANGLE;
			HIT_sitaintf_curr_mech_int_cmt = (signed int)HIT_sitaintf_curr_mech_f_cmt;
			HIT_sitaintf_curr_mech_int_cmt_bia = (signed int)HIT_sitaintf_curr_mech_f_cmt;
			
			
	//		HIT_sitaintf_curr_mech_short_cmt = (unsigned short)HIT_sitaintf_curr_mech_int_cmt;


////////check table////////	
	HIT_check_area_int_cmt = HIT_sitaintf_curr_mech_int_cmt_bia&0x0000ffc0;// high 10wei
	HIT_add_point_int_cmt = HIT_sitaintf_curr_mech_int_cmt_bia&0x0000003f;//low 6wei
	HIT_check_area_bia_int_cmt = HIT_check_area_int_cmt>>6;
	

	
//	HIT_check_area_bia_f = (float)HIT_check_area_bia_int;
	if(HIT_check_area_bia_int_cmt==1023)
	{
		HIT_y_a1_f_cmt = HIT_biaodingarry[1023];
		HIT_y_a2_f_cmt = HIT_biaodingarry[0];	
	}
	else
	{
		HIT_y_a1_f_cmt = HIT_biaodingarry[HIT_check_area_bia_int_cmt];
		HIT_y_a2_f_cmt = HIT_biaodingarry[HIT_check_area_bia_int_cmt+1];	
	}

	
	HIT_x_a1_f_cmt = (float)HIT_check_area_bia_int_cmt;
			
	HIT_k_f_cmt = HIT_y_a2_f_cmt - HIT_y_a1_f_cmt;
	HIT_b_f_cmt = HIT_y_a1_f_cmt - HIT_k_f_cmt * HIT_x_a1_f_cmt;
	
	HIT_add_point_f_cmt = (float)HIT_add_point_int_cmt/64;
	HIT_biaoding_ang_f_cmt = HIT_k_f_cmt*(HIT_x_a1_f_cmt +  HIT_add_point_f_cmt) + HIT_b_f_cmt;

	HIT_biaoding_f_cmt = (float)HIT_sitaintf_curr_mech_int_cmt;
	HIT_new_angle_f_cmt = HIT_biaoding_ang_f_cmt + HIT_biaoding_f_cmt;
	if(HIT_new_angle_f_cmt > 65535)
	{
		HIT_new_angle_f_cmt = HIT_new_angle_f_cmt - 65535;	
	}
	if(HIT_new_angle_f_cmt < 0)
	{
		HIT_new_angle_f_cmt = HIT_new_angle_f_cmt + 65535;	
	}
	HIT_new_angle_int_cmt = (int)HIT_new_angle_f_cmt;

	HIT_sitaintf_curr_int_cmt = HIT_new_angle_int_cmt;
	HIT_sitaintf_curr_mech_int_cmt = HIT_sitaintf_curr_int_cmt;
////////check table end////////		
		
			HIT_sitaintf_curr_mech_char_buff[7] = (unsigned char)(HIT_sitaintf_curr_mech_int_cmt&0x000f) + 128;	
			HIT_sitaintf_curr_mech_char_buff[6] = (unsigned char)((HIT_sitaintf_curr_mech_int_cmt&0x00f0)>>4) +112;
			HIT_sitaintf_curr_mech_char_buff[5] = (unsigned char)((HIT_sitaintf_curr_mech_int_cmt&0x0f00)>>8) + 96;
			HIT_sitaintf_curr_mech_char_buff[4] = (unsigned char)((HIT_sitaintf_curr_mech_int_cmt&0xf000)>>12) + 80;
			
			HIT_sitaintf_curr_mech_char_buff[3] = (unsigned char)(HIT_sitaintf_curr_mech_int_cmt&0x000f) + 64;	
			HIT_sitaintf_curr_mech_char_buff[2] = (unsigned char)((HIT_sitaintf_curr_mech_int_cmt&0x00f0)>>4) +48;
			HIT_sitaintf_curr_mech_char_buff[1] = (unsigned char)((HIT_sitaintf_curr_mech_int_cmt&0x0f00)>>8) + 32;
			HIT_sitaintf_curr_mech_char_buff[0] = (unsigned char)((HIT_sitaintf_curr_mech_int_cmt&0xf000)>>12) + 16;
			if(HIT_enc_count  == 10)
			{
				R_PG_SCI_StartSending_C2(HIT_sitaintf_curr_mech_char_buff,8);		
			}		
		}
////////////////////////////////////////////////////////////////ADD END////////////////////////////////////////////////			
		if(rcvbuff_short_title != 0x0c30)//Fn014 servo off
		{
			HIT_ready_go = 0;	
		}
		if(rcvbuff_short_title == 0x0c30)//Fn014 servo on
		{
			HIT_ready_go = 1;		
		}

///////////////////////////////////////////////////// receive xiugai data and write EE///////////////////////
		HIT_iic_write_choose++;
		if(HIT_iic_write_choose == 16)
		{
			HIT_iic_write_choose = 1;	
		}	
		if((HIT_change_num_title == 0)&&(HIT_change_num != 0))////////////***************////////////
		{
		//	HIT_iic_word_send[0] = 2;/////the address iic send
		HIT_change_num_H = (HIT_change_num&0xff00)>>8;
		HIT_change_num_L = HIT_change_num&0x00ff;
			if(HIT_iic_write_choose == 1)
			{
				HIT_iic_word_send[0] = HIT_iic_word_send_fir;
				HIT_iic_word_send[1] = 	(unsigned char)HIT_change_num_H;
				R_PG_I2C_MasterSend_C0(0xa2, HIT_iic_word_send, 2);//block 1 dizhi 1 xie 2
			}
			if(HIT_iic_write_choose == 8)
			{
				HIT_iic_word_send[0] = HIT_iic_word_send_sec;
				HIT_iic_word_send[1] = 	(unsigned char)HIT_change_num_L;
				R_PG_I2C_MasterSend_C0(0xa2, HIT_iic_word_send, 2);//block 1 dizhi 1 xie 2
			}
		
		
	//		HIT_iic_word_send[1] = (unsigned char)HIT_change_num;////the data iic send
	//		R_PG_I2C_MasterSend_C0(0xa2, HIT_iic_word_send, 2);//block 1 dizhi 1 xie 2	
		}

////////////////////////////////////////////////////////////////IIC set/////////////////////// 		

	
	HIT_iic_send_num++;
	HIT_iic_rec_num++;
	if(HIT_iic_send_num == 100)
	{
		HIT_iic_send_num = 2;	
	}
	if(HIT_iic_rec_num == 100)
	{
		HIT_iic_rec_num = 2;	
	}
//	if(rcvbuff_char_gr[0] == 0x55)/// IF shou chao qi send 0x55 zhukongban fasong ee nei di zhi shuju 
	{
//		R_PG_SCI_StartSending_C2(&HIT_iic_word_rec,1);	
	}
////////////////////////////////////////////////////////////////IIC set END/////////////////////// 

//	PORT2.DR.BIT.B4 = !PORT2.DR.BIT.B4; //20121022 dingwei END
	PORT2.DR.BIT.B2 = 0;

}
#endif