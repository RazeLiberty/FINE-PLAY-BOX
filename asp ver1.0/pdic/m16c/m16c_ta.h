/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  M16C�p�^�C�}�h���C�o
 *
 *  M16C/M32C/R32C�����^�C�}A�p�h���C�o�D
 */

#ifndef TOPPERS_M16C_TA_H
#define TOPPERS_M16C_TA_H

/* �^�C�}���[�h�ݒ� */
#define MODE_TIMER		UINT_C(0x00)
#define MODE_EVTCNT		UINT_C(0x01)
#define MODE_ONESHOT	UINT_C(0x02)
#define MODE_PWM		UINT_C(0x03)

#define GATE_NONE		UINT_C(0x00)
#define GATE_TAI_L		UINT_C(0x01)
#define GATE_TAI_H		UINT_C(0x02)

#define CNTSRC_F1		UINT_C(0x00)
#define CNTSRC_F8		UINT_C(0x01)
#define CNTSRC_F2N		UINT_C(0x02)
#define CNTSRC_FC32		UINT_C(0x03)


#ifndef TOPPERS_MACRO_ONLY

/*
 *  �^�C�}A�h���C�o�̏�����
 */
extern void m16c_ta_initialize(void);

/*
 *  �^�C�}A�h���C�o�̏I��
 */
extern void m16c_ta_terminate(void);

/*
 *  ���[�h�ݒ�
 */
extern void m16c_ta_setmode
	(ID ch , uint8_t mode , uint8_t clksrc , uint8_t opt);

/*
 *  ��������̊J�n
 */
extern void m16c_ta_start(ID ch , uint16_t period);

/*
 *  ��������̒�~
 */
extern void m16c_ta_stop(ID ch);

/*
 *  �^�C�}���W�X�^�l�̓ǂݏo��
 */
extern uint16_t m16c_ta_getcount(ID ch);

/*
 *  �^�C�}���W�X�^�l�̏�������
 */
extern void m16c_ta_setcount(ID ch , uint16_t count);

#endif	/* TOPPERS_MACRO_ONLY */
#endif	/* TOPPERS_M16C_TA_H */
