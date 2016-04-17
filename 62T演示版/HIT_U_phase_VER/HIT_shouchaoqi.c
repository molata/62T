#include"HIT_shouchaoqi.h"
#include"iodefine.h"
#include<math.h>
#include<mathf.h>

unsigned char HIT_pwm_mode_choose = 0;
unsigned short HIT_servo_count = 0;
unsigned char HIT_en_tog_start_flag = 0;
char HIT_unable_send_enc = 0;
extern float HIT_alarm;
unsigned char HIT_sv_sta_i = 0;
unsigned char HIT_sv_sta_send_buff[8];
unsigned char HIT_sv_sta_send_count = 0;
unsigned char HIT_high_sv_sta ;
unsigned char HIT_low_sv_sta ;
signed int HIT_sv_sta_int;
char HIT_unable_send_sta = 0;
extern int HIT_virtual_ps_sig_int;
int HIT_xianshi = 0;
extern int HIT_new_angle_int;


unsigned char HIT_rec_adrr_i =0;
unsigned short HIT_rec_adrr_short_0;
unsigned short HIT_rec_adrr_short_1;
unsigned short HIT_rec_adrr_short_2;
unsigned short HIT_rec_adrr_short_3;
unsigned short HIT_rec_adrr_short;
unsigned int HIT_send_adrr_int;
unsigned char HIT_case1 = 0;
unsigned char HIT_case2 = 0;
unsigned char HIT_case3 = 0;
unsigned char HIT_case4 = 0;
//extern unsigned char HIT_rec_adrr_buff[8];

unsigned char HIT_iic_word_rec_1;
unsigned char HIT_iic_word_rec_2;
unsigned char HIT_iic_word_write[2] ;
extern union {
		unsigned char HIT_rec_adrr_buff_char;
		struct {
			unsigned char HIT_rec_data:4;//最低位
			unsigned char HIT_rec_state:1;//中间位
			unsigned char HIT_rec_serial:3;//最高位
		} BIT;
	} HIT_rec_adrr_buff[8];
union {
		unsigned char HIT_send_adrr_buff_char;
		struct {
			unsigned char HIT_send_data:4;//最低位
			unsigned char HIT_send_state:1;//中间位
			unsigned char HIT_send_serial:3;//最高位
		} BIT;
	} HIT_send_adrr_buff[8];
extern union {
		unsigned char HIT_rec_adrr_real_char;
		struct {
			unsigned char HIT_rec_adrr_real_data:4;//最低位
			unsigned char HIT_rec_adrr_real_state:1;//中间位
			unsigned char HIT_rec_adrr_real_serial:3;//最高位
		} BIT;
	} HIT_rec_adrr_real[8];
unsigned short HIT_start_address = 0;
unsigned char HIT_qwereqw = 0;
unsigned short HIT_change_num_num1;
unsigned short HIT_change_num_num2;
unsigned short HIT_change_num_num3;
unsigned short HIT_change_num_num4;
extern unsigned char HIT_ling_zhi;
void HIT_read_sci_adrress();
void Sci2ReFunc()
{
}
void Sci2TrFunc()
{
}
unsigned int HIT_123 = 0;
unsigned char HIT_ee_con_byte_0 = 0;
unsigned char HIT_ee_con_byte_1 = 0;
unsigned short HIT_change_num_1;
unsigned char HIT_ee_write_time = 1;
int HIT_jogon_count = 501;
extern float HIT_Umsensor_f; 
void HIT_shouchaoqi()
{
	
	R_PG_SCI_StartReceiving_C2(HIT_rec_adrr_buff,8);//接收数据

	SCI2.SSR.BIT.RDRF = 0;	
////////////////////////Jogsvon////////////////////	
	HIT_jogon_count++;
	if(HIT_jogon_count > 500)
	{
		HIT_jogon_count = 501;	
	}
////////////////////////Jogsvon////////////////////
	HIT_get_sci_buf_data();
	if((HIT_rec_adrr_real[0].BIT.HIT_rec_adrr_real_state == 0)&&(HIT_rec_adrr_real[1].BIT.HIT_rec_adrr_real_state == 0))
	{
		HIT_read_sci_address();//获取发来的地址
		if((HIT_rec_adrr_short>7000)&&(HIT_rec_adrr_short<7800))//Fn 7600
		{
			HIT_ee_con_byte_0 = 0xa2;
			HIT_ee_con_byte_1 = 0xa3;
			HIT_start_address = 7600;
			if((HIT_rec_adrr_short!= 7605)&&(HIT_rec_adrr_short!=7601)&&(HIT_rec_adrr_short!=7600)&&(HIT_rec_adrr_short!=7607)&&(HIT_rec_adrr_short!=7614))
			{
				HIT_Fn_read_ee_addr_fnc();//ee block1
			}
			
	/*		if(HIT_rec_adrr_short == 7602)
			
			{
				PORT7.DR.BIT.B0 = 0;
				
			  }*/
			switch(HIT_rec_adrr_short)
			{
				case 7605://参数初始化 Fn005
				HIT_par_write_to_ee();
				break;
				case 7602://伺服启动   Fn002
				HIT_shouchaoqi_con_servon();
				break;
				case 7607://写EE角度值  Fn007
				HIT_write_U_angle_to_EE();
				break;
				case 7601://读取角度值  Fn001
				HIT_iic_word_rec_short = HIT_new_angle_short;
				HIT_send_ee_data();
				break;
				case 7614://读取角度值  Fn00E
				HIT_iic_word_rec_short = HIT_Umsensor_f;
				HIT_send_ee_data();
				break;
				case 7600://读取状态值  Fn000
				HIT_read_servo_state();
				break;
				case 7610://读取脉冲值  Fn00A
				HIT_iic_word_rec_short = HIT_virtual_ps_sig_int;
//				HIT_send_ee_data();
				break;
			}
		}
		if((HIT_rec_adrr_short>7900)&&(HIT_rec_adrr_short<8600))//NN 8000
		{
			HIT_ee_con_byte_0 = 0xa6;
			HIT_ee_con_byte_1 = 0xa7;
			HIT_start_address = 8000;
			HIT_Fn_read_ee_addr_fnc();//ee block3	
		}
		if((HIT_rec_adrr_short>8700)&&(HIT_rec_adrr_short<9000))//Pn 8800
		{
			HIT_ee_con_byte_0 = 0xa0;
			HIT_ee_con_byte_1 = 0xa1;
			HIT_start_address = 8800;

			HIT_Fn_read_ee_addr_fnc();//ee block0
				
		}
		if((HIT_rec_adrr_short>9000)&&(HIT_rec_adrr_short<10000))/////////////////////////////////Un 9200
		{
			HIT_ee_con_byte_0 = 0xa4;
			HIT_ee_con_byte_1 = 0xa5;
			HIT_start_address = 9200;
			HIT_Fn_read_ee_addr_fnc();//ee block2	
		}
		if((HIT_rec_adrr_short != 7605)&&(HIT_rec_adrr_short!=7601)&&(HIT_rec_adrr_short!=7600)&&(HIT_rec_adrr_short!=7607)&&(HIT_rec_adrr_short!=7614))
		{
			HIT_send_ee_data();
		}
	}
	
	if((HIT_rec_adrr_real[0].BIT.HIT_rec_adrr_real_state == 1)&&(HIT_rec_adrr_real[1].BIT.HIT_rec_adrr_real_state == 1))
	{
		HIT_read_sci_address();//获取发来的数据
		HIT_change_num = HIT_rec_adrr_short;
		if(HIT_change_num != 0)
		{
						
			if(HIT_iic_write_choose == 32)
			{
				HIT_iic_write_choose = 1;	
			}	
			
			HIT_change_num_H = (HIT_change_num&0xff00)>>8;
			HIT_change_num_L = HIT_change_num&0x00ff;
			if(HIT_ling_zhi == 1)
			{
				HIT_change_num_H = 0x00;
				HIT_change_num_L = 0x00;	
				HIT_iic_word_write[1] = 0x00;
			}
				HIT_write_ee_addr();//写入EE地址内
			
		}
	}

}