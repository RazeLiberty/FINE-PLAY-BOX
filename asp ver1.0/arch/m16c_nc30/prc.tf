$ 
$		�A�[�L�e�N�`���ˑ��e���v���[�g�iM16C�p�j
$ 



$ 
$  ATT_ISR�Ŏg�p�ł��銄���ݔԍ��Ƃ���ɑΉ����銄���݃n���h���ԍ�
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT�^DEF_EXC�Ŏg�p�ł��銄���݃n���h���ԍ��^CPU��O�n���h���ԍ�
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  CFG_INT�Ŏg�p�ł��銄���ݔԍ��Ɗ����ݗD��x
$ 
$INTNO_CFGINT_VALID = INHNO_VALID$
$INTPRI_CFGINT_VALID = { -7,-6,...,-1 }$

$ 
$  �X�^�b�N�T�C�Y�̃`�F�b�N���@�w��
$ 
$  M16C�ł̓A���C�����g�Ɋ֌W�Ȃ��������x�ŃA�N�Z�X�ł���
$ 
 
$CHECK_STKSZ_ALIGN = 1$

$ 
$ �^�[�Q�b�g�ˑ��̊����ݑ����̒�`
$ 

$TARGET_INTATR = TA_POSEDGE | TA_NEGEDGE | TA_BOTHEDGE$

$ 
$  �W���e���v���[�g�t�@�C���̃C���N���[�h
$ 
$INCLUDE "kernel.tf"$

$ 
$   CFG_INT�̃^�[�Q�b�g�ˑ��̃G���[�`�F�b�N
$ 
$ 
$ 

$FOREACH intno INT.ORDER_LIST$
$ INT�����ݔԍ����ǂ������`�F�b�N
	$IF (LENGTH(FIND(INTNO_INT , INT.INTNO[intno])) != 0)$
$   TA_POSEDGE��TA_NEGEDGE�������ɐݒ肳��Ă���ꍇ
		$IF  ((INT.INTATR[intno] & (TA_POSEDGE|TA_NEGEDGE)) == (TA_POSEDGE|TA_NEGEDGE))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$
$   TA_POSEDGE��TA_BOTHEDGE�������ɐݒ肳��Ă���ꍇ
		$IF  ((INT.INTATR[intno] & (TA_POSEDGE|TA_BOTHEDGE)) == (TA_POSEDGE|TA_BOTHEDGE))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$
$   TA_NEGEDGE��TA_BOTHEDGE�������ɐݒ肳��Ă���ꍇ
		$IF  ((INT.INTATR[intno] & (TA_NEGEDGE|TA_BOTHEDGE)) == (TA_NEGEDGE|TA_BOTHEDGE))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$
	$ELSE$
$   INT�����݈ȊO�̊����݂ɑ΂��Ċ����ݑ������w�肳��Ă���ꍇ
		$IF (INT.INTATR[intno] & ~(TA_ENAINT|TA_EDGE)) != 0$
			$ERROR$ INT.TEXT_LINE[intno]: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$
	$END$
$END$


$ 
$ �����ݔԍ����犄���ݗD��x�����o���e�[�u��
$ 

const PRI intpri_table[$LENGTH(INTNO_RANGE)$] = $NL$
{
$FOREACH intno INTNO_RANGE$
	$IF LENGTH(INT.INTNO[intno])$
		$intpri = INT.INTPRI[intno]$
	$ELSE$
		$intpri = "0"$
	$END$
	$TAB$$FORMAT("INT8_C(%2d), /* %02u */", intpri	, +intno)$$NL$
$END$
};$NL$$NL$


$ 
$  �A�Z���u���o�̓t�@�C��
$ 

$FILE "kernel_cfg_asm.a30"$

;$NL$
;  M16C�A�[�L�e�N�`���ˑ��o�̓t�@�C��$NL$
;$NL$
;  �����݃x�N�^�y�ъ����݃n���h����`$NL$
;$NL$
$NL$$NL$


$ 
$  �����ݓ�������
$ 

$ 
$  ���ʊ֐��̐錾
$ 

$TAB$.glb _kernel_interrupt			$NL$
$TAB$.section program, code, align	$NL$$NL$

$ 
$  �����݃n���h���̏o��
$ 

$FOREACH inhno INHNO_RANGE$
	$IF LENGTH(INH.INHNO[inhno])$
		$TAB$.glb	_$INH.INTHDR[inhno]$	$NL$
		$TAB$.glb	__kernel_$INH.INTHDR[inhno]$_$+INH.INHNO[inhno]$_entry	$NL$
		__kernel_$INH.INTHDR[inhno]$_$+INH.INHNO[inhno]$_entry:				$NL$
		$TAB$pushm	r0,r1,r2,r3,a0,a1,sb,fb		; ���W�X�^���^�X�N�X�^�b�N�֑ޔ� $NL$
		$TAB$mov.w	#(_$INH.INTHDR[inhno]$ & 0FFFFH) , r1		; �n���h���̉��ʃA�h���X $NL$
		$TAB$mov.w	#((_$INH.INTHDR[inhno]$ >> 16) & 0FFFFH) , r3		; �n���h���̏�ʃA�h���X $NL$
		$TAB$mov.w	#$+INH.INHNO[inhno]$ , r0 ; ������/CPU��O�n���h���ԍ� $NL$
		$TAB$jmp	_kernel_interrupt			; ���ʃ��[�`���� $NL$$NL$$NL$
	$END$
$END$


$ 
$  CPU��O�n���h����������
$ 

$TAB$.glb	_kernel_exception$NL$

$FOREACH excno EXCNO_RANGE$
	$IF LENGTH(EXC.EXCNO[excno])$
		$TAB$.glb	$$$EXC.EXCHDR[excno]$	$NL$
		$TAB$.glb	__kernel_$EXC.EXCHDR[excno]$_$+EXC.EXCNO[excno]$_entry	$NL$
		__kernel_$EXC.EXCHDR[excno]$_$+EXC.EXCNO[excno]$_entry:				$NL$
		$TAB$pushm	r0,r1,r2,r3,a0,a1,sb,fb		; ���W�X�^���^�X�N�X�^�b�N�֑ޔ� $NL$
		$TAB$mov.w	#($$$EXC.EXCHDR[excno]$ & 0FFFFH) , r0		; �n���h���̉��ʃA�h���X $NL$
		$TAB$mov.w	#(($$$EXC.EXCHDR[excno]$ >> 16) & 0FFFFH) , r2		; �n���h���̏�ʃA�h���X $NL$
		$TAB$mov.w	#$+EXC.EXCNO[excno]$ , r3 ; ������/CPU��O�n���h���ԍ� $NL$
		$TAB$jmp	_kernel_exception			; ���ʃ��[�`���� $NL$$NL$$NL$
	$END$
$END$


$ 
$  �σx�N�^�e�[�u��
$ 

;$NL$
;  �σx�N�^�e�[�u��$NL$
;$NL$
$NL$

$TAB$.glb $TAB$ _start$NL$
$TAB$.glb $TAB$ _unused_interrupt $NL$
$TAB$.section vvector$NL$$NL$
vvector_table:$NL$
$FOREACH inhno INHNO_RANGE$
	$IF LENGTH(INH.INHNO[inhno])$
		$inhhdr = CONCAT(CONCAT("_kernel_" , CONCAT(INH.INTHDR[inhno] , "_")) , CONCAT(+INH.INHNO[inhno] , "_entry"))$
	$ELSE$
		$inhhdr = "unused_interrupt"$
	$END$
	$TAB$.lword$TAB$_$inhhdr$ $TAB$ $TAB$ $FORMAT("; %02d" , inhno)$ $NL$
$END$

$ 
$  �Œ�x�N�^�e�[�u��
$ 
$FOREACH excno EXCNO_RANGE$
	$IF LENGTH(EXC.EXCNO[excno])$
		$EXCHDR[excno] = CONCAT(CONCAT("_kernel_" , CONCAT(EXC.EXCHDR[excno] , "_")) , CONCAT(+EXC.EXCNO[excno] , "_entry"))$
	$ELSE$
		$EXCHDR[excno] = "unused_interrupt"$
	$END$
$END$

$NL$
;$NL$
;  �Œ�x�N�^�e�[�u��$NL$
;$NL$
$NL$

$TAB$ .section fvector$NL$
$NL$
fvector_table:$NL$
$TAB$ .lword$TAB$ _$EXCHDR[0]$ $TAB$ $TAB$;$SPC$ 0 $SPC$$NL$
$TAB$ .lword$TAB$ _$EXCHDR[1]$ $TAB$ $TAB$;$SPC$ 1 $SPC$$NL$
$TAB$ .lword$TAB$ _$EXCHDR[2]$ $TAB$ $TAB$;$SPC$ 2 $SPC$$NL$
$TAB$ .lword$TAB$ _$EXCHDR[3]$ $TAB$ $TAB$;$SPC$ 3 $SPC$$NL$
$TAB$ .lword$TAB$ _$EXCHDR[4]$ $TAB$ $TAB$;$SPC$ 4 $SPC$$NL$
$TAB$ .lword$TAB$ _$EXCHDR[5]$ $TAB$ $TAB$;$SPC$ 5 $SPC$$NL$
$TAB$ .lword$TAB$ _$EXCHDR[6]$ $TAB$ $TAB$;$SPC$ 6 $SPC$$NL$
$TAB$ .lword$TAB$ _$EXCHDR[7]$ $TAB$ $TAB$;$SPC$ 7 $SPC$$NL$
$TAB$ .lword		_start ; 8

$NL$ $NL$

	$TAB$.end
$NL$
