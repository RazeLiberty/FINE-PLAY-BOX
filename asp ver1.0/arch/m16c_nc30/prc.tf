$ 
$		アーキテクチャ依存テンプレート（M16C用）
$ 



$ 
$  ATT_ISRで使用できる割込み番号とそれに対応する割込みハンドラ番号
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT／DEF_EXCで使用できる割込みハンドラ番号／CPU例外ハンドラ番号
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  CFG_INTで使用できる割込み番号と割込み優先度
$ 
$INTNO_CFGINT_VALID = INHNO_VALID$
$INTPRI_CFGINT_VALID = { -7,-6,...,-1 }$

$ 
$  スタックサイズのチェック方法指定
$ 
$  M16Cではアライメントに関係なく同じ速度でアクセスできる
$ 
 
$CHECK_STKSZ_ALIGN = 1$

$ 
$ ターゲット依存の割込み属性の定義
$ 

$TARGET_INTATR = TA_POSEDGE | TA_NEGEDGE | TA_BOTHEDGE$

$ 
$  標準テンプレートファイルのインクルード
$ 
$INCLUDE "kernel.tf"$

$ 
$   CFG_INTのターゲット依存のエラーチェック
$ 
$ 
$ 

$FOREACH intno INT.ORDER_LIST$
$ INT割込み番号かどうかをチェック
	$IF (LENGTH(FIND(INTNO_INT , INT.INTNO[intno])) != 0)$
$   TA_POSEDGEとTA_NEGEDGEが同時に設定されている場合
		$IF  ((INT.INTATR[intno] & (TA_POSEDGE|TA_NEGEDGE)) == (TA_POSEDGE|TA_NEGEDGE))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$
$   TA_POSEDGEとTA_BOTHEDGEが同時に設定されている場合
		$IF  ((INT.INTATR[intno] & (TA_POSEDGE|TA_BOTHEDGE)) == (TA_POSEDGE|TA_BOTHEDGE))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$
$   TA_NEGEDGEとTA_BOTHEDGEが同時に設定されている場合
		$IF  ((INT.INTATR[intno] & (TA_NEGEDGE|TA_BOTHEDGE)) == (TA_NEGEDGE|TA_BOTHEDGE))$
			$ERROR$ INT.TEXT_LINE[intno]:$FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$
	$ELSE$
$   INT割込み以外の割込みに対して割込み属性が指定されている場合
		$IF (INT.INTATR[intno] & ~(TA_ENAINT|TA_EDGE)) != 0$
			$ERROR$ INT.TEXT_LINE[intno]: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$
	$END$
$END$


$ 
$ 割込み番号から割込み優先度を取り出すテーブル
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
$  アセンブラ出力ファイル
$ 

$FILE "kernel_cfg_asm.a30"$

;$NL$
;  M16Cアーキテクチャ依存出力ファイル$NL$
;$NL$
;  割込みベクタ及び割込みハンドラ定義$NL$
;$NL$
$NL$$NL$


$ 
$  割込み入口処理
$ 

$ 
$  共通関数の宣言
$ 

$TAB$.glb _kernel_interrupt			$NL$
$TAB$.section program, code, align	$NL$$NL$

$ 
$  割込みハンドラの出力
$ 

$FOREACH inhno INHNO_RANGE$
	$IF LENGTH(INH.INHNO[inhno])$
		$TAB$.glb	_$INH.INTHDR[inhno]$	$NL$
		$TAB$.glb	__kernel_$INH.INTHDR[inhno]$_$+INH.INHNO[inhno]$_entry	$NL$
		__kernel_$INH.INTHDR[inhno]$_$+INH.INHNO[inhno]$_entry:				$NL$
		$TAB$pushm	r0,r1,r2,r3,a0,a1,sb,fb		; レジスタをタスクスタックへ退避 $NL$
		$TAB$mov.w	#(_$INH.INTHDR[inhno]$ & 0FFFFH) , r1		; ハンドラの下位アドレス $NL$
		$TAB$mov.w	#((_$INH.INTHDR[inhno]$ >> 16) & 0FFFFH) , r3		; ハンドラの上位アドレス $NL$
		$TAB$mov.w	#$+INH.INHNO[inhno]$ , r0 ; 割込み/CPU例外ハンドラ番号 $NL$
		$TAB$jmp	_kernel_interrupt			; 共通ルーチンへ $NL$$NL$$NL$
	$END$
$END$


$ 
$  CPU例外ハンドラ入口処理
$ 

$TAB$.glb	_kernel_exception$NL$

$FOREACH excno EXCNO_RANGE$
	$IF LENGTH(EXC.EXCNO[excno])$
		$TAB$.glb	$$$EXC.EXCHDR[excno]$	$NL$
		$TAB$.glb	__kernel_$EXC.EXCHDR[excno]$_$+EXC.EXCNO[excno]$_entry	$NL$
		__kernel_$EXC.EXCHDR[excno]$_$+EXC.EXCNO[excno]$_entry:				$NL$
		$TAB$pushm	r0,r1,r2,r3,a0,a1,sb,fb		; レジスタをタスクスタックへ退避 $NL$
		$TAB$mov.w	#($$$EXC.EXCHDR[excno]$ & 0FFFFH) , r0		; ハンドラの下位アドレス $NL$
		$TAB$mov.w	#(($$$EXC.EXCHDR[excno]$ >> 16) & 0FFFFH) , r2		; ハンドラの上位アドレス $NL$
		$TAB$mov.w	#$+EXC.EXCNO[excno]$ , r3 ; 割込み/CPU例外ハンドラ番号 $NL$
		$TAB$jmp	_kernel_exception			; 共通ルーチンへ $NL$$NL$$NL$
	$END$
$END$


$ 
$  可変ベクタテーブル
$ 

;$NL$
;  可変ベクタテーブル$NL$
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
$  固定ベクタテーブル
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
;  固定ベクタテーブル$NL$
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
