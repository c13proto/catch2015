/********************************************************/
//
//  �T�v
//      �R���g���[���[�ݒ�
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef	__CONTLOLLER_H__
#define	__CONTLOLLER_H__

/********************************************************/
//  TUTrobo
//
//  �T�v
//      �R���g���[���[�ݒ� �v���g�^�C�v�錾
/********************************************************/
void set_duty(void);
void input_PWM_ctrl(void);

void how_about_sensor(void);
char how_about_servo(void);
char how_about_stopper(void);
void how_about_hand(void);
void suspension_system(void);
void auto_suspension_system(void);
void fishing_rod_system(void);
void l_arm_system(void);
void r_hand_system(void);
void l_hand_system(void);
void r_tower_system(void);
//void l_tower_system(void);
void to_get_leaf(void);
void to_set_leaf(void);
void auto_direction_and_duty(double x,double y,double Kp,double Ki,double Kd);
void speed_check(void);


/*
extern unsigned char half_1, half_2;
extern unsigned char duty_L, degree_L, duty_R, degree_R;
extern unsigned char D_R, D_L;
extern unsigned char D_U, D_D;
extern unsigned char sankaku, maru, batsu, shikaku;
extern unsigned char L1, R1, L2, R2;
*/
//extern double set_duty_debug[7];
extern double max_speed;
extern double kaiten;
extern double choose_degree;//���݂̃}�V���̐�΍��W�̎�������
extern double direction_duty;//���x����duty
extern double fishing_rod_position,l_arm_position;

extern int servo_status;//�T�[�{�̏��
extern int ad_data[4];
extern int speed_timer;

/*
extern int front_shift;

,	//���[�^�[�ɓn��duty�����[����^
			l_arm;
*/
extern int fishing_rod,l_arm;
extern char /*tower_L_status,*/tower_R_b_status,tower_R_t_status,hand_R_status,hand_L_status;
extern char hand_R_position,hand_L_position,servo_position;
extern char pscon_err_flag;
extern char shoot_flag_g;
extern char senkai_stop_flag;
extern char	rom_debug_flag;
extern char	save_flag,load_flag;

extern auto_route red,blue,current; 
#define air_OPEN 	(1)
#define air_CLOSE 	(-1*air_OPEN)
#define air_DOWN  	(1)
#define air_UP 	 	(-1*air_DOWN)
#define air_MIDDLE 	(0)

//#define SERVO_T_OPEN 	4000//����OPEN�l
//#define SERVO_T_CLOSE	500//����CLOSE�l
#define SERVO_B_OPEN 	4912//2350//����OPEN�l
#define SERVO_B_CLOSE	2520//1000//CLOSE�l
//#define SERVO_B_OVER 	6300//2350//����OPEN�l

#define SERVO_T_OPEN 	4281//OPEN�l
#define SERVO_T_CLOSE	7155//CLOSE�l
//#define SERVO_T_OVER 	6300//2350//����OPEN�l


#endif//__CONTLOLLER_H__