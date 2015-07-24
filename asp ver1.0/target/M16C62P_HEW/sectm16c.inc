;*by K.H line95
;*   TOPPERS/ASP Kernel
;*       Toyohashi Open Platform for Embedded Real-Time Systems/
;*       Advanced Standard Profile Kernel
;*  
;*   Copyright (C) 2008 by Witz Corporation, JAPAN
;* 
;*  上記著作権者は，Free Software Foundation によって公表されている 
;*  GNU General Public License の Version 2 に記述されている条件か，以
;*  下の(1)～(4)の条件を満たす場合に限り，本ソフトウェア（本ソフトウェ
;*  アを改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
;*  利用と呼ぶ）することを無償で許諾する．
;*  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
;*      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
;*      スコード中に含まれていること．
;*  (2) 本ソフトウェアを再利用可能なバイナリコード（リロケータブルオブ
;*      ジェクトファイルやライブラリなど）の形で利用する場合には，利用
;*      に伴うドキュメント（利用者マニュアルなど）に，上記の著作権表示，
;*      この利用条件および下記の無保証規定を掲載すること．
;*  (3) 本ソフトウェアを再利用不可能なバイナリコードの形または機器に組
;*      み込んだ形で利用する場合には，次のいずれかの条件を満たすこと．
;*    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
;*        権表示，この利用条件および下記の無保証規定を掲載すること．
;*    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
;*        こと．
;*  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
;*      害からも，上記著作権者を免責すること．
;* 
;*  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
;*  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
;*  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
;*  かなる損害に関しても，その責任を負わない．

;
;  ターゲットシステム依存セクション定義ファイル(RSK-M16C-62P用)
;

;
;  セクションの定義
;

	;
	; 初期値有りデータ領域のセクション
	;
	.section	data_NE,DATA
	.org	0410H

	;
	; 初期値無し偶数データ領域のセクション
	;
	.section	bss_NE,DATA

	;
	; 初期値有り奇数データ領域のセクション
	;
	.section	data_NO,DATA

	;
	; 初期値無し奇数データ領域のセクション
	;
	.section	bss_NO,DATA

	;
	; カーネルスタック領域のセクション
	;
	.section	stack,DATA
	.org	07C00H
	.blkb	0400H
	.glb DEFAULT_ISTK_TOP
DEFAULT_ISTK_TOP:

	;
	; CODE領域のセクション
	;
	.section	program,CODE
	.org	0A0000H					; 080000H -> 0A0000Hに変更

	;
	; ROデータ領域のセクション
	;
	.section	rom_FE,ROMDATA,ALIGN
	.section	rom_FO,ROMDATA

	;
	; DATA領域の初期値
	;
	.section	data_NEI,ROMDATA,ALIGN
	.section	data_NOI,ROMDATA

	;
	; 可変ベクタテーブル領域のセクション
	;
	.section	vvector,CODE
;	.org	0FFEDCH
	.org	0fa000h		; for monitor on board  by K.H

	.glb VVECTOR_TOP
VVECTOR_TOP:

	;
	; 固定ベクタテーブル領域のセクション
	;
	.section	fvector,CODE
	.org	0FFFDCH


