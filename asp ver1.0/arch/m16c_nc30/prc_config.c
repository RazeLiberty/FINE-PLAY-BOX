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
 *  �����ݔ����񐔂�ۑ�����ϐ�
 */
uint16_t intnest;

/* activate_context�Ŏg�p����ꎞ�ϐ� */
uint8_t *tsk_sp;

/*
 *  CPU���b�N�t���O�����̂��߂̕ϐ�
 */
#if TIPM_LOCK != -7
bool_t		lock_flag;		/* CPU���b�N�t���O�̒l��ێ�����ϐ� */
uint16_t	saved_ipl;		/* �����ݗD��x���x����ۑ�����ϐ� */
#endif	/* TIPM_LOCK != -7	*/

/*
 *  �v���Z�b�T�ˑ��̏�����
 */
void
prc_initialize(void)
{
	/*
	 *  CPU���b�N�t���O�����̂��߂̕ϐ��̏�����
	 */
#if TIPM_LOCK != -7
	lock_flag = true;
	saved_ipl = IPL_ENAALL;
#endif	/* TIPM_LOCK != -7	*/
}

/*
 *  �v���Z�b�T�ˑ��̏I������
 */
void
prc_terminate(void)
{
	/* ���ɕK�v�ȏ����͂Ȃ� */
}


/*
 *  CPU��O�̔����󋵂̃��O�o��
 *
 *  CPU��O�n���h���̒�����CCPU��O���|�C���^�ip_excinf�j�������Ƃ�
 *  �ČĂяo�����ƂŁCCPU��O�̔����󋵂��V�X�e�����O�ɏo�͂���D
 */
#ifdef SUPPORT_XLOG_SYS

void
xlog_sys(void *p_excinf)
{
	syslog(LOG_ERROR , "r0 = %u") , *((uint16_t*)((intptr_t)p_excinf + 0));
	syslog(LOG_ERROR , "r1 = %u") , *((uint16_t*)((intptr_t)p_excinf + 2));
	syslog(LOG_ERROR , "r2 = %u") , *((uint16_t*)((intptr_t)p_excinf + 4));
	syslog(LOG_ERROR , "r3 = %u") , *((uint16_t*)((intptr_t)p_excinf + 6));
	syslog(LOG_ERROR , "a0 = %x") , *((uint16_t*)((intptr_t)p_excinf + 8));
	syslog(LOG_ERROR , "a2 = %x") , *((uint16_t*)((intptr_t)p_excinf + 10));
	syslog(LOG_ERROR , "sb = %x") , *((uint16_t*)((intptr_t)p_excinf + 12));
	syslog(LOG_ERROR , "fb = %x") , *((uint16_t*)((intptr_t)p_excinf + 14));
	syslog(LOG_ERROR , "pc = %x") , *((uint32_t*)((intptr_t)p_excinf + 16));
	syslog(LOG_ERROR , "flg = %x") , *((uint16_t*)((intptr_t)p_excinf + 20));
}

#endif /* SUPPORT_XLOG_SYS */

/*
 *  �����ݗv�����C���̑����̐ݒ�
 *
 *  ASP�J�[�l���ł̗��p��z�肵�āC�p�����[�^�G���[�̓A�T�[�V�����Ń`�F�b
 *  �N���Ă���Dcfg_int�T�[�r�X�R�[����݂���ꍇ�ɂ́C�G���[��Ԃ��悤
 *  �ɂ��ׂ��ł��낤�D
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	assert(VALID_INTNO_CFGINT(intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);
	
	/*
	 *  �����݂̃}�X�N
	 *
	 *  �����݂��󂯕t�����܂܁C���x���g���K�^�G�b�W�g���K�̐ݒ��C��
	 *  ���ݗD��x�̐ݒ���s���̂͊댯�Ȃ��߁C�����ݑ����ɂ�����炸�C
	 *  ��U�}�X�N����D
	 */
	(void) x_disable_int(intno);
	
	/* INT�[�q�̏ꍇ�͊����݌��m���@��ݒ肷�� */
	/* ���x���g���K�AINT�����݈ȊO�̓R���t�B�O���[�^�ňُ�Ƃ���B */
	if((intatr & TA_POSEDGE) != 0U)
	{
		/* ���オ��G�b�W */
		*(intc_reg[intno]) |= INTC_POLHIGH;
	}
	else
	{
		/* ������G�b�W */
		*(intc_reg[intno]) &= ~INTC_POLHIGH;

		/* ���G�b�W */
		if((intatr & TA_BOTHEDGE) != 0U)
		{
			m16c_config_int(intno);
		}
	}

	/*
	 *  M16C�ł͊����݋֎~/���������ݗD��x�ݒ�Ŏ������邽�߁A
	 *  �����Ŋ����ݗD��x�̐ݒ�͍s��Ȃ�
	 */

	/*
	 *  �����݂̃}�X�N����
 	 */
	if ((intatr & TA_ENAINT) == TA_ENAINT) {
		(void) x_enable_int(intno);
	}
}
