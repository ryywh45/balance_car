#ifdef __PARAMETER_CONTORL__
#define __PARAMETER_CONTORL__


extern float Kp_b;
extern float Kd_b;
extern float Kp_s;
extern float Ki_s;
extern float Kp_d;
extern float Kd_d;

void parameter_change_init();
void parameter_change();


#endif // __PARAMETER_CONTORL__