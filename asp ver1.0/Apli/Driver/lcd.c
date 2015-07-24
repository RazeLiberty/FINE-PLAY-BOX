//#######    LCD driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU					#######
//#######             version 1.0					#######
//#######           	By KH				        #######

#include	"device.h"

/* �v���g�^�C�v�錾 */
void lcd_init(void);					/*	LCD�����ݒ�				*/
void lcdwriteinit(unsigned char);		/*	LCD�����ݒ�R�}���h�o��	*/
void lcdwrite1command(unsigned char);	/*	LCD1�R�}���h�o��		*/
void lcdwrite1data(unsigned char);		/*	LCD1�f�[�^�o��			*/
void wait1(void);						/*	0.1ms�E�G�C�g			*/
void wait2(void);						/*	4.1ms�E�G�C�g			*/
void wait3(void);						/*	15ms�E�G�C�g			*/
unsigned char lcdbusycheck( void );		/*	LCD�r�W�[�`�F�b�N		*/
void BitSetP9(char command);			/*  P9����4�r�b�g���ʂɃZ�b�g*/


#define PORTIN		0			/*	�|�[�g�������W�X�^����͂ɐݒ肷��ׂ̃f�[�^	*/
#define	PORTOUT		1			/*	�|�[�g�������W�X�^���o�͂ɐݒ肷��ׂ̃f�[�^	*/
#define	LCDRS		p6_0		/*	RS�[�q					*/
#define	LCDRW		p8_7		/*	RW�[�q					*/
#define	LCDE		p6_1		/*	E�[�q					*/
#define	HIGH		1			/*	�[�q�o�́gH�h			*/
#define	LOW			0			/*	�[�q�o�́gL�h			*/
#define	LCD_COMMAND	0			/*	RS-command�w��			*/
#define	LCD_DATA	1			/*	RS-data�w��				*/
#define	BUSY		1			/*	LCD��������buzy			*/
#define	NOBUSY		0			/*	LCD��������OK			*/


/*----------------------------------------------------------*/
/* �֐���	:InitLCD(�j									*/
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

/*------------------------------------------------------------*/
/* �֐���	:DisplayLCD1L(line, ������|�C���^)				  */
/* �@�\		:1�s�������\��	16�����ȓ�����				      */
/*------------------------------------------------------------*/

void DisplayLCD1L(char data,char * row)
{
	int	i;
	data &= 0x01;
	while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N		*/
	lcdwrite1command ( data * 0x40 + 0x80 );/* �A�h���X�Z�b�g */
	for(i=0;i<16;i++){				/* 16�����]�� */
		if ( *row == '\0'){
			while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N		*/
			lcdwrite1data( ' ' );
		}else{
			while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N		*/
			lcdwrite1data( *row++ );
		}
	}
}

void SetCursol(int x, int y)
{
	wait1();
	wait1();
	while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N		*/
	lcdwrite1command ( x * 0x40 + 0x80 + y );/* �A�h���X�Z�b�g */
}

void DisplayLCD1C(char c)
{
	while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N		*/
	lcdwrite1data( c );
}

void DisplayLCD(char * row)
{
	char c;
	while( c=*row++ ){
		while(BUSY == lcdbusycheck());	/*	LCD�r�W�[�`�F�b�N		*/
		lcdwrite1data( c );
	}
}

/*----------------------------------------------------------*/
/* �֐���	:lcdwriteinit()									*/
/* �@�\		:LCD�����ݒ�R�}���h�Z�b�g					    */
/*----------------------------------------------------------*/
void lcdwriteinit( unsigned char command )
{
	
	/*===�����l�Z�b�g===*/
	p6_0 = 0x0;		/*	RS�|0(�R�}���h�w��)	*/
	p6_1 = 0x0;		/*	E�|0				*/
	p8_7 = 0x0;		/*	RW�|0(W�w��)		*/

	/*===�|�[�g�������W�X�^���o�͂ɐݒ�===*/
	pd6 |= 0x03;
	pd8_7 = 1;

	prc2 = 1;		/*	pd9�ւ̏������݋���	*/
	pd9 = 0x0F;
//	pd9 |= 0x0F;

	command &= 0x0f;	/*	�R���g���[���f�[�^�Z�b�g(��������jRW�|0(W�w��) RS�|0(�R�}���h�w��jE�|0 */
	BitSetP9(command);
//	p9 = command;		/*	�R���g���[���f�[�^�o��	*/
//	p9 |= command;		/*	�R���g���[���f�[�^�o��	*/
	
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
	p8_7 = 0x0;		/*	RW�|0(W�w��)		*/

	/*===�|�[�g�������W�X�^���o�͂ɐݒ�===*/
	pd6 |= 0x03;
	pd8_7 = 1;

	prc2 = 1;		/*	pd9�ւ̏������݋���	*/
	pd9 = 0x0F;
//	pd9 |= 0x0F;

	outcommand = command>>4;	/*	���4�r�b�g������4�r�b�g��	*/
	outcommand &= 0x0f;			/*	�}�X�N����					*/
	BitSetP9(outcommand);
//	p9 = outcommand;			/*	1�R�}���h�f�[�^���4�r�b�g���o�́@RW�|0(W�w��) RS�|0(�R�}���h�w��jE�|0 */
//	p9 |= outcommand;			/*	1�R�}���h�f�[�^���4�r�b�g���o�́@RW�|0(W�w��) RS�|0(�R�}���h�w��jE�|0 */

	LCDE = HIGH;				/*	E�|�P						*/
#pragma ASM						/*	�A�Z���u���\�L				*/
	NOP							/*	���Ԓ����ׂ̈�NOP			*/
	NOP
	NOP
	NOP
#pragma ENDASM					/*	�A�Z���u���\�L�I��			*/
	LCDE = LOW;					/*	E�|0						*/
	outcommand = command&0x0f;	/*	�R�}���h�f�[�^�̉���4�r�b�g���o(���4�r�b�g�}�X�N)	*/
	BitSetP9(outcommand);
//	p9 = outcommand;			/*	�R�}���h�f�[�^����4�r�b�g���o��						*/
//	p9 |= outcommand;			/*	�R�}���h�f�[�^����4�r�b�g���o��						*/
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
	p8_7 = 0x0;		/*	RW�|0(W�w��)		*/

	/*===�|�[�g�������W�X�^���o�͂ɐݒ�===*/
	pd6 |= 0x03;
	pd8_7 = 1;

	prc2 = 1;		/*	pd9�ւ̏������݋���	*/
	pd9 = 0x0F;
//	pd9 |= 0x0F;

	lcddata = data>>4;		/*	LCD�f�[�^���4�r�b�g������4�r�b�g��	*/
	lcddata &= 0x0f;		/*	�}�X�N����					*/

	BitSetP9(lcddata);
//	p9 = lcddata;			/*	LCD�f�[�^���4�r�b�g���o��	*/
//	p9 |= lcddata;			/*	LCD�f�[�^����4�r�b�g���o��	*/
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

	BitSetP9(lcddata);
//	p9 = lcddata;			/*	LCD�f�[�^����4�r�b�g���o��	*/
//	p9 |= lcddata;			/*	LCD�f�[�^����4�r�b�g���o��	*/
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
	p8_7 = 0x0;		/*	RW�|0(W�w��)		*/
	
	/*===�|�[�g�������W�X�^���o�͂ɐݒ�===*/
	pd6 |= 0x03;
	pd8_7 = 1;

	prc2 = 1;		/*	pd9�ւ̏������݋���	*/
	pd9 = 0x00;
//	pd9 &= 0xF0;
	
	LCDRW = HIGH;	/*	RW�|1(R�w��)		*/

	LCDE = HIGH;			/*	E�|1				*/
#pragma ASM					/*	�A�Z���u���\�L		*/
	NOP						/*	���Ԓ����ׂ̈�NOP	*/
	NOP
	NOP
	NOP
#pragma ENDASM				/*	�A�Z���u���\�L�I��	*/
	command_high = p9;		/*	�R�}���h���4�r�b�g�ǂݍ���	*/
//	command_high = p9|0xF0;		/*	�R�}���h���4�r�b�g�ǂݍ���	*/
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
//	command_low = p9|0xF0;		/*	�R�}���h����4�r�b�g�ǂݍ���	*/
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

void BitSetP9(char command)
{
	if(command & 0x01) p9_0 = 1;
	else p9_0 = 0;
	if(command & 0x02) p9_1 = 1;
	else p9_1 = 0;
	if(command & 0x04) p9_2 = 1;
	else p9_2 = 0;
	if(command & 0x08) p9_3 = 1;
	else p9_3 = 0;
}

///////////////////////////////end
