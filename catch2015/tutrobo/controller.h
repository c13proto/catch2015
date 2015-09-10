/********************************************************/
//
//  概要
//      コントローラー設定
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef	__CONTLOLLER_H__
#define	__CONTLOLLER_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      コントローラー設定 プロトタイプ宣言
/********************************************************/
void set_duty(void);
void input_register_ctrl(void);
void sensor_update(void);
double average_4(int data,char ch);
void arm_condition_update(int enc1,int enc2,int ad);
double PSstick_to_duty(int val,int th);

void duty_limit_ctrl(void);
void arm_k_limit(void);
void arm_xz_limit(void);
void K_pos_fix(void);

void auto_ctrl(void);
void task1(void);
void task_center(void);
void task_home(void);
void task_final(void);
void auto_xz_ctrl(double pos_x,double pos_z,double duty_x,double duty_z);

void manual_ctrl(void);
void arm_k_ctrl(void);//回転アームの制御
void arm_xz_ctrl(void);//XZアームの制御
void air_ctrl(void);
void servo_x_ctrl();//servo_x
void servo_lr_ctrl();//servo_lr
//char how_about_servo(void);
//char how_about_stopper(void);
//void how_about_hand(void);
//void suspension_system(void);
//void auto_suspension_system(void);
//void fishing_rod_system(void);
//void l_arm_system(void);
//void r_hand_system(void);
//void l_hand_system(void);
//void r_tower_system(void);
//void l_tower_system(void);
//void to_get_leaf(void);
//void to_set_leaf(void);
//void auto_direction_and_duty(double x,double y,double Kp,double Ki,double Kd);
//void speed_check(void);


/*
extern unsigned char half_1, half_2;
extern unsigned char duty_L, degree_L, duty_R, degree_R;
extern unsigned char D_R, D_L;
extern unsigned char D_U, D_D;
extern unsigned char sankaku, maru, batsu, shikaku;
extern unsigned char L1, R1, L2, R2;
*/
//extern double set_duty_debug[7];
//extern double max_speed;
//extern double kaiten;
//extern double choose_degree;//現在のマシンの絶対座標の軸を見る
//extern double direction_duty;//速度方向duty
//extern double fishing_rod_position,l_arm_position;

//extern int servo_status;//サーボの状態
extern int ad_data[4];
//extern int speed_timer;

/*
extern int front_shift;

,	//モーターに渡すdutyを収納する型
			l_arm;
*/
//extern int fishing_rod,l_arm;
//extern char /*tower_L_status,*/tower_R_b_status,tower_R_t_status,hand_R_status,hand_L_status;
//extern char hand_R_position,hand_L_position,servo_position;
extern char pscon_err_flag;
//extern char shoot_flag_g;
//extern char senkai_stop_flag;
//extern char	rom_debug_flag;
//extern char	save_flag,load_flag;
//extern auto_route red,blue,current;
extern arm_condition ARM_X,ARM_K,ARM_Z;
extern char AIR_STATUS;
extern char SERVO_X_STATUS;
extern char SERVO_LR_STATUS;
 
#define PSCON_TH	35
#define OPEN 	(1)
#define CLOSE 	(-1*OPEN)
//#define air_OPEN 	(1)
//#define air_CLOSE 	(-1*air_OPEN)
//#define air_DOWN  	(1)
//#define air_UP 	 	(-1*air_DOWN)
//#define air_MIDDLE 	(0)

//#define SERVO_T_OPEN 	4000//仮のOPEN値
//#define SERVO_T_CLOSE	500//仮のCLOSE値
//#define SERVO_B_OPEN 	4912//2350//仮のOPEN値
//#define SERVO_B_CLOSE	2520//1000//CLOSE値
//#define SERVO_B_OVER 	6300//2350//仮のOPEN値

//#define SERVO_T_OPEN 	4281//OPEN値
//#define SERVO_T_CLOSE	7155//CLOSE値
//#define SERVO_T_OVER 	6300//2350//仮のOPEN値

#define SERVO_X_OPEN	6125//初期
#define SERVO_X_CLOSE	3400
#define SERVO_L_CLOSE	3623//初期
#define SERVO_L_OPEN	5761
#define SERVO_R_CLOSE	3761//初期
#define SERVO_R_OPEN	4827


#endif//__CONTLOLLER_H__