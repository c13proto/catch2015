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

int renc_x,renc_z;
double duty_x,duty_z;//-100.0~100.0


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
	
	how_about_sensor();//センサーの状態を確認
	manual_ctrl();//手動操作
	
}

/********************************************************/
//  名前      
//		manual_cntl
//	概要
//		手動制御関連
//	機能説明
//		プレステコンデータからdutyを計算しPWMを出力
//	パラメータ説明
//		なし
//	戻り値
//		なし
//	作成者
//		S.Baba @ TUTrobo
/********************************************************/
void input_PWM_ctrl(void)
{
	int duty_dc=ANTI_CYCLE*DUTY_LX/255;
	int duty_sr=SERVO_CYCLE*DUTY_LX/255;
	
	MTU0.TGRA=duty_dc;
	MTU0.TGRB=duty_dc;
	MTU0.TGRC=duty_dc;
	MTU0.TGRD=duty_dc;
	
	MTU4.TGRA=duty_dc;
	MTU4.TGRC=duty_dc;

	MTU6.TGRA = duty_sr;
	MTU6.TGRB = duty_sr;
	MTU6.TGRC = duty_sr;
	MTU6.TGRD = duty_sr;
	
	MTU9.TGRA = duty_sr;
	MTU9.TGRC = duty_sr;
	MTU10.TGRA = duty_sr;
	MTU10.TGRC = duty_sr;
	
	//printf("%d,%d\n",duty_dc,duty_sr);


}

void manual_ctrl(void)
{
	duty_x=PSstick_to_duty(DUTY_LY,6);
	duty_z=PSstick_to_duty(DUTY_RY,6);
	
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
void how_about_sensor(void)
{
//	static int fish_ad[4];//移動平均フィルタのため
//	static int l_ad[4];
//	int i;
//	double fish=0,l_arm=0;
	encorder_count(MTU1.TCNT,MTU2.TCNT);
	ad_load_4_7(ad_data);
/*	
	for(i=3;i>0;i--)
	{
		fish_ad[i]=fish_ad[i-1];
		l_ad[i]=l_ad[i-1];
	}
	fish_ad[0]=ad_data[2];
	l_ad[0]=ad_data[1];

	fish=(double)(fish_ad[0]+fish_ad[1]+fish_ad[2]+fish_ad[3])/4.0;
	l_arm=(double)(l_ad[0]+l_ad[1]+l_ad[2]+l_ad[3])/4.0;	
	
	l_arm_position = (l_arm-(double)L_arm_offset)*480.0*PI/1023.0;
	fishing_rod_position = (fish-(double)fishing_rod_offset)*800.0*PI/1023.0;
	
	servo_position=how_about_servo();
	stopper_position=how_about_stopper();
	how_about_hand();
	how_about_rom();
*/

}

/********************************************************/
//  名前      
//		encorder_count
//	概要
//		renc_x,renc_zにエンコーダカウントの累積値を代入
//	作成者
//		やまむろ
/********************************************************/
void encorder_count(int enc_x,int enc_z)
{
	static int enc_x_,enc_z_;		//過去のエンコーダカウント

	int diff_x =  (short)((unsigned short)enc_x - (unsigned short)enc_x_);		//エンコーダの回転の向きをここで補正する。
	int diff_z =  (short)((unsigned short)enc_z - (unsigned short)enc_z_);		//エンコーダの回転の向きをここで補正する。
	
	renc_x += diff_x;			//左のエンコーダカウントの累積値
	renc_z += diff_z;			//右のエンコーダカウントの累積値	
	
	enc_x_=enc_x;				//過去のエンコーダカウントを保存
	enc_z_=enc_z;
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

	return duty;
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