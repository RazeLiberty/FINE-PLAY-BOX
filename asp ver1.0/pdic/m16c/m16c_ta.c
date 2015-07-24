/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
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

#include <sil.h>
#include "target_syssvc.h"
#include "m16c/m16c_ta.h"

/* �^�C�}���W�X�^��� */
typedef struct _M16C_TIMERREG
{
	volatile uint8_t	*mode;				/* �^�C�}���[�h���W�X�^ */
	volatile uint16_t	*counter;			/* �J�E���^���W�X�^ */
	volatile uint8_t	*start;				/* �J�E���g�J�n���W�X�^ */
	volatile uint8_t	*updown;			/* �A�b�v�J�E���g/�_�E���J�E���g�I�����W�X�^ */
	volatile uint8_t	*oneshot;			/* �����V���b�g�J�n���W�X�^ */
	volatile uint8_t	*trigsel;			/* �g���K�I�����W�X�^ */
	uint8_t				bitmsk;				/* �X�^�[�g���W�X�^����p�̃r�b�g�}�X�N */
	uint8_t				trig_bitmask;		/* �g���K�I�����W�X�^�p�̃r�b�g�ʒu�I�t�Z�b�g */
	uint8_t				intno;				/* ���荞�ݗv���ԍ� */
} M16C_TIMERREG;                    

/* ���W�X�^�e�[�u�� */
static M16C_TIMERREG const timerreg_table[TNUM_M16C_TA] =
{
	/* �^�C�}A0 */
	{
		(volatile uint8_t *)TA0MR_ADDR ,		/* �^�C�}���[�h���W�X�^ */
		(volatile uint16_t *)TA0_ADDR ,	/* �J�E���^���W�X�^ */
		(volatile uint8_t *)TABSR_ADDR ,	/* �J�E���g�J�n���W�X�^ */
		(volatile uint8_t *)UDF_ADDR ,		/* �A�b�v�J�E���g/�_�E���J�E���g�I�����W�X�^ */
		(volatile uint8_t *)ONSF_ADDR ,		/* �����V���b�g�J�n���W�X�^ */
		(volatile uint8_t *)ONSF_ADDR ,		/* �g���K�I�����W�X�^ */
		TA0_START_BIT ,						/* �J�E���g�J�n���W�X�^����p�r�b�g�}�X�N */
		TA0_TRIGSEL_OFFSET ,					/* �g���K�I�����W�X�^�p�̃r�b�g�ʒu�I�t�Z�b�g */
		(INT_TA0) ,							/* ���荞�ݗv���ԍ� */
	} ,
#if	TNUM_M16C_TA > 2
	/* �^�C�}A1 */
	{
		(volatile uint8_t *)TA1MR_ADDR ,		/* �^�C�}���[�h���W�X�^ */
		(volatile uint16_t *)TA1_ADDR ,	/* �J�E���^���W�X�^ */
		(volatile uint8_t *)TABSR_ADDR ,	/* �J�E���g�J�n���W�X�^ */
		(volatile uint8_t *)UDF_ADDR ,		/* �A�b�v�J�E���g/�_�E���J�E���g�I�����W�X�^ */
		(volatile uint8_t *)ONSF_ADDR ,		/* �����V���b�g�J�n���W�X�^ */
		(volatile uint8_t *)TAGSR_ADDR ,	/* �g���K�I�����W�X�^ */
		TA1_START_BIT ,						/* ���W�X�^����p�̃r�b�g�}�X�N */
		TA1_TRIGSEL_OFFSET ,				/* �g���K�I�����W�X�^�p�̃r�b�g�ʒu�I�t�Z�b�g */
		(INT_TA1) ,							/* ���荞�ݗv���ԍ� */
	} ,
#endif
#if	TNUM_M16C_TA > 3
	/* �^�C�}A2 */
	{
		(volatile uint8_t *)TA2MR_ADDR ,		/* �^�C�}���[�h���W�X�^ */
		(volatile uint16_t *)TA2_ADDR ,	/* �J�E���^���W�X�^ */
		(volatile uint8_t *)TABSR_ADDR ,	/* �J�E���g�J�n���W�X�^ */
		(volatile uint8_t *)UDF_ADDR ,		/* �A�b�v�J�E���g/�_�E���J�E���g�I�����W�X�^ */
		(volatile uint8_t *)ONSF_ADDR ,		/* �����V���b�g�J�n���W�X�^ */
		(volatile uint8_t *)TAGSR_ADDR ,	/* �g���K�I�����W�X�^ */
		TA2_START_BIT ,						/* ���W�X�^����p�̃r�b�g�}�X�N */
		TA2_TRIGSEL_OFFSET ,				/* �g���K�I�����W�X�^�p�̃r�b�g�ʒu�I�t�Z�b�g */
		(INT_TA2) ,							/* ���荞�ݗv���ԍ� */
	} ,
#endif
#if	TNUM_M16C_TA > 4
	/* �^�C�}A3 */
	{
		(volatile uint8_t *)TA3MR_ADDR ,		/* �^�C�}���[�h���W�X�^ */
		(volatile uint16_t *)TA3_ADDR ,	/* �J�E���^���W�X�^ */
		(volatile uint8_t *)TABSR_ADDR ,	/* �J�E���g�J�n���W�X�^ */
		(volatile uint8_t *)UDF_ADDR ,		/* �A�b�v�J�E���g/�_�E���J�E���g�I�����W�X�^ */
		(volatile uint8_t *)ONSF_ADDR ,		/* �����V���b�g�J�n���W�X�^ */
		(volatile uint8_t *)TAGSR_ADDR ,	/* �g���K�I�����W�X�^ */
		TA3_START_BIT ,						/* ���W�X�^����p�̃r�b�g�}�X�N */
		TA3_TRIGSEL_OFFSET ,				/* �g���K�I�����W�X�^�p�̃r�b�g�ʒu�I�t�Z�b�g */
		(INT_TA3) ,							/* ���荞�ݗv���ԍ� */
	} ,
#endif
#if	TNUM_M16C_TA > 5
	/* �^�C�}A4 */
	{
		(volatile uint8_t *)TA4MR_ADDR ,		/* �^�C�}���[�h���W�X�^ */
		(volatile uint16_t *)TA4_ADDR ,	/* �J�E���^���W�X�^ */
		(volatile uint8_t *)TABSR_ADDR ,	/* �J�E���g�J�n���W�X�^ */
		(volatile uint8_t *)UDF_ADDR ,		/* �A�b�v�J�E���g/�_�E���J�E���g�I�����W�X�^ */
		(volatile uint8_t *)ONSF_ADDR ,		/* �����V���b�g�J�n���W�X�^ */
		(volatile uint8_t *)TAGSR_ADDR ,	/* �g���K�I�����W�X�^ */
		TA4_START_BIT ,						/* ���W�X�^����p�̃r�b�g�}�X�N */
		TA4_TRIGSEL_OFFSET ,				/* �g���K�I�����W�X�^�p�̃r�b�g�ʒu�I�t�Z�b�g */
		(INT_TA3) ,							/* ���荞�ݗv���ԍ� */
	} ,
#endif
};

/*
 *  ���W�X�^���̎擾
 */
#define get_timerreg(ch)	(&(timerreg_table[(ch)]))

/*
 *  �^�C�}A�h���C�o�̏�����
 */
void m16c_ta_initialize(void)
{
	const M16C_TIMERREG *tmreg;
	uint8_t i;
	
	for(i = 0 ; i < TNUM_M16C_TA ; i++)
	{
		tmreg = get_timerreg(i);
		/* �^�C�}��~ */
		*(tmreg->start) &= ~(tmreg->bitmsk);
	}
	
}

/*
 *  �^�C�}A�h���C�o�̏I��
 */
void m16c_ta_terminate(void)
{
	const M16C_TIMERREG *tmreg;
	uint8_t i;
	
	for(i = 0 ; i < TNUM_M16C_TA ; i++)
	{
		tmreg = get_timerreg(i);
		/* �^�C�}��~ */
		*(tmreg->start) &= ~(tmreg->bitmsk);
	}
}

/*
 *  ���[�h�ݒ�
 */
void m16c_ta_setmode(ID ch , uint8_t mode , uint8_t clksrc , uint8_t opt)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	/* ���[�h���W�X�^�ւ̐ݒ� */
	sil_wrb_mem(tmreg->mode , mode | (clksrc << 6U) | (opt << 3U));
}

/*
 *  ��������̊J�n
 */
void m16c_ta_start(ID ch , uint16_t period)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	/* �����ݒ� */
	sil_wrh_mem(tmreg->counter , period);
	/* �^�C�}�X�^�[�g */
	sil_wrb_mem(tmreg->start , 
		(sil_reb_mem(tmreg->start) | tmreg->bitmsk));
}

/*
 *  ��������̒�~
 */
void m16c_ta_stop(ID ch)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	/* �^�C�}�X�g�b�v */
	*(tmreg->start) &= ~(tmreg->bitmsk);
}

/*
 *  �^�C�}���W�X�^�l�̓ǂݏo��
 */
uint16_t m16c_ta_getcount(ID ch)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	return sil_reh_mem(tmreg->counter);
}

/*
 *  �^�C�}���W�X�^�l�̏�������
 */
void m16c_ta_setcount(ID ch , uint16_t count)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	sil_wrh_mem(tmreg->counter , count);
}

