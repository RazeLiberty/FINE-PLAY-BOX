//#######    Device driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU					#######
//#######             version 1.0					#######
//#######           					        #######

/* デバイス定義ファイル */
#include  	"sfr62p.h"

/* ドライバ公開関数　ヘッダファイル */
//#include "led.h"
//#include "swinput.h"
//#include "timer.h"
//#include "lcd.h"
#include "job_motorLCD.h"
#include "uart.h"
//#include "KEY.h"

/*device.c 公開関数-----------------------------------------*/
/* 関数名	:InitDevice										*/
/* 機能		:デバイスドライバの初期化						*/
/*----------------------------------------------------------*/
void InitDevice( void );

///////////////////////////////end
