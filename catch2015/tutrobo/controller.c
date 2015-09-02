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
//int 	speed_timer;
char 	pscon_err_flag=0;
//double 	max_speed;
//char 	shoot_flag_g=0;//���˂����n�߂�t���O
//char	rom_debug_flag=0;
//char	save_flag=0;
//char	load_flag=0;



/*
		//�ԃ]�[���o�H				x		y			�p�x		�ފ�		
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
*/

arm_condition ARM_X={
	0,		//�G���R�[�_�̗ݐϒl
	0,		//���W[mm]
	0,		//���x[mm/sec]
	
	1000.0,		//�ő呬�x[mm/sec]
	0,		//�ڕW���x[mm/sec]
	0		//���݂����Ă���duty(-100~100)
};
arm_condition ARM_K={
	0,		//�G���R�[�_�̗ݐϒl
	0,		//���W[degree]
	0,		//�p���x[degree/sec]
	
	120.0,	//�ő�p���x[deg/sec]
	0,		//�ڕW�p���x[mm/sec]
	0		//���݂����Ă���duty(-100~100)
};

arm_condition ARM_Z={
	0,		//ad�̗ݐϒl
	0,		//���W[mm]
	0,		//���x[mm/sec]
	
	1000.0,	//�ő呬�x[mm/sec]
	0,		//�ڕW���x[mm/sec]
	0		//���݂����Ă���duty(-100~100)
};

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
	
	manual_ctrl();//�蓮����
	
}

/********************************************************/
//  ���O      input_PWM_ctrl
//  �T�v      duty����e���W�X�^�ɑΉ��������l���i�[
/********************************************************/
void input_PWM_ctrl(void)
{
	int duty_dc=ANTI_CYCLE*PSstick_to_duty(DUTY_LX,6)/100;
	int duty_sr=SERVO_CYCLE*PSstick_to_duty(DUTY_LX,6)/100;
	
	MTU0.TGRA=ANTI_CYCLE*ARM_X.duty/100;
	MTU0.TGRB=ANTI_CYCLE*ARM_Z.duty/100;
	MTU0.TGRC=ANTI_CYCLE*ARM_K.duty/100;
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
	arm_k_ctrl();//��]�A�[���̐���
	arm_xz_ctrl();//XZ�A�[���̐���
}

void arm_xz_ctrl(void)
{
	
	if(PSCON_PRE_R1>0)//R1��������Ă���Ԃ̓Z���T�̏���p������������Ȃ�
	{
		ARM_X.duty=PSstick_to_duty(DUTY_LY,6)/100.0;
		ARM_Z.duty=PSstick_to_duty(DUTY_RY,6)/100.0;
	}
	else
	{
		ARM_X.aim_v=PSstick_to_duty(DUTY_LY,6)*ARM_X.max_v/100.0;//PS�R���̌X������A�[���̖ڕW���x�v�Z
		ARM_Z.aim_v=PSstick_to_duty(DUTY_RY,6)*ARM_Z.max_v/100.0;
		ARM_X.duty=PID_control_d(ARM_X.aim_v,ARM_X.v,100.0,2.0,0.1,0,10.0,0);//�ڕW���x[mm/sec]�ƌ��ݑ��x����PID�����duty�v�Z
		ARM_Z.duty=PID_control_d(ARM_Z.aim_v,ARM_Z.v,100.0,2.0,0.1,0,10.0,1);
	}
}
void arm_k_ctrl(void)
{
	if(PSCON_PRE_R1>0)//R1��������Ă���Ԃ̓Z���T�̏���p������������Ȃ�
	{
		if(D_direction_U>0)ARM_K.duty=10.0;
		else if(D_direction_D>0)ARM_K.duty=-10.0;
		else ARM_K.duty=0.0;
	}
	else
	{
		if(D_direction_U>0)ARM_K.aim_v=ARM_K.max_v;
		else if(D_direction_D>0)ARM_K.aim_v=-ARM_K.max_v;
		else ARM_K.aim_v=0.0;
		ARM_K.duty=PID_control_d(ARM_K.aim_v,ARM_K.v,30.0,0.1,0.01,0,10.0,2);//�ڕW�p���x[deg/sec]�ƌ��݊p���x����PID�����duty�v�Z
	}
}
/********************************************************/
//  ���O      
//		PSstick_to_duty
//	�T�v
//		�v���X�e�R���̃X�e�B�b�N�̌X����duty�ɕϊ�(th�͒��S�����+-臒l)
//	�쐬��
//		��܂ނ�
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

/********************************************************/
//  ���O      
//		how_about_sensor
//	�T�v
//		�蓮����֘A
//	�@�\����
//		�Z���T�[�̏�Ԃ��m�F
//	�쐬��
//		��܂ނ�
/********************************************************/
void sensor_update(void)
{
	ad_load_4_7(ad_data);
	arm_condition_update(MTU1.TCNT,MTU2.TCNT,ad_data[0]);
	
}

/********************************************************/
//  ���O      
//		arm_condition_update
//	�T�v
//		�A�[����Ԃ̍X�V
//	�쐬��
//		��܂ނ�
/********************************************************/
void arm_condition_update(int enc1,int enc2,int ad)
{
	static int enc1_,enc2_,ad_;		//�ߋ��̃G���R�[�_�J�E���g
	
	const int enc_pulse1=800;		//1��]������̃G���R�[�_�p���X��
	const int enc_pulse2=800;
	const int ad_initial=10;		//ad�ϊ��ł̏����ʒu
	
	const double circ1=50.0*PI;	//1��]�ӂ�ɐi�ދ���[mm]
	const double circ_ad=50.0*PI;

	int diff_x =  (short)((unsigned short)enc1 - (unsigned short)enc1_);		//�G���R�[�_�̉�]�̌����������ŕ␳����B
	int diff_k =  (short)((unsigned short)enc2 - (unsigned short)enc2_);		//�G���R�[�_�̉�]�̌����������ŕ␳����B
	int diff_ad = ad - ad_;		//���x���ׂ邽��ad�ł������͕K�v�B
		
	ARM_X.renc += diff_x;			//�G���R�[�_�J�E���g�̗ݐϒl
	ARM_K.renc += diff_k;
	ARM_Z.renc += diff_ad;			//�|�e���V���Ȃ̂ŗv��Ȃ����ǈꉞ�Ƃ��Ă݂�
					
	ARM_X.pos=ARM_X.renc*circ1/(double)enc_pulse1;//�ݐϒl���猻�݈ʒu�̌v�Z
	ARM_K.pos=ARM_K.renc*360.0/(double)enc_pulse2;//�ݐϒl���猻�݊p�x�̌v�Z
	ARM_Z.pos=(ad-ad_initial)*circ_ad/10.23;//10��]�|�e���V���Ȃ̂�1��]��10.23
	
	ARM_X.v=diff_x*(circ1/(double)enc_pulse1)/(cmt1_counter*0.01);//���x�v�Z[mm/sec]
	ARM_K.v=diff_k*(360.0/(double)enc_pulse2)/(cmt1_counter*0.01);
	ARM_Z.v=diff_ad*(circ_ad/10.23)/(cmt1_counter*0.01);
	cmt1_counter=0;
	
	enc1_=enc1;				//�ߋ��̃G���R�[�_�J�E���g��ۑ�
	enc2_=enc2;
	ad_=ad;
}



#if 0

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
//		how_about_stopper
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

#endif