#ifndef SPACEVECTORCONTROLC
#define SPACEVECTORCONTROLC
#include"HIT_current_pi.h"
#include"HIT_spacevectorcontrol.h"	
#include <math.h>
#include <mathf.h>
#include "iodefine.h"

#include"HIT_check_table_ab.h"
void HIT_spacevectorcontrol()
{
/*2-2*/
		HIT_Ua = HIT_Ud*HIT_coszhi_a-HIT_Uq*HIT_sinzhi_a;
		HIT_Ub = HIT_Ud*HIT_sinzhi_a+HIT_Uq*HIT_coszhi_a;
		HIT_Usquare = HIT_Ua*HIT_Ua+HIT_Ub*HIT_Ub;
		
		HIT_Ualfa_transfer = sqrt(HIT_Usquare);
		HIT_Ualfa = HIT_Ualfa_transfer;
		
//		HIT_Um = HITnow_voltage_f_out;//give ad_now Voltage modify on 20120414
//		HIT_Um = 37;//27.2;// modify on 20120414
		
//		HITUlim = HITnow_voltage_f_out*HITKr; // modify on 20120414
		HIT_Ulim = HIT_now_voltage_f_out*HIT_kr;// modify on 20120414
		HIT_make_angleab();
		
		if(HIT_Ualfa>HIT_Ulim)
		{
			HIT_Ualfa = HIT_Ulim;	
		}
		HIT_Ualfam = HIT_Ualfa*HIT_ualfamax_k;
		
		
/*fan xiang pwm_0ff*/

		HIT_Vol_adj_fac = HIT_Um_standard/HIT_now_voltage_f;//calculate the PWM adjust factor
		if(HIT_Ualfam<0)
		{
			HIT_Ualfam=HIT_Ualfam*(-1);	
		}

		if(HIT_sitadianab<HIT_boun2)/*zone 1*/
		{
			
			if(HIT_sitadianab == HIT_boun1)
			{
				HIT_pwm_af = HIT_kr*HIT_pwm_full;
				HIT_pwm_af = HIT_pwm_af*HIT_Ualfam;
				HIT_pwm_af = HIT_pwm_af/HIT_Um;
		//		HIT_pwm_af = HIT_pwm_af*HIT_Vol_adj_fac;
				HIT_pwm_af = HIT_pwm_af+HIT_pwm_off;
				HIT_pwm_bf = HIT_pwm_off;
				HIT_pwm_cf = HIT_pwm_off;
			}
			else
			{
				HIT_sitacheck_ab = HIT_sitadianab;
				HIT_check_table_ab();//check sin and cos of AB-axis
				HIT_U_a = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab+HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
				HIT_U_b = HIT_Ualfam*HIT_sinzhi_a_ab;
				HIT_U_c = 0;
				HIT_pwm_af = HIT_U_a/HIT_Um;
				HIT_pwm_af = HIT_pwm_af*HIT_pwm_full;
		//		HIT_pwm_af = HIT_pwm_af*HIT_Vol_adj_fac;
				HIT_pwm_af = HIT_pwm_af+HIT_pwm_off;
				HIT_pwm_bf = HIT_U_b/HIT_Um;
				HIT_pwm_bf = HIT_pwm_bf*HIT_pwm_full;
		//		HIT_pwm_bf = HIT_pwm_bf*HIT_Vol_adj_fac;
				HIT_pwm_bf = HIT_pwm_bf+HIT_pwm_off;
				HIT_pwm_cf = HIT_pwm_off;
			}
		}
		else
		{
			if(HIT_sitadianab<HIT_boun3)/*zone 2*/
			{
				if(HIT_sitadianab == HIT_boun2)
				{
					HIT_pwm_af = HIT_kr*HIT_pwm_full;
					HIT_pwm_af = HIT_pwm_af*HIT_Ualfam;
					HIT_pwm_af = HIT_pwm_af/HIT_Um;
			//		HIT_pwm_af = HIT_pwm_af*HIT_Vol_adj_fac;
					HIT_pwm_af = HIT_pwm_af+HIT_pwm_off;
					HIT_pwm_bf = HIT_kr*HIT_pwm_full;
					HIT_pwm_bf = HIT_pwm_bf*HIT_Ualfam;
					HIT_pwm_bf = HIT_pwm_bf/HIT_Um;
			//		HIT_pwm_bf = HIT_pwm_bf*HIT_Vol_adj_fac;
					HIT_pwm_bf = HIT_pwm_bf+HIT_pwm_off;
					HIT_pwm_cf = HIT_pwm_off;		
				}
			
				else
				{
					HIT_sitacheck_ab = HIT_sitadianab-HIT_boun2;
					HIT_check_table_ab();
					HIT_U_a = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab-HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
					HIT_U_b = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab+HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
					HIT_U_c = 0.0;
					HIT_pwm_af = HIT_U_a/HIT_Um;
					HIT_pwm_af = HIT_pwm_af*HIT_pwm_full;
			//		HIT_pwm_af = HIT_pwm_af*HIT_Vol_adj_fac;
					HIT_pwm_af = HIT_pwm_af+HIT_pwm_off;
					HIT_pwm_bf = HIT_U_b/HIT_Um;
					HIT_pwm_bf = HIT_pwm_bf*HIT_pwm_full;
			//		HIT_pwm_bf = HIT_pwm_bf*HIT_Vol_adj_fac;
					HIT_pwm_bf = HIT_pwm_bf+HIT_pwm_off;
					HIT_pwm_cf = HIT_pwm_off;	
				}	
			}
			else
			{
				if(HIT_sitadianab<HIT_boun4)/*zone 3*/
				{
					if(HIT_sitadianab == HIT_boun3)
					{
						HIT_pwm_af = HIT_pwm_off;
						HIT_pwm_bf = HIT_kr*HIT_pwm_full;
						HIT_pwm_bf = HIT_pwm_bf*HIT_Ualfam;
						HIT_pwm_bf = HIT_pwm_bf/HIT_Um;
				//		HIT_pwm_bf = HIT_pwm_bf*HIT_Vol_adj_fac;
						HIT_pwm_bf = HIT_pwm_bf+HIT_pwm_off;
						HIT_pwm_cf = HIT_pwm_off;		
					}
					else
					{
						HIT_sitacheck_ab = HIT_sitadianab-HIT_boun3;
						HIT_check_table_ab();
						HIT_U_a = 0.0;
						HIT_U_b = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab+HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
						HIT_U_c = HIT_Ualfam*HIT_sinzhi_a_ab;
						HIT_pwm_af = HIT_pwm_off;
						HIT_pwm_bf = HIT_U_b/HIT_Um;
						HIT_pwm_bf = HIT_pwm_bf*HIT_pwm_full;
				//		HIT_pwm_bf = HIT_pwm_bf*HIT_Vol_adj_fac;
						HIT_pwm_bf = HIT_pwm_bf+HIT_pwm_off;
						HIT_pwm_cf = HIT_U_c/HIT_Um;
						HIT_pwm_cf = HIT_pwm_cf*HIT_pwm_full;
				//		HIT_pwm_cf = HIT_pwm_cf*HIT_Vol_adj_fac;
						HIT_pwm_cf = HIT_pwm_cf+HIT_pwm_off;	
					}		
				}
				else
				{
					if(HIT_sitadianab<HIT_boun5)/*zone 4*/
					{
						if(HIT_sitadianab == HIT_boun4)
						{
							HIT_pwm_af = HIT_pwm_off;
							HIT_pwm_bf = HIT_kr*HIT_pwm_full;
							HIT_pwm_bf = HIT_pwm_bf*HIT_Ualfam;
							HIT_pwm_bf = HIT_pwm_bf/HIT_Um;
					//		HIT_pwm_bf = HIT_pwm_bf*HIT_Vol_adj_fac;
							HIT_pwm_bf = HIT_pwm_bf+HIT_pwm_off;
							HIT_pwm_cf = HIT_kr*HIT_pwm_full;
							HIT_pwm_cf = HIT_pwm_cf*HIT_Ualfam;
							HIT_pwm_cf = HIT_pwm_cf/HIT_Um;
					//		HIT_pwm_cf = HIT_pwm_cf*HIT_Vol_adj_fac;
							HIT_pwm_cf = HIT_pwm_cf+HIT_pwm_off;	
						}
						else
						{
							HIT_sitacheck_ab = HIT_sitadianab-HIT_boun4;
							HIT_check_table_ab();
							HIT_U_a = 0.0;
							HIT_U_b = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab-HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
							HIT_U_c = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab+HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
							HIT_pwm_af = HIT_pwm_off;
							HIT_pwm_bf = HIT_U_b/HIT_Um;
							HIT_pwm_bf = HIT_pwm_bf*HIT_pwm_full;
					//		HIT_pwm_bf = HIT_pwm_bf*HIT_Vol_adj_fac;
							HIT_pwm_bf = HIT_pwm_bf+HIT_pwm_off;
							HIT_pwm_cf = HIT_U_c/HIT_Um;
							HIT_pwm_cf = HIT_pwm_cf*HIT_pwm_full;
					//		HIT_pwm_cf = HIT_pwm_cf*HIT_Vol_adj_fac;
							HIT_pwm_cf = HIT_pwm_cf+HIT_pwm_off;
						}
					}
					else
					{
						if(HIT_sitadianab<HIT_boun6)/*zone 5*/
						{
							if(HIT_sitadianab == HIT_boun5)
							{
								HIT_pwm_af = HIT_pwm_off;
								HIT_pwm_bf = HIT_pwm_off;
								HIT_pwm_cf = HIT_kr*HIT_pwm_full;
								HIT_pwm_cf = HIT_pwm_cf*HIT_Ualfam;
								HIT_pwm_cf = HIT_pwm_cf/HIT_Um;
						//		HIT_pwm_cf = HIT_pwm_cf*HIT_Vol_adj_fac;
								HIT_pwm_cf = HIT_pwm_cf+HIT_pwm_off;	
							}
							else
							{
								HIT_sitacheck_ab = HIT_sitadianab-HIT_boun5;
								HIT_check_table_ab();
								HIT_U_a = HIT_Ualfam*HIT_sinzhi_a_ab;
								HIT_U_b = 0;
								HIT_U_c = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab+HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
								HIT_pwm_af = HIT_U_a/HIT_Um;
								HIT_pwm_af = HIT_pwm_af*HIT_pwm_full;
						//		HIT_pwm_af = HIT_pwm_af*HIT_Vol_adj_fac;
								HIT_pwm_af = HIT_pwm_af+HIT_pwm_off;
								HIT_pwm_bf = HIT_pwm_off;
								HIT_pwm_cf = HIT_U_c/HIT_Um;
								HIT_pwm_cf = HIT_pwm_cf*HIT_pwm_full;
						//		HIT_pwm_cf = HIT_pwm_cf*HIT_Vol_adj_fac;
								HIT_pwm_cf = HIT_pwm_cf+HIT_pwm_off;
							}
						}
						else
						{
							if(HIT_sitadianab == HIT_boun6)
							{
								HIT_pwm_af = HIT_kr*HIT_pwm_full;
								HIT_pwm_af = HIT_pwm_af*HIT_Ualfam;
								HIT_pwm_af = HIT_pwm_af/HIT_Um;
					//			HIT_pwm_af = HIT_pwm_af*HIT_Vol_adj_fac;
								HIT_pwm_af = HIT_pwm_af+HIT_pwm_off;
								HIT_pwm_bf = HIT_pwm_off;
								HIT_pwm_cf = HIT_kr*HIT_pwm_full;
								HIT_pwm_cf = HIT_pwm_cf*HIT_Ualfam;
								HIT_pwm_cf = HIT_pwm_cf/HIT_Um;
					//			HIT_pwm_cf = HIT_pwm_cf*HIT_Vol_adj_fac;
								HIT_pwm_cf = HIT_pwm_cf+HIT_pwm_off;	
							}
							else
							{
								HIT_sitacheck_ab = HIT_sitadianab-HIT_boun6;
								HIT_check_table_ab();
								HIT_U_a = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab+HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
								HIT_U_b = 0;
								HIT_U_c = HIT_kr*HIT_Ualfam*HIT_coszhi_a_ab-HIT_khalf*HIT_Ualfam*HIT_sinzhi_a_ab;
								HIT_pwm_af = HIT_U_a/HIT_Um;
								HIT_pwm_af = HIT_pwm_af*HIT_pwm_full;
						//		HIT_pwm_af = HIT_pwm_af*HIT_Vol_adj_fac;
								HIT_pwm_af = HIT_pwm_af+HIT_pwm_off;
								HIT_pwm_bf = HIT_pwm_off;
								HIT_pwm_cf = HIT_U_c/HIT_Um;
								HIT_pwm_cf = HIT_pwm_cf*HIT_pwm_full;
						//		HIT_pwm_cf = HIT_pwm_cf*HIT_Vol_adj_fac;
								HIT_pwm_cf = HIT_pwm_cf+HIT_pwm_off;
							}	
						}	
					}	
				}	
			}	
		}
//		HIT_pwm_af = HIT_pwm_af-HITpwm_deadoff;
			
//		HIT_pwm_bf = HIT_pwm_bf-HITpwm_deadoff;
		
//		HIT_pwm_cf = HIT_pwm_cf-HITpwm_deadoff;
}
#endif