;*by K.H line95
;*   TOPPERS/ASP Kernel
;*       Toyohashi Open Platform for Embedded Real-Time Systems/
;*       Advanced Standard Profile Kernel
;*  
;*   Copyright (C) 2008 by Witz Corporation, JAPAN
;* 
;*  ��L���쌠�҂́CFree Software Foundation �ɂ���Č��\����Ă��� 
;*  GNU General Public License �� Version 2 �ɋL�q����Ă���������C��
;*  ����(1)�`(4)�̏����𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F
;*  �A�����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
;*  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
;*  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
;*      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
;*      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
;*  (2) �{�\�t�g�E�F�A���ė��p�\�ȃo�C�i���R�[�h�i�����P�[�^�u���I�u
;*      �W�F�N�g�t�@�C���⃉�C�u�����Ȃǁj�̌`�ŗ��p����ꍇ�ɂ́C���p
;*      �ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C
;*      ���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
;*  (3) �{�\�t�g�E�F�A���ė��p�s�\�ȃo�C�i���R�[�h�̌`�܂��͋@��ɑg
;*      �ݍ��񂾌`�ŗ��p����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂������ƁD
;*    (a) ���p�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒���
;*        ���\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
;*    (b) ���p�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āC��L���쌠�҂ɕ񍐂���
;*        ���ƁD
;*  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
;*      �Q������C��L���쌠�҂�Ɛӂ��邱�ƁD
;* 
;*  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂́C
;*  �{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\�����܂߂āC�����Ȃ�ۏ؂��s��
;*  �Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ�������
;*  ���Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D

;
;  �^�[�Q�b�g�V�X�e���ˑ��Z�N�V������`�t�@�C��(RSK-M16C-62P�p)
;

;
;  �Z�N�V�����̒�`
;

	;
	; �����l�L��f�[�^�̈�̃Z�N�V����
	;
	.section	data_NE,DATA
	.org	0410H

	;
	; �����l���������f�[�^�̈�̃Z�N�V����
	;
	.section	bss_NE,DATA

	;
	; �����l�L���f�[�^�̈�̃Z�N�V����
	;
	.section	data_NO,DATA

	;
	; �����l������f�[�^�̈�̃Z�N�V����
	;
	.section	bss_NO,DATA

	;
	; �J�[�l���X�^�b�N�̈�̃Z�N�V����
	;
	.section	stack,DATA
	.org	07C00H
	.blkb	0400H
	.glb DEFAULT_ISTK_TOP
DEFAULT_ISTK_TOP:

	;
	; CODE�̈�̃Z�N�V����
	;
	.section	program,CODE
	.org	0A0000H					; 080000H -> 0A0000H�ɕύX

	;
	; RO�f�[�^�̈�̃Z�N�V����
	;
	.section	rom_FE,ROMDATA,ALIGN
	.section	rom_FO,ROMDATA

	;
	; DATA�̈�̏����l
	;
	.section	data_NEI,ROMDATA,ALIGN
	.section	data_NOI,ROMDATA

	;
	; �σx�N�^�e�[�u���̈�̃Z�N�V����
	;
	.section	vvector,CODE
;	.org	0FFEDCH
	.org	0fa000h		; for monitor on board  by K.H

	.glb VVECTOR_TOP
VVECTOR_TOP:

	;
	; �Œ�x�N�^�e�[�u���̈�̃Z�N�V����
	;
	.section	fvector,CODE
	.org	0FFFDCH

