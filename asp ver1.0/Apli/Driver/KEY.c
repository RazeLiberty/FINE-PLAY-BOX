/**************************************************************
//#######　Matrix Key driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU			　　		#######
//#######             version 1.0			　　		#######
//#######           By OAKS support	(KH)	 　　       #######
***************************************************************/
#include  	"device.h"
//#include  	"sfr62p.h"

/*----------------------------------------------------------*/
/* 関数名	:InitKEY()										*/
/* 機能		:スイッチ入力初期化							    */
/*----------------------------------------------------------*/
void InitKEY( void )
{
	/*キーマトリックスリターンラインポートを入力設定*/
	pd7_4 = 0;	
	pd7_5 = 0;	
	pd7_6 = 0;	
	pd7_7 = 0;		
	/*キーマトリックススキャンラインポートを出力設定*/
	p10_4 = 1;		pd10_4 = 1;
	p10_5 = 1;		pd10_5 = 1;
	p10_6 = 1;		pd10_6 = 1;
	p10_7 = 1;		pd10_7 = 1;
}

/*----------------------------------------------------------*/
/* 関数名	:KEYInput()																			*/
/* 機能		:キーマトリックス(4x4)入力（２キーロックアウト）								*/
/* 戻り値	:上から1行目左端SWを最上位ビットに、順に16bits配置				*/
/*	**** 15,14,13,12		<- SWが押されると該当ビットに1が立つ						*/
/*	**** 11,10, 9,  8																				*/
/*	****  7,  6,  5, 4																				*/
/*	****  3,  2,  1, 0																				*/
/*----------------------------------------------------------*/
unsigned int KEYInput( void )
{
	static unsigned int SW_data0 = 0x00;
	static unsigned int SW_data1 = 0x00;
	static unsigned int SW_data2 = 0x00;	
	static unsigned int SW_data3 = 0x00;
	static unsigned int SW_flag = 0;	/*SW連続押し無効フラグ(0:無効,1:有効)*/
	
	SW_data2 = SW_data1;
	SW_data1 = SW_data0;  	

	/* 1-4行目のSWデータをビット反転して入力、ビットシフトし16-bitにパック*/
	p10_4 = 0; 
	SW_data0 = (unsigned int)~p7 & 0xf0;
	p10_4 = 1; 
	SW_data0 = SW_data0 << 8;
	p10_5 = 0; 
	SW_data0 = SW_data0 | ((unsigned int)(~p7 & 0xf0) << 4 );
	p10_5 = 1; 
 	p10_6 = 0; 
	SW_data0 = SW_data0 | ((unsigned int)(~p7 & 0xf0) );
	p10_6 = 1; 
	p10_7 = 0; 
	SW_data0 = SW_data0 | ((unsigned int)(~p7 & 0xf0) >> 4 );
	p10_7 = 1; 
	
	/* 3回一致しない限り変更しない。チャタリング除去 */
	if ( SW_data0 == SW_data1 && SW_data0 == SW_data2 ){
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
