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
static unsigned char SW_flag;		/* SW idle�ω��t���O   1:SW idle��Ԃ���̓��͂���@by K.Hirota */

/*----------------------------------------------------------*/
/* �֐���	:InitSWInput()									*/
/* �@�\		:�X�C�b�`���͏�����							    */
/*----------------------------------------------------------*/
void InitSWInput( void )
{
	SW_data0 = 0x00;
	SW_data1 = 0x00;
	SW_data2 = 0x00;
	SW_data3 = 0x00;
	SW_data4 = 0x00;
	SW_flag = 0;	/*SW�A�����������t���O(0:����,1:�L��)*/

	/*�L�[�}�g���b�N�X���^�[�����C���|�[�g����͐ݒ�*/
	pd7=0x00;		
	/*�L�[�}�g���b�N�X�X�L�������C���|�[�g�i1�s�ځj���o�͐ݒ�*/
	p10_4 = 0x1;	
	pd10_4 = 0x1;
}

/*----------------------------------------------------------*/
/* �֐���	:SWInput()										*/
/* �@�\		:�L�[�}�g���b�N�X1�s�ړ��́i�Q�L�[���b�N�A�E�g�j*/
/* �߂�l	:SW1=0x80, SW5=0x40, SW9=0x20, SW13=0x10		*/
/*----------------------------------------------------------*/
unsigned char SWInput( void )
{
	SW_data2 = SW_data1;
	SW_data1 = SW_data0;  	

	/* 1�s�ڂ�SW�f�[�^���r�b�g���]���ē���*/
	p10_4 = 0x0; 
	SW_data0 = ~p7 & 0xf0;
	p10_4 = 0x1; 

	if ( SW_data0 == SW_data1 && SW_data0 == SW_data2 ){	/* 3���v�A�`���^�����O���� */
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

