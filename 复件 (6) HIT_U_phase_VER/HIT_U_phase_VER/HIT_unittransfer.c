#ifndef SYSTEM_PARAMETER
#define SYSTEM_PARAMETER
#include"unittransfer.h"
#include"systemparameter.h"
#include"parameter.h"
void uinttransfer()
{
/*/////////////////////////////       Sn         //////////////////////////////////////////*/	
	if(HITsystemparameter[1] == 1)//s//////////////////////////HITTi
	{
		HITconstantrans = (int)HITsystemparameter[0];
		HITTi = (float)HITconstantrans;	
	}
	else if(HITsystemparameter[1] == 2)//ms
			{
				HITconstantrans = (int)HITsystemparameter[0];
				HITTi = (float)HITconstantrans;
				HITTi = HITTi/1000;	
			}
		 	else//us
			{
				HITconstantrans = (int)HITsystemparameter[0];
				HITTi = (float)HITconstantrans;
				HITTi = HITTi/1000000;	
			}
 	 if(HITsystemparameter[3] == 2)//////////////////////////HITalfa
	{
		HITconstantrans = (int)HITsystemparameter[2];
		HITalfa = (float)HITconstantrans;
		HITalfa = HITalfa/10;	
	}
	else//////////////////////////HITalfa
	{
		HITconstantrans = (int)HITsystemparameter[2];
		HITalfa = (float)HITconstantrans;	
	} 

	HITconstantrans = (int)HITsystemparameter[4];//////////////HITkv
	HITkv = (float)HITconstantrans;
	if(HITsystemparameter[6] == 1)/////////////////////////////HITlm
	{
		HITconstantrans = (int)HITsystemparameter[5];	
		HITlm = (float)HITconstantrans;
	}
	else if(HITsystemparameter[6] == 4)//uH
			{
				HITconstantrans = (int)HITsystemparameter[5];	
				HITlm = (float)HITconstantrans;
				HITlm = HITlm/1000000;
			}
			else//mH
			{
				HITconstantrans = (int)HITsystemparameter[5];	
				HITlm = (float)HITconstantrans;
				HITlm = HITlm/1000;
			}

	HITconstantrans = (int)HITsystemparameter[7];/////////////HITpoles
	HITpoles = (float)HITconstantrans;
	if(HITsystemparameter[9] == 1)////////////////////////////HITUm_standard
	{
		HITconstantrans = (int)HITsystemparameter[8];
		HITUm_standard = (float)HITconstantrans	;
	}
	else//HITUm_standard/10
	{
		HITconstantrans = (int)HITsystemparameter[8];
		HITUm_standard = (float)HITconstantrans	;
		HITUm_standard = HITUm_standard/10;
	}
 	HITconstantrans = (int)HITsystemparameter[10];/////////////HIT_Umsensor_f_standard
	HIT_Umsensor_f_standard = (float)HITconstantrans;
	if(HITsystemparameter[12] == 1)////////////////////////////HITTs
	{
		HITconstantrans = (int)HITsystemparameter[11];
		HITTs = (float)HITconstantrans;
	}
	else if(HITsystemparameter[12] == 2)//ms
			{
				HITconstantrans = (int)HITsystemparameter[11];
				HITTs = (float)HITconstantrans;
				HITTs = HITTs/1000;
			}
			else	//us
			{
				HITconstantrans = (int)HITsystemparameter[11];
				HITTs = (float)HITconstantrans;
				HITTs = HITTs/1000000;
			}
	HITconstantrans = (int)HITsystemparameter[13];/////////////HITcurr_sen
	HITcurr_sen = (float)HITconstantrans;
	if(HITsystemparameter[15] == 1)//s (HITcurr_tal)
	{
		HITconstantrans = (int)HITsystemparameter[14];
		HITcurr_tal = (float)HITconstantrans;
	}
	else if(HITsystemparameter[15] == 2)//ms
			{
				HITconstantrans = (int)HITsystemparameter[14];
				HITcurr_tal = (float)HITconstantrans;
				HITcurr_tal = HITcurr_tal/1000;
			}
			else//us
			{
				HITconstantrans = (int)HITsystemparameter[14];
				HITcurr_tal = (float)HITconstantrans;
				HITcurr_tal = HITcurr_tal/1000000;
			}
	if(HITsystemparameter[17] == 1)//s (HITUm_standard_tal)
	{
		HITconstantrans = (int)HITsystemparameter[16];
		HITUm_standard_tal = (float)HITconstantrans;
	}
	else if(HITsystemparameter[17] == 2)//ms
			{
				HITconstantrans = (int)HITsystemparameter[16];
				HITUm_standard_tal = (float)HITconstantrans;
				HITUm_standard_tal = HITUm_standard_tal/1000;
			}
			else///us
			{
				HITconstantrans = (int)HITsystemparameter[16];
				HITUm_standard_tal = (float)HITconstantrans;
				HITUm_standard_tal = HITUm_standard_tal/1000000;
			}
/*/////////////////////////////       Pn         //////////////////////////////////////////*/	
	 HITconstantrans = (int)HITparameter[160];/////HITWLMechkv
	 HITWLMechkv = (float)HITconstantrans;
	 if(HITparameter[957] == 2)/////////////////////HITMech_alfa
	 {
	  	HITconstantrans = (int)HITparameter[956]; 
	 	HITMech_alfa = (float)HITconstantrans;
		HITMech_alfa = HITMech_alfa/10;		 
	 }
	 else/////////////////////HITMech_alfa
	 {
	  	HITconstantrans = (int)HITparameter[956]; 
	 	HITMech_alfa = (float)HITconstantrans;		 
	 }


	 if(HITparameter[958] == 1)//HITMechTi  s
	 {
		 HITconstantrans = (int)HITparameter[161];
		 HITMechTi = (float)HITconstantrans;	 
	 }
	 else if(HITparameter[958] == 4)//HITMechTi  us
			 {
				 HITconstantrans = (int)HITparameter[161];
				 HITMechTi = (float)HITconstantrans;
				 HITMechTi = HITMechTi/1000000;	 
			 }
	 		 else//HITMechTi  ms=>200ms
			 {
				 HITconstantrans = (int)HITparameter[161];
				 HITMechTi = (float)HITconstantrans;
				 HITMechTi = HITMechTi/1000;	 
			 }

	HITconstantrans = (int)HITparameter[163];
	HITWL_Jm = (float)HITconstantrans;
	HITWL_Jm = HITWL_Jm/10000000;//Jm(kg*m2)


	 if(HITparameter[05] == 1)//HITtal  s
	 {
		 HITconstantrans = (int)HITparameter[04];
		 HITtal = (float)HITconstantrans;	 
	 }
	 else if(HITparameter[05] == 2)// us
			 {
				 HITconstantrans = (int)HITparameter[04];
				 HITtal = (float)HITconstantrans;
				 HITtal = HITtal/1000;	 
			 }
	  		 else//	ms:200ms=>ki=5	
			 {
				 HITconstantrans = (int)HITparameter[04];
				 HITtal = (float)HITconstantrans;
				 HITtal = HITtal/1000000;	 
			 }
			 
			 
	HITconstantrans = (int)HITparameter[6];
	HITWL_T_factor = (float)HITconstantrans;
	HITWL_T_factor = HITWL_T_factor/1000;//Jm(kg*m2)	
	
	
	HITconstantrans = (int)HITparameter[478];////Jog_speed_mode
	HITWLw_jog_ref = (float)HITconstantrans;
	HITWLw_jog_ref = HITWLw_jog_ref*HITtwopie/sixtysecond;//  rpm==>rad/s
}
#endif