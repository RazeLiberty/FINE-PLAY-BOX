/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2008 by Witz Corporation, JAPAN
 * 
 *  ��L���쌠�҂́CFree Software Foundation �ɂ���Č��\����Ă��� 
 *  GNU General Public License �� Version 2 �ɋL�q����Ă���������C��
 *  ����(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F
 *  �A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���ė��p�\�ȃo�C�i���R�[�h�i�����P�[�^�u���I�u
 *      �W�F�N�g�t�@�C���⃉�C�u�����Ȃǁj�̌`�ŗ��p����ꍇ�ɂ́C���p
 *      �ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C
 *      ���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���ė��p�s�\�ȃo�C�i���R�[�h�̌`�܂��͋@��ɑg
 *      �ݍ��񂾌`�ŗ��p����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂������ƁD
 *    (a) ���p�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒���
 *        ���\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *    (b) ���p�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āC��L���쌠�҂ɕ񍐂���
 *        ���ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂�Ɛӂ��邱�ƁD
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂́C
 *  �{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\�����܂߂āC�����Ȃ�ۏ؂��s��
 *  �Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ�������
 *  ���Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *	RSK-M16C-62P UART�p�V���A��I/O���W���[��
 */

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "RSK-M16C-62P.h"
#include "target_serial.h"

/*
 *  SIO�h���C�o�̏�����
 */
void
sio_initialize(intptr_t exinf)
{
#ifndef	USE_KD3083
	m16c_uart_initialize();
#endif
}

/*
 *  �V���A��I/O�|�[�g�̃I�[�v��
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB  *p_siopcb;
	ER      ercd;
	
	/*
	 *  �V���A��I/O�����݂��}�X�N����D
	 */
	ercd = dis_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
	ercd = dis_int(INTNO_SIO_RX);
	assert(ercd == E_OK);
	
#ifndef	USE_KD3083
	/*
	 *  �f�o�C�X�ˑ��̃I�[�v�������D
	 */
	p_siopcb = 
		m16c_uart_opn_por(siopid , exinf , UART_BAUDRATE , UART_CLKSRC);
	
	/*
	 *  �V���A��I/O�����݂̃}�X�N����������D
	 */
	ercd = ena_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
	ercd = ena_int(INTNO_SIO_RX);
	assert(ercd == E_OK);
#endif
	return(p_siopcb);
}

/*
 *  �V���A��I/O�|�[�g�̃N���[�Y
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	ER        ercd;
	
#ifndef	USE_KD3083
	/*
	 *  �f�o�C�X�ˑ��̃N���[�Y�����D
	 */
	m16c_uart_cls_por(p_siopcb);
#endif
	
	/*
	 *  �V���A��I/O�����݂��}�X�N����D
	 */
	ercd = dis_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
	ercd = dis_int(INTNO_SIO_RX);
	assert(ercd == E_OK);
}

/*
 *  SIO�̊����݃n���h��
 */
void
sio_tx_isr(intptr_t exinf)
{
#ifndef	USE_KD3083
	m16c_uart_tx_isr(exinf);
#endif
}


/*
 *  SIO�̊����݃n���h��
 */
void
sio_rx_isr(intptr_t exinf)
{
#ifndef	USE_KD3083
	m16c_uart_rx_isr(exinf);
#endif
}

/*
 *  �V���A��I/O�|�[�g�ւ̕������M
 */
bool_t
sio_snd_chr(SIOPCB *siopcb, char_t c)
{
#ifndef	USE_KD3083
	return(m16c_uart_snd_chr(siopcb, c));
#else
	return true;
#endif
}

/*
 *  �V���A��I/O�|�[�g����̕�����M
 */
int_t
sio_rcv_chr(SIOPCB *siopcb)
{
#ifndef	USE_KD3083
	return(m16c_uart_rcv_chr(siopcb));
#else
	return 0;
#endif
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋���
 */
void
sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
#ifndef	USE_KD3083
	m16c_uart_ena_cbr(siopcb, cbrtn);
#endif
}

/*
 *  �V���A��I/O�|�[�g����̃R�[���o�b�N�̋֎~
 */
void
sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
#ifndef	USE_KD3083
	m16c_uart_dis_cbr(siopcb, cbrtn);
#endif
}

/*
 *  �V���A��I/O�|�[�g����̑��M�\�R�[���o�b�N
 */
void
m16c_uart_irdy_snd(intptr_t exinf)
{
#ifndef	USE_KD3083
	sio_irdy_snd(exinf);
#endif
}

/*
 *  �V���A��I/O�|�[�g����̎�M�ʒm�R�[���o�b�N
 */
void
m16c_uart_irdy_rcv(intptr_t exinf)
{
#ifndef	USE_KD3083
	sio_irdy_rcv(exinf);
#endif
}

