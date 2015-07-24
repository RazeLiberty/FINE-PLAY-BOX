/* 
 *  TOPPERS/ASP ���[�N�v���O����
 *	UART0����M�T���v���v���O����
 *	���d�l��
 *	PC�ƃ}�C�R���{�[�h��UART0�R�l�N�^��USB-�V���A���ϊ��P�[�u���Őڑ���
 *	PC���̃^�[�~�i���\�t�g�Ƃ̃V���A���ʐM���e�X�g����B
 *	��Terminal Soft(PC��)�̐ݒ聄
 *		�ݒ�  	�V���A���|�[�g
 *				�{�[���[�g�F�R�W�S�O�O
 *				8�r�b�g,�m���p���e�B,1�X�g�b�v�r�b�g
 *  2014/2/13 
 *	
 *	
 *	motorLCD.c����g�������֐���job_motorLCD.h�Ńv���g�^�C�v�錾���邱�Ƃ�job.c�Ŏg����悤�ɕύX�B
 *	2014/2/17 by T.K
 *
 *	InitDevice()�̒���Init_IO()�AInit_TIMER()��ǉ��B
 *	main��ini_dtq(UART_DTQ)��ǉ��B
 *	job_motorLCD.h��motor(int)��ǉ��B
 *	�ϐ�Motor_Power�Amask��ǉ��B
 *	UART0�����M�����f�[�^��Motor_Power�ցB
 *	���̌�}�X�N���������Ă��ꂼ���Motor�̏o�͂ցB
 *	2014/2/18 by T.K
 *
 *	
 */

#include <itron.h>
#include <kernel.h>
#include "kernel_cfg.h"
#include "arch/m16c_nc30/m16C62p.h"
#include "job.h"
#include "Driver/device.h"

//�萔��`
#define	CPUCLOCK 24320		/*CPU�����N���b�N 6MHz x 4 = 24000KHz(��6.08MHz �␳�l)*/
#define	TIMERINTERVAL 10	/*�Z�b�g�������^�C�}�C���^�[�o��(ms)*/

/* �֐��v���g�^�C�v�錾 */
int8_t ReceiveUART(void);
void SendUART(uint8_t c);

////////////////// �^�X�N ///////////////////////
/*
 *  Initial and Idle�^�X�N
 *  �������Ə����N���A������A�C�h�����O
 */
void main(intptr_t exinf)
{
	//char title[]="FINE PLAY BOX";
	
	/* ���p�ϐ��̏����� */

	/* IO�̏����� */
	InitDevice();			//UART0�̏�������uart.c��InitUART0()�ōs��			uart.c�̂݌Ăэ���
							//�ʐM���x��ς���ꍇ��U0_BRG�̒l��ύX����
							
	/*1�s�^�C�g���\��*/
	//SetCursol(0, 1);
	//DisplayLCD(title);
	
	/*�I�u�W�F�N�g�̏�����*/
	ini_dtq(UART_DTQ);		//�f�[�^�L���[��������
	
	/* �����N���^�X�N�̋N���Ǝ����N���^�X�N�J�n */
	dis_dsp();				//�f�B�X�p�b�`��~
	  //�^�X�N�N��
	  act_tsk(FUNC1_TASK);		//UART0����M�e�X�g
	  //act_tsk(FUNC2_TASK);		//�����R���g���[���e�X�g
	  ena_int(TINTNO_S0RACK);	//UART0��M�����݋���
	  ena_int(TINTNO_S0TNACK);	//UART0���M�����݋���
	
	ena_dsp();				//�f�B�X�p�b�`�J�n

	while(FOREVER);			//�A�C�h�����O
}

/* ID:FUNC1_TASK		priority=mid
*	UART0����M�e�X�g�^�X�N
*	PC�ƃ}�C�R���{�[�h��UART0�R�l�N�^��USB-�V���A���ϊ��P�[�u���Őڑ���
*	PC���̃^�[�~�i���\�t�g�Ƃ̑���M���e�X�g����B
 */
void func1_task(intptr_t exinf)
{
	int8_t Motor_Power;
	int8_t c;
	
	while(FOREVER){
		
		//SendUART('A');		//����'A'�𑗐M���遨PC���^�[�~�i���\�t�g�ɕ������\�������
		
		Motor_Power = ReceiveUART();	//PC��Kinect����̃f�[�^����M���ă��[�^�ɔ��f������
		
		// ���[�^�p�����[�^�������ōX�V
		
		
		Motor1( Motor_Power );
		Motor2( Motor_Power );
		Motor3( Motor_Power );
		Motor4( Motor_Power );
		
		//c = ReceiveUART();	//PC���^�[�~�i���\�t�g����̃f�[�^����M����LCD�ɕ\������
		c = Motor_Power;
		if((c & 0x80) == 0){
			SetCursol(0,5);
			DisplayLCD1C(0x30);
		} else {
			SetCursol(0,5);
			DisplayLCD1C(0x31);
		}
		if((c & 0x08) == 0){
			SetCursol(0,7);
			DisplayLCD1C(0x30);
		} else {
			SetCursol(0,7);
			DisplayLCD1C(0x31);
		}
	}

}


////////////////// �֐� ///////////////////////
/* 
* UART0��M�֐�  
* �@�\	:�P�o�C�g�̃f�[�^����M����B
* �߂�l:��M����1�o�C�g�̃f�[�^
* ����	:�T�[�r�X�R�[�����g�p���邽�߁A���M����^�X�N����Ăяo���B
*		:�f�[�^����M����܂ő҂�
*/
int8_t ReceiveUART()
{
	intptr_t p;
	
	rcv_dtq(UART_DTQ, &p);	//UART_DTQ����̃f�[�^�҂�

	return (int8_t)p;		//8�r�b�g
}

/* 
* UART0���M�֐�  
* �@�\	:�P�o�C�g�̃f�[�^�𑗐M����B
* ����	:���M�p1�o�C�g�̃f�[�^
* ����	:�T�[�r�X�R�[�����g�p���邽�߁A���M����^�X�N����Ăяo��
*		:�f�[�^�𑗐M��������܂ő҂�
*/
void SendUART(uint8_t c)
{
	FLGPTN flgptn;
	
	u0tb = c;									//UART0���M
	wai_flg(UART_FLG,0x0001,TWF_ORW,&flgptn);	//���M�����҂�
}

////////////////// �n���h�� ///////////////////////
/*
 *  UART��M�����݃n���h���iOS�ˑ��j
 *  UART��M�����݂Ŏ�M�f�[�^��ǂݍ��݁ADTQ�Ƀf�[�^�𑗂�B
 */
 void UART_receive_handler(intptr_t exinf)
 {
	uint8_t c;
	
	c = u0rb;					//UART0��M���W�X�^��ǂݍ��� //Kinect����f�[�^��M
	ipsnd_dtq(UART_DTQ, c);		//UART�pDTQ�փf�[�^�𑗂�
	c = 0;
 }
 
 /*
 *  UART���M���������݃n���h���iOS�ˑ��j
 *  �P�o�C�g�f�[�^�𑗐M��ɔ������銄���݂ő��M�����𑗐M�^�X�N�ɒʒm����B
 */
void UART_send_handler(intptr_t exinf)
{
 	iset_flg(UART_FLG, 0x0001);	//���M�����C�x���g�t���O���Z�b�g
}

/************* End *************/