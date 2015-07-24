//#######    LCD driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU					#######
//#######             version 1.0					#######
//#######           	By KH				        #######

#include	"device.h"

/* プロトタイプ宣言 */
void lcd_init(void);					/*	LCD初期設定				*/
void lcdwriteinit(unsigned char);		/*	LCD初期設定コマンド出力	*/
void lcdwrite1command(unsigned char);	/*	LCD1コマンド出力		*/
void lcdwrite1data(unsigned char);		/*	LCD1データ出力			*/
void wait1(void);						/*	0.1msウエイト			*/
void wait2(void);						/*	4.1msウエイト			*/
void wait3(void);						/*	15msウエイト			*/
unsigned char lcdbusycheck( void );		/*	LCDビジーチェック		*/
void BitSetP9(char command);			/*  P9下位4ビットを個別にセット*/


#define PORTIN		0			/*	ポート方向レジスタを入力に設定する為のデータ	*/
#define	PORTOUT		1			/*	ポート方向レジスタを出力に設定する為のデータ	*/
#define	LCDRS		p6_0		/*	RS端子					*/
#define	LCDRW		p8_7		/*	RW端子					*/
#define	LCDE		p6_1		/*	E端子					*/
#define	HIGH		1			/*	端子出力“H”			*/
#define	LOW			0			/*	端子出力“L”			*/
#define	LCD_COMMAND	0			/*	RS-command指定			*/
#define	LCD_DATA	1			/*	RS-data指定				*/
#define	BUSY		1			/*	LCD書き込みbuzy			*/
#define	NOBUSY		0			/*	LCD書き込みOK			*/


/*----------------------------------------------------------*/
/* 関数名	:InitLCD(）									*/
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

/*------------------------------------------------------------*/
/* 関数名	:DisplayLCD1L(line, 文字列ポインタ)				  */
/* 機能		:1行分文字表示	16文字以内も可				      */
/*------------------------------------------------------------*/

void DisplayLCD1L(char data,char * row)
{
	int	i;
	data &= 0x01;
	while(BUSY == lcdbusycheck());	/*	LCDビジーチェック		*/
	lcdwrite1command ( data * 0x40 + 0x80 );/* アドレスセット */
	for(i=0;i<16;i++){				/* 16文字転送 */
		if ( *row == '\0'){
			while(BUSY == lcdbusycheck());	/*	LCDビジーチェック		*/
			lcdwrite1data( ' ' );
		}else{
			while(BUSY == lcdbusycheck());	/*	LCDビジーチェック		*/
			lcdwrite1data( *row++ );
		}
	}
}

void SetCursol(int x, int y)
{
	wait1();
	wait1();
	while(BUSY == lcdbusycheck());	/*	LCDビジーチェック		*/
	lcdwrite1command ( x * 0x40 + 0x80 + y );/* アドレスセット */
}

void DisplayLCD1C(char c)
{
	while(BUSY == lcdbusycheck());	/*	LCDビジーチェック		*/
	lcdwrite1data( c );
}

void DisplayLCD(char * row)
{
	char c;
	while( c=*row++ ){
		while(BUSY == lcdbusycheck());	/*	LCDビジーチェック		*/
		lcdwrite1data( c );
	}
}

/*----------------------------------------------------------*/
/* 関数名	:lcdwriteinit()									*/
/* 機能		:LCD初期設定コマンドセット					    */
/*----------------------------------------------------------*/
void lcdwriteinit( unsigned char command )
{
	
	/*===初期値セット===*/
	p6_0 = 0x0;		/*	RS－0(コマンド指定)	*/
	p6_1 = 0x0;		/*	E－0				*/
	p8_7 = 0x0;		/*	RW－0(W指定)		*/

	/*===ポート方向レジスタを出力に設定===*/
	pd6 |= 0x03;
	pd8_7 = 1;

	prc2 = 1;		/*	pd9への書き込み許可	*/
	pd9 = 0x0F;
//	pd9 |= 0x0F;

	command &= 0x0f;	/*	コントロールデータセット(引数から）RW－0(W指定) RS－0(コマンド指定）E－0 */
	BitSetP9(command);
//	p9 = command;		/*	コントロールデータ出力	*/
//	p9 |= command;		/*	コントロールデータ出力	*/
	
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
	p8_7 = 0x0;		/*	RW－0(W指定)		*/

	/*===ポート方向レジスタを出力に設定===*/
	pd6 |= 0x03;
	pd8_7 = 1;

	prc2 = 1;		/*	pd9への書き込み許可	*/
	pd9 = 0x0F;
//	pd9 |= 0x0F;

	outcommand = command>>4;	/*	上位4ビットを下位4ビットへ	*/
	outcommand &= 0x0f;			/*	マスク処理					*/
	BitSetP9(outcommand);
//	p9 = outcommand;			/*	1コマンドデータ上位4ビットを出力　RW－0(W指定) RS－0(コマンド指定）E－0 */
//	p9 |= outcommand;			/*	1コマンドデータ上位4ビットを出力　RW－0(W指定) RS－0(コマンド指定）E－0 */

	LCDE = HIGH;				/*	E－１						*/
#pragma ASM						/*	アセンブラ表記				*/
	NOP							/*	時間調整の為のNOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM					/*	アセンブラ表記終了			*/
	LCDE = LOW;					/*	E－0						*/
	outcommand = command&0x0f;	/*	コマンドデータの下位4ビット抽出(上位4ビットマスク)	*/
	BitSetP9(outcommand);
//	p9 = outcommand;			/*	コマンドデータ下位4ビットを出力						*/
//	p9 |= outcommand;			/*	コマンドデータ下位4ビットを出力						*/
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
	p8_7 = 0x0;		/*	RW－0(W指定)		*/

	/*===ポート方向レジスタを出力に設定===*/
	pd6 |= 0x03;
	pd8_7 = 1;

	prc2 = 1;		/*	pd9への書き込み許可	*/
	pd9 = 0x0F;
//	pd9 |= 0x0F;

	lcddata = data>>4;		/*	LCDデータ上位4ビットを下位4ビットへ	*/
	lcddata &= 0x0f;		/*	マスク処理					*/

	BitSetP9(lcddata);
//	p9 = lcddata;			/*	LCDデータ上位4ビットを出力	*/
//	p9 |= lcddata;			/*	LCDデータ下位4ビットを出力	*/
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

	BitSetP9(lcddata);
//	p9 = lcddata;			/*	LCDデータ下位4ビットを出力	*/
//	p9 |= lcddata;			/*	LCDデータ下位4ビットを出力	*/
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
	p8_7 = 0x0;		/*	RW－0(W指定)		*/
	
	/*===ポート方向レジスタを出力に設定===*/
	pd6 |= 0x03;
	pd8_7 = 1;

	prc2 = 1;		/*	pd9への書き込み許可	*/
	pd9 = 0x00;
//	pd9 &= 0xF0;
	
	LCDRW = HIGH;	/*	RW－1(R指定)		*/

	LCDE = HIGH;			/*	E－1				*/
#pragma ASM					/*	アセンブラ表記		*/
	NOP						/*	時間調整の為のNOP	*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	アセンブラ表記終了	*/
	command_high = p9;		/*	コマンド上位4ビット読み込み	*/
//	command_high = p9|0xF0;		/*	コマンド上位4ビット読み込み	*/
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
//	command_low = p9|0xF0;		/*	コマンド下位4ビット読み込み	*/
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

void BitSetP9(char command)
{
	if(command & 0x01) p9_0 = 1;
	else p9_0 = 0;
	if(command & 0x02) p9_1 = 1;
	else p9_1 = 0;
	if(command & 0x04) p9_2 = 1;
	else p9_2 = 0;
	if(command & 0x08) p9_3 = 1;
	else p9_3 = 0;
}

///////////////////////////////end
