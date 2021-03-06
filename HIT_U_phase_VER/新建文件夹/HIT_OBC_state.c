float HIT_Vd = 0;
float HIT_Vq = 0;
extern float HIT_Lq;
extern float HIT_Ld;
extern float HIT_speedlpf_pole;
extern float HIT_iq_fb;
extern float HIT_id_fb;
extern float HIT_id_org;
extern float HIT_iq_org;
extern float HIT_alfa;
extern float HIT_id_ref;
extern float HIT_iq_ref;
extern float HIT_Ud;
extern float HIT_Uq;
extern float HIT_faif;

float HIT_Vd_ob;
float HIT_Vq_ob;
extern float HIT_OBC_id;
extern float HIT_OBC_iq;
extern float HIT_OBC_Dd;
extern float HIT_OBC_Dq;
extern float HIT_OBC_Lq;
extern float HIT_OBC_Ld;
extern float HIT_OBC_id_ob_1;
extern float HIT_OBC_id_ob_2;
extern float HIT_OBC_id_ob_3;
extern float HIT_OBC_iq_ob_1;
extern float HIT_OBC_iq_ob_2;
extern float HIT_OBC_iq_ob_3;
extern float HIT_Ts;

void HIT_OBC_state()
{
	HIT_Vd_ob = (HIT_speedlpf_pole*HIT_OBC_Lq*HIT_iq_fb+ HIT_Ud)/HIT_OBC_Ld ;
	
	HIT_Vq_ob = (-HIT_speedlpf_pole*HIT_OBC_Ld*HIT_id_fb - HIT_speedlpf_pole*HIT_faif + HIT_Uq)/HIT_OBC_Lq;
	
	HIT_OBC_id = HIT_OBC_id - HIT_OBC_id_ob_1*HIT_OBC_id + HIT_OBC_Dd*HIT_Ts;
	HIT_OBC_id = HIT_OBC_id + HIT_Vd_ob*HIT_Ts;
	HIT_OBC_id = HIT_OBC_id + HIT_OBC_id_ob_2*(HIT_id_fb - HIT_OBC_id);
	
	HIT_OBC_Dd = HIT_OBC_Dd + HIT_OBC_id_ob_3*(HIT_id_fb - HIT_OBC_id);
	
	HIT_OBC_iq = HIT_OBC_iq - HIT_OBC_iq_ob_1*HIT_OBC_iq + HIT_OBC_Dq*HIT_Ts;
	HIT_OBC_iq = HIT_OBC_iq + HIT_Vq_ob*HIT_Ts;
	HIT_OBC_iq = HIT_OBC_iq + HIT_OBC_iq_ob_2*(HIT_iq_fb - HIT_OBC_iq);
	
	HIT_OBC_Dq = HIT_OBC_Dq + HIT_OBC_iq_ob_3*(HIT_iq_fb - HIT_OBC_iq);
}