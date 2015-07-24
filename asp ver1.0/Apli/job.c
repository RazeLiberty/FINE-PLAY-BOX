/* 
 *  TOPPERS/ASP ワークプログラム
 *	UART0送受信サンプルプログラム
 *	＜仕様＞
 *	PCとマイコンボードのUART0コネクタをUSB-シリアル変換ケーブルで接続し
 *	PC側のターミナルソフトとのシリアル通信をテストする。
 *	＜Terminal Soft(PC側)の設定＞
 *		設定  	シリアルポート
 *				ボーレート：３８４００
 *				8ビット,ノンパリティ,1ストップビット
 *  2014/2/13 
 *	
 *	
 *	motorLCD.cから使いたい関数をjob_motorLCD.hでプロトタイプ宣言することでjob.cで使えるように変更。
 *	2014/2/17 by T.K
 *
 *	InitDevice()の中にInit_IO()、Init_TIMER()を追加。
 *	mainにini_dtq(UART_DTQ)を追加。
 *	job_motorLCD.hにmotor(int)を追加。
 *	変数Motor_Power、maskを追加。
 *	UART0から受信したデータをMotor_Powerへ。
 *	その後マスク処理をしてそれぞれのMotorの出力へ。
 *	2014/2/18 by T.K
 *
 *	
 */

#include <itron.h>
#include <kernel.h>
#include "kernel_cfg.h"
#include "arch/m16c_nc30/m16C62p.h"
#include "job.h"
#include "Driver/device.h"

//定数定義
#define	CPUCLOCK 24320		/*CPU内部クロック 6MHz x 4 = 24000KHz(源6.08MHz 補正値)*/
#define	TIMERINTERVAL 10	/*セットしたいタイマインターバル(ms)*/

/* 関数プロトタイプ宣言 */
int8_t ReceiveUART(void);
void SendUART(uint8_t c);

////////////////// タスク ///////////////////////
/*
 *  Initial and Idleタスク
 *  初期化と初期起動、完了後アイドリング
 */
void main(intptr_t exinf)
{
	//char title[]="FINE PLAY BOX";
	
	/* 共用変数の初期化 */

	/* IOの初期化 */
	InitDevice();			//UART0の初期化はuart.cのInitUART0()で行う			uart.cのみ呼び込む
							//通信速度を変える場合はU0_BRGの値を変更する
							
	/*1行タイトル表示*/
	//SetCursol(0, 1);
	//DisplayLCD(title);
	
	/*オブジェクトの初期化*/
	ini_dtq(UART_DTQ);		//データキューを初期化
	
	/* 初期起動タスクの起動と周期起動タスク開始 */
	dis_dsp();				//ディスパッチ停止
	  //タスク起動
	  act_tsk(FUNC1_TASK);		//UART0送受信テスト
	  //act_tsk(FUNC2_TASK);		//無線コントローラテスト
	  ena_int(TINTNO_S0RACK);	//UART0受信割込み許可
	  ena_int(TINTNO_S0TNACK);	//UART0送信割込み許可
	
	ena_dsp();				//ディスパッチ開始

	while(FOREVER);			//アイドリング
}

/* ID:FUNC1_TASK		priority=mid
*	UART0送受信テストタスク
*	PCとマイコンボードのUART0コネクタをUSB-シリアル変換ケーブルで接続し
*	PC側のターミナルソフトとの送受信をテストする。
 */
void func1_task(intptr_t exinf)
{
	int8_t Motor_Power;
	int8_t c;
	
	while(FOREVER){
		
		//SendUART('A');		//文字'A'を送信する→PC側ターミナルソフトに文字が表示される
		
		Motor_Power = ReceiveUART();	//PC側Kinectからのデータを受信してモータに反映させる
		
		// モータパラメータをここで更新
		
		
		Motor1( Motor_Power );
		Motor2( Motor_Power );
		Motor3( Motor_Power );
		Motor4( Motor_Power );
		
		//c = ReceiveUART();	//PC側ターミナルソフトからのデータを受信してLCDに表示する
		c = Motor_Power;
		if((c & 0x80) == 0){
			SetCursol(0,5);
			DisplayLCD1C(0x30);
		} else {
			SetCursol(0,5);
			DisplayLCD1C(0x31);
		}
		if((c & 0x08) == 0){
			SetCursol(0,7);
			DisplayLCD1C(0x30);
		} else {
			SetCursol(0,7);
			DisplayLCD1C(0x31);
		}
	}

}


////////////////// 関数 ///////////////////////
/* 
* UART0受信関数  
* 機能	:１バイトのデータを受信する。
* 戻り値:受信した1バイトのデータ
* 注意	:サービスコールを使用するため、送信するタスクから呼び出す。
*		:データを受信するまで待つ
*/
int8_t ReceiveUART()
{
	intptr_t p;
	
	rcv_dtq(UART_DTQ, &p);	//UART_DTQからのデータ待ち

	return (int8_t)p;		//8ビット
}

/* 
* UART0送信関数  
* 機能	:１バイトのデータを送信する。
* 引数	:送信用1バイトのデータ
* 注意	:サービスコールを使用するため、送信するタスクから呼び出す
*		:データを送信完了するまで待つ
*/
void SendUART(uint8_t c)
{
	FLGPTN flgptn;
	
	u0tb = c;									//UART0送信
	wai_flg(UART_FLG,0x0001,TWF_ORW,&flgptn);	//送信完了待ち
}

////////////////// ハンドラ ///////////////////////
/*
 *  UART受信割込みハンドラ（OS依存）
 *  UART受信割込みで受信データを読み込み、DTQにデータを送る。
 */
 void UART_receive_handler(intptr_t exinf)
 {
	uint8_t c;
	
	c = u0rb;					//UART0受信レジスタを読み込む //Kinectからデータ受信
	ipsnd_dtq(UART_DTQ, c);		//UART用DTQへデータを送る
	c = 0;
 }
 
 /*
 *  UART送信完了割込みハンドラ（OS依存）
 *  １バイトデータを送信後に発生する割込みで送信完了を送信タスクに通知する。
 */
void UART_send_handler(intptr_t exinf)
{
 	iset_flg(UART_FLG, 0x0001);	//送信完了イベントフラグをセット
}

/************* End *************/