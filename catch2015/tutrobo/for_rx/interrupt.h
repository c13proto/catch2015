/********************************************************/
//
//  �T�v
//      ���荞�݊֐��֘A
//	�X�V����
//		2013/02/02
//  �쐬��
//		K.ishimori @ TUTrobo
//
/********************************************************/

#ifndef __INTPRG_H__
#define __INTPRG_H__

/********************************************************/
//  TUTrobo
//
//  �T�v
//      ���荞�݊֐��֘A �v���g�^�C�v�錾
/********************************************************/
void int_cmt_cmt0(void);	// �^�C�}���荞�݊֐�
void int_cmt_cmt1(void);	// �^�C�}���荞�݊֐�
void int_sci1_rxi1(void);	// ��M���荞�݊֐�

//void int_sci0_txi0(void);	// ���M���荞�݊֐�
//void int_sci0_tei0(void);	// ���M�������荞�݊֐�
void int_sci0_rxi0(void);	// ��M���荞�݊֐�
void int_sci0_eri0(void);	// ��M�G���[���荞�݊֐�

//void int_sci1_txi1(void);	// ���M���荞�݊֐�
//void int_sci1_tei1(void);	// ���M�������荞�݊֐�
void int_sci1_rxi1(void);	// ��M���荞�݊֐�
void int_sci1_eri1(void);	// ��M�G���[���荞�݊֐�

//void int_sci2_txi2(void);	// ���M���荞�݊֐�
//void int_sci2_tei2(void);	// ���M�������荞�݊֐�
void int_sci2_rxi2(void);	// ��M���荞�݊֐�
void int_sci2_eri2(void);	// ��M�G���[���荞�݊֐�

void automatic_mode(void);	// ��M�����f�[�^���玩�����s���邩���Ȃ����𔻒f
void R1350N(unsigned char c);			// �W���C��

/********************************************************/
//  TUTrobo
//
//  �T�v
//      ���荞�݊֘A �}�N����`
/********************************************************/
#define SENCE_START()	{CMT.CMSTR0.BIT.STR0 = 1;}
#define SENCE_END()		{CMT.CMSTR0.BIT.STR0 = 0;}
#define TASK_START()	{CMT.CMSTR0.BIT.STR1 = 1;}
#define TASK_END()		{CMT.CMSTR0.BIT.STR1 = 0;}

extern int angle,accX,accY,accZ;//�W���C���̏��B�p�x�A�����x
extern int m_angle;//�p�x
//extern int cmt1_counter;//�^�C�}���荞�݂ɓ������񐔂𐔂���

#endif	//__INTPRG_H__