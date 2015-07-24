/**************************************************************
//#######�@Matrix Key driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU			�@�@		#######
//#######             version 1.0			�@�@		#######
//#######           By OAKS support	(KH)	 �@�@       #######
***************************************************************/
#include  	"device.h"
//#include  	"sfr62p.h"

/*----------------------------------------------------------*/
/* �֐���	:InitKEY()										*/
/* �@�\		:�X�C�b�`���͏�����							    */
/*----------------------------------------------------------*/
void InitKEY( void )
{
	/*�L�[�}�g���b�N�X���^�[�����C���|�[�g����͐ݒ�*/
	pd7_4 = 0;	
	pd7_5 = 0;	
	pd7_6 = 0;	
	pd7_7 = 0;		
	/*�L�[�}�g���b�N�X�X�L�������C���|�[�g���o�͐ݒ�*/
	p10_4 = 1;		pd10_4 = 1;
	p10_5 = 1;		pd10_5 = 1;
	p10_6 = 1;		pd10_6 = 1;
	p10_7 = 1;		pd10_7 = 1;
}

/*----------------------------------------------------------*/
/* �֐���	:KEYInput()																			*/
/* �@�\		:�L�[�}�g���b�N�X(4x4)���́i�Q�L�[���b�N�A�E�g�j								*/
/* �߂�l	:�ォ��1�s�ڍ��[SW���ŏ�ʃr�b�g�ɁA����16bits�z�u				*/
/*	**** 15,14,13,12		<- SW���������ƊY���r�b�g��1������						*/
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
	static unsigned int SW_flag = 0;	/*SW�A�����������t���O(0:����,1:�L��)*/
	
	SW_data2 = SW_data1;
	SW_data1 = SW_data0;  	

	/* 1-4�s�ڂ�SW�f�[�^���r�b�g���]���ē��́A�r�b�g�V�t�g��16-bit�Ƀp�b�N*/
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
	
	/* 3���v���Ȃ�����ύX���Ȃ��B�`���^�����O���� */
	if ( SW_data0 == SW_data1 && SW_data0 == SW_data2 ){
		if( SW_data0==0x00 ){	/*SW���S�I�t�̏ꍇ*/
			SW_data3 = SW_data0;
			SW_flag=1;
		}
		else {
			if(SW_flag == 1) SW_data3 = SW_data0;  /*��U�S�I�t�̌�̓��͂̏ꍇ�L��*/
			SW_flag=0;
		}
	}
	return ( SW_data3 ); /*�A�������̎��͍ŏ���SW�R�[�h��Ԃ�*/
}

///////////////////////////////end
