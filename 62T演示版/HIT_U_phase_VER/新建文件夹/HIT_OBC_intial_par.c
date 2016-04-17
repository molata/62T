float HIT_OBC_current_wn;
float HIT_OBC_current_kexi;
float HIT_OBC_Rs;
float HIT_OBC_Ld;
float HIT_OBC_Lq;
extern float HIT_Rs;
extern float HIT_Ld;
extern float HIT_Lq;
void HIT_OBC_intial_par()
{
	HIT_OBC_current_wn = 0.1;
	HIT_OBC_current_kexi = 1;
	HIT_OBC_Rs = HIT_Rs;
	HIT_OBC_Ld = HIT_Ld;
	HIT_OBC_Lq = HIT_Lq;
}