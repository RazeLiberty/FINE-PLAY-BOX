//#######Matrix Key driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU					#######
//#######             version 1.0					#######
//#######           	By KH				        #######

#include  	"device.h"

static unsigned char SW_data0;
static unsigned char SW_data1;
static unsigned char SW_data2;	
static unsigned char SW_data3;
static unsigned char SW_data4;
static unsigned char SW_flag;		/* SW idle変化フラグ   1:SW idle状態からの入力あり　by K.Hirota */

/*----------------------------------------------------------*/
/* 関数名	:InitSWInput()									*/
/* 機能		:スイッチ入力初期化							    */
/*----------------------------------------------------------*/
void InitSWInput( void )
{
	SW_data0 = 0x00;
	SW_data1 = 0x00;
	SW_data2 = 0x00;
	SW_data3 = 0x00;
	SW_data4 = 0x00;
	SW_flag = 0;	/*SW連続押し無効フラグ(0:無効,1:有効)*/

	/*キーマトリックスリターンラインポートを入力設定*/
	pd7=0x00;		
	/*キーマトリックススキャンラインポート（1行目）を出力設定*/
	p10_4 = 0x1;	
	pd10_4 = 0x1;
}

/*----------------------------------------------------------*/
/* 関数名	:SWInput()										*/
/* 機能		:キーマトリックス1行目入力（２キーロックアウト）*/
/* 戻り値	:SW1=0x80, SW5=0x40, SW9=0x20, SW13=0x10		*/
/*----------------------------------------------------------*/
unsigned char SWInput( void )
{
	SW_data2 = SW_data1;
	SW_data1 = SW_data0;  	

	/* 1行目のSWデータをビット反転して入力*/
	p10_4 = 0x0; 
	SW_data0 = ~p7 & 0xf0;
	p10_4 = 0x1; 

	if ( SW_data0 == SW_data1 && SW_data0 == SW_data2 ){	/* 3回一致、チャタリング除去 */
		if( SW_data0==0x00 ){	/*SWが全オフの場合*/
			SW_data3 = SW_data0;
			SW_flag=1;
		}
		else {
			if(SW_flag == 1) SW_data3 = SW_data0;  /*一旦全オフの後の入力の場合有効*/
			SW_flag=0;
		}
	}
	return ( SW_data3 ); /*連続押しの時は最初のSWコードを返す*/
}

///////////////////////////////end

