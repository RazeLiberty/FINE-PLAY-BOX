/************************************************************************/
/*  PROGRAM     :全方向移動車サンプル									*/
/*  DATE        :2014.01.10			                                    */
/*  DESCRIPTION :モータx4 エンコーダx4 LCD SWx2 LEDx2                   */
/*  CPU GROUP   :M16C/62P(Original I/O Board)                           */
/*  NOTE		:                       	    						*/
/*  PROGRAMMER	:														*/
/************************************************************************/

typedef unsigned char uint8_t;
#include "sfr62p.h"

//定数定義
#define	CPUCLOCK 24320		/*CPU内部クロック 6MHz x 4 = 24000KHz(源6.08MHz 補正値)*/
#define	TIMERINTERVAL 10	/*セットしたいタイマインターバル(ms)*/

#define M1_IN1 p7_3
#define M1_POW ta1
#define M2_IN1 p7_5
#define M2_POW ta2
#define M3_IN1 p7_7
#define M3_POW ta3
#define M4_IN1 p8_1
#define M4_POW ta4

#define LED_RED p1_0
#define LED_GRE p1_1

// エンコーダ
#define E1_INA p8_2
#define E1_INB p8_6
#define E2_INA p8_3
#define E2_INB p8_7
#define E3_INA p8_4
#define E3_INB p1_3
#define E4_INA p1_5
#define E4_INB p1_4

#define PORTIN		0			/*	ポート方向レジスタを入力に設定する為のデータ	*/
#define	PORTOUT		1			/*	ポート方向レジスタを出力に設定する為のデータ	*/
#define	LCDRS		p6_0		/*	RS端子					*/
#define	LCDRW		p1_2		/*	RW端子					*/
#define	LCDE		p6_1		/*	E端子					*/
#define	HIGH		1			/*	端子出力“H”			*/
#define	LOW			0			/*	端子出力“L”			*/
#define	LCD_COMMAND	0			/*	RS-command指定			*/
#define	LCD_DATA	1			/*	RS-data指定				*/
#define	BUSY		1			/*	LCD書き込みbuzy			*/
#define	NOBUSY		0			/*	LCD書き込みOK			*/

//関数のプロトタイプ宣言
void main2(void);
void Init_IO(void);
void Init_TIMER(void);
void TA0_handler(void);
void TB2_handler(void);
void INT0_handler(void);
void INT1_handler(void);
void INT2_handler(void);
void INT3_handler(void);

void Motor1(uint8_t);
void Motor2(uint8_t);
void Motor3(uint8_t);
void Motor4(uint8_t);

// LCD
void InitLCD(void);						/*	LCD初期設定				*/
void SetCursol(int x, int y);			/*  表示位置をセット		*/
void DisplayLCD1C(char c);				/*  現位置に1文字表示		*/
void DisplayLCD(char * row);			/*　LCD文字列表示			*/
void SetCGRAM(void);					/*　カスタム文字をLCDのRAMに登録*/

void lcdwriteinit(unsigned char);		/*	LCD初期設定コマンド出力	*/
void lcdwrite1command(unsigned char);	/*	LCD1コマンド出力		*/
void lcdwrite1data(unsigned char);		/*	LCD1データ出力			*/
void wait1(void);						/*	0.1msウエイト			*/
void wait2(void);						/*	4.1msウエイト			*/
void wait3(void);						/*	15msウエイト			*/
unsigned char lcdbusycheck( void );		/*	LCDビジーチェック		*/

long enc1_count = 0;
long enc2_count = 0;
long enc3_count = 0;
long enc4_count = 0;


/*************************************************
 * main　
 * メイン処理
 *************************************************/
void main2(void)
{	
		char mess[]="xxxx";
			
	Init_IO();		//IOポートの初期化
		InitLCD();		//LCD初期設定(LCDの初期化シーケンスを実行)
	Init_TIMER();	//タイマの初期化

	//ei();			// 割り込み許可(アセンブラルーチン呼出し)
	

	//LCDのコマンド、データ書込みをテスト
	while(BUSY == lcdbusycheck());	//LCDビジーチェック
	lcdwrite1command ( 0b10001111 );//LCDの表示アドレスをセット
	while(BUSY == lcdbusycheck());	//LCDビジーチェック
	lcdwrite1data( '!' );			//LCDに文字データを書き込む
	
	/*1行表示*/
	SetCursol(0, 5);
	DisplayLCD(mess);
	
	while(1){	//無限ループ
		SetCursol(0, 5);
		mess[0] = enc4_count % 10 + 0x30;
		DisplayLCD(mess);
		/* メイン処理 */
		wait3();
	}
}

/*************************************************
 * Init_IO　　
 * IOポートの初期化
 *************************************************/
void Init_IO(void)
{
	/*==== ボード上LED ====*/
	p0_0 = 1;		// LED消灯	
	pd0_0 = 1;		// ポートを出力に設定
	
	p10_2 = 1;
	pd10_2 = 1;
	
	p10_3 = 1;
	pd10_3 = 1;
	
	/*==== モータ 1 ====*/
	M1_IN1 = 0;		// モータ1:IN2 LOW
	pd7_3 = 1;		// モータ1:IN2を出力に設定 

	/*==== モータ 2 ====*/
	M2_IN1 = 0;		// モータ2:IN2 LOW
	pd7_5 = 1;		// モータ2:IN2を出力に設定 

	/*==== モータ 3 ====*/
	M3_IN1 = 0;		// モータ3:IN2 LOW
	pd7_7 = 1;		// モータ3:IN2を出力に設定 

	/*==== モータ 4 ====*/
	M4_IN1 = 0;		// モータ3:IN2 LOW
	pd8_1 = 1;		// モータ3:IN2を出力に設定 

#if 0
	/*==== エンコーダ 1 ====*/
	int0ic = 0x07;
	ifsr0 = 1;
	pd8_2 = 0;
	pd8_6 = 0;

	/*==== エンコーダ 2 ====*/
	int1ic = 0x07;
	ifsr1 = 1;
	pd8_3 = 0;
	pd8_7 = 0;

	/*==== エンコーダ 3 ====*/
	int2ic = 0x07;
	ifsr2 = 1;
	pd8_4 = 0;
	pd1_3 = 0;

	/*==== エンコーダ 4 ====*/
	int3ic = 0x07;
	ifsr3 = 1;
	pd1_5 = 0;
	pd1_4 = 0;

#endif

	/*==== LED 赤緑 ====*/
	pd1_0 = 1;
	pd1_1 = 1;
	LED_RED = 1;
	LED_GRE = 1;
}

/*************************************************
 * Init_TIMER　　
 * タイマの初期化
 *************************************************/
void Init_TIMER(void)
{
	udf = 0x00;
	trgsr = 0x55;
	/* タイマ TA0:メインタイマ */
	ta0mr = 0x84;								/* タイマモードセット		*/
	ta0 = (CPUCLOCK / 32 * TIMERINTERVAL) - 1;	/* タイマカウントセット10ms */
	ta0ic = 0x01;								/* 割込み優先レベル IPL=1 (0は割込み不可)*/
	ta0s = 1;									/* タイマ0開始 				*/

	/* モータ 1:個別PWM */
	ta1mr = 0x84;
	ta1 = 0;// 起動後は停止 
	ta1s = 1;									/* タイマA1開始 			*/

	/* モータ 2:個別PWM */
	ta2mr = 0x84;
	ta2 = 0;// 起動後は停止 
	ta2s = 1;									/* タイマA1開始 			*/

	/* モータ 3:個別PWM */
	ta3mr = 0x84;
	ta3 = 0;// 起動後は停止 
	ta3s = 1;									/* タイマA1開始 			*/

	/* モータ 4:個別PWM */
	ta4mr = 0x84;
	ta4 = 0;// 起動後は停止 
	ta4s = 1;									/* タイマA1開始 			*/

	/* モータ 1-4:全体周期 */
	tb2mr = 0x84;								/* タイマモードセット		*/
	tb2 = (CPUCLOCK / 32 * TIMERINTERVAL) - 1;	/* タイマカウントセット10ms	*/
	tb2ic = 0x02;								/* 割込み優先レベル IPL=2 (0は割込み不可)*/
	tb2s = 1;									/* タイマB2開始 			*/

}

/*************************************************
 * INT0_handler : ENCODER1割り込み
 *************************************************/
#pragma INTERRUPT INT0_handler

void INT0_handler(void)
{
	if(E1_INA == 0){
		if(E1_INB == 0){
			enc1_count++;
		} else {
			enc1_count--;
		}
	} else {
		if(E1_INB == 1){
			enc1_count++;
		} else {
			enc1_count--;
		}
	}
}

/*************************************************
 * INT1_handler : ENCODER2割り込み
 *************************************************/
#pragma INTERRUPT INT1_handler

void INT1_handler(void)
{
	if(E2_INA == 0){
		if(E2_INB == 0){
			enc2_count++;
		} else {
			enc2_count--;
		}
	} else {
		if(E2_INB == 1){
			enc2_count++;
		} else {
			enc2_count--;
		}
	}
}

/*************************************************
 * INT2_handler : ENCODER3割り込み
 *************************************************/
#pragma INTERRUPT INT2_handler

void INT2_handler(void)
{
	if(E3_INA == 0){
		if(E3_INB == 0){
			enc3_count++;
		} else {
			enc3_count--;
		}
	} else {
		if(E3_INB == 1){
			enc3_count++;
		} else {
			enc3_count--;
		}
	}
}


/*************************************************
 * INT3_handler : ENCODER4割り込み
 *************************************************/
#pragma INTERRUPT INT3_handler

void INT3_handler(void)
{
	if(E4_INA == 0){
		if(E4_INB == 0){
			enc4_count++;
		} else {
			enc4_count--;
		}
	} else {
		if(E4_INB == 1){
			enc4_count++;
		} else {
			enc4_count--;
		}
	}
}

/*************************************************
 * TA0_handler : 10msタイマ割り込み
 *************************************************/
#pragma INTERRUPT TA0_handler

void TA0_handler(void)
{
	static int cnt = 100;	//割込みカウント　初期値100(1s)
	static char F_alt = 0;	//交互フラグ
	
	if(!cnt--){				//割込みを100回カウントする毎にLED点灯/消灯
		if(F_alt^=1){		//フラグ切替え
	//	p0_0 = 0;		//IOボード LED1点灯
		}
		else{
	//	p0_0 = 1;		//IOボード LED1消灯
		}
		cnt=100;			//カウントを再設定
	}
}

/*************************************************
 * TB2_handler : 100Hz周期　
 *************************************************/
#pragma INTERRUPT TB2_handler

void TB2_handler(void)
{
	// モータパラメータをここで更新
	Motor1(40);
	Motor2(40);
	Motor3(40);
	Motor4(40);
}

void Motor1(uint8_t power)
{
	uint8_t mask = power >> 4;
	if(mask == 0)
	{
		M1_IN1 = 0;
		M1_POW = 0;
	}
	else
	{
		if((mask & 0x08) == 0)
		{
			M1_IN1 = 0;	// HIの時回転
			M1_POW = (mask & 0x07) *10 * 7 + 59;
			// power * 7 + 59
			// 上記power40の場合　40 * 7 + 59 = 339
		}
		else
		{
			M1_IN1 = 1; // LOWの時回転
			M1_POW = (0x08 - (mask & 0x07)) *10 * 7 + 59;
		}
	}
}

void Motor2(uint8_t power)
{
	uint8_t mask = power & 0x0F;
	if(mask == 0)
	{
		M2_IN1 = 0;
		M2_POW = 0;
	}
	else
	{
		if((mask & 0x08) == 0)
		{
			M2_IN1 = 0;	// HIの時回転
			M2_POW = (mask & 0x07) *10 * 7 + 59;
			// power * 7 + 59
			// 上記power40の場合　40 * 7 + 59 = 339
		}
		else
		{
			M2_IN1 = 1; // LOWの時回転
			M2_POW = (0x08 - (mask & 0x07)) *10 * 7 + 59;
		}
	}
}

void Motor3(uint8_t power)
{
	uint8_t mask = power & 0x0F;
	if(mask == 0)
	{
		M3_IN1 = 0;
		M3_POW = 0;
	}
	else
	{
		if((mask & 0x08) == 0)
		{
			M3_IN1 = 0;	// HIの時回転
			M3_POW = (mask & 0x07) *10 * 7 + 59;
			// power * 7 + 59
			// 上記power40の場合　40 * 7 + 59 = 339
		}
		else
		{
			M3_IN1 = 1; // LOWの時回転
			M3_POW = (0x08 - (mask & 0x07)) *10 * 7 + 59;
		}
	}
}

void Motor4(uint8_t power)
{
	uint8_t mask = power >> 4;
	if(mask == 0)
	{
		M4_IN1 = 0;
		M4_POW = 0;
	}
	else
	{
		if((mask & 0x08) == 0)
		{
			M4_IN1 = 0;	// HIの時回転
			M4_POW = (mask & 0x07) *10 * 7 + 59;
			// power * 7 + 59
			// 上記power40の場合　40 * 7 + 59 = 339
		}
		else
		{
			M4_IN1 = 1; // LOWの時回転
			M4_POW = (0x08 - (mask & 0x07)) *10 * 7 + 59;
		}
	}
}

/*********************************************************************************************************
=============================================以下解説=====================================================
(mask & 0x07) *10 * 7 + 59;				// 正転
(0x08 - (mask & 0x07)) *10 * 7 + 59;	// 逆転
について

正転時
	0x07でANDを取ると最高値で7にしかならず数が少ないので先ず10倍
	それを(*7+59)これはオマジナイ
	
逆転時
	0x07でANDで10倍までは正転時と同じ
	0 <= power < 100 ( 0 <= power <= 99)
	(power+100) * 7 + 59;		//	逆転
		これの+100に関する解説
			powerが負の数で送られてきた場合、LOW時にモータが
回転する処理になる。
			しかしM1_POWは"HI"にする時間を設定する為、-40の
出力を出したければ(-40+100)を行い
			M1_POWの値を60にする必要がある。
			
	今回のプログラムでは負数が直接送られてくることは無いので
		0 <= power <= 7 という条件より
			(0x08 - (power&0x07)) * 10 * 7 + 59;
	以上のような式になる。
*********************************************************************************************************/

/*------------------------------------------------------------*/
/* 関数名	:SetCursol(タテ(上段:0,下段:1), ヨコ(0 - 15)	  */
/* 機能		:表示位置をセットする						      */
/*------------------------------------------------------------*/
void SetCursol(int x, int y)
{
	while(BUSY == lcdbusycheck());	/*	LCDビジーチェック	　*/
	lcdwrite1command ( x * 0x40 + 0x80 + y );/* アドレスセット */
}

/*------------------------------------------------------------*/
/* 関数名	:DisplayLCD1C(文字コード)						　*/
/* 機能		:SetCursolで指定した位置に1文字を表示		      */
/*------------------------------------------------------------*/
void DisplayLCD1C(char c)
{
	while(BUSY == lcdbusycheck());	/*	LCDビジーチェック	*/
	lcdwrite1data( c );
}

/*------------------------------------------------------------*/
/* 関数名	:DisplayLCD(文字列ポインタ)					　*/
/* 機能		:SetCursolで指定した位置から文字列表示		      */
/*------------------------------------------------------------*/
void DisplayLCD(char * row)
{
	char c;

	while( (c=*row++) != '\0' ){		/* \0文字繰り返し 	*/
		while(BUSY == lcdbusycheck());	/*	LCDビジーチェック*/
		lcdwrite1data( c );				/*	文字出力		*/
	}
}

//------------------------------------------------------------*/
// 関数名	:SetCGRAM()				　
// 機能		:カスタム文字をLCDのRAMに登録する（8文字まで登録可）
//           カスタム文字は文字コード0x00～0x07に１文字づつ登録できる。
//           登録する文字コードをセットし、5ドット×8ラインに文字パターンを書き込む。
//------------------------------------------------------------*/
void SetCGRAM(void)
{
	/*例：CGRAMコード0x01に'℃'を登録する*/
	/*①CGRAMアドレスセット　CGRAMコード0x01を指定*/
	while(BUSY == lcdbusycheck());	/*LCDビジーチェック*/
	lcdwrite1command ( 0b01001000 );/*CGRAMアドレスセット*/
                      /* |||||+++---- 3ビット ラインアドレス(0-7)*/
                      /* ||+++------- 3ビット CGRAMコード(0-7)*/
                      /* ++---------- 01固定 CGRAM指定*/

	/*②CGRAMデータ書込み(5ドット×8ライン　書込み時自動ライン増加）*/
	while(BUSY == lcdbusycheck());	/*1段目(最上段) */
	lcdwrite1data( 0b00001000);		/*下位5ビットで指定。上位3ビットは000。1:黒点, 0:白点*/
	while(BUSY == lcdbusycheck());	/*2段目*/
	lcdwrite1data( 0b00010100);	
	while(BUSY == lcdbusycheck());	/*3段目*/
	lcdwrite1data( 0b00001000);	
	while(BUSY == lcdbusycheck());	/*4段目*/
	lcdwrite1data( 0b00000110);	
	while(BUSY == lcdbusycheck());	/*5段目*/
	lcdwrite1data( 0b00001001);	
	while(BUSY == lcdbusycheck());	/*6段目*/
	lcdwrite1data( 0b00001000);	
	while(BUSY == lcdbusycheck());	/*7段目*/
	lcdwrite1data( 0b00001001);	
	while(BUSY == lcdbusycheck());	/*8段目(最下段) アンダーラインカーソルを使う場合は1行空ける*/
	lcdwrite1data( 0b00000110);	
	
	/*以下、登録する文字をセットする（最大8文字）*/
}

/*----------------------------------------------------------*/
/* 関数名	:InitLCD(）										*/
/* 機能		:LCD初期設定								    */
/*----------------------------------------------------------*/
void InitLCD(void)
{
	wait3();						/*	15msウエイト				*/
	lcdwriteinit( 0x03 );			/*	LCDファンクションセット		*/
	wait2();						/*	4.1msウエイト				*/
	lcdwriteinit( 0x03 );			/*	LCDファンクションセット		*/
	wait1();						/*	0.1msウエイト				*/
	lcdwriteinit( 0x03 );			/*	LCDファンクションセット		*/
	
	wait1();						/*	0.1msウエイト 				*/
	lcdwriteinit( 0x03 );			/*	LCDファンクションセット		*/
	
	wait1();
	lcdwriteinit( 0x02 );			/*	LCDデータを4ビット長に設定	*/
	wait1();
	lcdwrite1command(0x28);			/*	4bit､2行文､5×7ドットに設定	*/
	wait1();

	/* 	ここまでで4ビット×2回のデータ転送ができるように設定されたので
	この後はビジーチェックをしてからデータ転送を行なう。 */

	while(BUSY == lcdbusycheck())	/*	LCDビジーチェック		*/
	;
	lcdwrite1command(0x08);			/*	表示オフ				*/

	while(BUSY == lcdbusycheck())	/*	LCDビジーチェック		*/
	;
	lcdwrite1command(0x01);			/*	表示クリア				*/

	while(BUSY == lcdbusycheck())	/*	LCDビジーチェック		*/
	;
	lcdwrite1command(0x06);			/*	エントリーモード､インクリメント*/

	while(BUSY == lcdbusycheck())	/*	LCDビジーチェック		*/
	;
	lcdwrite1command(0x0c);			/*	表示オン､カーソルオフ	*/
}

/*----------------------------------------------------------*/
/* 関数名	:lcdwriteinit()									*/
/* 機能		:LCD初期設定コマンドセット					    */
/*----------------------------------------------------------*/
void lcdwriteinit( unsigned char command )
{
	;
	/*===初期値セット===*/
	p6_0 = 0x0;		/*	RS－0(コマンド指定)	*/
	p6_1 = 0x0;		/*	E－0				*/
	p1_2 = 0x0;		/*	RW－0(W指定)		*/

	/*===ポート方向レジスタを出力に設定===*/
	pd6 |= 0x03;
	pd1_2 = 1;

	prc2 = 1;		/*	pd9への書き込み許可	*/
	pd9 = 0xFF;

	command &= 0x0f;	/*	コントロールデータセット(引数から）RW－0(W指定) RS－0(コマンド指定）E－0 */
	p9 = command;		/*	コントロールデータ出力	*/
	LCDE = HIGH;		/*	E－１					*/
#pragma ASM				/*	アセンブラ表記			*/
	NOP					/*	時間調整の為のNOP 		*/
	NOP
	NOP
	NOP
#pragma ENDASM			/*	アセンブラ表記終了		*/
	LCDE = LOW;			/*	E－0					*/
}
/*----------------------------------------------------------*/
/* 関数名	:lcdwrite1command(）							*/
/* 機能		:LCDコマンド出力							    */
/*----------------------------------------------------------*/
void lcdwrite1command( unsigned char command )
{
	unsigned char outcommand;

	/*===初期値セット===*/
	p6_0 = 0x0;		/*	RS－0(コマンド指定)	*/
	p6_1 = 0x0;		/*	E－0				*/
	p1_2 = 0x0;		/*	RW－0(W指定)		*/

	/*===ポート方向レジスタを出力に設定===*/
	pd6 |= 0x03;
	pd1_2 = 1;

	prc2 = 1;		/*	pd9への書き込み許可	*/
	pd9 = 0xFF;

	outcommand = command>>4;	/*	上位4ビットを下位4ビットへ	*/
	outcommand &= 0x0f;			/*	マスク処理					*/
	p9 = outcommand;			/*	1コマンドデータ上位4ビットを出力　RW－0(W指定) RS－0(コマンド指定）E－0 */
	LCDE = HIGH;				/*	E－１						*/
#pragma ASM						/*	アセンブラ表記				*/
	NOP							/*	時間調整の為のNOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM					/*	アセンブラ表記終了			*/
	LCDE = LOW;					/*	E－0						*/
	outcommand = command&0x0f;	/*	コマンドデータの下位4ビット抽出(上位4ビットマスク)	*/
	p9 = outcommand;			/*	コマンドデータ下位4ビットを出力						*/
	LCDE = HIGH;				/*	E－１						*/
#pragma ASM						/*	アセンブラ表記				*/
	NOP							/*	時間調整の為のNOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM					/*	アセンブラ表記終了			*/
	LCDE = LOW;					/*	E－0						*/

}
/*----------------------------------------------------------*/
/* 関数名	:lcdwrite1data(）								*/
/* 機能		:LCDデータ出力								    */
/*----------------------------------------------------------*/
void	lcdwrite1data( unsigned char data )
{
	unsigned char lcddata;

	/*===初期値セット===*/
	p6_0 = 0x0;		/*	RS－0(コマンド指定)	*/
	p6_1 = 0x0;		/*	E－0				*/
	p1_2 = 0x0;		/*	RW－0(W指定)		*/

	/*===ポート方向レジスタを出力に設定===*/
	pd6 |= 0x03;
	pd1_2 = 1;

	prc2 = 1;		/*	pd9への書き込み許可	*/
	pd9 = 0xFF;

	lcddata = data>>4;		/*	LCDデータ上位4ビットを下位4ビットへ	*/
	lcddata &= 0x0f;		/*	マスク処理					*/

	p9 = lcddata;			/*	LCDデータ上位4ビットを出力	*/
	LCDRS = LCD_DATA;		/*	RS－1(データ指定）			*/
	LCDE = HIGH;			/*	E－１						*/
#pragma ASM					/*	アセンブラ表記				*/
	NOP						/*	時間調整の為のNOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	アセンブラ表記終了			*/
	LCDE = LOW;				/*	E－0						*/
	lcddata =data & 0x0f;	/*	LCDデータの下位4ビット抽出(上位4ビットマスク)	*/
	p9 = lcddata;			/*	LCDデータ下位4ビットを出力	*/
	LCDRS = LCD_DATA;		/*	RS－1(データ指定）			*/
	LCDE = HIGH;			/*	E－1						*/
#pragma ASM					/*	アセンブラ表記				*/
	NOP						/*	時間調整の為のNOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	アセンブラ表記終了	*/
	LCDE = LOW;				/*	E－0				*/
}

/*----------------------------------------------------------*/
/* 関数名	:wait1()										*/
/* 機能		:0.1msウエイト								    */
/*----------------------------------------------------------*/
void wait1(void)
{			/*	約0.1msのウエイト	*/
#pragma ASM					/*	アセンブラ表記		*/
	MOV.W 	#0C8H,A0		/*	カウンタ初期値セット*/
LOOP1:
	NOP
	NOP
	NOP
	DEC.W	A0
	JNZ	LOOP1				/*	ループ終了？		*/
#pragma ENDASM				/*	アセンブラ表記終了	*/
}
/*----------------------------------------------------------*/
/* 関数名	:wait2()										*/
/* 機能		:4.1msウエイト								    */
/*----------------------------------------------------------*/
void wait2(void)
{			/*	約4.1msのウエイト 	*/
#pragma ASM					/*	アセンブラ表記		*/
	MOV.W 	#2007H,A0		/*	カウンタ初期値セット*/
LOOP2:
	NOP
	NOP
	NOP
	DEC.W	A0
	JNZ	LOOP2				/*	ループ終了？		*/
#pragma ENDASM				/*	アセンブラ表記終了	*/
}
/*----------------------------------------------------------*/
/* 関数名	:wait3()										*/
/* 機能		:15msウエイト									*/
/*----------------------------------------------------------*/
void wait3(void)
{			/*	約15msのウエイト	*/
#pragma ASM					/*	アセンブラ表記		*/
	MOV.W 	#7530H,A0		/*	カウンタ初期値セット*/
LOOP3:
	NOP
	NOP
	NOP
	DEC.W	A0
	JNZ	LOOP3				/*	ループ終了？		*/
#pragma ENDASM				/*	アセンブラ表記終了	*/
}
/*----------------------------------------------------------*/
/* 関数名	:lcdbusycheck()									*/
/* 機能		:LCDビジーチェック							    */
/*----------------------------------------------------------*/
unsigned char lcdbusycheck( void )
{
	unsigned char command_high,command_low,b_data;

	/*===初期値セット===*/
	p6_0 = 0x0;		/*	RS－0(コマンド指定)	*/
	p6_1 = 0x0;		/*	E－0				*/
	p1_2 = 0x0;		/*	RW－0(W指定)		*/
	
	/*===ポート方向レジスタを出力に設定===*/
	pd6 |= 0x03;
	pd1_2 = 1;

	prc2 = 1;		/*	pd9への書き込み許可	*/
	pd9 = 0x00;

	LCDRW = HIGH;	/*	RW－1(R指定)		*/

	LCDE = HIGH;			/*	E－1				*/
#pragma ASM					/*	アセンブラ表記		*/
	NOP						/*	時間調整の為のNOP	*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	アセンブラ表記終了	*/
	command_high = p9;		/*	コマンド上位4ビット読み込み	*/
	LCDE = LOW;				/*	E－0				*/

	command_high <<=4;		/*	下位4ビットを上位へ	*/
	command_high &= 0xf0;	/*	上位4ビット抽出(下位4ビットマスク処理)	*/

	LCDE = HIGH;			/*	E－1				*/
#pragma ASM					/*	アセンブラ表記		*/
	NOP						/*	時間調整の為のNOP	*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	アセンブラ表記終了	*/
	command_low = p9;		/*	コマンド下位4ビット読み込み	*/
	LCDE = LOW;				/*	E－0				*/
	command_low &= 0x0f;	/*	下位4ビット抽出(上位4ビットマスク処理)	*/
	b_data = command_high|command_low;	/*	2つの4ビットコマンドデータを8ビットにまとめる	*/
	b_data &= 0x80;			/*	ビット7のマスク処理	*/
	if(b_data == 0)
		b_data = NOBUSY;	/*	ビット7が0ならLCD書き込みokを返す		*/
	else
		b_data = BUSY;		/*	ビット7が1ならLCD書き込みbuzyを返す		*/
		
	return(b_data);
}