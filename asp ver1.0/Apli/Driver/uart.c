//#######      Interval UART0 driver         #######
//#######             version 1.3            #######
//#######        Edited : 2010/2/4           #######
// Arranged by K.Hirota

#include	"device.h"

/*--------------------------------------------------------------*/
/* UART0���g�p�������b�Z�[�W�o�́BPC�̃��j�^�ɏo�͂ł���B		*/
/* 		�]�����x�F38400pbs(�}�j���A�����f1�ABRG:38��I��) 		*/	/* ����������	115200bps = "12" BRG:12*/
/*		�f�[�^��:8bit �X�g�b�v�r�b�g�F1 �p���e�B�F�Ȃ�			*/
/*--------------------------------------------------------------*/

/*   �萔�̐ݒ�	*/
#define	U0_BRG		12	//	/*	�]�����x���W�X�^�̐ݒ�l	1.8432	*/

/* �v���g�^�C�v�錾 */
//void	InitUART0(void);			/*	���C���֐�		*/
//void 	receive(void);		/*	��M�����݊֐�	*/
#pragma INTERRUPT  receive

/*----------------------------------------------------------
* �֐���	:InitUART0�i�j									
* �@�\		:uart0�����ݒ�	(CNT10�R�l�N�^)		
----------------------------------------------------------*/
void InitUART0()
{
	
	u0mr = 0x05;			/* ����M���|�h���W�X�^ �����N���b�N*/
								/* �񓯊��A8�r�b�g�A�p���e�B�Ȃ��A	*/
								/* �X���[�v�Ȃ�						*/

	u0c0 = 0x18;			/* ����M���䃌�W�X�^�O �N���b�Nf1�I��*/
	u0brg = U0_BRG;		/* �]�����x���W�X�^					*/

	ucon= 0x01;			//�@UART0�����ݗv�������M����

	s0ric = 0x06;			/* �����݃��x���̐ݒ�				*/
	u0c1 = 0x05;			/* UART0:����M���䃌�W�X�^�P ����M����	*/
	
	
//	_asm( "\tFSET	I");	/* ���荞�݋���						*/

}



/*----------------------------------------------------------
* �֐���	:receive(�j									
* �@�\		:��M�����݊֐�								    
*�@		:��M�����f�[�^�����̂܂ܑ��M����				
*----------------------------------------------------------*/
void receive()
{
	int rdata = 0;				/* ��M�o�b�t�@			*/

	rdata = u0rb;				/* �f�[�^��M			*/
	
	rdata &= 0x0ff;			/* ��M�f�[�^���M(PC�ւ̃G�R�[�o�b�N)		*/
	u0tb = rdata;

}

/*----------------------------------------------------------
* �֐���	:send(�j									
* �@�\		:1�o�C�g���M�֐�								    
*�@		:������1�o�C�g�f�[�^�𑗐M����			
*----------------------------------------------------------*/
void send(int c)
{
	while(!ti_u0c1){}
	c &= 0x0ff;				/* ��M�f�[�^���M(PC�ւ̃G�R�[�o�b�N)		*/
	u0tb = c;
}

/*------------------------------------------------------------
* �֐���	:CONSout(������|�C���^)							  
* �@�\		:NULL�R�[�h�܂ł̕�������R���\�[���ɏo�͂���     
*------------------------------------------------------------*/
void CONSout(char *row)
{
		while ( *row != '\0'){
			send( *row++ );
		}
		send('\r');
		send('\n');
}

///////////////////////////////end