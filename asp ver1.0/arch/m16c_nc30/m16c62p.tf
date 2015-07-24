$ 
$		アーキテクチャ依存テンプレート（M16C/62P用）
$ 


/*$NL$
$SPC$*  Architecture-dependent Definitions (M16C/62P)$NL$
$SPC$*/$NL$
$NL$

$ 
$  割込み番号と割込みハンドラ番号の定義
$ 
$  M16C/では割込み番号と割込みハンドラ番号が1対1で対応する．
$ 

$INTNO_VALID = { 4, 5,..., 63 }$
$INHNO_VALID = INTNO_VALID$

$ 
$  例外番号の定義
$ 
$  固定ベクタテーブルのベクタテーブルアドレスの小さい順番に例外番号を割振る．
$  (予約領域も含む)
$ 

$EXCNO_VALID = { 0, 1,...,7 }$

$ 
$  INT割込みの番号
$ 
;
$INTNO_INT = { 4; 8; 9; 29; 30; 31 }$

$ 
$  割込み番号，割込みハンドラ番号，例外番号の範囲
$ 

$INTNO_RANGE = { 0 , 1,...,63 }$
$INHNO_RANGE = INTNO_RANGE$
$EXCNO_RANGE = { 0 , 1,...,7 }$

$ 
$  プロセッサ依存のテンプレートファイルのインクルード
$ 
$INCLUDE"m16c_nc30/prc.tf"$

