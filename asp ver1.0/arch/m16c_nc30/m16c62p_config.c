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
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
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
 * 
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 */

/*
 *		�v���Z�b�T�ˑ����W���[���iM16C�p�j
 */

#include "kernel_impl.h"

/*
 *  �����ݗv�����C���̑����̐ݒ�(�v���Z�b�T�ˑ���)
 */
void
m16c_config_int(INTNO intno)
{
	/* �����ݗv���I�����W�X�^��ݒ肷�� */
	switch(intno)
	{
		case	TINTNO_INT0:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x01;
		break;
		case	TINTNO_INT1:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x02;
		break;
		case	TINTNO_INT2:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x04;
		break;
		case	TINTNO_INT3:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x08;
		break;
		case	TINTNO_INT4:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x10;
		break;
		case	TINTNO_INT5:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x20;
		break;
		default:
		/* INT�����݈ȊO�̓R���t�B�M�����[�^�ňُ�Ƃ���B */
		break;
	}
}

/* �����ݗv�����W�X�^ */
volatile uint8_t * const intc_reg[INHNO_MAX] = 
{
	/* 0- */
	NULL ,	/* BRK */
	NULL ,	/* Reserve */
	NULL ,	/* Reserve */
	NULL ,	/* Reserve */
	(volatile uint8_t *)TADR_SFR_INT3IC ,	/* INT3	*/
	(volatile uint8_t *)TADR_SFR_TB5IC ,	/* �^�C�}B5	*/
	(volatile uint8_t *)TADR_SFR_TB4IC ,	/* �^�C�}B4	*/
	(volatile uint8_t *)TADR_SFR_TB3IC ,	/* �^�C�}B3	*/
	/* 8- */
	(volatile uint8_t *)TADR_SFR_INT5IC ,	/* SIO4,INT5 */
	(volatile uint8_t *)TADR_SFR_INT4IC ,	/* SIO3,INT4 */
	(volatile uint8_t *)TADR_SFR_BCNIC ,	/* UART�o�X�Փˌ��o */
	(volatile uint8_t *)TADR_SFR_DM0IC ,	/* DMA0 */
	(volatile uint8_t *)TADR_SFR_DM1IC ,	/* DMA1 */
	(volatile uint8_t *)TADR_SFR_KUPIC ,	/* �L�[���͊����� */
	(volatile uint8_t *)TADR_SFR_ADIC  ,	/* A/D */
	(volatile uint8_t *)TADR_SFR_S2TIC ,	/* UART2���M */
	/* 16- */
	(volatile uint8_t *)TADR_SFR_S2RIC ,	/* UART2��M */
	(volatile uint8_t *)TADR_SFR_S0TIC ,	/* UART0���M */
	(volatile uint8_t *)TADR_SFR_S0RIC ,	/* UART0��M */
	(volatile uint8_t *)TADR_SFR_S1TIC ,	/* UART1���M */
	(volatile uint8_t *)TADR_SFR_S1RIC ,	/* UART1��M */
	(volatile uint8_t *)TADR_SFR_TA0IC ,	/* �^�C�}A0	*/
	(volatile uint8_t *)TADR_SFR_TA1IC ,	/* �^�C�}A1	*/
	(volatile uint8_t *)TADR_SFR_TA2IC ,	/* �^�C�}A2	*/
	/* 24- */
	(volatile uint8_t *)TADR_SFR_TA3IC ,	/* �^�C�}A3	*/
	(volatile uint8_t *)TADR_SFR_TA4IC ,	/* �^�C�}A4	*/
	(volatile uint8_t *)TADR_SFR_TB0IC ,	/* �^�C�}B0	*/
	(volatile uint8_t *)TADR_SFR_TB1IC ,	/* �^�C�}B1	*/
	(volatile uint8_t *)TADR_SFR_TB2IC ,	/* �^�C�}B2	*/
	(volatile uint8_t *)TADR_SFR_INT0IC ,	/* INT0	*/
	(volatile uint8_t *)TADR_SFR_INT1IC ,	/* INT1	*/
	(volatile uint8_t *)TADR_SFR_INT2IC ,	/* INT2	*/
	/* 32- */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	/* 40- */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	/* 48- */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	/* 56- */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
};
