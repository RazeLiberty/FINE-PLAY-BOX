//#######      Interval Timer driver         #######
//#######             version 1.3            #######
//#######        Edited : 2010/2/4           #######
//#######           	By KH		         #######
// Arranged by K.Hirota

#include	"device.h"

/*----------------------------------------------------------*/
/* �֐���	:InitTimer( n )									*/
/* �@�\		:�C���^�[�o���ݒ� n * 1us					    */
/*----------------------------------------------------------*/
void InitTimer( unsigned short data )
{
	ta2 = data/2-1;		/* set time 2us *data/2 */
	ta2mr = 0x80;		/* timer clock 2us */
	ta2s = 1;			/* timer start */
}

//#######    Timer driver for OAKS Multi I/O Board	#######
//#######             M16C/62A CPU					#######
//#######             version 1.0					#######
//#######           By OAKS support	(KH)	        #######

/*----------------------------------------------------------*/
/* �֐���	:WaitTimer()									*/
/* �@�\		:�C���^�[�o���^�C�}�҂�						    */
/*----------------------------------------------------------*/
void WaitTimer( void )
{
	while (ir_ta2ic == 0);	/* wait timer underflow flag */
	ir_ta2ic = 0;			/* flag clear */
}

///////////////////////////////end
