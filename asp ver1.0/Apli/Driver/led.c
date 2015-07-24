//#######    LED driver for OAKS Multi I/O Board	#######
//#######             M16C/62A CPU					#######
//#######             version 1.0					#######
//#######           	By KH				        #######

#include	"device.h"

#define	PORTOUT		1	/*	ポート方向レジスタを出力に設定する為のデータ	*/
#define	LightON		0	/*	LED点灯データ　*/
#define	LightOFF	1	/*	LED消灯データ　*/

/*----------------------------------------------------------*/
/* 関数名	:InitLED()										*/
/* 機能		:LED出力初期化								    */
/*----------------------------------------------------------*/
void InitLED( void )
{
	/*====LED消灯処理====*/
	p10_2 = LightOFF;			
	p10_3 = LightOFF;
	p0=1;		/* CPUボード LED1ポートを消灯 */	
	
	/*====P10_2,3方向出力====*/
	pd10_2 = PORTOUT;		
	pd10_3 = PORTOUT;
	pd0_0 = 1;	/* CPUボード LED1ポートを出力方向設定 */
}

/*----------------------------------------------------------*/
/* 関数名	:LEDOutput( data )								*/
/* 機能		:LED(LED1,2)出力　								*/
/*  data	0x10:両消灯	0x20:左点灯	0x40:右点灯	0x80:両点灯	*/
/*----------------------------------------------------------*/
void LEDOutput( unsigned char data )
{
	switch(data){
		case 0x10:
		 p10_2=LightOFF;
		 p10_3=LightOFF;
		break;
		case 0x20:
		 p10_2=LightON;
		 p10_3=LightOFF;
		break;
		case 0x40:
		 p10_2=LightOFF;
		 p10_3=LightON;
		break;
		case 0x80:
		 p10_2=LightON;
		 p10_3=LightON;
		break;
		default:
		 p10_2=LightOFF;
		 p10_3=LightOFF;
	}
}

///////////////////////////////end
