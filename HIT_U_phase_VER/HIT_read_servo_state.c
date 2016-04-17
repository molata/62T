extern char HIT_ready_go;
extern signed int HIT_sv_sta_int;
extern unsigned short HIT_iic_word_rec_short;
extern float HIT_alarm;
extern int HIT_alarm_num;
void HIT_read_servo_state()
{
	if(HIT_ready_go == 1)
	{
		 HIT_sv_sta_int = 0x1BAC;
	}
	if(HIT_ready_go == 0)
	{
		 HIT_sv_sta_int = 0x1BAB;
	}
	if(HIT_alarm == 1)
	{
		 HIT_sv_sta_int = 0x1658;
		 switch(HIT_alarm_num)
		 {
			case 1:
			HIT_sv_sta_int = 0x1659;
			break;
			case 2:
			HIT_sv_sta_int = 0x165A;
			break;
			case 3:
			HIT_sv_sta_int = 0x165B;
			break;
			case 4:
			HIT_sv_sta_int = 0x165C;
			break;
			case 5:
			HIT_sv_sta_int = 0x165D;
			break;	 
		 }
	}
	HIT_iic_word_rec_short = HIT_sv_sta_int;
	HIT_send_ee_data();	
}