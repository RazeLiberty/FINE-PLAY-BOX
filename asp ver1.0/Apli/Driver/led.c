//#######    LED driver for OAKS Multi I/O Board	#######
//#######             M16C/62A CPU					#######
//#######             version 1.0					#######
//#######           	By KH				        #######

#include	"device.h"

#define	PORTOUT		1	/*	�|�[�g�������W�X�^���o�͂ɐݒ肷��ׂ̃f�[�^	*/
#define	LightON		0	/*	LED�_���f�[�^�@*/
#define	LightOFF	1	/*	LED�����f�[�^�@*/

/*----------------------------------------------------------*/
/* �֐���	:InitLED()										*/
/* �@�\		:LED�o�͏�����								    */
/*----------------------------------------------------------*/
void InitLED( void )
{
	/*====LED��������====*/
	p10_2 = LightOFF;			
	p10_3 = LightOFF;
	p0=1;		/* CPU�{�[�h LED1�|�[�g������ */	
	
	/*====P10_2,3�����o��====*/
	pd10_2 = PORTOUT;		
	pd10_3 = PORTOUT;
	pd0_0 = 1;	/* CPU�{�[�h LED1�|�[�g���o�͕����ݒ� */
}

/*----------------------------------------------------------*/
/* �֐���	:LEDOutput( data )								*/
/* �@�\		:LED(LED1,2)�o�́@								*/
/*  data	0x10:������	0x20:���_��	0x40:�E�_��	0x80:���_��	*/
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
