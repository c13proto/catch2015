/********************************************************/
//
//  概要
//      CMT関連
//  作成者
//		K.ishimori @ TUTrobo
//
/********************************************************/

#include "../setup.h"		//マイコンの設定

/********************************************************/
//  名前      
//		cmt_init
//  概要
// 		CMT関数
//  機能説明
//		CMTの初期設定　(クロック設定が25MHzにしてある)
//  パラメタ説明
//		なし
//  戻り値
//		なし
//	注意事項
//		タイマカウントは
//		TASK_START()およびTASK_END()でコントロールしている
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void cmt_init(void) 
{

	STB.CR4.BIT._CMT = 0;				// スタンバイ解除
	
	//割り込みタイマ
	//発生の表示、割り込み、およびカウンタ入力クロックの設定 -----
	CMT0.CMCSR.BIT.CMIE= 1;				//割込許可
	CMT0.CMCSR.BIT.CKS = 1;				//クロック選択	 0：Pφ/8		1：Pφ/32	 2：Pφ/128 	3：Pφ/512	
	CMT0.CMCSR.BIT.CMF = 0;				//コンペアマッチフラグクリア
	CMT0.CMCNT = 0;          			//カウンタクリア
	CMT.CMSTR.BIT.STR0 = 0;				//カウント停止
	
	//コンペアマッチするまでの期間を設定 -----
//	CMT0.CMCOR = 7812;					// 1  [msec] 25000000(Hz)/32 = 781250(≒1sec)
	CMT0.CMCOR = 1;						// 1  [msec] 25000000(Hz)/32 = 781250(≒1sec)
//	CMT0.CMCOR = 78;					// 1  [msec] 25000000(Hz)/32 = 781250(≒1sec)
//	CMT0.CMCOR = 781;					// 1  [msec] 25000000(Hz)/32 = 781250(≒1sec)
//	CMT0.CMCOR = 781*2;					// 1  [msec] 25000000(Hz)/32 = 781250(≒1sec)
	//CMT1の割り込みレベルを設定
	INTC.IPRJ.BIT._CMT0= 13;     	  	// 割り込みレベル設定(CMT1)0〜15 0:最低 15:最高
	
	//割り込みタイマ
	//発生の表示、割り込み、およびカウンタ入力クロックの設定 -----
	CMT1.CMCSR.BIT.CMIE= 1;				//割込許可
	CMT1.CMCSR.BIT.CKS = 1;				//クロック選択	 0：Pφ/8		1：Pφ/32	 2：Pφ/128 	3：Pφ/512	
	CMT1.CMCSR.BIT.CMF = 0;				//コンペアマッチフラグクリア
	CMT1.CMCNT = 0;          			//カウンタクリア
	CMT.CMSTR.BIT.STR1 = 0;				//カウント停止
	
	//コンペアマッチするまでの期間を設定 -----
	CMT1.CMCOR = 7812;					// 1  [msec] 25000000(Hz)/32 = 781250(≒1sec)
	
	//CMT1の割り込みレベルを設定
	INTC.IPRJ.BIT._CMT1= 13;     	  	// 割り込みレベル設定(CMT1)0〜15 0:最低 15:最高

}

/********************************************************/
//  名前      
//		delay_ms
//  概要
// 		CMT関数
//  機能説明
//		遅延関数
//  パラメタ説明
//		number		割り込み時間×引数＝遅延時間
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
void delay_ms(int number)
{
	long value;
	
	CMT.CMSTR.BIT.STR0 = 1;				//カウント開始
	
	for( value = 0; value < number; value ++ )
	{
		while( !CMT0.CMCSR.BIT.CMF ) ;	//CMCNT=CMCORフラグ待ち
		CMT0.CMCSR.BIT.CMF = 0;			//フラグクリア
	}
	
	CMT.CMSTR.BIT.STR0 = 0;				//カウント停止
}

/********************************************************/
//  名前      
//		delay
//  概要
// 		TIMER関数
//  機能説明
//		遅延関数
//  パラメタ説明
//		number		引数1×引数2＝遅延時間
//  戻り値
//		なし
//  作成者
//		K.Ishimori @ TUTrobo
//
/********************************************************/
//void delay_ms(int number1, int number2)
//{
//	loop
//}