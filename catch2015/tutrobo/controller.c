/********************************************************/
//
//  �T�v
//      �R���g���[���[�ݒ�
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "setup.h"		// �}�C�R���̐ݒ�

//	#define 	ABSOLUTE	//��������΍��W����ɐ���
	#define 	RELATIVE	//���������΍��W����ɐ���

int 	ad_data[4];
int 	speed_timer;
char 	pscon_err_flag=0;
double 	max_speed;
char 	shoot_flag_g=0;//���˂����n�߂�t���O
char	rom_debug_flag=0;
char	save_flag=0;
char	load_flag=0;
/*
unsigned char half_1, half_2;
unsigned char duty_L, degree_L, duty_R, degree_R;
unsigned char D_direction_R, D_direction_L;
unsigned char D_direction_U, D_direction_D;
unsigned char sankaku, maru, batsu, shikaku;
unsigned char L1, R1, L2, R2;
*/

/*
double real_spot1[4];//���΍��W�̂��߂̌^
double real_spot2[3];
double real_spot3[3];
double real_pass_field[3];
*/




		//�ԃ]�[���o�H				x		y			�p�x		�ފ�		
auto_route 
/*
red = {
{6296.04, -5449.12, -88.55, 3.07,  },
{ 4840.80, -3486.19, 60.00, 1450.00,  },
{ 4248.64, -3322.24, 60.00, 900.00,  },
{ 3147.57, -1906.85, 60.00, 1300.00,  },
{ 277.01, -351.19, 69.48, 1.84,  },
{ 2988.84, 3078.23, 183.74, 3.07,  },
{ 2680.00, 2872.95, 227.00, 1.84,  }
};
*/
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
//�O��/*
/*
blue = {
{6375.65, 5482.00, 90.30, 2.45,  },
{ 4750.31, 3566.08, -45.00, 1450.00,  },
{ 4290.16, 3472.49, -45.00, 900.00,  },
{ 3121.67, 1875.78, -45.00, 1300.00,  },
{ 407.94, 300.00, -150.82, 1.84,  },
{ 3135.96, -2827.43, -180.52, 3.68,  },
{ 2750.00, -2750.07, -221.00, 0.61,  }
};
*/
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

int fishing_rod,	//�A�[���n���[�^�[�ɓn��duty�����[����^
	l_arm;
					
double	front_direction,//rad
		choose_degree,//�}�V���̐�΍��W�I���̂���(36000)
		kaiten,
		direction_rad,
		direction_duty;
		
//double set_duty_debug[7];
		
//		old_kaiten,
//		old_direction_duty;

char //tower_L_status=air_OPEN,//�������
	 tower_R_t_status=air_OPEN,//�������
	 tower_R_b_status=air_OPEN,
	 hand_R_status=air_UP,
	 hand_L_status=air_UP;
	 
double 	fishing_rod_position,l_arm_position;//�A�[���̏����ʒu����̋�����ۑ�
int 	L_arm_offset  		= 158;			//L�A�[�������ʒu��AD�ϊ��l(���[�t������ʒu�������ʒu�Ƃ���)
int		fishing_rod_offset	= 135;			//�ފƏ����ʒu��AD�ϊ��l(���[�t������ʒu�������ʒu�Ƃ���)
int 	r_psd = 432;						//PSD�����[�t�����m����Ƃ��̒l
int		l_psd = 480;

char hand_R_position,//R�n���h�̏ꏊ
	 hand_L_position,//L�n���h�̏ꏊ
	 servo_position,//�T�[�{�̏ꏊ
	 stopper_position;//�X�g�b�p�[�̏ꏊ
char stopper_count;
char senkai_stop_flag;
/********************************************************/
//  ���O      
//		recieve_data_input
//	�T�v
//		�f�[�^��M�֘A
//	�@�\����
//		�v���X�e�R�������M
//	�p�����[�^����
//		�Ȃ�
//	�߂�l
//		�Ȃ�
//	�쐬��
//		D_direction.Yamamuro @ TUTrobo
/********************************************************/
void recieve_data_input(void)
{


	controller_data();

	if(D_direction_R+D_direction_L+D_direction_U+D_direction_D+PSCON_PRE_SANKAKU+PSCON_PRE_MARU+PSCON_PRE_BATSU+PSCON_PRE_SHIKAKU+
			PSCON_PRE_L1+PSCON_PRE_R1+PSCON_PRE_L2+PSCON_PRE_R2 > 1000)//�\���h�~
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


//	set_duty();		//	�l��duty�ɕϊ�

}

/********************************************************/
//  ���O      
//		set_duty
//	�T�v
//		�f�[�^��M�֘A
//	�@�\����
//		�v���X�e�R���̒l��duty�ɕϊ��B
//
//	������@
//		�ϐ���duty����
//
//	�쐬��
//		D_direction.Yamamuro @ TUTrobo
/********************************************************/
void set_duty(void)
{
	
	how_about_sensor();//�Z���T�[�̏�Ԃ��m�F
	

	
	//�A�[���n�f�o�b�O�̂���
//	set_duty_debug[0]=(double)fishing_rod;
//	set_duty_debug[1]=l_arm;
//	set_duty_debug[2]=direction_rad;

}

/********************************************************/
//  ���O      
//		manual_cntl
//	�T�v
//		�蓮����֘A
//	�@�\����
//		�v���X�e�R���f�[�^����duty���v�Z��PWM���o��
//	�p�����[�^����
//		�Ȃ�
//	�߂�l
//		�Ȃ�
//	�쐬��
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
/********************************************************/
//  ���O      
//		how_about_rom
//	�T�v
//		LED�ł̎��F�p
//	�쐬��
//		��܂ނ�
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
//  ���O      
//		how_about_sensor
//	�T�v
//		�蓮����֘A
//	�@�\����
//		�Z���T�[�̏�Ԃ��m�F
//	�p�����[�^����
//		�Ȃ�
//	�߂�l
//		�Ȃ�
//	�쐬��
//		��܂ނ�
/********************************************************/
void how_about_sensor(void)
{
	static int fish_ad[4];//�ړ����σt�B���^�̂���
	static int l_ad[4];
	int i;
	double fish=0,l_arm=0;
	
	ad_load_4_7(ad_data);
	
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

}

/********************************************************/
//  ���O      
//		how_about_servo
//	�T�v
//		�蓮����֘A
//	�@�\����
//		�T�[�{�̏�Ԃ��m�F
//	�p�����[�^����
//		�Ȃ�
//	�߂�l
//		�Ȃ�
//	�쐬��
//		��܂ނ�
/********************************************************/
char how_about_stopper(void)
{
	char pos;
	static int open_count=0;
	static int close_count=0;
	int interval=0;//�w�����o����0.1�b��ɂ��̃|�W�V�����ɂȂ����Ɖ��肷��
	
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
//  ���O      
//		how_about_servo
//	�T�v
//		�蓮����֘A
//	�@�\����
//		�T�[�{�̏�Ԃ��m�F
//	�p�����[�^����
//		�Ȃ�
//	�߂�l
//		�Ȃ�
//	�쐬��
//		��܂ނ�
/********************************************************/
char how_about_servo(void)
{
	char servo_pos;
	static int servo_open_count=0;
	static int servo_close_count=0;
	int servo_interval=30;//�T�[�{�Ɏw�����o����0.3�b��ɂ��̃|�W�V�����ɂȂ����Ɖ��肷��
	
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
//  ���O      
//		how_about_hand
//	�T�v
//		�蓮����֘A
//	�@�\����
//		�T�[�{�̏�Ԃ��m�F
//	�p�����[�^����
//		�Ȃ�
//	�߂�l
//		�Ȃ�
//	�쐬��
//		��܂ނ�
/********************************************************/
void how_about_hand(void)
{
	static int r_u_timer,r_d_timer,
			   l_u_timer,l_d_timer;
			   
	char interval=17;//�G�A�[�㉺�̐M���o���Ă���̃C���^�[�o��
	char up_interval=15;//�n���h�グ��Ƃ��ɂƂ��Ă���C���^�[�o��
/*	
	//���~�b�g�ł̔���-----------------------------------------------------------
	//R�n���h�ɂ���
	if(AIR_R_UNDER_LIMIT==0)		hand_R_position=air_DOWN;//�����~�b�g�ɐG��Ă�
	else if(AIR_R_UP_LIMIT==0)	hand_R_position=air_UP;//�ナ�~�b�g�ɐG��Ă�
	else hand_R_position=air_MIDDLE;//�����~�b�g�ɂ��ナ�~�b�g�ɂ��G��Ă��Ȃ�
	
	//L�n���h�ɂ���
	if(AIR_L_UNDER_LIMIT==0)		hand_L_position=air_DOWN;//�����~�b�g�ɐG��Ă�
	else if(AIR_L_UP_LIMIT==0)	hand_L_position=air_UP;//�ナ�~�b�g�ɐG��Ă�
	else hand_L_position=air_MIDDLE;//�����~�b�g�ɂ��ナ�~�b�g�ɂ��G��Ă��Ȃ�
	//----------------------------------------------------------------------------
*/	
	
	//timer�ł̔���--------------------------------------------------------------
	if(hand_R_status==air_UP)//R�n���h�ɂ���
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
	
	if(hand_L_status==air_UP)//L�n���h�ɂ���
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