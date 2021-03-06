/********************************************************/
//
//  概要
//      コントローラー設定
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "setup.h"		// マイコンの設定

//	#define 	ABSOLUTE	//自動化絶対座標を基に制御
	#define 	RELATIVE	//自動化相対座標を基に制御

int 	ad_data[4];
//int 	speed_timer;
char 	pscon_err_flag=0;
//double 	max_speed;
//char 	shoot_flag_g=0;//発射が回り始めるフラグ
//char	rom_debug_flag=0;
//char	save_flag=0;
//char	load_flag=0;



/*
		//赤ゾーン経路				x		y			角度		釣竿		
auto_route 

red = {
{6278.85, -5431.03, -90.00, 0.00,  },
{ 4834.48, -3458.79, 60.00, 1450.00,  },
{ 4207.00, -3267.68, 60.00, 900.00,  },
{ 3157.76, -1810.84, 60.00, 1300.00,  },
{ 277.01, -351.19, 69.48, 1.84,  },
{ 2988.84, 3078.23, 183.74, 3.07,  },
{ 2680.00, 2872.95, 227.00, 1.84,  },
};
auto_route 

blue = {
{6240.58, 5303.86, 90.00, -2.45,  },
{ 4779.23, 3471.63, -50.00, 1450.00,  },
{ 4248.62, 3353.47, -50.00, 900.00,  },
{ 3080.85, 1860.94, -50.00, 1300.00,  },
{ 325.51, 220.76, -156.10, 3.07,  },
{ 3136.85, -2824.64, -186.53, 3.68,  },
{ 2750.00, -2750.07, -222.00, 0.61,  }
};

auto_route 
current = {{ 0.0,0.0,0.0,0.0,  },
{ 0.0, 0.0, 0.0, 0.0,  },
{ 0.0, 0.0, 0.0, 0.0,  },
{ 0.0, 0.0, 0.0, 0.0,  },
{ 0.0, 0.0, 0.0, 0.0,  },
{ 0.0, 0.0, 0.0, 0.0,  },
{ 0.0, 0.0, 0.0, 0.0,  }};

*/

/*
int fishing_rod,	//アーム系モーターに渡すdutyを収納する型
	l_arm;
					
double	front_direction,//rad
		choose_degree,//マシンの絶対座標選択のため(36000)
		kaiten,
		direction_rad,
		direction_duty;
		
//double set_duty_debug[7];
		
//		old_kaiten,
//		old_direction_duty;

char //tower_L_status=air_OPEN,//初期状態
	 tower_R_t_status=air_OPEN,//初期状態
	 tower_R_b_status=air_OPEN,
	 hand_R_status=air_UP,
	 hand_L_status=air_UP;
	 
double 	fishing_rod_position,l_arm_position;//アームの初期位置からの距離を保存
int 	L_arm_offset  		= 158;			//Lアーム初期位置のAD変換値(リーフを取れる位置を初期位置とする)
int		fishing_rod_offset	= 135;			//釣竿初期位置のAD変換値(リーフを取れる位置を初期位置とする)
int 	r_psd = 432;						//PSDがリーフを検知するときの値
int		l_psd = 480;

char hand_R_position,//Rハンドの場所
	 hand_L_position,//Lハンドの場所
	 servo_position,//サーボの場所
	 stopper_position;//ストッパーの場所
char stopper_count;
char senkai_stop_flag;
*/

arm_condition ARM_X={
	0,		//エンコーダの累積値
	0,		//座標[mm]
	0,		//速度[mm/sec]
	
	500.0,		//最大速度[mm/sec]
	0,		//目標速度[mm/sec]
	0		//現在かけているduty(-100~100)
};
arm_condition ARM_K={
	0,		//エンコーダの累積値
	0,		//座標[degree]
	0,		//角速度[degree/sec]
	
	360.0,	//最大角速度[deg/sec]
	0,		//目標角速度[mm/sec]
	0		//現在かけているduty(-100~100)
};

arm_condition ARM_Z={
	0,		//adの累積値
	0,		//座標[mm]
	0,		//速度[mm/sec]
	
	1000.0,	//最大速度[mm/sec]
	0,		//目標速度[mm/sec]
	0		//現在かけているduty(-100~100)
};

char AIR_STATUS=CLOSE;//初期状態;
char SERVO_X_STATUS=OPEN;//初期状態;
char SERVO_LR_STATUS=CLOSE;//初期状態;

const double GET_DEG=195.0;//190
const double THROW_DEG=-25.0;
/********************************************************/
//  名前      
//		recieve_data_input
//	概要
//		データ受信関連
//	機能説明
//		プレステコンから受信
//	パラメータ説明
//		なし
//	戻り値
//		なし
//	作成者
//		D_direction.Yamamuro @ TUTrobo
/********************************************************/
void recieve_data_input(void)
{


	controller_data();

	if(D_direction_R+D_direction_L+D_direction_U+D_direction_D+PSCON_PRE_SANKAKU+PSCON_PRE_MARU+PSCON_PRE_BATSU+PSCON_PRE_SHIKAKU+
			PSCON_PRE_L1+PSCON_PRE_R1+PSCON_PRE_L2+PSCON_PRE_R2 > 1000)//暴走防止
	{
/*		HALF_1=HALF_2=255;
		DUTY_L=DEGREE_L=DUTY_R=DEGREE_R=0;
		D_direction_R=D_direction_L=D_direction_U=D_direction_D=0;
		PSCON_PRE_SANKAKU=PSCON_PRE_MARU=PSCON_PRE_BATSU=PSCON_PRE_SHIKAKU=0;
		PSCON_PRE_L1=PSCON_PRE_R1=PSCON_PRE_L2=PSCON_PRE_R2=0;
*/		
//		set_duty();
//		input_PWM_ctrl();
		POWER_OUT=0;
		pscon_err_flag=1;

	}
	else if(pscon_err_flag==1)
	{
		pscon_err_flag=0;
		POWER_OUT=1;
	}
	else set_duty();


//	set_duty();		//	値をdutyに変換

}

/********************************************************/
//  名前      
//		set_duty
//	概要
//		データ受信関連
//	機能説明
//		プレステコンの値をdutyに変換。
//
//	操作方法
//		変数にdutyを代入
//
//	作成者
//		D_direction.Yamamuro @ TUTrobo
/********************************************************/
void set_duty(void)
{
	
	if(PSCON_PRE_L1==0)manual_ctrl();//手動操作
	auto_ctrl();//自動操作
	if(PSCON_PRE_R1==0)duty_limit_ctrl();//R1押してない時リミットをかける
}

/********************************************************/
//  名前      input_PWM_ctrl
//  概要      dutyから各レジスタに対応した数値を格納
/********************************************************/
void input_register_ctrl(void)
{//ここで正転逆転反転
	int duty_dc=anti_lock_pwm(0.3*PSstick_to_duty(DUTY_LY,PSCON_TH));
	int duty_sr=SERVO_UP*ad_data[1]/1023.0;//servo_pwm(100.0*ad_data[0]/1023.0);//servo_pwm(PSstick_to_duty(DUTY_LX,PSCON_TH));
//DCモータ
	MTU0.TGRA=anti_lock_pwm(ARM_X.duty);
	MTU0.TGRB=anti_lock_pwm(ARM_Z.duty);
	MTU0.TGRC=anti_lock_pwm(-ARM_K.duty);//
	MTU0.TGRD=duty_dc;
	
	MTU4.TGRA=duty_dc;
	MTU4.TGRC=duty_dc;
//サーボ
	if(SERVO_X_STATUS==OPEN)	MTU6.TGRA = SERVO_X_OPEN;
	else 						MTU6.TGRA = SERVO_X_CLOSE;

	if(SERVO_LR_STATUS==OPEN)	MTU6.TGRB = SERVO_L_OPEN;
	else 						MTU6.TGRB = SERVO_L_CLOSE;
	
	MTU6.TGRC = duty_sr;
	
	if(SERVO_LR_STATUS==OPEN)	MTU6.TGRD = SERVO_R_OPEN;
	else						MTU6.TGRD = SERVO_R_CLOSE;
		
	MTU9.TGRA = duty_sr;
	MTU9.TGRC = duty_sr;
	MTU10.TGRA = duty_sr;
	MTU10.TGRC = duty_sr;
	
	if(AIR_STATUS==OPEN)AIR=0;
	else AIR=1;
//	printf("%d,%d\n",duty_dc,duty_sr);


}

//--------------------------------------
//リミット
//-------------------------------------
void duty_limit_ctrl(void)
{
	arm_xz_limit();
	arm_k_limit();
	//K_pos_fix();//ARM_Kのdutyが入っていない時にポジションを固定する制御
}
void arm_k_limit(void)
{

	if (ARM_K.pos > GET_DEG && ARM_K.duty > 0)ARM_K.duty = -2.5;
	if (ARM_K.pos < THROW_DEG && ARM_K.duty < 0)ARM_K.duty = 2.5;

}
void arm_xz_limit(void)
{
	const double x_front_limit = 810.0;
	const double z_down_limit = 536.0;
	const double z_common = 440.0;//zがコレより下じゃないとコモンゾーン上に干渉
	const double x_common = 560.0;//xがコレより奥だとコモンゾーンと干渉
	const double z_lear = 40.0;//zがこれより上じゃないと手前の組付けに干渉
	const double x_lear = 490.0;//xがコレより手前だと手前の組付けに干渉

	//Xアーム
	if (ARM_X.pos < 0 && ARM_X.duty < 0)ARM_X.duty = 0.0;//アームX後ろリミット
	if (ARM_X.pos > x_front_limit && ARM_X.duty>0)ARM_X.duty = -0.0;//アームX前リミット
	if (ARM_Z.pos<z_common && ARM_X.pos>x_common && ARM_X.duty > 0)ARM_X.duty = -1.0;//コモンゾーンとの干渉防止
	if (ARM_Z.pos>z_lear && ARM_X.pos<x_lear && ARM_X.duty < 0)ARM_X.duty = 1.0;//組み付け位置との干渉防止
	//Zアーム
	if (ARM_Z.pos < 0 && ARM_Z.duty < 0)ARM_Z.duty = 0.0;//アームZ上リミット
	if (ARM_Z.pos > z_down_limit && ARM_Z.duty>0)ARM_Z.duty = -0.0;//アームZ下リミット
	if (ARM_X.pos > x_common && ARM_Z.pos < z_common && ARM_Z.duty < 0)ARM_Z.duty = 0.0;//コモンゾーンとの干渉防止
	if (ARM_X.pos < x_lear && ARM_Z.pos<z_lear && ARM_Z.duty > 0)ARM_Z.duty = -0.0;//組み付け位置との干渉防止(上から↓)

	//if (ARM_X.pos < x_lear && ARM_Z.pos>350.0 && ARM_Z.duty<0)ARM_Z.duty=0.0;

}

void K_pos_fix(void)
{
	if(ARM_K.duty==0 && ABS(ARM_K.pos)>10.0 && ARM_K.pos<180.0)ARM_K.duty=50.0*mycos(ARM_K.pos*PI/180.0);
}

//--------------------------------------
//自動
//-------------------------------------

void auto_ctrl(void)
{
	static char L1_count = 0;
	static char old_L1;

	if (PSCON_PRE_L1>0 && D_direction_U>0)task_final();
	else if (PSCON_PRE_L1>0 && D_direction_D>0)task_home();
	else if(PSCON_PRE_L2>0)task_center();
	else
	{ 
		if (PSCON_PRE_L1>0 && L1_count == 1)task1();
		if (PSCON_PRE_L1>0 && L1_count == 2)task_center();
		if (PSCON_PRE_L1>0 && L1_count == 3)task_home();
		if (PSCON_PRE_L1>0 && L1_count == 4)task_final();
		if (PSCON_PRE_L1>0 && L1_count > 4)task_home();
		
		if (PSCON_PRE_L1>0 && old_L1 == 0)L1_count++;
		old_L1 = PSCON_PRE_L1;
	}

}
void task1(void)
{
	const double max_k=2000.0;
	const double stopper_out=49.05;
	static int air_count = 0;
	const int interval = 1;//0.01sで保持(安全仕様:15,GET_DEG-5)

	if (air_count == 0 && ABS(ARM_K.pos - GET_DEG) > 10.0)
	{
		
		//ARM_K.duty = PID_control_d(get_deg, ARM_K.pos, 10.0, 0.1, 0, 0, 1.0, 0);//取得位置まで回転(duty制御)
		if(ARM_K.pos<stopper_out)ARM_K.duty=40.0;//40
		else
		{
			//double duty=PID_control_d(get_deg, ARM_K.pos, 100.0, 1.0, 0, 0, 1.0, 0);//取得位置まで回転(速度制御)
			//if(ARM_K.pos<90.0)ARM_K.duty=20.0;
			//else
			
			{
				if(ARM_K.pos>90.0)AIR_STATUS=OPEN;
				ARM_K.aim_v=360.0;//360
				ARM_K.duty=ARM_K.aim_v*100.0/max_k+PID_control_d(ARM_K.aim_v,ARM_K.v,30.0,0.05,0,0,10.0,0);//目標角速度[deg/sec]と現在角速度からPID制御でduty計算
			}
			if(ARM_K.pos>GET_DEG-20.0)
			{
				ARM_K.duty=-1;
				AIR_STATUS=CLOSE;
				air_count++;
			}
		}
	}
	else if (air_count<interval)//オブジェクト取得
	{
		air_count++;
		ARM_K.duty=-1.0;
	}
	else if (ARM_K.pos > THROW_DEG)
	{
		if(ARM_K.pos>95.0)ARM_K.duty=-90.0;
		else ARM_K.duty=-20.0;
	}
	else 
	{
		ARM_K.duty=0;
		AIR_STATUS=OPEN;
		if(INPUT_PIN(PORTE,3)!=0)SERVO_LR_STATUS=OPEN;
	}
}
void task_center(void)
{
	if(ARM_Z.pos<440.0)auto_xz_ctrl(507.0,470.0,65.0,70.0);
	else auto_xz_ctrl(805.0,470.0,50.0,50.0);//コモンゾーン下側の取得
	//SERVO_X_STATUS=OPEN;
}
void task_home(void)
{
	if(ARM_Z.pos>-5.0)auto_xz_ctrl(507.0,-15.0,40.0,65.0);
	//else auto_xz_ctrl(0.0,0.0,60.0,65.0);//初期位置に戻す
}
void task_final(void)//自陣のオブジェクト
{
	auto_xz_ctrl(507.0,470.0,50.0,50.0);
	//SERVO_X_STATUS=OPEN;
}

void auto_xz_ctrl(double pos_x,double pos_z,double duty_x,double duty_z)
{
	if(ABS(ARM_Z.pos-pos_z)>10.0 || ABS(ARM_X.pos-pos_x)>10.0)//取得エリアのちょい上空まで移動
	{
		ARM_X.duty=PID_control_d(pos_x, ARM_X.pos, duty_x, 0.5, 0, 0, 1.0, 1);
		ARM_Z.duty=PID_control_d(pos_z, ARM_Z.pos, duty_z, 2.25, 0, 0, 1.0, 2);
	}
	else
	{
		ARM_X.duty=0;
		ARM_Z.duty=0;
	}
}

//--------------------------------------
//手動
//-------------------------------------
void manual_ctrl(void)
{
	arm_k_ctrl();//回転アームの制御
	arm_xz_ctrl();//XZアームの制御
	air_ctrl();//Air
	servo_x_ctrl();//servo_x
	servo_lr_ctrl();//servo_lr
}
void servo_lr_ctrl(void)
{
	static char old_maru;
	if(PSCON_PRE_MARU>0 && old_maru==0)SERVO_LR_STATUS*=-1;	
	old_maru=PSCON_PRE_MARU;
}
void servo_x_ctrl(void)
{
	static char old_batsu;
	if(PSCON_PRE_BATSU>0 && old_batsu==0)SERVO_X_STATUS*=-1;	
	old_batsu=PSCON_PRE_BATSU;
}
void air_ctrl(void)
{
	static char old_sankaku;
	if(PSCON_PRE_SANKAKU>0 && old_sankaku==0)AIR_STATUS*=-1;	
	old_sankaku=PSCON_PRE_SANKAKU;
}
void arm_xz_ctrl(void)
{
	double max_x=1394.9;//Duty100での速度[mm/s]
	double max_z=1000.0;
	
	if(PSCON_PRE_R1>0)//R1が押されている間はセンサの情報を用いた制御をしない
	{
		ARM_X.duty=0.1*PSstick_to_duty(DUTY_LY,PSCON_TH);
		ARM_Z.duty=-0.75*PSstick_to_duty(DUTY_RY,PSCON_TH);
	}
	else
	{
		//ARM_X.aim_v=PSstick_to_duty(DUTY_LY,PSCON_TH)*ARM_X.max_v/100.0;//PSコンの傾きからアームの目標速度計算
		//ARM_Z.aim_v=-PSstick_to_duty(DUTY_RY,PSCON_TH)*ARM_Z.max_v/100.0;//↓が正
		//ARM_X.duty = ARM_X.aim_v*100.0 / max_x;// +PID_control_d(ARM_X.aim_v, ARM_X.v, 30.0, 0.05, 0.0, 0, 10.0, 1);//目標速度[mm/sec]と現在速度からPID制御でduty計算
		//ARM_Z.duty = ARM_Z.aim_v*100.0 / max_z;// +PID_control_d(ARM_Z.aim_v, ARM_Z.v, 30.0, 0.05, 0, 0, 10.0, 2);
		ARM_X.duty=PSstick_to_duty(DUTY_LY,PSCON_TH)*0.4;//PSコンの傾きからアームの目標速度計算
		ARM_Z.duty=-PSstick_to_duty(DUTY_RY,PSCON_TH)*0.75;//↓が正
	}
}
void arm_k_ctrl(void)
{
	double max_k=2000.0;//duty100での角速度[deg/s]
	
	if(PSCON_PRE_R1>0)//R1が押されている間はセンサの情報を用いた制御をしない
	{
		if(D_direction_R>0)ARM_K.duty=10.0;
		else if(D_direction_L>0)ARM_K.duty=-10.0;
		else ARM_K.duty=0.0;
	}
	else
	{
		if(D_direction_R>0)ARM_K.duty=25.0;
		else if(D_direction_L>0)ARM_K.duty=-25.0;
		else ARM_K.duty=0.0;
		//if(D_direction_R>0)ARM_K.aim_v=ARM_K.max_v;
		//else if(D_direction_L>0)ARM_K.aim_v=-ARM_K.max_v;
		//else ARM_K.aim_v=0.0;
		//ARM_K.duty=ARM_K.aim_v*100.0/max_k+PID_control_d(ARM_K.aim_v,ARM_K.v,10.0,0.1,0,0,10.0,0);//目標角速度[deg/sec]と現在角速度からPID制御でduty計算
		//if(ARM_K.aim_v==0)ARM_K.duty=0;
	}
}
/********************************************************/
//  名前      
//		PSstick_to_duty
//	概要
//		プレステコンのスティックの傾きをdutyに変換(thは中心からの+-閾値)
//	作成者
//		やまむろ
/********************************************************/
double PSstick_to_duty(int val,int th)
{
	double duty=0;
	
	if( (val>=127-th) && (val<=127+th) )duty=0.0;
	else if(val<127)duty=-100.0*(127.0-(th+val))/(double)(127-th);
	else if(val>127)duty= 100.0*(val-(127.0+th))/(double)(128-th);
	
	if(duty>100)duty=100;
	else if(duty<-100)duty=-100;

	return -duty;//↑で正の値になるように
}

/********************************************************/
//  名前      
//		how_about_sensor
//	概要
//		手動制御関連
//	機能説明
//		センサーの状態を確認
//	作成者
//		やまむろ
/********************************************************/
void sensor_update(void)
{
	if(ABS(ARM_K.pos)>30.0)SAVE_LED=1;
	ad_load_0_3(ad_data);
	arm_condition_update(MTU1.TCNT,MTU2.TCNT,(int)average_4(ad_data[0],0));
	
}
/********************************************************/
//  名前      
//		average_4
//	概要
//		4つの移動平均
//	作成者
//		やまむろ
/********************************************************/
double average_4(int data,char ch)
{
	static int stack[4][4];
	static double ave;
	char i;
	for(i=3;i>0;i--)
	{
		stack[ch][i]=stack[ch][i-1];
	}
	stack[ch][0]=data;
	ave=(double)(stack[ch][0]+stack[ch][1]+stack[ch][2]+stack[ch][3])/4.0;
	
	return ave;
}

/********************************************************/
//  名前      
//		arm_condition_update
//	概要
//		アーム状態の更新
//	作成者
//		やまむろ
/********************************************************/
void arm_condition_update(int enc1,int enc2,int ad)
{
	static int enc1_,enc2_,ad_;		//過去のエンコーダカウント
	
	const int enc_pulse1=4000;		//1回転あたりのエンコーダパルス数
	const int enc_pulse2=1600;
	const int ad_initial=307;		//ad変換での初期位置
	
	const double circ1=48.0*PI;	//1回転辺りに進む距離[mm]
	const double circ_ad=48.0*PI;

	int diff_x =  -(short)((unsigned short)enc1 - (unsigned short)enc1_);		//エンコーダの回転の向きをここで補正する。
	int diff_k =  -(short)((unsigned short)enc2 - (unsigned short)enc2_);		//エンコーダの回転の向きをここで補正する。
	int diff_ad = ad - ad_;		//速度調べるためadでも差分は必要。
		
	ARM_X.renc += diff_x;			//エンコーダカウントの累積値
	ARM_K.renc += diff_k;
	ARM_Z.renc += diff_ad;			//ポテンショなので要らないけど一応とってみる
					
	ARM_X.pos=ARM_X.renc*circ1/(double)enc_pulse1;//累積値から現在位置の計算
	ARM_K.pos=ARM_K.renc*360.0/(double)enc_pulse2;//累積値から現在角度の計算
	ARM_Z.pos=(ad-ad_initial)*circ_ad/102.3;//10回転ポテンショなので1回転で102.3
	
	ARM_X.v=diff_x*(circ1/(double)enc_pulse1)/(cmt1_counter*0.01);//速度計算[mm/sec]
	ARM_K.v=diff_k*(360.0/(double)enc_pulse2)/(cmt1_counter*0.01);
	ARM_Z.v=diff_ad*(circ_ad/102.3)/(cmt1_counter*0.01);
	cmt1_counter=0;
	
	enc1_=enc1;				//過去のエンコーダカウントを保存
	enc2_=enc2;
	ad_=ad;
}



#if 0
/********************************************************/
//  名前      
//		how_about_rom
//	概要
//		LEDでの視認用
//	作成者
//		やまむろ
/********************************************************/

void how_about_rom(void)
{
	static int save_count,load_count;
	
	if(save_flag==1)
	{
		save_count++;
		SAVE_LED=1;
		if(save_count>100)
		{
			SAVE_LED=0;
			save_flag=0;
			save_count=0;
		}
	}
	
	if(load_flag==1)
	{
		load_count++;
		SAVE_LED=1;
		if(load_count>10)SAVE_LED=0;
		if(load_count>20)SAVE_LED=1;
		if(load_count>30)SAVE_LED=0;
		if(load_count>40)SAVE_LED=1;
		if(load_count>50)SAVE_LED=0;
		if(load_count>60)SAVE_LED=1;
		if(load_count>70)SAVE_LED=0;
		if(load_count>80)SAVE_LED=1;
		if(load_count>90)
		{
			SAVE_LED=0;
			load_flag=0;
			load_count=0;
		}
	}
}

/********************************************************/
//  名前      
//		how_about_stopper
//	概要
//		手動制御関連
//	機能説明
//		サーボの状態を確認
//	パラメータ説明
//		なし
//	戻り値
//		なし
//	作成者
//		やまむろ
/********************************************************/
char how_about_stopper(void)
{
	char pos;
	static int open_count=0;
	static int close_count=0;
	int interval=0;//指示を出して0.1秒後にそのポジションになったと仮定する
	
	if(tower_R_b_status==air_OPEN)
	{
		if(open_count<500)open_count++;
		close_count=0;
		
		if(open_count>interval)pos=air_OPEN;
	}
	else if(tower_R_b_status==air_CLOSE)
	{
		open_count=0;
		if(close_count<500)close_count++;
		
		if(close_count>interval)pos=air_CLOSE;
	}
	
	return pos;
}
/********************************************************/
//  名前      
//		how_about_servo
//	概要
//		手動制御関連
//	機能説明
//		サーボの状態を確認
//	パラメータ説明
//		なし
//	戻り値
//		なし
//	作成者
//		やまむろ
/********************************************************/
char how_about_servo(void)
{
	char servo_pos;
	static int servo_open_count=0;
	static int servo_close_count=0;
	int servo_interval=30;//サーボに指示を出して0.3秒後にそのポジションになったと仮定する
	
	if(tower_R_t_status==air_OPEN)
	{
		if(servo_open_count<500)servo_open_count++;
		servo_close_count=0;
		
		if(servo_open_count>servo_interval)servo_pos=air_OPEN;
	}
	else if(tower_R_t_status==air_CLOSE)
	{
		servo_open_count=0;
		if(servo_close_count<500)servo_close_count++;
		
		if(servo_close_count>servo_interval)servo_pos=air_CLOSE;
	}
	
	return servo_pos;
}

/********************************************************/
//  名前      
//		how_about_hand
//	概要
//		手動制御関連
//	機能説明
//		サーボの状態を確認
//	パラメータ説明
//		なし
//	戻り値
//		なし
//	作成者
//		やまむろ
/********************************************************/
void how_about_hand(void)
{
	static int r_u_timer,r_d_timer,
			   l_u_timer,l_d_timer;
			   
	char interval=17;//エアー上下の信号出してからのインターバル
	char up_interval=15;//ハンド上げるときにとっているインターバル
/*	
	//リミットでの判定-----------------------------------------------------------
	//Rハンドについて
	if(AIR_R_UNDER_LIMIT==0)		hand_R_position=air_DOWN;//下リミットに触れてる
	else if(AIR_R_UP_LIMIT==0)	hand_R_position=air_UP;//上リミットに触れてる
	else hand_R_position=air_MIDDLE;//下リミットにも上リミットにも触れていない
	
	//Lハンドについて
	if(AIR_L_UNDER_LIMIT==0)		hand_L_position=air_DOWN;//下リミットに触れてる
	else if(AIR_L_UP_LIMIT==0)	hand_L_position=air_UP;//上リミットに触れてる
	else hand_L_position=air_MIDDLE;//下リミットにも上リミットにも触れていない
	//----------------------------------------------------------------------------
*/	
	
	//timerでの判定--------------------------------------------------------------
	if(hand_R_status==air_UP)//Rハンドについて
	{
		if(r_u_timer<500)r_u_timer++;
		r_d_timer=0;
		if(r_u_timer>(interval+up_interval))hand_R_position=air_UP;
		else hand_R_position=air_MIDDLE;
	}
	else
	{
		r_u_timer=0;
		if(r_d_timer<500)r_d_timer++;
		if(r_d_timer>interval)hand_R_position=air_DOWN;
		else hand_R_position=air_MIDDLE;
	}
	
	if(hand_L_status==air_UP)//Lハンドについて
	{
		if(l_u_timer<500)l_u_timer++;
		l_d_timer=0;
		if(l_u_timer>(interval+up_interval))hand_L_position=air_UP;
		else hand_L_position=air_MIDDLE;
	}
	else
	{
		l_u_timer=0;
		if(l_d_timer<500)l_d_timer++;
		if(l_d_timer>interval)hand_L_position=air_DOWN;
		else hand_L_position=air_MIDDLE;
	}
	//-----------------------------------------------------------------------
	

}

#endif