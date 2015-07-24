//#######    Device driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU					#######
//#######             version 1.0					#######
//#######           					        #######

#include	"device.h"

/*----------------------------------------------------------*/
/* 関数名	:InitDevice										*/
/* 機能		:デバイスドライバの初期化						*/
/*----------------------------------------------------------*/
void InitDevice( void ){
	//InitSWInput();
	//InitLED();
	InitLCD();
	InitUART0();
	Init_IO();
	Init_TIMER();
	//InitKEY();
}

///////////////////////////////end