/* 
 *  job �w�b�_�t�@�C��
 *  UART0�T���v���v���O�����p
 */
#define FOREVER 1

/* �^�X�N�D��x�̐ݒ� */
#define IDLE_PRIORITY 16	//�ŉ��ʗD��x
#define HI_PRIORITY 10
#define MID_PRIORITY 11
#define LOW_PRIORITY 12

/*  UART�����݃n���h���̗D��x */
#define	INTPRI_UART_send	-4	
#define	INTPRI_UART_recieve	-5	

/*
 *  �^�[�Q�b�g�Ɉˑ�����\���̂���萔�̒�`
 *  �X�^�b�N�T�C�Y
 */
#ifdef STACK_SIZE
#undef STACK_SIZE
#endif /* STACK_SIZE */
#define	STACK_SIZE	386	/* �^�X�N�̃X�^�b�N�T�C�Y */

/*
 *  �֐��̃v���g�^�C�v�錾
 */
#ifndef _MACRO_ONLY

extern void	main(intptr_t exinf);
extern void func1_task(intptr_t exinf);
//extern void func2_task(intptr_t exinf);

extern void UART_send_DD_task(intptr_t exinf);
extern void UART_receive_DD_task(intptr_t exinf);

#endif /* _MACRO_ONLY */


/************* End *************/