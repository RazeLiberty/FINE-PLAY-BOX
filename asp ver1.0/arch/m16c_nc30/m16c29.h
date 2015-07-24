/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
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


#ifndef TOPPERS_M16C29_H
#define TOPPERS_M16C29_H

/* �v���Z�b�T�ˑ��̏���` */

/*1
 *  SFR�A�h���X��`
 */
#define TADR_SFR_PM0     0x0004 /* �v���Z�b�T���[�h���W�X�^0 */
#define TADR_SFR_PM1     0x0005 /* �v���Z�b�T���[�h���W�X�^1 */
#define TADR_SFR_CM0     0x0006 /* �V�X�e���N���b�N���䃌�W�X�^0 */
#define TADR_SFR_CM1     0x0007 /* �V�X�e���N���b�N���䃌�W�X�^1 */
#define TADR_SFR_CSR     0x0008 /* �`�b�v�Z���N�g���䃌�W�X�^ */
#define TADR_SFR_AIER    0x0009 /* �A�h���X��v���荞�݋����W�X�^ */
#define TADR_SFR_PRCR    0x000A /* �v���e�N�g���W�X�^ */
#define TADR_SFR_DBR     0x000B /* �f�[�^�o���N���W�X�^ */
#define TADR_SFR_CM2     0x000C /* ���U��~���o���W�X�^ */
#define TADR_SFR_WDTS    0x000E /* �E�H�b�`�h�b�O�^�C�}�X�^�[�g���W�X�^ */
#define TADR_SFR_WDC     0x000F /* �E�H�b�`�h�b�O�^�C�}���䃌�W�X�^ */
#define TADR_SFR_RMAD0   0x0010 /* �A�h���X��v���荞�݃��W�X�^0 */
#define TADR_SFR_RMAD1   0x0014 /* �A�h���X��v���荞�݃��W�X�^1 */
#define TADR_SFR_VCR1    0x0019 /* �d�����o���W�X�^1 (��5�A6) */
#define TADR_SFR_VCR2    0x001A /* �d�����o���W�X�^2 (��5�A6) */
#define TADR_SFR_CSE     0x001B /* �`�b�v�Z���N�g�g�����䃌�W�X�^ */
#define TADR_SFR_PLC0    0x001C /* PLL���䃌�W�X�^0 */
#define TADR_SFR_PM2     0x001E /* �v���Z�b�T���[�h���W�X�^2 */
#define TADR_SFR_D4INT   0x001F /* �d���ቺ���o���荞�݃��W�X�^ */
#define TADR_SFR_SAR0    0x0020 /* DMA0�\�|�X�|�C���^ */
#define TADR_SFR_DAR0    0x0024 /* DMA0�f�B�X�e�B�l�|�V�����|�C���^ */
#define TADR_SFR_TCR0    0x0028 /* DMA0�]���J�E���^ */
#define TADR_SFR_DM0CON  0x002C /* DMA0���䃌�W�X�^ */
#define TADR_SFR_SAR1    0x0030 /* DMA1�\�|�X�|�C���^ */
#define TADR_SFR_DAR1    0x0034 /* DMA1�f�B�X�e�B�l�|�V�����|�C���^ */
#define TADR_SFR_TCR1    0x0038 /* DMA1�]���J�E���^ */
#define TADR_SFR_DM1CON  0x003C /* DMA1���䃌�W�X�^ */
#define TADR_SFR_C01WKIC 0x0041 /* CAN0�E�F�C�N�A�b�v���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_C0RECIC 0x0042 /* CAN0��M�������荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_C0TRMIC 0x0043 /* CAN0���M�M�������荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_INT3IC  0x0044 /* INT3���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TB5IC   0x0045 /* �^�C�}B5���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TB4IC   0x0046 /* �^�C�}B4���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_U1BCNIC 0x0046 /* �o�X�Փˌ��o���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TB3IC   0x0047 /* �^�C�}B3���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_U0BCNIC 0x0047 /* UART0�o�X�Փˌ��o���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_S4IC    0x0048 /* SI/O4���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_INT5IC  0x0048 /* INT5���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_S3IC    0x0049 /* SI/O3���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_INT4IC  0x0049 /* INT4���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_BCNIC   0x004A /* UART2�o�X�Փˌ��o���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_DM0IC   0x004B /* DMA0���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_DM1IC   0x004C /* DMA1���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_KUPIC   0x004D /* �L�|���͊��荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_ADIC    0x004E /* A/D�ϊ����荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_S2TIC   0x004F /* UART2���M���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_S2RIC   0x0050 /* UART2��M���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_S0TIC   0x0051 /* UART0���M���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_S0RIC   0x0052 /* UART0��M���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_S1TIC   0x0053 /* UART1���M���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_S1RIC   0x0054 /* UART1��M���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TA0IC   0x0055 /* �^�C�}A0���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TA1IC   0x0056 /* �^�C�}A1���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TA2IC   0x0057 /* �^�C�}A2���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TA3IC   0x0058 /* �^�C�}A3���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TA4IC   0x0059 /* �^�C�}A4���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TB0IC   0x005A /* �^�C�}B0���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TB1IC   0x005B /* �^�C�}B1���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_TB2IC   0x005C /* �^�C�}B2���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_INT0IC  0x005D /* INT0���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_INT1IC  0x005E /* INT1���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_INT2IC  0x005F /* INT2���荞�ݐ��䃌�W�X�^ */
#define TADR_SFR_FIDR    0x01B4 /* �t���b�V�����ʃ��W�X�^ */
#define TADR_SFR_FMR1    0x01B5 /* �t���b�V�����������䃌�W�X�^1 */
#define TADR_SFR_FMR0    0x01B7 /* �t���b�V�����������䃌�W�X�^0 */
#define TADR_SFR_RMAD2   0x01B8 /* �A�h���X��v���荞�݃��W�X�^2 */
#define TADR_SFR_AIER2   0x01BB /* �A�h���X��v���荞�݋����W�X�^2 */
#define TADR_SFR_RMAD3   0x01BC /* �A�h���X��v���荞�݃��W�X�^3 */
#define TADR_SFR_PCLKR   0x025E /* ���ӃN���b�N�I�����W�X�^*/
#define TADR_SFR_TBSR    0x0340 /* �^�C�}B3,4,5�J�E���g�J�n�t���O */
#define TADR_SFR_TA11    0x0342 /* �^�C�}A1-1���W�X�^ */
#define TADR_SFR_TA21    0x0344 /* �^�C�}A2-1���W�X�^ */
#define TADR_SFR_TA41    0x0346 /* �^�C�}A4-1���W�X�^ */
#define TADR_SFR_INVC0   0x0348 /* �O��PWM���䃌�W�X�^0 */
#define TADR_SFR_INVC1   0x0349 /* �O��PWM���䃌�W�X�^1 */
#define TADR_SFR_IDB0    0x034A /* �O���o�̓o�b�t�@���W�X�^0 */
#define TADR_SFR_IDB1    0x034B /* �O���o�̓o�b�t�@���W�X�^1 */
#define TADR_SFR_DTT     0x034C /* �Z���h�~�^�C�} */
#define TADR_SFR_ICTB2   0x034D /* �^�C�}B2���荞�ݔ����p�x�ݒ�J�E���^ */
#define TADR_SFR_TB3     0x0350 /* �^�C�}B3���W�X�^ */
#define TADR_SFR_TB4     0x0352 /* �^�C�}B4���W�X�^ */
#define TADR_SFR_TB5     0x0354 /* �^�C�}B5���W�X�^ */
#define TADR_SFR_TB3MR   0x035B /* �^�C�}B3���[�h���W�X�^ */
#define TADR_SFR_TB4MR   0x035C /* �^�C�}B4���[�h���W�X�^ */
#define TADR_SFR_TB5MR   0x035D /* �^�C�}B5���[�h���W�X�^ */
#define TADR_SFR_IFSR2A  0x035E /* ���荞�ݗv���I�����W�X�^2 */
#define TADR_SFR_IFSR    0x035F /* ���荞�ݗv���I�����W�X�^ */
#define TADR_SFR_S3TRR   0x0360 /* SI/O3����M���W�X�^ */
#define TADR_SFR_S3C     0x0362 /* SI/O3���䃌�W�X�^ */
#define TADR_SFR_S3BRG   0x0363 /* SI/O3�r�b�g���[�g���W�X�^ */
#define TADR_SFR_S4TRR   0x0364 /* SI/O4����M���W�X�^ */
#define TADR_SFR_S4C     0x0366 /* SI/O4���䃌�W�X�^ */
#define TADR_SFR_S4BRG   0x0367 /* SI/O4�r�b�g���[�g���W�X�^ */
#define TADR_SFR_U0SMR4  0x036C /* UART0���ꃂ�[�h���W�X�^4 */
#define TADR_SFR_U0SMR3  0x036D /* UART0���ꃂ�[�h���W�X�^3 */
#define TADR_SFR_U0SMR2  0x036E /* UART0���ꃂ�[�h���W�X�^2 */
#define TADR_SFR_U0SMR   0x036F /* UART0���ꃂ�[�h���W�X�^ */
#define TADR_SFR_U1SMR4  0x0370 /* UART1���ꃂ�[�h���W�X�^4 */
#define TADR_SFR_U1SMR3  0x0371 /* UART1���ꃂ�[�h���W�X�^3 */
#define TADR_SFR_U1SMR2  0x0372 /* UART1���ꃂ�[�h���W�X�^2 */
#define TADR_SFR_U1SMR   0x0373 /* UART1���ꃂ�[�h���W�X�^ */
#define TADR_SFR_U2SMR4  0x0374 /* UART2���ꃂ�[�h���W�X�^4 */
#define TADR_SFR_U2SMR3  0x0375 /* UART2���ꃂ�[�h���W�X�^3 */
#define TADR_SFR_U2SMR2  0x0376 /* UART2���ꃂ�[�h���W�X�^2 */
#define TADR_SFR_U2SMR   0x0377 /* UART2���ꃂ�[�h���W�X�^ */
#define TADR_SFR_U2MR    0x0378 /* UART2����M���[�h���W�X�^ */
#define TADR_SFR_U2BRG   0x0379 /* UART2�r�b�g���[�g���W�X�^ */
#define TADR_SFR_U2TB    0x037A /* UART2���M�o�b�t�@���W�X�^ */
#define TADR_SFR_U2C0    0x037C /* UART2����M���䃌�W�X�^0 */
#define TADR_SFR_U2C1    0x037D /* UART2����M���䃌�W�X�^1 */
#define TADR_SFR_U2RB    0x037E /* UART2��M�o�b�t�@���W�X�^ */

/*
 *  DMAC
 */ 
#define TADR_SFR_DM0SL   0x03B8 /* DMA0�v���I�����W�X�^ */
#define TADR_SFR_DM1SL   0x03BA /* DMA1�v���I�����W�X�^ */

/*
 *  �^�C�}
 */
#define TADR_SFR_TABSR   0x0380 /* �J�E���g�J�n�t���O */
#define TADR_SFR_CPSRF   0x0381 /* ���v�p�v���X�P�[�����Z�b�g�t���O */
#define TADR_SFR_ONSF    0x0382 /* �����V���b�g�J�n�t���O */
#define TADR_SFR_TRGSR   0x0383 /* �g���K�I�����W�X�^ */
#define TADR_SFR_UDF     0x0384 /* �A�b�v�_�E���t���O */
#define TADR_SFR_TA0     0x0386 /* �^�C�}A0���W�X�^ */
#define TADR_SFR_TA1     0x0388 /* �^�C�}A1���W�X�^ */
#define TADR_SFR_TA2     0x038A /* �^�C�}A2���W�X�^ */
#define TADR_SFR_TA3     0x038C /* �^�C�}A3���W�X�^ */
#define TADR_SFR_TA4     0x038E /* �^�C�}A4���W�X�^ */
#define TADR_SFR_TB0     0x0390 /* �^�C�}B0���W�X�^ */
#define TADR_SFR_TB1     0x0392 /* �^�C�}B1���W�X�^ */
#define TADR_SFR_TB2     0x0394 /* �^�C�}B2���W�X�^ */
#define TADR_SFR_TA0MR   0x0396 /* �^�C�}A0���|�h���W�X�^ */
#define TADR_SFR_TA1MR   0x0397 /* �^�C�}A1���|�h���W�X�^ */
#define TADR_SFR_TA2MR   0x0398 /* �^�C�}A2���|�h���W�X�^ */
#define TADR_SFR_TA3MR   0x0399 /* �^�C�}A3���|�h���W�X�^ */
#define TADR_SFR_TA4MR   0x039A /* �^�C�}A4���|�h���W�X�^ */
#define TADR_SFR_TB0MR   0x039B /* �^�C�}B0���|�h���W�X�^ */
#define TADR_SFR_TB1MR   0x039C /* �^�C�}B1���|�h���W�X�^ */
#define TADR_SFR_TB2MR   0x039D /* �^�C�}B2���|�h���W�X�^ */
#define TADR_SFR_TB2SC   0x039E /* �^�C�}B2���ꃂ�|�h���W�X�^ */

/*
 *  CRC���Z
 */
#define TADR_SFR_CRCD    0x03BC /* CRC�f�[�^���W�X�^ */
#define TADR_SFR_CRCIN   0x03BE /* CRC�C���v�b�g���W�X�^ */

/*
 *  �V���A���C���^�t�F�[�X
 */
#define TADR_SFR_UART0_BASE    0x03A0 /* UART0����M���|�h���W�X�^ */
#define TADR_SFR_UART1_BASE    0x03A8 /* UART1����M���|�h���W�X�^ */
#define TADR_SFR_UART2_BASE    0x0378 /* UART2����M���|�h���W�X�^ */

#define TADR_SFR_UMR_OFFSET         0 /* ����M���|�h���W�X�^ */
#define TADR_SFR_UBRG_OFFSET        1 /* �r�b�g���[�g���W�X�^ */
#define TADR_SFR_UTB_OFFSET         2 /* ���M�o�b�t�@���W�X�^ */
#define TADR_SFR_UC0_OFFSET         4 /* ����M���䃌�W�X�^�O*/
#define TADR_SFR_UC1_OFFSET         5 /* ����M���䃌�W�X�^�P */
#define TADR_SFR_URB_OFFSET         6 /* ��M�o�b�t�@���W�X�^ */
#define TADR_SFR_UCON          0x03B0 /* UART����M���䃌�W�X�^�Q */

/*
 *  A-D/D-A�R���o�[�^
 */
#define TADR_SFR_AD0     0x03C0 /* A/D���W�X�^0 */
#define TADR_SFR_AD1     0x03C2 /* A/D���W�X�^1 */
#define TADR_SFR_AD2     0x03C4 /* A/D���W�X�^2 */
#define TADR_SFR_AD3     0x03C6 /* A/D���W�X�^3 */
#define TADR_SFR_AD4     0x03C8 /* A/D���W�X�^4 */
#define TADR_SFR_AD5     0x03CA /* A/D���W�X�^5 */
#define TADR_SFR_AD6     0x03CC /* A/D���W�X�^6 */
#define TADR_SFR_AD7     0x03CE /* A/D���W�X�^7 */
#define TADR_SFR_ADCON2  0x03D4 /* A/D���䃌�W�X�^2 */
#define TADR_SFR_ADCON0  0x03D6 /* A/D���䃌�W�X�^0 */
#define TADR_SFR_ADCON1  0x03D7 /* A/D���䃌�W�X�^1 */
#define TADR_SFR_DA0     0x03D8 /* D/A���W�X�^0 */
#define TADR_SFR_DA1     0x03DA /* D/A���W�X�^1 */
#define TADR_SFR_DACON   0x03DC /* D/A���䃌�W�X�^*/

/*
 *  �v���O���}�u�����o�̓|�[�g
 */

#define TADR_SFR_PC14    0x03DE /* �|�[�gP14���䃌�W�X�^ */
#define TADR_SFR_PUR3    0x03DF /* �v���A�b�v���䃌�W�X�^3 */
#define TADR_SFR_P0      0x03E0 /* �|�[�gP0���W�X�^ */
#define TADR_SFR_P1      0x03E1 /* �|�[�gP1���W�X�^ */
#define TADR_SFR_PD0     0x03E2 /* �|�[�gP0�������W�X�^ */
#define TADR_SFR_PD1     0x03E3 /* �|�[�gP1�������W�X�^ */
#define TADR_SFR_P2      0x03E4 /* �|�[�gP2���W�X�^ */
#define TADR_SFR_P3      0x03E5 /* �|�[�gP3���W�X�^ */
#define TADR_SFR_PD2     0x03E6 /* �|�[�gP2�������W�X�^ */
#define TADR_SFR_PD3     0x03E7 /* �|�[�gP3�������W�X�^ */
#define TADR_SFR_P4      0x03E8 /* �|�[�gP4���W�X�^ */
#define TADR_SFR_P5      0x03E9 /* �|�[�gP5���W�X�^ */
#define TADR_SFR_PD4     0x03EA /* �|�[�gP4�������W�X�^ */
#define TADR_SFR_PD5     0x03EB /* �|�[�gP5�������W�X�^ */
#define TADR_SFR_P6      0x03EC /* �|�[�gP6���W�X�^ */
#define TADR_SFR_P7      0x03ED /* �|�[�gP7���W�X�^ */
#define TADR_SFR_PD6     0x03EE /* �|�[�gP6�������W�X�^ */
#define TADR_SFR_PD7     0x03EF /* �|�[�gP7�������W�X�^ */
#define TADR_SFR_P8      0x03F0 /* �|�[�gP8���W�X�^ */
#define TADR_SFR_P9      0x03F1 /* �|�[�gP9���W�X�^ */
#define TADR_SFR_PD8     0x03F2 /* �|�[�gP8�������W�X�^ */
#define TADR_SFR_PD9     0x03F3 /* �|�[�gP9�������W�X�^ */
#define TADR_SFR_P10     0x03F4 /* �|�[�gP10���W�X�^ */
#define TADR_SFR_P11     0x03F5 /* �|�[�gP11���W�X�^ */
#define TADR_SFR_PD10    0x03F6 /* �|�[�gP10�������W�X�^ */
#define TADR_SFR_PD11    0x03F7 /* �|�[�gP11�������W�X�^ */
#define TADR_SFR_P12     0x03F8 /* �|�[�gP12���W�X�^ */
#define TADR_SFR_P13     0x03F9 /* �|�[�gP13���W�X�^ */
#define TADR_SFR_PD12    0x03FA /* �|�[�gP12�������W�X�^ */
#define TADR_SFR_PD13    0x03FB /* �|�[�gP13�������W�X�^ */
#define TADR_SFR_PUR0    0x03FC /* �v���A�b�v���䃌�W�X�^0 */
#define TADR_SFR_PUR1    0x03FD /* �v���A�b�v���䃌�W�X�^1 */
#define TADR_SFR_PUR2    0x03FE /* �v���A�b�v���䃌�W�X�^2 */
#define TADR_SFR_PCR     0x03FF /* �|�[�g���䃌�W�X�^ */

/*
 *  CPU��O�n���h���ԍ��̒�`
 */

#define INT_UNDEF_INSTRUNCTION	0		/* ����`���� */
#define INT_OVERFLOW			1		/* �I�[�o�[�t���[ */
#define INT_BRK_INSTRUCTION		2		/* BRK���� */
#define INT_ADDRESS_MATCH		3		/* �A�h���X��v */
#define INT_WDT					5		/* �E�H�b�`�h�b�O�^�C�} */
#define INT_XIN_STOP			5		/* ���U��~���o */
#define INT_LOW_VOLT_DETECT		5		/* �d���ቺ���o */
#define INT_NMI					7		/* NMI */
#define INT_RESET				8		/* ���Z�b�g */

/*
 *  �����݃n���h���ԍ��̒�`
 */
#define	TINHNO_BRK      0		/* BRK */
#define TINHNO_CAN0WUP  1  		/* CAN0�E�G�C�N�A�b�v */
#define TINHNO_CAN0R    2 		/* CAN0��M���� */
#define TINHNO_CAN0S    3 		/* CAN0���M���� */
#define TINHNO_INT3     4		/* INT3 */
#define TINHNO_TB5      5		/* �^�C�}B5 */
#define TINHNO_TB4      6		/* �^�C�}B4 */
#define TINHNO_TB3      7		/* �^�C�}B3 */
#define TINHNO_SIO4     8		/* SIO4 */
#define TINHNO_INT5     8		/* INT5 */
#define TINHNO_SIO3     9		/* SIO3 */
#define TINHNO_INT4     9		/* INT4 */
#define TINHNO_BCN     10		/* UART�o�X�Փˌ��o */
#define TINHNO_DMA0    11		/* DMA0 */
#define TINHNO_DMA1    12		/* DMA1 */
#define TINHNO_KEY     13		/* �L�[���͊����� */
#define TINHNO_AD      14		/* A/D */
#define TINHNO_S2TNACK 15		/* UART2���M,NACK */
#define TINHNO_S2RACK  16		/* UART2��M,ACK */
#define TINHNO_S0TNACK 17		/* UART0���M,NACK */
#define TINHNO_S0RACK  18		/* UART0��M,ACK */
#define TINHNO_S1TNACK 19		/* UART1���M,NACK */
#define TINHNO_S1RACK  20		/* UART1��M,ACK */
#define TINHNO_TA0     21		/* �^�C�}A0 */
#define TINHNO_TA1     22		/* �^�C�}A1 */
#define TINHNO_TA2     23		/* �^�C�}A2 */
#define TINHNO_TA3     24		/* �^�C�}A3 */
#define TINHNO_TA4     25		/* �^�C�}A4 */
#define TINHNO_TB0     26		/* �^�C�}B0 */
#define TINHNO_TB1     27		/* �^�C�}B1 */
#define TINHNO_TB2     28		/* �^�C�}B2 */
#define TINHNO_INT0    29		/* INT0 */
#define TINHNO_INT1    30		/* INT1 */
#define TINHNO_INT2    31		/* INT2 */

/*
 *  �����ݔԍ��̒�`
 */
#define	TINTNO_BRK      0		/* BRK */
#define TINTNO_INT3     4		/* INT3 */
#define TINTNO_TB5      5		/* �^�C�}B5 */
#define TINTNO_TB4      6		/* �^�C�}B4 */
#define TINTNO_TB3      7		/* �^�C�}B3 */
#define TINTNO_SIO4     8		/* SIO4 */
#define TINTNO_INT5     8		/* INT5 */
#define TINTNO_SIO3     9		/* SIO3 */
#define TINTNO_INT4     9		/* INT4 */
#define TINTNO_BCN     10		/* UART�o�X�Փˌ��o */
#define TINTNO_DMA0    11		/* DMA0 */
#define TINTNO_DMA1    12		/* DMA1 */
#define TINTNO_KEY     13		/* �L�[���͊����� */
#define TINTNO_AD      14		/* A/D */
#define TINTNO_S2TNACK 15		/* UART2���M,NACK */
#define TINTNO_S2RACK  16		/* UART2��M,ACK */
#define TINTNO_S0TNACK 17		/* UART0���M,NACK */
#define TINTNO_S0RACK  18		/* UART0��M,ACK */
#define TINTNO_S1TNACK 19		/* UART1���M,NACK */
#define TINTNO_S1RACK  20		/* UART1��M,ACK */
#define TINTNO_TA0     21		/* �^�C�}A0 */
#define TINTNO_TA1     22		/* �^�C�}A1 */
#define TINTNO_TA2     23		/* �^�C�}A2 */
#define TINTNO_TA3     24		/* �^�C�}A3 */
#define TINTNO_TA4     25		/* �^�C�}A4 */
#define TINTNO_TB0     26		/* �^�C�}B0 */
#define TINTNO_TB1     27		/* �^�C�}B1 */
#define TINTNO_TB2     28		/* �^�C�}B2 */
#define TINTNO_INT0    29		/* INT0 */
#define TINTNO_INT1    30		/* INT1 */
#define TINTNO_INT2    31		/* INT2 */



/*
 *  �^�C�}A���
 *
 *  pdic��m16c/m16c_ta.c�Ŏg�p����D
 */

/*
 *  �^�C�}A�̌�
 */
#define TNUM_M16C_TA		(5)

/*
 *  pdic�p�̒�`�l�Ƀ��l�[��
 */
#define TABSR_ADDR		TADR_SFR_TABSR
#define UDF_ADDR		TADR_SFR_UDF
#define ONSF_ADDR		TADR_SFR_ONSF
#define TAGSR_ADDR		TADR_SFR_TRGSR

#define INT_TA0			TINHNO_TA0
#define INT_TA1			TINHNO_TA1
#define INT_TA2			TINHNO_TA2
#define INT_TA3			TINHNO_TA3

/*
 *  �e�`�����l���̃��W�X�^�y�ѐݒ�r�b�g���
 */
#define TA0_ADDR			(TADR_SFR_TA0)
#define TA0MR_ADDR			(TADR_SFR_TA0MR)
#define TA0_START_BIT		(0x01U << 0U)
#define TA0_ONESHOT_BIT		(0x01U << 0U)
#define TA0_UDSEL_BIT		(0x01U << 0U)
#define TA0_TRIGSEL_OFFSET	(6U)

#define TA1_ADDR			(TADR_SFR_TA1)
#define TA1MR_ADDR			(TADR_SFR_TA1MR)
#define TA1_START_BIT		(0x01U << 1U)
#define TA1_ONESHOT_BIT		(0x01U << 1U)
#define TA1_UDSEL_BIT		(0x01U << 1U)
#define TA1_TRIGSEL_OFFSET	(0U)

#define TA2_ADDR			(TADR_SFR_TA2)
#define TA2MR_ADDR			(TADR_SFR_TA2MR)
#define TA2_START_BIT		(0x01U << 2U)
#define TA2_ONESHOT_BIT		(0x01U << 2U)
#define TA2_UDSEL_BIT		(0x01U << 2U)
#define TA2_TRIGSEL_OFFSET	(2U)

#define TA3_ADDR			(TADR_SFR_TA3)
#define TA3MR_ADDR			(TADR_SFR_TA3MR)
#define TA3_START_BIT		(0x01U << 3U)
#define TA3_ONESHOT_BIT		(0x01U << 3U)
#define TA3_UDSEL_BIT		(0x01U << 3U)
#define TA3_TRIGSEL_OFFSET	(4U)

#define TA4_ADDR			(TADR_SFR_TA4)
#define TA4MR_ADDR			(TADR_SFR_TA4MR)
#define TA4_START_BIT		(0x01U << 4U)
#define TA4_ONESHOT_BIT		(0x01U << 4U)
#define TA4_UDSEL_BIT		(0x01U << 4U)
#define TA4_TRIGSEL_OFFSET	(6U)

/*
 *  UART�֘A�̒�`
 *
 *  pdic��m16c/m16c_uart.c�Ŏg�p����D
 */

/*
 *  �V���A��I/O�̌�
 */
#define TNUM_SIOP			(3)

/*
 *  �e�|�[�g�̃��W�X�^�y�ѐݒ�r�b�g���
 */
#define UART0_UC0_ADDR		(TADR_SFR_UART0_BASE+TADR_SFR_UC0_OFFSET)
#define UART0_UC1_ADDR		(TADR_SFR_UART0_BASE+TADR_SFR_UC1_OFFSET)
#define UART0_MODE_ADDR		(TADR_SFR_UART0_BASE+TADR_SFR_UMR_OFFSET)
#define UART0_BAUD_ADDR		(TADR_SFR_UART0_BASE+TADR_SFR_UBRG_OFFSET)
#define UART0_TXBUF_ADDR	(TADR_SFR_UART0_BASE+TADR_SFR_UTB_OFFSET)
#define UART0_RXBUF_ADDR	(TADR_SFR_UART0_BASE+TADR_SFR_URB_OFFSET)
#define UART0_TXINTNO		(TINHNO_S0TNACK)
#define UART0_RXINTNO		(TINHNO_S0TNACK)

#define UART1_UC0_ADDR		(TADR_SFR_UART1_BASE+TADR_SFR_UC0_OFFSET)
#define UART1_UC1_ADDR		(TADR_SFR_UART1_BASE+TADR_SFR_UC1_OFFSET)
#define UART1_MODE_ADDR		(TADR_SFR_UART1_BASE+TADR_SFR_UMR_OFFSET)
#define UART1_BAUD_ADDR		(TADR_SFR_UART1_BASE+TADR_SFR_UBRG_OFFSET)
#define UART1_TXBUF_ADDR	(TADR_SFR_UART1_BASE+TADR_SFR_UTB_OFFSET)
#define UART1_RXBUF_ADDR	(TADR_SFR_UART1_BASE+TADR_SFR_URB_OFFSET)
#define UART1_TXINTNO		(TINHNO_S1TNACK)
#define UART1_RXINTNO		(TINHNO_S1RACK)

#define UART2_UC0_ADDR		(TADR_SFR_UART2_BASE+TADR_SFR_UC0_OFFSET)
#define UART2_UC1_ADDR		(TADR_SFR_UART2_BASE+TADR_SFR_UC1_OFFSET)
#define UART2_MODE_ADDR		(TADR_SFR_UART2_BASE+TADR_SFR_UMR_OFFSET)
#define UART2_BAUD_ADDR		(TADR_SFR_UART2_BASE+TADR_SFR_UBRG_OFFSET)
#define UART2_TXBUF_ADDR	(TADR_SFR_UART2_BASE+TADR_SFR_UTB_OFFSET)
#define UART2_RXBUF_ADDR	(TADR_SFR_UART2_BASE+TADR_SFR_URB_OFFSET)
#define UART2_TXINTNO		(TINHNO_S2TNACK)
#define UART2_RXINTNO		(TINHNO_S2RACK)


#endif	/* TOPPERS_M16C29_H */
