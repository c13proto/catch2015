/********************************************************/
//
//  概要
//      マイコンの設定
//  作成者
//		@ TUTrobo
//
/********************************************************/

#ifndef __SETUP_H__
#define __SETUP_H__

/********************************************************/
//  TUTrobo
//
//  概要
//      マイコンの設定 読み込みヘッダファイル宣言
/********************************************************/

#include <stdio.h>
#include <stdarg.h> 	//printf 関数のような可変個の実引数の操作に関する型とマクロの定義
#include <math.h>		//一般的な数値演算および変換を計算する関数のセットを宣言

#include "type.h"		//プログラムの型名宣言
#include "table.h"
#include "../iodefine.h"	//PINdefine
#include "../typedefine.h"	//型の別名宣言 


#define CPU_RX621
//#define CPU_SH7125

//CPU別インクルードファイル
#ifdef CPU_SH7125
	#include "for_sh7125/ad.h"			//A/D変換設定
	#include "for_sh7125/clock.h"		//CLOCK設定
	#include "for_sh7125/cmt.h"		//CMT関連
	#include "for_sh7125/io.h"			//ピン設定
	#include "for_sh7125/enc.h"		//エンコーダ関連
	#include "for_sh7125/interrupt.h"	//割り込み関連定義
	#include "for_sh7125/pwm.h"		//PWM設定
	#include "for_sh7125/sci.h"		//SCI関連設定
	#include "for_sh7125/wdt.h"		//WDT関連定義
#endif

#ifdef CPU_RX621
	#include "for_rx/ad.h"			//A/D変換設定
	#include "for_rx/clock.h"		//CLOCK設定
	#include "for_rx/cmt.h"		//CMT関連
	#include "for_rx/io.h"			//ピン設定
	#include "for_rx/enc.h"		//エンコーダ関連
	#include "for_rx/interrupt.h"	//割り込み関連定義
	#include "for_rx/pwm.h"		//PWM設定
	#include "for_rx/sci.h"		//SCI関連設定
	#include "for_rx/fld.h"     //データフラッシュ
	#include "for_rx/wdt.h"		//WDT関連定義
#endif

//#include "calc.h"		//計算関連定義 おもに移動経路関連
#include "macro.h"		//計算用マクロ定義

#include "common.h"		//共通の設定事項
//#include "sence.h"		//計測関連定義　ioの上位関数

//#include "omuni.h"		//オムニ関連 ioの上位関数

#include "comu2.h"		//通信関連定義 sciの上位関数

//#include "control.h"	//マシン移動制御関連 発射
#include "controller.h"	//コントローラー関連 手動　omuniの上位関数

#include "cet.h"

//#include "feedback.h"	//フィードバック関連定義
//#include "path.h"		// パス（コマンド）設定


#ifdef CPU_SH7125
/*******************************************************************/
//PIN CONFIG
/*******************************************************************/
#define AIR_RIGHT_HAND 			OUTPUT_PIN(PE,4)
#define AIR_LEFT_HAND 			OUTPUT_PIN(PE,7)
#define AIR_RIGHT_HAND_WIDE		OUTPUT_PIN(PE,5)
#define AIR_LEFT_TOWER 			OUTPUT_PIN(PE,9)
#define AIR_RIGHT_TOWER      	OUTPUT_PIN(PE,6)
#define POWER_OUT				OUTPUT_PIN(PE,3)
#define AIR_LEFT_HAND_WIDE		OUTPUT_PIN(PE,11)
#define BUZZER_OUT				OUTPUT_PIN(PE,15)

//#define MODE_IN					INPUT_PIN(PORTE,0)
//#define L_HOLD_LIMIT 			INPUT_PIN(PORTA,1)
//#define L_UNHOLD_LIMIT 			INPUT_PIN(PORTA,0)

#define AIR_R_UNDER_LIMIT 		INPUT_PIN_PF(0)
#define AIR_R_UP_LIMIT   		INPUT_PIN_PF(1)
#define AIR_L_UNDER_LIMIT 		INPUT_PIN_PF(3)
#define AIR_L_UP_LIMIT   		INPUT_PIN_PF(2)

#define R_TOWER_UNDER_LIMIT 	INPUT_PIN(PB,1)//リーフ
#define L_TOWER_UNDER_LIMIT 	INPUT_PIN(PB,2)//リーフ
#define SERVO_LIMIT				INPUT_PIN(PB,3)

//#define LEAF_COLLECT_HAND_PIN 	INPUT_PIN(PORTE,7) // PE.DRL.BIT.B7
//#define LEAF_ESTA_HAND_PIN 		INPUT_PIN(PORTE,6) // PE.DRL.BIT.B6

/*//以前の配置
#define FRONT_SIFT_PWM		    PWM_PIN(0,B)//MTU20.TGRB
#define L_ARM_PWM               PWM_PIN(0,C)//MTU20.TGRC
#define FISH_PWM				PWM_PIN(0,A)//MTU20.TGRA
#define O_PWM					PWM_PIN(3,A)//MTU23.TGRA
#define L_PWM					PWM_PIN(3,C)//MTU23.TGRC
#define R_PWM					PWM_PIN(4,A)//MTU24.TGRA
#define SERVO_PWM 				PWM_PIN(4,C)//MTU24.TGRC
*/

#define O_PWM					PWM_PIN(0,A)//MTU20.TGRA
#define L_PWM					PWM_PIN(0,B)//MTU20.TGRB
#define R_PWM					PWM_PIN(0,C)//MTU20.TGRC
//#define L_ARM_PWM             PWM_PIN(3,A)//MTU23.TGRA
//#define FISH_PWM				PWM_PIN(3,C)//MTU23.TGRC
#define SERVO_T_PWM				PWM_PIN(4,A)//MTU24.TGRA
#define SERVO_B_PWM 			PWM_PIN(4,C)//MTU24.TGRC

#endif

#ifdef CPU_RX621
/*******************************************************************/
//PIN CONFIG
/*******************************************************************/
#define AIR_RIGHT_HAND 			OUTPUT_PIN(PORTD,0)
#define AIR_RIGHT_TOWER   		OUTPUT_PIN(PORTD,1)
#define AIR_RIGHT_HAND_WIDE		OUTPUT_PIN(PORTD,2)
#define AIR_LEFT_HAND 			OUTPUT_PIN(PORTD,3)
#define AIR_LEFT_TOWER 			OUTPUT_PIN(PORTD,4)

//#define AIR_LEFT_HAND_WIDE		OUTPUT_PIN(PORTA,5)
#define AIR						OUTPUT_PIN(PORTA,5)
#define POWER_OUT				OUTPUT_PIN(PORTA,6)
#define SAVE_LED				OUTPUT_PIN(PORTA,7)
#define LASER_OUT				OUTPUT_PIN(PORTA,4)
#define LED_BLUE				OUTPUT_PIN(PORTB,3)
#define LED_RED					OUTPUT_PIN(PORTB,2)

#define SAVE_BTN				INPUT_PIN(PORTB,6)
#define LOAD_BTN				INPUT_PIN(PORTE,4)

//#define MODE_IN					INPUT_PIN(PORTE,0)
//#define L_HOLD_LIMIT 			INPUT_PIN(PORTA,1)
//#define L_UNHOLD_LIMIT 			INPUT_PIN(PORTA,0)

#define AIR_R_UNDER_LIMIT 		INPUT_PIN(PORTE,0)
#define AIR_R_UP_LIMIT   		INPUT_PIN(PORTE,1)
#define AIR_L_UNDER_LIMIT 		INPUT_PIN(PORTE,2)
#define FIELD_MODE              INPUT_PIN(PORTE,3)

#define R_TOWER_UNDER_LIMIT 	INPUT_PIN(PORTE,5)//リーフ
#define L_TOWER_UNDER_LIMIT 	INPUT_PIN(PORTE,6)//リーフ
#define SERVO_LIMIT				INPUT_PIN(PORTE,7)

//#define LEAF_COLLECT_HAND_PIN 	INPUT_PIN(PORTE,7) // PE.DRL.BIT.B7
//#define LEAF_ESTA_HAND_PIN 		INPUT_PIN(PORTE,6) // PE.DRL.BIT.B6

/*//以前の配置
#define FRONT_SIFT_PWM		    PWM_PIN(0,B)//MTU20.TGRB
#define L_ARM_PWM               PWM_PIN(0,C)//MTU20.TGRC
#define FISH_PWM				PWM_PIN(0,A)//MTU20.TGRA
#define O_PWM					PWM_PIN(3,A)//MTU23.TGRA
#define L_PWM					PWM_PIN(3,C)//MTU23.TGRC
#define R_PWM					PWM_PIN(4,A)//MTU24.TGRA
#define SERVO_PWM 				PWM_PIN(4,C)//MTU24.TGRC
*/

#define O_PWM					PWM_PIN(0,A)//MTU20.TGRA
#define L_PWM					PWM_PIN(0,B)//MTU20.TGRB
#define R_PWM					PWM_PIN(0,D)//MTU20.TGRC
#define L_ARM_PWM               PWM_PIN(6,A)//PWM_PIN(0,C)//MTU23.TGRA
#define FISH_PWM				PWM_PIN(6,D)//PWM_PIN(4,A)//MTU23.TGRC

#define SERVO_B_PWM				PWM_PIN(10,C)//MTU24.TGRA
#define SERVO_T_PWM 			PWM_PIN(10,A)//MTU24.TGRC

//pinコンフィグ
#define ENC1_TCNT 				MTU7.TCNT 
#define ENC2_TCNT 				MTU8.TCNT 

#define ROLLER1_PWM 			PWM_PIN(4,C)
#define ROLLER2_PWM 			PWM_PIN(4,A)//PWM_PIN(6,A)

#define RELOAD1_PWM 			PWM_PIN(6,B)
#define RELOAD2_PWM 			PWM_PIN(6,C)

#endif
/*******************************************************************/


/********************************************************/
//  TUTrobo
//
//  概要
//      マイコンの設定 プロトタイプ宣言
/********************************************************/
void MTU2_init(void);	//MTU2のスタンバイ解除
void setup(void); 		//初期設定
void debug(void);
#endif // __SETUP_H__