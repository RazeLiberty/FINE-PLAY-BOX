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
 *		�^�[�Q�b�g�ˑ����W���[���iRSK-M16C-62P�p�j
 *
 *  �J�[�l���̃^�[�Q�b�g�ˑ����̃C���N���[�h�t�@�C���Dkernel_impl.h�̃^�[
 *  �Q�b�g�ˑ����̈ʒu�t���ƂȂ�D
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 *  �^�[�Q�b�g�V�X�e���̃n�[�h�E�F�A�����̒�`
 */
#include "RSK-M16C-62P.h"
#include "m16c_nc30/m16c62p_config.h"



/*
 *  ASP�J�[�l�����쎞�̃������}�b�v�Ɗ֘A�����`
 *
 *	00400 - 07fff		RAM(31KB)
 *  0F000 - FFFF		ROM�̈�(�u���b�NA)(4K)
 *	80000 - fffff		ROM�̈�i��512KB�j
 *	00000 -				�f�[�^�̈�i��3MB�j
 *		  - 07fff		�f�t�H���g�̔�^�X�N�R���e�L�X�g�p�̃X�^�b�N�̈�
 */

/*
 *  �f�t�H���g�̔�^�X�N�R���e�L�X�g�p�̃X�^�b�N�̈�̒�`
 */
#define DEFAULT_ISTKSZ		0x00400U
#define DEFAULT_ISTK		(void *)(0x8000 - DEFAULT_ISTKSZ)

/*
 *  �^�[�Q�b�g�ˑ��̕����o�͂Ɏg�p����|�[�g�̒�`  
 */
#define TARGET_PUTC_PORTID	 1


#ifndef TOPPERS_MACRO_ONLY
/*
 *  �^�[�Q�b�g�V�X�e���ˑ��̏�����
 */
extern void	target_initialize(void);

/*
 *  �^�[�Q�b�g�V�X�e���̏I��
 *
 *  �V�X�e�����I�����鎞�Ɏg���D
 */
extern void	target_exit(void) NoReturn;

/*
 *  �^�[�Q�b�g�V�X�e���̕����o��
 */
extern void	target_fput_log(char_t c);

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �v���Z�b�T�ˑ����W���[���iM16C�p�j
 */
#include "m16c_nc30/prc_config.h"

/*
 *  �g���[�X���O�Ɋւ���ݒ�
 */

#define TCNT_TRACE_BUFFER	(32)

#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

#endif /* TOPPERS_TARGET_CONFIG_H */
