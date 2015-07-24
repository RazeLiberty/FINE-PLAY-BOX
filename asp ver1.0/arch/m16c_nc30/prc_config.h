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
 *
 *  ���̃C���N���[�h�t�@�C���́Ctarget_config.h�i�܂��́C��������C���N
 *  ���[�h�����t�@�C���j�݂̂���C���N���[�h�����D���̃t�@�C������
 *  ���ڃC���N���[�h���Ă͂Ȃ�Ȃ��D
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �v���Z�b�T�̓��ꖽ�߂̃C�����C���֐���`
 */
#include "prc_insn.h"
#include "interrupt.h"


/*
 *  ��^�X�N�R���e�L�X�g�p�̃X�^�b�N�����l
 */

#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char_t *)(istk) + (istksz)))

/*
 *  �^�X�N�R���e�L�X�g�u���b�N�̒�`
 */
typedef struct task_context_block {
	void		*sp;		/* �X�^�b�N�|�C���^ */
	uint32_t	pc;			/* �v���O�����J�E���^ */
} CTXB;

/*
 *  �����ݔ����񐔂�ۑ�����ϐ�
 */
extern uint16_t intnest;


/*
 *  CPU���b�N��Ԃł̊����ݗD��x�}�X�N
 *
 *  TIPM_LOCK�́CCPU���b�N��Ԃł̊����ݗD��x�}�X�N�C���Ȃ킿�C�J�[�l
 *  ���Ǘ��O�̂��̂��������ׂĂ̊����ݗv�����}�X�N����l�ɒ�`����D
 *
 *  �Ⴆ��TIPM_LOCK��-6�ɐݒ肷��ƁC���x��7�̊����݂��J�[�l���Ǘ��O��
 *  �Ȃ�DTIPM_LOCK��-7�ɐݒ肷��ƁCNMI�ȊO�ɃJ�[�l���Ǘ��O�̊����݂�
 *  �݂��Ȃ����ƂɂȂ�i���̏ꍇ�ɂ�-7�ɐݒ肷�邱�Ƃ𐄏�����j�D
 */
#ifndef TIPM_LOCK
#define TIPM_LOCK	(-7)		/* �J�[�l���Ǘ��O�̊����݂�݂��Ȃ� */
#endif /* TIPM_LOCK */

/*
 *  TOPPERS�W�������ݏ������f���̎���
 *
 */

/*
 *  �R���e�L�X�g�̎Q��
 *
 *  M16C�ł́C�����݂̖߂�悪�^�X�N���ǂ����𔻒f���邽�߂� intnest
 *  ���g�p���Ă���D�����p���ăR���e�L�X�g�𔻒f����D
 */
Inline bool_t
sense_context(void)
{
	/*  �l�X�g�J�E���^0����Ȃ��^�X�N�R���e�L�X�g  */
	return (intnest > 0);
}

/*
 *  CPU���b�N�t���O�����̂��߂̕ϐ�
 *
 *  �����̕ϐ��́CCPU���b�N��Ԃ̎��̂ݏ��������Ă悢���̂Ƃ���D
 */
#if TIPM_LOCK != -7
extern bool_t		lock_flag;		/* CPU���b�N�t���O�̒l��ێ�����ϐ� */
extern uint16_t	saved_ipl;		/* �����ݗD��x���x����ۑ�����ϐ� */
#endif	/* TIPM_LOCK != -7	*/

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����ݗD��x�}�X�N�̊O���\���Ɠ����\���̕ϊ�
 *
 *  M16C�ł́C�t���O���W�X�^�iFLG�j�̉�����12�`14�r�b�g�ڂ�3�r�b�g��
 *  �����ݗD��x���x���iIPL�j���u����Ă���D
 *  �J�[�l���Ǘ��O�����݂���������ꍇ��IPL���g�p����������s���D
 *  �J�[�l���͊����ݗD��x�}�X�N�i-1����A���������̒l�j�ŊǗ������
 *  ���邽��IPL�Ƃ̕ϊ����K�v�ƂȂ�D
 */
#define IPL2IPM(ipl)	(-((PRI)((ipl) >> 12)))			/* IPL��IPM��	*/
#define IPM2IPL(ipm)	(((uint16_t)(-(ipm))) << 12)	/* IPM��IPL��	*/


/*
 *  CPU���b�N��Ԃł̊����ݗD��x�}�X�N��IPL
 */
#define IPL_LOCK	(IPM2IPL(TIPM_LOCK))

/*
 *  TIPM_ENAALL�i�����ݗD��x�}�X�N�S�����j��IPL
 */
#define IPL_ENAALL		(IPM2IPL(TIPM_ENAALL))

#ifndef TOPPERS_MACRO_ONLY

/*
 *  CPU���b�N��Ԃւ̈ڍs
 *
 *  IPM�i�n�[�h�E�F�A�̊����ݗD��x�}�X�N�j���Csaved_iipm�ɕۑ����C�J�[
 *  �l���Ǘ��O�̂��̂��������ׂĂ̊����ݗv�����}�X�N����l�iTIPM_LOCK�j
 *  �ɐݒ肷��D�܂��Clock_flag��true�ɂ���D
 *
 *  IPM���C�ŏ�����TIPM_LOCK�Ɠ����������荂���ꍇ�ɂ́C�����
 *  saved_iipm�ɕۑ�����݂̂ŁCTIPM_LOCK�ɂ͐ݒ肵�Ȃ��D����́C���f��
 *  ��̊����ݗD��x�}�X�N���CTIPM_LOCK�Ɠ����������荂�����x���ɐݒ�
 *  ����Ă����Ԃɂ�����D
 *
 *  ���̊֐��́CCPU���b�N��ԁilock_flag��true�̏�ԁj�ŌĂ΂�邱�Ƃ�
 *  �Ȃ����̂Ƒz�肵�Ă���D
 */
Inline void
x_lock_cpu(void)
{
#if TIPM_LOCK == -7
	disint();
#else	/* TIPM_LOCK == -7	*/
	uint16_t	ipl;

	/*
	 *  current_ipl()�̕Ԃ�l�𒼐�saved_ipl�ɕۑ������C�ꎞ�ϐ�ipl
	 *  ��p���Ă���̂́Ccurrent_ipl()���Ă񂾒���Ɋ����݂��������C
	 *  �N�����ꂽ�����ݏ�����saved_ipl���ύX�����\�������邽�߂�
	 *  ����D
	 */
	ipl = current_ipl();
	if (IPL_LOCK > ipl) {
		set_ipl(IPL_LOCK);
	}
	saved_ipl = ipl;
	lock_flag = true;
#endif	/* TIPM_LOCK == -7	*/
}

#define t_lock_cpu()	x_lock_cpu()
#define i_lock_cpu()	x_lock_cpu()

/*
 *  CPU���b�N��Ԃ̉���
 *
 *  lock_flag��false�ɂ��CIPM�i�n�[�h�E�F�A�̊����ݗD��x�}�X�N�j���C
 *  saved_iipm�ɕۑ������l�ɖ߂��D
 *
 *  ���̊֐��́CCPU���b�N��ԁilock_flag��true�̏�ԁj�ł̂݌Ă΂���
 *  �̂Ƒz�肵�Ă���D
 */
Inline void
x_unlock_cpu(void)
{
#if TIPM_LOCK == -7
	enaint();
#else	/* TIPM_LOCK == -7	*/
	lock_flag = false;
	set_ipl(saved_ipl);
#endif	/* TIPM_LOCK == -7	*/
}

#define t_unlock_cpu()	x_unlock_cpu()
#define i_unlock_cpu()	x_unlock_cpu()

/*
 *  CPU���b�N��Ԃ̎Q��
 */
Inline bool_t
x_sense_lock(void)
{
#if TIPM_LOCK == -7
	return((bool_t)((current_flgreg() & FLG_I_MASK) == 0));
#else	/* TIPM_LOCK == -7	*/
	return lock_flag;
#endif	/* TIPM_LOCK == -7	*/
}

#define t_sense_lock()	x_sense_lock()
#define i_sense_lock()	x_sense_lock()

/*
 * �i���f����́j�����ݗD��x�}�X�N�̐ݒ�
 *
 *  CPU���b�N�t���O���N���A����Ă��鎞�́C�n�[�h�E�F�A�̊����ݗD��x�}
 *  �X�N��ݒ肷��DCPU���b�N�t���O���Z�b�g����Ă��鎞�́Csaved_iipm
 *  ��ݒ肵�C����ɁC�n�[�h�E�F�A�̊����ݗD��x�}�X�N���C�ݒ肵�悤��
 *  �����i���f����́j�����ݗD��x�}�X�N��TIPM_LOCK�̍������ɐݒ肷��D
 */
Inline void
x_set_ipm(PRI intpri)
{
	set_ipl((current_ipl() & ~FLG_IPL_MASK) | IPM2IPL(intpri));
}

#define t_set_ipm(intpri)	x_set_ipm(intpri)
#define i_set_ipm(intpri)	x_set_ipm(intpri)

/*
 * �i���f����́j�����ݗD��x�}�X�N�̎Q��
 *
 *  CPU���b�N�t���O���N���A����Ă��鎞�̓n�[�h�E�F�A�̊����ݗD��x�}
 *  �X�N���C�Z�b�g����Ă��鎞��saved_iipm���Q�Ƃ���D
 */
Inline PRI
x_get_ipm(void)
{
	return IPL2IPM(current_ipl() & FLG_IPL_MASK);
}

#define t_get_ipm()	x_get_ipm()
#define i_get_ipm()	x_get_ipm()


/*
 *  �����ݔԍ��͈̔͂̔���
 */
#define VALID_INTNO(intno)	((intno) < INHNO_MAX)
#define VALID_INTNO_DISINT(intno)	VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)	VALID_INTNO(intno)

/*
 *  IPL���犄���ݐ��䃌�W�X�^�ł̕\���ɕϊ�����}�N��
 */
#define IPL2ILVL(ipl)	(-(ipl))

/*
 *  �����݃R���g���[�����W�X�^�̃A�h���X�e�[�u��
 *  (target_config.c�ɒ�`)
 */
extern volatile uint8_t * const intc_reg[];

/*
 *  �����ݗv�����̃��x����`�e�[�u��
 *  (tf�ɂ��o��)
 */
extern const PRI intpri_table[];

/*
 *  �����ݐ��䃌�W�X�^�֘A�̒�`
 */
#define INTC_LVLMASK	(0x07U)
#define INTC_IRMASK		(0x08U)
#define INTC_POLMASK	(0x10U)		/* INT�����݂̂� */
#define INTC_LVSMASK	(0x20U)		/* INT�����݂̂� */

#define INTC_POLHIGH	(0x10U)		/* INT�����݂̂� */
#define INTC_POLLOW		(0x00U)		/* INT�����݂̂� */
#define INTC_LVSEDGE	(0x00U)		/* INT�����݂̂� */
#define INTC_LVSLVL		(0x20U)		/* INT�����݂̂� */

/*
 *  �����ݗv���֎~�t���O�̃Z�b�g
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���Z�b�g���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	/* ���x����`��0�ł���ꍇ��CFG_INT����Ă��Ȃ� */
	if(intpri_table[intno] == 0U)
	{
		return (false);
	}
	*intc_reg[intno] &= ~INTC_LVLMASK;

	return(true);
}

#define t_disable_int(intno)	x_disable_int(intno)
#define i_disable_int(intno)	x_disable_int(intno)

/*
 *  �����ݗv���֎~�t���O�̃N���A
 *
 *  �����ݑ������ݒ肳��Ă��Ȃ������ݗv�����C���ɑ΂��Ċ����ݗv���֎~
 *  �t���O���N���A���悤�Ƃ����ꍇ�ɂ́Cfalse��Ԃ��D
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	/* ���x����`��0�ł���ꍇ��CFG_INT����Ă��Ȃ� */
	if(intpri_table[intno] == 0U)
	{
		return (false);
	}
	/* �����݃��x�������ɖ߂� */
	*intc_reg[intno] = (*intc_reg[intno] & ~INTC_LVLMASK) | IPL2ILVL(intpri_table[intno]);
	
	return(true);
}

#define t_enable_int(intno)		x_enable_int(intno)
#define i_enable_int(intno)		x_enable_int(intno)

/*
 *  �����ݗv���̃N���A
 */
Inline void
x_clear_int(INTNO intno)
{
	*(intc_reg[intno]) &= ~INTC_IRMASK;
}

#define t_clear_int(intno)		x_clear_int(intno)
#define i_clear_int(intno)		x_clear_int(intno)

/*
 *  �����ݗv���̃`�F�b�N
 */
Inline bool_t
x_probe_int(INTNO intno)
{
	return (((*intc_reg[intno] & INTC_IRMASK) == INTC_IRMASK)? true : false);
}

#define t_probe_int(intno)		x_probe_int(intno)
#define i_probe_int(intno)		x_probe_int(intno)

/*
 *  �����ݗv�����C���̑����̐ݒ�
 */
extern void	x_config_int(INTNO intno, ATR intatr, PRI intpri);

/*
 *  �����݃n���h���̓����ŕK�v��IRC����
 *
 */
Inline void
i_begin_int(INTNO intno)
{
	/* ���ɍs���ׂ������͂Ȃ� */
}

/*
 *  �����݃n���h���̏o���ŕK�v��IRC����
 *
 */
Inline void
i_end_int(INTNO intno)
{
	/* ���ɍs���ׂ������͂Ȃ� */
}


/*
 *  �ō��D�揇�ʃ^�X�N�ւ̃f�B�X�p�b�`�iprc_support.a30�j
 *
 *  dispatch�́C�^�X�N�R���e�L�X�g����Ăяo���ꂽ�T�[�r�X�R�[��������
 *  ��Ăяo���ׂ����̂ŁC�^�X�N�R���e�L�X�g�ECPU���b�N��ԁE�f�B�X�p�b
 *  �`����ԁE�i���f����́j�����ݗD��x�}�X�N�S������ԂŌĂяo����
 *  ����΂Ȃ�Ȃ��D
 */
extern void	dispatch(void);

/*
 *  �f�B�X�p�b�`���̓���J�n�iprc_support.a30�j
 *
 *  start_dispatch�́C�J�[�l���N�����ɌĂяo���ׂ����̂ŁC�S�Ă̊�����
 *  ���֎~������ԁi�S�����݃��b�N��ԂƓ����̏�ԁj�ŌĂяo���Ȃ����
 *  �Ȃ�Ȃ��D
 */
extern void	start_dispatch(void) NoReturn;

/*
 *  ���݂̃R���e�L�X�g���̂Ăăf�B�X�p�b�`�iprc_support.a30�j
 *
 *  exit_and_dispatch�́Cext_tsk����Ăяo���ׂ����̂ŁC�^�X�N�R���e�L
 *  �X�g�ECPU���b�N��ԁE�f�B�X�p�b�`����ԁE�i���f����́j�����ݗD��
 *  �x�}�X�N�S������ԂŌĂяo���Ȃ���΂Ȃ�Ȃ��D
 */
#define _kernel_exit_and_dispatch();	\
	_exit_and_dispatch();		\
	ercd = E_SYS;
extern void	_exit_and_dispatch(void) NoReturn;

/*
 *  �J�[�l���̏I�������̌ďo���iprc_support.a30�j
 *
 *  call_exit_kernel�́C�J�[�l���̏I�����ɌĂяo���ׂ����̂ŁC��^�X�N
 *  �R���e�L�X�g�ɐ؂芷���āC�J�[�l���̏I�������iexit_kernel�j���Ăяo
 *  ���D
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  �^�X�N�R���e�L�X�g�̏�����
 *
 *  �^�X�N���x�~��Ԃ�����s�ł����ԂɈڍs���鎞�ɌĂ΂��D���̎��_
 *  �ŃX�^�b�N�̈���g���Ă͂Ȃ�Ȃ��D
 *
 *  activate_context���C�C�����C���֐��ł͂Ȃ��}�N����`�Ƃ��Ă���̂́C
 *  ���̎��_�ł�TCB����`����Ă��Ȃ����߂ł���D
 */
extern void	start_r(void);
extern uint8_t *tsk_sp;

#define activate_context(p_tcb)																\
{																							\
	{																						\
		(p_tcb)->tskctxb.sp = (void*)((uint32_t)(p_tcb)->p_tinib->stk + 					\
						(uint16_t)(p_tcb)->p_tinib->stksz);									\
		(p_tcb)->tskctxb.pc = (uint32_t)start_r;											\
	}																						\
}

/*
 *  calltex�͎g�p���Ȃ�
 */
#define OMIT_CALLTEX

/*
 *  �����݃n���h���̐ݒ�
 *
 *  M16C��ROM�Ɋ����݃x�N�^��z�u���邽�߁C�{�֐��͋�֐��Ŏ�������D
 */
Inline void
x_define_inh(INHNO inhno, FP inthdr)
{
}

/*
 *  CPU��O�n���h���̐ݒ�
 *
 *  M16C��ROM�ɗ�O�x�N�^��z�u���邽�߁C�{�֐��͋�֐��Ŏ�������D
 */
Inline void
x_define_exc(EXCNO excno, FP exchdr)
{
}

/*
 *  ������/��O�n���h���̓��������̐����}�N��
 *
 *  �e���v���[�g�t�@�C���ɂ�萶�����邽�ߋ�}�N���Ƃ���D
 */
#define HDR_ENTRY(hdr, intexc_num , tobejmp)

/*
 *  �����݃n���h���̓��������̐����}�N��
 */
#define _INT_ENTRY(inhno, inthdr)				_kernel_##inthdr##_##inhno##_entry
#define INT_ENTRY(inhno, inthdr)				_INT_ENTRY(inhno , inthdr)

#define _INTHDR_ENTRY(inhno, inhno_num ,inthdr)	\
		extern _kernel_##inthdr##_##inhno##_entry(void);
#define INTHDR_ENTRY(inhno, inhno_num ,inthdr)	_INTHDR_ENTRY(inhno, inhno_num ,inthdr)

/*
 *  CPU��O�n���h���̓��������̐����}�N��
 */
#define _EXC_ENTRY(excno , exchdr)					_kernel_##exchdr##_##excno##_entry
#define EXC_ENTRY(excno , exchdr)					_EXC_ENTRY(excno , exchdr)

#define _EXCHDR_ENTRY(excno , excno_num , exchdr)	\
		extern _kernel_##exchdr##_##excno##_entry(void);
#define EXCHDR_ENTRY(excno , excno_num , exchdr)	_EXCHDR_ENTRY(excno , excno_num , exchdr)


/*
 *  CPU��O�̔����������̃R���e�L�X�g�̎Q��
 *
 *  CPU��O�̔����������̃R���e�L�X�g���C�^�X�N�R���e�L�X�g�̎���false�C
 *  �����łȂ�����true��Ԃ��D
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
	/* 
	 *  �l�X�g�J�E���^��1����Ȃ��^�X�N�R���e�L�X�g
	 */
	return( intnest > 1u );
}

/*
 *  CPU��O�̔�����������IPL�̎Q��
 */
Inline uint16_t
exc_get_ipl(void *p_excinf)
{
	return(((*((uint8_t *)((uintptr_t)p_excinf+19))) & 0x70U) >> 4u);
}

Inline bool_t
exc_sense_i(void *p_excinf)
{
	return((*((uint8_t *)((uintptr_t)p_excinf+18)) & 0x40U) != 0u);
}

/*
 *  CPU��O�̔����������̃R���e�L�X�g�Ɗ����݂̃}�X�N��Ԃ̎Q��
 *
 *  CPU��O�̔����������̃V�X�e����Ԃ��C�J�[�l�����s���łȂ��C�^�X�N�R
 *  ���e�L�X�g�ł���C�S�����݃��b�N��ԂłȂ��CCPU���b�N��ԂłȂ��C
 *  �i���f����́j�����ݗD��x�}�X�N�S������Ԃł��鎞��true�C�����ł�
 *  ������false��Ԃ��iCPU��O���J�[�l���Ǘ��O�̊����ݏ������Ŕ�������
 *  �ꍇ�ɂ�false��Ԃ��j�D
 *
 *  �J�[�l�����s���łȂ��� (TIPM_LOCK== -7) I�t���O == 0
 *                         (else)           IPL < IPL_LOCK
 *  �^�X�N�R���e�L�X�g�ł��遨intnest == 0
 *  �S�����݃��b�N�łȂ��� I�t���O == 0
 *  �����ݗD��x�}�X�N���S������IPL == 0
 *  
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return(!exc_sense_context(p_excinf)
			&& !exc_sense_i(p_excinf)
			&& (exc_get_ipl(p_excinf) == IPL_ENAALL));
}

/*
 *  CPU��O�̔����������̃R���e�L�X�g�Ɗ����݁^CPU���b�N��Ԃ̎Q��
 *
 *  CPU��O�̔����������̃V�X�e����Ԃ��C�J�[�l�����s���łȂ��C�^�X�N�R
 *  ���e�L�X�g�ł���C�S�����݃��b�N��ԂłȂ��CCPU���b�N��ԂłȂ���
 *  ��true�C�����łȂ�����false��Ԃ��iCPU��O���J�[�l���Ǘ��O�̊�����
 *  �������Ŕ��������ꍇ�ɂ�false��Ԃ��j�D
 *
 *  �J�[�l�����s���łȂ��� (TIPM_LOCK== -7) I�t���O == 0
 *                         (else)           IPL < TIPM_LOCK
 *  �^�X�N�R���e�L�X�g�ł��遨intnest < 1 
 *  �S�����݃��b�N�łȂ��� I�t���O == 0
 *  CPU���b�N��ԂłȂ���(TIPM_LOCK== -7) I�t���O == 0
 *                         (else)           IPL < TIPM_LOCK
 */
Inline bool_t
exc_sense_unlock(void *p_excinf)
{
#if TIPM_LOCK == -7
	return(!exc_sense_context(p_excinf)
			&& exc_sense_i(p_excinf));
#else
	return(!exc_sense_context(p_excinf)
			&& exc_sense_i(p_excinf)
			&& exc_get_ipl(p_excinf) < TIPM_LOCK);
#endif
}

/*
 *  �v���Z�b�T�ˑ��̏�����
 */
extern void	prc_initialize(void);

/*
 *  �v���Z�b�T�ˑ��̏I��������
 */
extern void	prc_terminate(void);


#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */