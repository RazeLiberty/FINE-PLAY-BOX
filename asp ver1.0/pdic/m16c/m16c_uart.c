/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́C�ȉ���(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F
 *  �A�i�{�\�t�g�E�F�A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E��
 *  �ρE�Ĕz�z�i�ȉ��C���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
 *      �ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
 *        �񍐂��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *      �܂��C�{�\�t�g�E�F�A�̃��[�U�܂��̓G���h���[�U����̂����Ȃ闝
 *      �R�Ɋ�Â�����������C��L���쌠�҂����TOPPERS�v���W�F�N�g��
 *      �Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC����̎g�p�ړI
 *  �ɑ΂���K�������܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F
 *  �A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C��
 *  �̐ӔC�𕉂�Ȃ��D
 * 
 */


/*
 *   M16C UART�p �Ȉ�SIO�h���C�o
 */

#include <sil.h>
#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "m16c_uart.h"

/* ����M���䃌�W�X�^0 */
#define CRS			UINT_C(0x04)
#define TXEPT		UINT_C(0x08)
#define CRD			UINT_C(0x10)
#define NCH			UINT_C(0x20)
#define CKPOL		UINT_C(0x40)
#define UFORM		UINT_C(0x80)

/* ����M���䃌�W�X�^1 */

#define TE			UINT_C(0x01)
#define TI			UINT_C(0x02)
#define RE			UINT_C(0x04)
#define RI			UINT_C(0x08)
#define IRS			UINT_C(0x10)
#define RRM			UINT_C(0x20)
#define LCH			UINT_C(0x40)
#define SCLKSTPB	UINT_C(0x80)

/* ����M���[�h���W�X�^ */
#define NO_USE		UINT_C(0x00)
#define SYNC		UINT_C(0x01)
#define IIC			UINT_C(0x10)
#define ASYNC_7BIT	UINT_C(0x04)
#define ASYNC_8BIT	UINT_C(0x05)
#define ASYNC_9BIT	UINT_C(0x06)
#define CKDIR		UINT_C(0x08)
#define STPS		UINT_C(0x10)
#define ODDEVEN		UINT_C(0x20)
#define PARITY		UINT_C(0x40)
#define IOPOL		UINT_C(0x80)

/* UART��M�o�b�t�@ */
#define RXDATA		UINT_C(0x00ff)
#define ABT			UINT_C(0x0400)
#define OER			UINT_C(0x1000)
#define FER			UINT_C(0x2000)
#define PER			UINT_C(0x4000)
#define SUM			UINT_C(0x8000)

/*
 *  �V���A��I/O�|�[�g�������u���b�N�̒�`
 */
typedef struct sio_port_initialization_block {
	volatile uint8_t	*ctlreg0 , *ctlreg1;	/* ����M���䃌�W�X�^0,1 */
	volatile uint8_t	*modereg;				/* ����M���[�h���W�X�^ */
	volatile uint8_t	*baudratereg;			/* �]�����x���W�X�^ */
	volatile uint16_t	*txbufreg;				/* ���M�o�b�t�@ */
	volatile uint16_t	*rxbufreg;				/* ��M�o�b�t�@ */
	uint8_t		tx_intno;						/* ���M���荞�ݔԍ� */
	uint8_t		rx_intno;						/* ��M���荞�ݔԍ� */
} SIOPINIB;

/*
 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̒�`
 */
struct sio_port_control_block {
	const SIOPINIB	*p_siopinib; 				/* �V���A��I/O�|�[�g�������u���b�N */
	intptr_t 	exinf;			 				/* �g����� */
	bool_t		openflag;						/* �I�[�v���ς݃t���O */
	bool_t		sendflag;						/* ���M�����݃C�l�[�u���t���O */
	bool_t		getready;						/* ��������M������� */
	bool_t		putready;						/* �����𑗐M�ł����� */
	bool_t		is_initialized; 				/* �f�o�C�X�������ς݃t���O */
};

/*
 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̃G���A
 */
static SIOPCB	siopcb_table[TNUM_SIOP];

/* ���W�X�^�e�[�u�� */
static const SIOPINIB siopinib_table[TNUM_SIOP] =
{
	{
		(volatile uint8_t *)UART0_UC0_ADDR ,
		(volatile uint8_t *)UART0_UC1_ADDR ,
		(volatile uint8_t *)UART0_MODE_ADDR ,
		(volatile uint8_t *)UART0_BAUD_ADDR ,
		(volatile uint16_t *)UART0_TXBUF_ADDR ,
		(volatile uint16_t *)UART0_RXBUF_ADDR  ,
		UART0_TXINTNO ,
		UART0_RXINTNO ,
	} ,			/* UART0 */
#if TNUM_SIOP > 1
	{
		(volatile uint8_t *)UART1_UC0_ADDR ,
		(volatile uint8_t *)UART1_UC1_ADDR ,
		(volatile uint8_t *)UART1_MODE_ADDR ,
		(volatile uint8_t *)UART1_BAUD_ADDR ,
		(volatile uint16_t *)UART1_TXBUF_ADDR ,
		(volatile uint16_t *)UART1_RXBUF_ADDR ,
		UART1_TXINTNO ,
		UART1_RXINTNO	,
	} ,			/* UART1 */
#endif
#if TNUM_SIOP > 2
	{
		(volatile uint8_t *)UART2_UC0_ADDR ,
		(volatile uint8_t *)UART2_UC1_ADDR ,
		(volatile uint8_t *)UART2_MODE_ADDR ,
		(volatile uint8_t *)UART2_BAUD_ADDR ,
		(volatile uint16_t *)UART2_TXBUF_ADDR ,
		(volatile uint16_t *)UART2_RXBUF_ADDR ,
		UART2_TXINTNO , 
		UART2_RXINTNO	,
	} ,			/* UART2 */
#endif
#if TNUM_SIOP > 3
	{
		(volatile uint8_t *)UART3_UC0_ADDR ,
		(volatile uint8_t *)UART3_UC1_ADDR ,
		(volatile uint8_t *)UART3_MODE_ADDR ,
		(volatile uint8_t *)UART3_BAUD_ADDR ,
		(volatile uint16_t *)UART3_TXBUF_ADDR ,
		(volatile uint16_t *)UART3_RXBUF_ADDR  ,
		UART3_TXINTNO ,
		UART3_RXINTNO	,
	} ,			/* UART3 */
#endif
#if TNUM_SIOP > 4
	{
		(volatile uint8_t *)UART4_UC0_ADDR ,
		(volatile uint8_t *)UART4_UC1_ADDR ,
		(volatile uint8_t *)UART4_MODE_ADDR ,
		(volatile uint8_t *)UART4_BAUD_ADDR ,
		(volatile uint16_t *)UART4_TXBUF_ADDR ,
		(volatile uint16_t *)UART4_RXBUF_ADDR ,
		UART4_TXINTNO ,
		UART4_RXINTNO	,
	  } 			/* UART4 */
#endif
};

/*
 *  �V���A��I/O�|�[�gID����Ǘ��u���b�N�����o�����߂̃}�N��
 */
#define INDEX_SIOP(siopid)	 ((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	 (&(siopcb_table[INDEX_SIOP(siopid)]))
#define get_siopinib(siopid) (&(siopinib_table[INDEX_SIOP(siopid)]))


static void m16c_uart_setmode(const SIOPINIB *p_siopinib , uint8_t baud , uint8_t clksrc)
{
	/* ����M�֎~ */
	sil_wrb_mem(p_siopinib->ctlreg1 , 0x00U);
	
	/* ���[�h���W�X�^�A����M���W�X�^0�A1�̏����� */
	sil_wrb_mem(p_siopinib->modereg , ASYNC_8BIT);
	sil_wrb_mem(p_siopinib->ctlreg0 , clksrc | CRD);
	sil_wrb_mem(p_siopinib->ctlreg1 , (TE | RE));
	
	/* �{�[���[�g�ݒ� */
	sil_wrb_mem(p_siopinib->baudratereg , baud);
}

/*
 *  SIO�h���C�o�̏��������[�`��
 */
void m16c_uart_initialize(void)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  �V���A��I/O�|�[�g�Ǘ��u���b�N�̏�����
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++)
	{
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->openflag = false;
		p_siopcb->sendflag = false;
	}
}

/*
 * �J�[�l���N�����̃o�i�[�o�͗p�̏�����
 */
void m16c_uart_init(ID siopid , uint8_t baud , uint8_t clksrc)
{
	SIOPCB          *p_siopcb   = get_siopcb(siopid);
	const SIOPINIB  *p_siopinib = get_siopinib(siopid);
	/*  ���̎��_�ł́Ap_siopcb->p_siopinib�͏���������Ă��Ȃ�  */
	
	/*  ��d�������̖h�~  */
	p_siopcb->is_initialized = true;
	
	/*  �n�[�h�E�F�A�̏����������Ƒ��M����  */
	m16c_uart_setmode(p_siopinib , baud , clksrc);
	sil_wrb_mem(p_siopinib->ctlreg1 , (sil_reb_mem(p_siopinib->ctlreg1) | TE));
}

/*
 *  �V���A��I/O�|�[�g�ւ̃|�[�����O�ł̏o��
 */
void m16c_uart_pol_putc(char c, ID siopid)
{
	const SIOPINIB *p_siopinib;
	
	p_siopinib = get_siopinib(siopid);
	
	while((sil_reb_mem(p_siopinib->ctlreg1) & TI) == 0)
		;
	sil_wrh_mem(p_siopinib->txbufreg , (uint16_t)c);
}

/*
 *  �V���A��I/O�|�[�g�̃I�[�v��
 */
SIOPCB *m16c_uart_opn_por
	(ID siopid, intptr_t exinf , uint8_t baud , uint8_t clksrc)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;
	
	p_siopcb = get_siopcb(siopid);
	p_siopinib = p_siopcb->p_siopinib;
	
	/*
	*  �n�[�h�E�F�A�̏�����     
	*  ���ɏ��������Ă���ꍇ�́A��d�ɏ��������Ȃ��B
	*/
	if (!(p_siopcb->is_initialized))
	{
		m16c_uart_setmode(p_siopinib , baud , clksrc);
		p_siopcb->is_initialized = true;
	}
	
	p_siopcb->exinf = exinf;
	p_siopcb->getready = p_siopcb->putready = false;
	p_siopcb->openflag = true;
	
    return(p_siopcb);
}

/*
 *  �V���A��I/O�|�[�g�̃N���[�Y
 */
void m16c_uart_cls_por(SIOPCB *p_siopcb)
{
	/*
	 * UART��~
	 */
	sil_wrh_mem(p_siopcb->p_siopinib->ctlreg1, 0x00U);
	p_siopcb->openflag = false;
	p_siopcb->is_initialized = false;
}

/*
 *  �V���A��I/O�|�[�g�ւ̕������M
 */
bool_t m16c_uart_snd_chr(SIOPCB *p_siopcb, char_t c)
{
	bool_t ercd = false;
	
	if ((sil_reb_mem(p_siopcb->p_siopinib->ctlreg1) & TI) != 0)
	{
		sil_wrh_mem(p_siopcb->p_siopinib->txbufreg , (uint16_t)c);
		ercd = true;
	}
	return ercd;
}

/*
 *  �V���A��I/O�|�[�g����̕�����M
 */
int_t m16c_uart_rcv_chr(SIOPCB *p_siopcb)
{
	int_t c = -1;
	
	if ((sil_reb_mem(p_siopcb->p_siopinib->ctlreg1) & RI) != 0)
	{
		c = (int)(sil_reh_mem(p_siopcb->p_siopinib->rxbufreg) & RXDATA);
	}
	return c;
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋���
 */
void  m16c_uart_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
		case SIO_RDY_SND:
			ena_int(p_siopcb->p_siopinib->tx_intno);
			break;
		case SIO_RDY_RCV:
			ena_int(p_siopcb->p_siopinib->rx_intno);
			break;
		default:
			assert(1);
			break;
	}
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋֎~
 */
void m16c_uart_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
		case SIO_RDY_SND:
			dis_int(p_siopcb->p_siopinib->tx_intno);
			break;
		case SIO_RDY_RCV:
			dis_int(p_siopcb->p_siopinib->rx_intno);
			break;
		default:
			assert(1);
			break;
	}
}

/*
 *  SIO�̊����݃T�[�r�X���[�`��
 */
void m16c_uart_tx_isr(ID siopid)
{
	SIOPCB	*p_siopcb = get_siopcb(siopid);

	if ((sil_reb_mem(p_siopcb->p_siopinib->ctlreg1) & TI) != 0U)
	{
		/*
		 *  ���M�\�R�[���o�b�N���[�`�����Ăяo���D
		 */
		m16c_uart_irdy_snd(p_siopcb->exinf);
	}
}

void m16c_uart_rx_isr(ID siopid)
{
	SIOPCB	*p_siopcb = get_siopcb(siopid);

	if ((sil_reb_mem(p_siopcb->p_siopinib->ctlreg1) & RI) != 0U)
	{
		/*
		 *  ��M�ʒm�R�[���o�b�N���[�`�����Ăяo���D
		 */
		m16c_uart_irdy_rcv(p_siopcb->exinf);
	}
}

