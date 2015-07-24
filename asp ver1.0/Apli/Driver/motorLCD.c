/************************************************************************/
/*  PROGRAM     :�S�����ړ��ԃT���v��									*/
/*  DATE        :2014.01.10			                                    */
/*  DESCRIPTION :���[�^x4 �G���R�[�_x4 LCD SWx2 LEDx2                   */
/*  CPU GROUP   :M16C/62P(Original I/O Board)                           */
/*  NOTE		:                       	    						*/
/*  PROGRAMMER	:														*/
/************************************************************************/

typedef unsigned char uint8_t;
#include "sfr62p.h"

//�萔��`
#define	CPUCLOCK 24320		/*CPU�����N���b�N 6MHz x 4 = 24000KHz(��6.08MHz �␳�l)*/
#define	TIMERINTERVAL 10	/*�Z�b�g�������^�C�}�C���^�[�o��(ms)*/

#define M1_IN1 p7_3
#define M1_POW ta1
#define M2_IN1 p7_5
#define M2_POW ta2
#define M3_IN1 p7_7
#define M3_POW ta3
#define M4_IN1 p8_1
#define M4_POW ta4

#define LED_RED p1_0
#define LED_GRE p1_1

// �G���R�[�_
#define E1_INA p8_2
#define E1_INB p8_6
#define E2_INA p8_3
#define E2_INB p8_7
#define E3_INA p8_4
#define E3_INB p1_3
#define E4_INA p1_5
#define E4_INB p1_4

#define PORTIN		0			/*	�|�[�g�������W�X�^����͂ɐݒ肷��ׂ̃f�[�^	*/
#define	PORTOUT		1			/*	�|�[�g�������W�X�^���o�͂ɐݒ肷��ׂ̃f�[�^	*/
#define	LCDRS		p6_0		/*	RS�[�q					*/
#define	LCDRW		p1_2		/*	RW�[�q					*/
#define	LCDE		p6_1		/*	E�[�q					*/
#define	HIGH		1			/*	�[�q�o�́gH�h			*/
#define	LOW			0			/*	�[�q�o�́gL�h			*/
#define	LCD_COMMAND	0			/*	RS-command�w��			*/
#define	LCD_DATA	1			/*	RS-data�w��				*/
#define	BUSY		1			/*	LCD��������buzy			*/
#define	NOBUSY		0			/*	LCD��������OK			*/

//�֐��̃v���g�^�C�v�錾
void main2(void);
void Init_IO(void);
void Init_TIMER(void);
void TA0_handler(void);
void TB2_handler(void);
void INT0_handler(void);
void INT1_handler(void);
void INT2_handler(void);
void INT3_handler(void);

void Motor1(uint8_t);
void Motor2(uint8_t);
void Motor3(uint8_t);
void Motor4(uint8_t);

// LCD
void InitLCD(void);						/*	LCD�����ݒ�				*/
void SetCursol(int x, int y);			/*  �\���ʒu���Z�b�g		*/
void DisplayLCD1C(char c);				/*  ���ʒu��1�����\��		*/
void DisplayLCD(char * row);			/*�@LCD������\��			*/
void SetCGRAM(void);					/*�@�J�X�^��������LCD��RAM�ɓo�^*/

void lcdwriteinit(unsigned char);		/*	LCD�����ݒ�R�}���h�o��	*/
void lcdwrite1command(unsigned char);	/*	LCD1�R�}���h�o��		*/
void lcdwrite1data(unsigned char);		/*	LCD1�f�[�^�o��			*/
void wait1(void);						/*	0.1ms�E�G�C�g			*/
void wait2(void);						/*	4.1ms�E�G�C�g			*/
void wait3(void);						/*	15ms�E�G�C�g			*/
unsigned char lcdbusycheck( void );		/*	LCD�r�W�[�`�F�b�N		*/

long enc1_count = 0;
long enc2_count = 0;
long enc3_count = 0;
long enc4_count = 0;


/*************************************************
 * main�@
 * ���C������
 *************************************************/
void main2(void)
{	
		char mess[]="xxxx";
			
	Init_IO();		//IO�|�[�g�̏�����
		InitLCD();		//LCD�����ݒ�(LCD�̏������V�[�P���X�����s)
	Init_TIMER();	//�^�C�}�̏�����

	//ei();			// ���荞�݋���(�A�Z���u�����[�`���ďo��)
	

	//LCD�̃R�}���h�A�f�[�^�����݂��e�X�g
	while(BUSY == lcdbusycheck());	//LCD�r�W�[�`�F�b�N
	lcdwrite1command ( 0b10001111 );//LCD�̕\���A�h���X���Z�b�g
	while(BUSY == lcdbusycheck());	//LCD�r�W�[�`�F�b�N
	lcdwrite1data( '!' );			//LCD�ɕ����f�[�^����������
	
	/*1�s�\��*/
	SetCursol(0, 5);
	DisplayLCD(mess);
	
	while(1){	//�������[�v
		SetCursol(0, 5);
		mess[0] = enc4_count % 10 + 0x30;
		DisplayLCD(mess);
		/* ���C������ */
		wait3();
	}
}

/*************************************************
 * Init_IO�@�@
 * IO�|�[�g�̏�����
 *************************************************/
void Init_IO(void)
{
	/*==== �{�[�h��LED ====*/
	p0_0 = 1;		// LED����	
	pd0_0 = 1;		// �|�[�g���o�͂ɐݒ�
	
	p10_2 = 1;
	pd10_2 = 1;
	
	p10_3 = 1;
	pd10_3 = 1;
	
	/*==== ���[�^ 1 ====*/
	M1_IN1 = 0;		// ���[�^1:IN2 LOW
	pd7_3 = 1;		// ���[�^1:IN2���o�͂ɐݒ� 

	/*==== ���[�^ 2 ====*/
	M2_IN1 = 0;		// ���[�^2:IN2 LOW
	pd7_5 = 1;		// ���[�^2:IN2���o�͂ɐݒ� 

	/*==== ���[�^ 3 ====*/
	M3_IN1 = 0;		// ���[�^3:IN2 LOW
	pd7_7 = 1;		// ���[�^3:IN2���o�͂ɐݒ� 

	/*==== ���[�^ 4 ====*/
	M4_IN1 = 0;		// ���[�^3:IN2 LOW
	pd8_1 = 1;		// ���[�^3:IN2���o�͂ɐݒ� 

#if 0
	/*==== �G���R�[�_ 1 ====*/
	int0ic = 0x07;
	ifsr0 = 1;
	pd8_2 = 0;
	pd8_6 = 0;

	/*==== �G���R�[�_ 2 ====*/
	int1ic = 0x07;
	ifsr1 = 1;
	pd8_3 = 0;
	pd8_7 = 0;

	/*==== �G���R�[�_ 3 ====*/
	int2ic = 0x07;
	ifsr2 = 1;
	pd8_4 = 0;
	pd1_3 = 0;

	/*==== �G���R�[�_ 4 ====*/
	int3ic = 0x07;
	ifsr3 = 1;
	pd1_5 = 0;
	pd1_4 = 0;

#endif

	/*==== LED �ԗ� ====*/
	pd1_0 = 1;
	pd1_1 = 1;
	LED_RED = 1;
	LED_GRE = 1;
}

/*************************************************
 * Init_TIMER�@�@
 * �^�C�}�̏�����
 *************************************************/
void Init_TIMER(void)
{
	udf = 0x00;
	trgsr = 0x55;
	/* �^�C�} TA0:���C���^�C�} */
	ta0mr = 0x84;								/* �^�C�}���[�h�Z�b�g		*/
	ta0 = (CPUCLOCK / 32 * TIMERINTERVAL) - 1;	/* �^�C�}�J�E���g�Z�b�g10ms */
	ta0ic = 0x01;								/* �����ݗD�惌�x�� IPL=1 (0�͊����ݕs��)*/
	ta0s = 1;									/* �^�C�}0�J�n 				*/

	/* ���[�^ 1:��PWM */
	ta1mr = 0x84;
	ta1 = 0;// �N����͒�~ 
	ta1s = 1;									/* �^�C�}A1�J�n 			*/

	/* ���[�^ 2:��PWM */
	ta2mr = 0x84;
	ta2 = 0;// �N����͒�~ 
	ta2s = 1;									/* �^�C�}A1�J�n 			*/

	/* ���[�^ 3:��PWM */
	ta3mr = 0x84;
	ta3 = 0;// �N����͒�~ 
	ta3s = 1;									/* �^�C�}A1�J�n 			*/

	/* ���[�^ 4:��PWM */
	ta4mr = 0x84;
	ta4 = 0;// �N����͒�~ 
	ta4s = 1;									/* �^�C�}A1�J�n 			*/

	/* ���[�^ 1-4:�S�̎��� */
	tb2mr = 0x84;								/* �^�C�}���[�h�Z�b�g		*/
	tb2 = (CPUCLOCK / 32 * TIMERINTERVAL) - 1;	/* �^�C�}�J�E���g�Z�b�g10ms	*/
	tb2ic = 0x02;								/* �����ݗD�惌�x�� IPL=2 (0�͊����ݕs��)*/
	tb2s = 1;									/* �^�C�}B2�J�n 			*/

}

/*************************************************
 * INT0_handler : ENCODER1���荞��
 *************************************************/
#pragma INTERRUPT INT0_handler

void INT0_handler(void)
{
	if(E1_INA == 0){
		if(E1_INB == 0){
			enc1_count++;
		} else {
			enc1_count--;
		}
	} else {
		if(E1_INB == 1){
			enc1_count++;
		} else {
			enc1_count--;
		}
	}
}

/*************************************************
 * INT1_handler : ENCODER2���荞��
 *************************************************/
#pragma INTERRUPT INT1_handler

void INT1_handler(void)
{
	if(E2_INA == 0){
		if(E2_INB == 0){
			enc2_count++;
		} else {
			enc2_count--;
		}
	} else {
		if(E2_INB == 1){
			enc2_count++;
		} else {
			enc2_count--;
		}
	}
}

/*************************************************
 * INT2_handler : ENCODER3���荞��
 *************************************************/
#pragma INTERRUPT INT2_handler

void INT2_handler(void)
{
	if(E3_INA == 0){
		if(E3_INB == 0){
			enc3_count++;
		} else {
			enc3_count--;
		}
	} else {
		if(E3_INB == 1){
			enc3_count++;
		} else {
			enc3_count--;
		}
	}
}


/*************************************************
 * INT3_handler : ENCODER4���荞��
 *************************************************/
#pragma INTERRUPT INT3_handler

void INT3_handler(void)
{
	if(E4_INA == 0){
		if(E4_INB == 0){
			enc4_count++;
		} else {
			enc4_count--;
		}
	} else {
		if(E4_INB == 1){
			enc4_count++;
		} else {
			enc4_count--;
		}
	}
}

/*************************************************
 * TA0_handler : 10ms�^�C�}���荞��
 *************************************************/
#pragma INTERRUPT TA0_handler

void TA0_handler(void)
{
	static int cnt = 100;	//�����݃J�E���g�@�����l100(1s)
	static char F_alt = 0;	//���݃t���O
	
	if(!cnt--){				//�����݂�100��J�E���g���閈��LED�_��/����
		if(F_alt^=1){		//�t���O�ؑւ�
	//	p0_0 = 0;		//IO�{�[�h LED1�_��
		}
		else{
	//	p0_0 = 1;		//IO�{�[�h LED1����
		}
		cnt=100;			//�J�E���g���Đݒ�
	}
}

/*************************************************
 * TB2_handler : 100Hz�����@
 *************************************************/
#pragma INTERRUPT TB2_handler

void TB2_handler(void)
{
	// ���[�^�p�����[�^�������ōX�V
	Motor1(40);
	Motor2(40);
	Motor3(40);
	Motor4(40);
}

void Motor1(uint8_t power)
{
	uint8_t mask = power >> 4;
	if(mask == 0)
	{
		M1_IN1 = 0;
		M1_POW = 0;
	}
	else
	{
		if((mask & 0x08) == 0)
		{
			M1_IN1 = 0;	// HI�̎���]
			M1_POW = (mask & 0x07) *10 * 7 + 59;
			// power * 7 + 59
			// ��Lpower40�̏ꍇ�@40 * 7 + 59 = 339
		}
		else
		{
			M1_IN1 = 1; // LOW�̎���]
			M1_POW = (0x08 - (mask & 0x07)) *10 * 7 + 59;
		}
	}
}

void Motor2(uint8_t power)
{
	uint8_t mask = power & 0x0F;
	if(mask == 0)
	{
		M2_IN1 = 0;
		M2_POW = 0;
	}
	else
	{
		if((mask & 0x08) == 0)
		{
			M2_IN1 = 0;	// HI�̎���]
			M2_POW = (mask & 0x07) *10 * 7 + 59;
			// power * 7 + 59
			// ��Lpower40�̏ꍇ�@40 * 7 + 59 = 339
		}
		else
		{
			M2_IN1 = 1; // LOW�̎���]
			M2_POW = (0x08 - (mask & 0x07)) *10 * 7 + 59;
		}
	}
}

void Motor3(uint8_t power)
{
	uint8_t mask = power & 0x0F;
	if(mask == 0)
	{
		M3_IN1 = 0;
		M3_POW = 0;
	}
	else
	{
		if((mask & 0x08) == 0)
		{
			M3_IN1 = 0;	// HI�̎���]
			M3_POW = (mask & 0x07) *10 * 7 + 59;
			// power * 7 + 59
			// ��Lpower40�̏ꍇ�@40 * 7 + 59 = 339
		}
		else
		{
			M3_IN1 = 1; // LOW�̎���]
			M3_POW = (0x08 - (mask & 0x07)) *10 * 7 + 59;
		}
	}
}

void Motor4(uint8_t power)
{
	uint8_t mask = power >> 4;
	if(mask == 0)
	{
		M4_IN1 = 0;
		M4_POW = 0;
	}
	else
	{
		if((mask & 0x08) == 0)
		{
			M4_IN1 = 0;	// HI�̎���]
			M4_POW = (mask & 0x07) *10 * 7 + 59;
			// power * 7 + 59
			// ��Lpower40�̏ꍇ�@40 * 7 + 59 = 339
		}
		else
		{
			M4_IN1 = 1; // LOW�̎���]
			M4_POW = (0x08 - (mask & 0x07)) *10 * 7 + 59;
		}
	}
}

/*********************************************************************************************************
=============================================�ȉ����=====================================================
(mask & 0x07) *10 * 7 + 59;				// ���]
(0x08 - (mask & 0x07)) *10 * 7 + 59;	// �t�]
�ɂ���

���]��
	0x07��AND�����ƍō��l��7�ɂ����Ȃ炸�������Ȃ��̂Ő悸10�{
	�����(*7+59)����̓I�}�W�i�C
	
�t�]��
	0x07��AND��10�{�܂ł͐��]���Ɠ���
	0 <= power < 100 ( 0 <= power <= 99)
	(power+100) * 7 + 59;		//	�t�]
		�����+100�Ɋւ�����
			power�����̐��ő����Ă����ꍇ�ALOW���Ƀ��[�^��
��]���鏈���ɂȂ�B
			������M1_POW��"HI"�ɂ��鎞�Ԃ�ݒ肷��ׁA-40��
�o�͂��o���������(-40+100)���s��
			M1_POW�̒l��60�ɂ���K�v������B
			
	����̃v���O�����ł͕��������ڑ����Ă��邱�Ƃ͖����̂�
		0 <= power <= 7 �Ƃ����������
			(0x08 - (power&0x07)) * 10 * 7 + 59;
	�ȏ�̂悤�Ȏ��ɂȂ�B
*********************************************************************************************************/

/*------------------------------------------------------------*/
/* �֐���	:SetCursol(�^�e(��i:0,���i:1), ���R(0 - 15)	  */
/* �@�\		:�\���ʒu���Z�b�g����						      */
/*------------------------------------------------------------*/
void SetCursol(int x, int y)
{
	while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N	�@*/
	lcdwrite1command ( x * 0x40 + 0x80 + y );/* �A�h���X�Z�b�g */
}

/*------------------------------------------------------------*/
/* �֐���	:DisplayLCD1C(�����R�[�h)						�@*/
/* �@�\		:SetCursol�Ŏw�肵���ʒu��1������\��		      */
/*------------------------------------------------------------*/
void DisplayLCD1C(char c)
{
	while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N	*/
	lcdwrite1data( c );
}

/*------------------------------------------------------------*/
/* �֐���	:DisplayLCD(������|�C���^)					�@*/
/* �@�\		:SetCursol�Ŏw�肵���ʒu���當����\��		      */
/*------------------------------------------------------------*/
void DisplayLCD(char * row)
{
	char c;

	while( (c=*row++) != '\0' ){		/* \0�����J��Ԃ� 	*/
		while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N*/
		lcdwrite1data( c );				/*	�����o��		*/
	}
}

//------------------------------------------------------------*/
// �֐���	:SetCGRAM()				�@
// �@�\		:�J�X�^��������LCD��RAM�ɓo�^����i8�����܂œo�^�j
//           �J�X�^�������͕����R�[�h0x00�`0x07�ɂP�����Âo�^�ł���B
//           �o�^���镶���R�[�h���Z�b�g���A5�h�b�g�~8���C���ɕ����p�^�[�����������ށB
//------------------------------------------------------------*/
void SetCGRAM(void)
{
	/*��FCGRAM�R�[�h0x01��'��'��o�^����*/
	/*�@CGRAM�A�h���X�Z�b�g�@CGRAM�R�[�h0x01���w��*/
	while(BUSY == lcdbusycheck());	/*LCD�r�W�[�`�F�b�N*/
	lcdwrite1command ( 0b01001000 );/*CGRAM�A�h���X�Z�b�g*/
                      /* |||||+++---- 3�r�b�g ���C���A�h���X(0-7)*/
                      /* ||+++------- 3�r�b�g CGRAM�R�[�h(0-7)*/
                      /* ++---------- 01�Œ� CGRAM�w��*/

	/*�ACGRAM�f�[�^������(5�h�b�g�~8���C���@�����ݎ��������C�������j*/
	while(BUSY == lcdbusycheck());	/*1�i��(�ŏ�i) */
	lcdwrite1data( 0b00001000);		/*����5�r�b�g�Ŏw��B���3�r�b�g��000�B1:���_, 0:���_*/
	while(BUSY == lcdbusycheck());	/*2�i��*/
	lcdwrite1data( 0b00010100);	
	while(BUSY == lcdbusycheck());	/*3�i��*/
	lcdwrite1data( 0b00001000);	
	while(BUSY == lcdbusycheck());	/*4�i��*/
	lcdwrite1data( 0b00000110);	
	while(BUSY == lcdbusycheck());	/*5�i��*/
	lcdwrite1data( 0b00001001);	
	while(BUSY == lcdbusycheck());	/*6�i��*/
	lcdwrite1data( 0b00001000);	
	while(BUSY == lcdbusycheck());	/*7�i��*/
	lcdwrite1data( 0b00001001);	
	while(BUSY == lcdbusycheck());	/*8�i��(�ŉ��i) �A���_�[���C���J�[�\�����g���ꍇ��1�s�󂯂�*/
	lcdwrite1data( 0b00000110);	
	
	/*�ȉ��A�o�^���镶�����Z�b�g����i�ő�8�����j*/
}

/*----------------------------------------------------------*/
/* �֐���	:InitLCD(�j										*/
/* �@�\		:LCD�����ݒ�								    */
/*----------------------------------------------------------*/
void InitLCD(void)
{
	wait3();						/*	15ms�E�G�C�g				*/
	lcdwriteinit( 0x03 );			/*	LCD�t�@���N�V�����Z�b�g		*/
	wait2();						/*	4.1ms�E�G�C�g				*/
	lcdwriteinit( 0x03 );			/*	LCD�t�@���N�V�����Z�b�g		*/
	wait1();						/*	0.1ms�E�G�C�g				*/
	lcdwriteinit( 0x03 );			/*	LCD�t�@���N�V�����Z�b�g		*/
	
	wait1();						/*	0.1ms�E�G�C�g 				*/
	lcdwriteinit( 0x03 );			/*	LCD�t�@���N�V�����Z�b�g		*/
	
	wait1();
	lcdwriteinit( 0x02 );			/*	LCD�f�[�^��4�r�b�g���ɐݒ�	*/
	wait1();
	lcdwrite1command(0x28);			/*	4bit�2�s���5�~7�h�b�g�ɐݒ�	*/
	wait1();

	/* 	�����܂ł�4�r�b�g�~2��̃f�[�^�]�����ł���悤�ɐݒ肳�ꂽ�̂�
	���̌�̓r�W�[�`�F�b�N�����Ă���f�[�^�]�����s�Ȃ��B */

	while(BUSY == lcdbusycheck())	/*	LCD�r�W�[�`�F�b�N		*/
	;
	lcdwrite1command(0x08);			/*	�\���I�t				*/

	while(BUSY == lcdbusycheck())	/*	LCD�r�W�[�`�F�b�N		*/
	;
	lcdwrite1command(0x01);			/*	�\���N���A				*/

	while(BUSY == lcdbusycheck())	/*	LCD�r�W�[�`�F�b�N		*/
	;
	lcdwrite1command(0x06);			/*	�G���g���[���[�h��C���N�������g*/

	while(BUSY == lcdbusycheck())	/*	LCD�r�W�[�`�F�b�N		*/
	;
	lcdwrite1command(0x0c);			/*	�\���I����J�[�\���I�t	*/
}

/*----------------------------------------------------------*/
/* �֐���	:lcdwriteinit()									*/
/* �@�\		:LCD�����ݒ�R�}���h�Z�b�g					    */
/*----------------------------------------------------------*/
void lcdwriteinit( unsigned char command )
{
	;
	/*===�����l�Z�b�g===*/
	p6_0 = 0x0;		/*	RS�|0(�R�}���h�w��)	*/
	p6_1 = 0x0;		/*	E�|0				*/
	p1_2 = 0x0;		/*	RW�|0(W�w��)		*/

	/*===�|�[�g�������W�X�^���o�͂ɐݒ�===*/
	pd6 |= 0x03;
	pd1_2 = 1;

	prc2 = 1;		/*	pd9�ւ̏������݋���	*/
	pd9 = 0xFF;

	command &= 0x0f;	/*	�R���g���[���f�[�^�Z�b�g(��������jRW�|0(W�w��) RS�|0(�R�}���h�w��jE�|0 */
	p9 = command;		/*	�R���g���[���f�[�^�o��	*/
	LCDE = HIGH;		/*	E�|�P					*/
#pragma ASM				/*	�A�Z���u���\�L			*/
	NOP					/*	���Ԓ����ׂ̈�NOP 		*/
	NOP
	NOP
	NOP
#pragma ENDASM			/*	�A�Z���u���\�L�I��		*/
	LCDE = LOW;			/*	E�|0					*/
}
/*----------------------------------------------------------*/
/* �֐���	:lcdwrite1command(�j							*/
/* �@�\		:LCD�R�}���h�o��							    */
/*----------------------------------------------------------*/
void lcdwrite1command( unsigned char command )
{
	unsigned char outcommand;

	/*===�����l�Z�b�g===*/
	p6_0 = 0x0;		/*	RS�|0(�R�}���h�w��)	*/
	p6_1 = 0x0;		/*	E�|0				*/
	p1_2 = 0x0;		/*	RW�|0(W�w��)		*/

	/*===�|�[�g�������W�X�^���o�͂ɐݒ�===*/
	pd6 |= 0x03;
	pd1_2 = 1;

	prc2 = 1;		/*	pd9�ւ̏������݋���	*/
	pd9 = 0xFF;

	outcommand = command>>4;	/*	���4�r�b�g������4�r�b�g��	*/
	outcommand &= 0x0f;			/*	�}�X�N����					*/
	p9 = outcommand;			/*	1�R�}���h�f�[�^���4�r�b�g���o�́@RW�|0(W�w��) RS�|0(�R�}���h�w��jE�|0 */
	LCDE = HIGH;				/*	E�|�P						*/
#pragma ASM						/*	�A�Z���u���\�L				*/
	NOP							/*	���Ԓ����ׂ̈�NOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM					/*	�A�Z���u���\�L�I��			*/
	LCDE = LOW;					/*	E�|0						*/
	outcommand = command&0x0f;	/*	�R�}���h�f�[�^�̉���4�r�b�g���o(���4�r�b�g�}�X�N)	*/
	p9 = outcommand;			/*	�R�}���h�f�[�^����4�r�b�g���o��						*/
	LCDE = HIGH;				/*	E�|�P						*/
#pragma ASM						/*	�A�Z���u���\�L				*/
	NOP							/*	���Ԓ����ׂ̈�NOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM					/*	�A�Z���u���\�L�I��			*/
	LCDE = LOW;					/*	E�|0						*/

}
/*----------------------------------------------------------*/
/* �֐���	:lcdwrite1data(�j								*/
/* �@�\		:LCD�f�[�^�o��								    */
/*----------------------------------------------------------*/
void	lcdwrite1data( unsigned char data )
{
	unsigned char lcddata;

	/*===�����l�Z�b�g===*/
	p6_0 = 0x0;		/*	RS�|0(�R�}���h�w��)	*/
	p6_1 = 0x0;		/*	E�|0				*/
	p1_2 = 0x0;		/*	RW�|0(W�w��)		*/

	/*===�|�[�g�������W�X�^���o�͂ɐݒ�===*/
	pd6 |= 0x03;
	pd1_2 = 1;

	prc2 = 1;		/*	pd9�ւ̏������݋���	*/
	pd9 = 0xFF;

	lcddata = data>>4;		/*	LCD�f�[�^���4�r�b�g������4�r�b�g��	*/
	lcddata &= 0x0f;		/*	�}�X�N����					*/

	p9 = lcddata;			/*	LCD�f�[�^���4�r�b�g���o��	*/
	LCDRS = LCD_DATA;		/*	RS�|1(�f�[�^�w��j			*/
	LCDE = HIGH;			/*	E�|�P						*/
#pragma ASM					/*	�A�Z���u���\�L				*/
	NOP						/*	���Ԓ����ׂ̈�NOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	�A�Z���u���\�L�I��			*/
	LCDE = LOW;				/*	E�|0						*/
	lcddata =data & 0x0f;	/*	LCD�f�[�^�̉���4�r�b�g���o(���4�r�b�g�}�X�N)	*/
	p9 = lcddata;			/*	LCD�f�[�^����4�r�b�g���o��	*/
	LCDRS = LCD_DATA;		/*	RS�|1(�f�[�^�w��j			*/
	LCDE = HIGH;			/*	E�|1						*/
#pragma ASM					/*	�A�Z���u���\�L				*/
	NOP						/*	���Ԓ����ׂ̈�NOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	�A�Z���u���\�L�I��	*/
	LCDE = LOW;				/*	E�|0				*/
}

/*----------------------------------------------------------*/
/* �֐���	:wait1()										*/
/* �@�\		:0.1ms�E�G�C�g								    */
/*----------------------------------------------------------*/
void wait1(void)
{			/*	��0.1ms�̃E�G�C�g	*/
#pragma ASM					/*	�A�Z���u���\�L		*/
	MOV.W 	#0C8H,A0		/*	�J�E���^�����l�Z�b�g*/
LOOP1:
	NOP
	NOP
	NOP
	DEC.W	A0
	JNZ	LOOP1				/*	���[�v�I���H		*/
#pragma ENDASM				/*	�A�Z���u���\�L�I��	*/
}
/*----------------------------------------------------------*/
/* �֐���	:wait2()										*/
/* �@�\		:4.1ms�E�G�C�g								    */
/*----------------------------------------------------------*/
void wait2(void)
{			/*	��4.1ms�̃E�G�C�g 	*/
#pragma ASM					/*	�A�Z���u���\�L		*/
	MOV.W 	#2007H,A0		/*	�J�E���^�����l�Z�b�g*/
LOOP2:
	NOP
	NOP
	NOP
	DEC.W	A0
	JNZ	LOOP2				/*	���[�v�I���H		*/
#pragma ENDASM				/*	�A�Z���u���\�L�I��	*/
}
/*----------------------------------------------------------*/
/* �֐���	:wait3()										*/
/* �@�\		:15ms�E�G�C�g									*/
/*----------------------------------------------------------*/
void wait3(void)
{			/*	��15ms�̃E�G�C�g	*/
#pragma ASM					/*	�A�Z���u���\�L		*/
	MOV.W 	#7530H,A0		/*	�J�E���^�����l�Z�b�g*/
LOOP3:
	NOP
	NOP
	NOP
	DEC.W	A0
	JNZ	LOOP3				/*	���[�v�I���H		*/
#pragma ENDASM				/*	�A�Z���u���\�L�I��	*/
}
/*----------------------------------------------------------*/
/* �֐���	:lcdbusycheck()									*/
/* �@�\		:LCD�r�W�[�`�F�b�N							    */
/*----------------------------------------------------------*/
unsigned char lcdbusycheck( void )
{
	unsigned char command_high,command_low,b_data;

	/*===�����l�Z�b�g===*/
	p6_0 = 0x0;		/*	RS�|0(�R�}���h�w��)	*/
	p6_1 = 0x0;		/*	E�|0				*/
	p1_2 = 0x0;		/*	RW�|0(W�w��)		*/
	
	/*===�|�[�g�������W�X�^���o�͂ɐݒ�===*/
	pd6 |= 0x03;
	pd1_2 = 1;

	prc2 = 1;		/*	pd9�ւ̏������݋���	*/
	pd9 = 0x00;

	LCDRW = HIGH;	/*	RW�|1(R�w��)		*/

	LCDE = HIGH;			/*	E�|1				*/
#pragma ASM					/*	�A�Z���u���\�L		*/
	NOP						/*	���Ԓ����ׂ̈�NOP	*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	�A�Z���u���\�L�I��	*/
	command_high = p9;		/*	�R�}���h���4�r�b�g�ǂݍ���	*/
	LCDE = LOW;				/*	E�|0				*/

	command_high <<=4;		/*	����4�r�b�g����ʂ�	*/
	command_high &= 0xf0;	/*	���4�r�b�g���o(����4�r�b�g�}�X�N����)	*/

	LCDE = HIGH;			/*	E�|1				*/
#pragma ASM					/*	�A�Z���u���\�L		*/
	NOP						/*	���Ԓ����ׂ̈�NOP	*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	�A�Z���u���\�L�I��	*/
	command_low = p9;		/*	�R�}���h����4�r�b�g�ǂݍ���	*/
	LCDE = LOW;				/*	E�|0				*/
	command_low &= 0x0f;	/*	����4�r�b�g���o(���4�r�b�g�}�X�N����)	*/
	b_data = command_high|command_low;	/*	2��4�r�b�g�R�}���h�f�[�^��8�r�b�g�ɂ܂Ƃ߂�	*/
	b_data &= 0x80;			/*	�r�b�g7�̃}�X�N����	*/
	if(b_data == 0)
		b_data = NOBUSY;	/*	�r�b�g7��0�Ȃ�LCD��������ok��Ԃ�		*/
	else
		b_data = BUSY;		/*	�r�b�g7��1�Ȃ�LCD��������buzy��Ԃ�		*/
		
	return(b_data);
}