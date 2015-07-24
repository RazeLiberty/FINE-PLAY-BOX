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
 *  上記著作権者は，以下の (1)～(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 */

/*
 *		プロセッサ依存モジュール（M16C用）
 *
 *  このインクルードファイルは，target_config.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  プロセッサの特殊命令のインライン関数定義
 */
#include "prc_insn.h"
#include "interrupt.h"


/*
 *  非タスクコンテキスト用のスタック初期値
 */

#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char_t *)(istk) + (istksz)))

/*
 *  タスクコンテキストブロックの定義
 */
typedef struct task_context_block {
	void		*sp;		/* スタックポインタ */
	uint32_t	pc;			/* プログラムカウンタ */
} CTXB;

/*
 *  割込み発生回数を保存する変数
 */
extern uint16_t intnest;


/*
 *  CPUロック状態での割込み優先度マスク
 *
 *  TIPM_LOCKは，CPUロック状態での割込み優先度マスク，すなわち，カーネ
 *  ル管理外のものを除くすべての割込み要求をマスクする値に定義する．
 *
 *  例えばTIPM_LOCKを-6に設定すると，レベル7の割込みがカーネル管理外と
 *  なる．TIPM_LOCKを-7に設定すると，NMI以外にカーネル管理外の割込みを
 *  設けないことになる（この場合には-7に設定することを推奨する）．
 */
#ifndef TIPM_LOCK
#define TIPM_LOCK	(-7)		/* カーネル管理外の割込みを設けない */
#endif /* TIPM_LOCK */

/*
 *  TOPPERS標準割込み処理モデルの実現
 *
 */

/*
 *  コンテキストの参照
 *
 *  M16Cでは，割込みの戻り先がタスクかどうかを判断するために intnest
 *  を使用している．これを用いてコンテキストを判断する．
 */
Inline bool_t
sense_context(void)
{
	/*  ネストカウンタ0より大なら非タスクコンテキスト  */
	return (intnest > 0);
}

/*
 *  CPUロックフラグ実現のための変数
 *
 *  これらの変数は，CPUロック状態の時のみ書き換えてよいものとする．
 */
#if TIPM_LOCK != -7
extern bool_t		lock_flag;		/* CPUロックフラグの値を保持する変数 */
extern uint16_t	saved_ipl;		/* 割込み優先度レベルを保存する変数 */
#endif	/* TIPM_LOCK != -7	*/

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  割込み優先度マスクの外部表現と内部表現の変換
 *
 *  M16Cでは，フラグレジスタ（FLG）の下から12～14ビット目の3ビットに
 *  割込み優先度レベル（IPL）が置かれている．
 *  カーネル管理外割込みを実装する場合にIPLを使用した制御を行う．
 *  カーネルは割込み優先度マスク（-1から連続した負の値）で管理されて
 *  いるためIPLとの変換が必要となる．
 */
#define IPL2IPM(ipl)	(-((PRI)((ipl) >> 12)))			/* IPLをIPMに	*/
#define IPM2IPL(ipm)	(((uint16_t)(-(ipm))) << 12)	/* IPMをIPLに	*/


/*
 *  CPUロック状態での割込み優先度マスクのIPL
 */
#define IPL_LOCK	(IPM2IPL(TIPM_LOCK))

/*
 *  TIPM_ENAALL（割込み優先度マスク全解除）のIPL
 */
#define IPL_ENAALL		(IPM2IPL(TIPM_ENAALL))

#ifndef TOPPERS_MACRO_ONLY

/*
 *  CPUロック状態への移行
 *
 *  IPM（ハードウェアの割込み優先度マスク）を，saved_iipmに保存し，カー
 *  ネル管理外のものを除くすべての割込み要求をマスクする値（TIPM_LOCK）
 *  に設定する．また，lock_flagをtrueにする．
 *
 *  IPMが，最初からTIPM_LOCKと同じかそれより高い場合には，それを
 *  saved_iipmに保存するのみで，TIPM_LOCKには設定しない．これは，モデル
 *  上の割込み優先度マスクが，TIPM_LOCKと同じかそれより高いレベルに設定
 *  されている状態にあたる．
 *
 *  この関数は，CPUロック状態（lock_flagがtrueの状態）で呼ばれることは
 *  ないものと想定している．
 */
Inline void
x_lock_cpu(void)
{
#if TIPM_LOCK == -7
	disint();
#else	/* TIPM_LOCK == -7	*/
	uint16_t	ipl;

	/*
	 *  current_ipl()の返り値を直接saved_iplに保存せず，一時変数ipl
	 *  を用いているのは，current_ipl()を呼んだ直後に割込みが発生し，
	 *  起動された割込み処理でsaved_iplが変更される可能性があるためで
	 *  ある．
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
 *  CPUロック状態の解除
 *
 *  lock_flagをfalseにし，IPM（ハードウェアの割込み優先度マスク）を，
 *  saved_iipmに保存した値に戻す．
 *
 *  この関数は，CPUロック状態（lock_flagがtrueの状態）でのみ呼ばれるも
 *  のと想定している．
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
 *  CPUロック状態の参照
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
 * （モデル上の）割込み優先度マスクの設定
 *
 *  CPUロックフラグがクリアされている時は，ハードウェアの割込み優先度マ
 *  スクを設定する．CPUロックフラグがセットされている時は，saved_iipm
 *  を設定し，さらに，ハードウェアの割込み優先度マスクを，設定しようと
 *  した（モデル上の）割込み優先度マスクとTIPM_LOCKの高い方に設定する．
 */
Inline void
x_set_ipm(PRI intpri)
{
	set_ipl((current_ipl() & ~FLG_IPL_MASK) | IPM2IPL(intpri));
}

#define t_set_ipm(intpri)	x_set_ipm(intpri)
#define i_set_ipm(intpri)	x_set_ipm(intpri)

/*
 * （モデル上の）割込み優先度マスクの参照
 *
 *  CPUロックフラグがクリアされている時はハードウェアの割込み優先度マ
 *  スクを，セットされている時はsaved_iipmを参照する．
 */
Inline PRI
x_get_ipm(void)
{
	return IPL2IPM(current_ipl() & FLG_IPL_MASK);
}

#define t_get_ipm()	x_get_ipm()
#define i_get_ipm()	x_get_ipm()


/*
 *  割込み番号の範囲の判定
 */
#define VALID_INTNO(intno)	((intno) < INHNO_MAX)
#define VALID_INTNO_DISINT(intno)	VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)	VALID_INTNO(intno)

/*
 *  IPLから割込み制御レジスタでの表現に変換するマクロ
 */
#define IPL2ILVL(ipl)	(-(ipl))

/*
 *  割込みコントローラレジスタのアドレステーブル
 *  (target_config.cに定義)
 */
extern volatile uint8_t * const intc_reg[];

/*
 *  割込み要因毎のレベル定義テーブル
 *  (tfによる出力)
 */
extern const PRI intpri_table[];

/*
 *  割込み制御レジスタ関連の定義
 */
#define INTC_LVLMASK	(0x07U)
#define INTC_IRMASK		(0x08U)
#define INTC_POLMASK	(0x10U)		/* INT割込みのみ */
#define INTC_LVSMASK	(0x20U)		/* INT割込みのみ */

#define INTC_POLHIGH	(0x10U)		/* INT割込みのみ */
#define INTC_POLLOW		(0x00U)		/* INT割込みのみ */
#define INTC_LVSEDGE	(0x00U)		/* INT割込みのみ */
#define INTC_LVSLVL		(0x20U)		/* INT割込みのみ */

/*
 *  割込み要求禁止フラグのセット
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをセットしようとした場合には，falseを返す．
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	/* レベル定義が0である場合はCFG_INTされていない */
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
 *  割込み要求禁止フラグのクリア
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	/* レベル定義が0である場合はCFG_INTされていない */
	if(intpri_table[intno] == 0U)
	{
		return (false);
	}
	/* 割込みレベルを元に戻す */
	*intc_reg[intno] = (*intc_reg[intno] & ~INTC_LVLMASK) | IPL2ILVL(intpri_table[intno]);
	
	return(true);
}

#define t_enable_int(intno)		x_enable_int(intno)
#define i_enable_int(intno)		x_enable_int(intno)

/*
 *  割込み要求のクリア
 */
Inline void
x_clear_int(INTNO intno)
{
	*(intc_reg[intno]) &= ~INTC_IRMASK;
}

#define t_clear_int(intno)		x_clear_int(intno)
#define i_clear_int(intno)		x_clear_int(intno)

/*
 *  割込み要求のチェック
 */
Inline bool_t
x_probe_int(INTNO intno)
{
	return (((*intc_reg[intno] & INTC_IRMASK) == INTC_IRMASK)? true : false);
}

#define t_probe_int(intno)		x_probe_int(intno)
#define i_probe_int(intno)		x_probe_int(intno)

/*
 *  割込み要求ラインの属性の設定
 */
extern void	x_config_int(INTNO intno, ATR intatr, PRI intpri);

/*
 *  割込みハンドラの入口で必要なIRC操作
 *
 */
Inline void
i_begin_int(INTNO intno)
{
	/* 特に行うべき処理はない */
}

/*
 *  割込みハンドラの出口で必要なIRC操作
 *
 */
Inline void
i_end_int(INTNO intno)
{
	/* 特に行うべき処理はない */
}


/*
 *  最高優先順位タスクへのディスパッチ（prc_support.a30）
 *
 *  dispatchは，タスクコンテキストから呼び出されたサービスコール処理か
 *  ら呼び出すべきもので，タスクコンテキスト・CPUロック状態・ディスパッ
 *  チ許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さな
 *  ければならない．
 */
extern void	dispatch(void);

/*
 *  ディスパッチャの動作開始（prc_support.a30）
 *
 *  start_dispatchは，カーネル起動時に呼び出すべきもので，全ての割込み
 *  を禁止した状態（全割込みロック状態と同等の状態）で呼び出さなければ
 *  ならない．
 */
extern void	start_dispatch(void) NoReturn;

/*
 *  現在のコンテキストを捨ててディスパッチ（prc_support.a30）
 *
 *  exit_and_dispatchは，ext_tskから呼び出すべきもので，タスクコンテキ
 *  スト・CPUロック状態・ディスパッチ許可状態・（モデル上の）割込み優先
 *  度マスク全解除状態で呼び出さなければならない．
 */
#define _kernel_exit_and_dispatch();	\
	_exit_and_dispatch();		\
	ercd = E_SYS;
extern void	_exit_and_dispatch(void) NoReturn;

/*
 *  カーネルの終了処理の呼出し（prc_support.a30）
 *
 *  call_exit_kernelは，カーネルの終了時に呼び出すべきもので，非タスク
 *  コンテキストに切り換えて，カーネルの終了処理（exit_kernel）を呼び出
 *  す．
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  タスクコンテキストの初期化
 *
 *  タスクが休止状態から実行できる状態に移行する時に呼ばれる．この時点
 *  でスタック領域を使ってはならない．
 *
 *  activate_contextを，インライン関数ではなくマクロ定義としているのは，
 *  この時点ではTCBが定義されていないためである．
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
 *  calltexは使用しない
 */
#define OMIT_CALLTEX

/*
 *  割込みハンドラの設定
 *
 *  M16CはROMに割込みベクタを配置するため，本関数は空関数で実装する．
 */
Inline void
x_define_inh(INHNO inhno, FP inthdr)
{
}

/*
 *  CPU例外ハンドラの設定
 *
 *  M16CはROMに例外ベクタを配置するため，本関数は空関数で実装する．
 */
Inline void
x_define_exc(EXCNO excno, FP exchdr)
{
}

/*
 *  割込み/例外ハンドラの入口処理の生成マクロ
 *
 *  テンプレートファイルにより生成するため空マクロとする．
 */
#define HDR_ENTRY(hdr, intexc_num , tobejmp)

/*
 *  割込みハンドラの入口処理の生成マクロ
 */
#define _INT_ENTRY(inhno, inthdr)				_kernel_##inthdr##_##inhno##_entry
#define INT_ENTRY(inhno, inthdr)				_INT_ENTRY(inhno , inthdr)

#define _INTHDR_ENTRY(inhno, inhno_num ,inthdr)	\
		extern _kernel_##inthdr##_##inhno##_entry(void);
#define INTHDR_ENTRY(inhno, inhno_num ,inthdr)	_INTHDR_ENTRY(inhno, inhno_num ,inthdr)

/*
 *  CPU例外ハンドラの入口処理の生成マクロ
 */
#define _EXC_ENTRY(excno , exchdr)					_kernel_##exchdr##_##excno##_entry
#define EXC_ENTRY(excno , exchdr)					_EXC_ENTRY(excno , exchdr)

#define _EXCHDR_ENTRY(excno , excno_num , exchdr)	\
		extern _kernel_##exchdr##_##excno##_entry(void);
#define EXCHDR_ENTRY(excno , excno_num , exchdr)	_EXCHDR_ENTRY(excno , excno_num , exchdr)


/*
 *  CPU例外の発生した時のコンテキストの参照
 *
 *  CPU例外の発生した時のコンテキストが，タスクコンテキストの時にfalse，
 *  そうでない時にtrueを返す．
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
	/* 
	 *  ネストカウンタが1より大なら非タスクコンテキスト
	 */
	return( intnest > 1u );
}

/*
 *  CPU例外の発生した時のIPLの参照
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
 *  CPU例外の発生した時のコンテキストと割込みのマスク状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル実行中でなく，タスクコ
 *  ンテキストであり，全割込みロック状態でなく，CPUロック状態でなく，
 *  （モデル上の）割込み優先度マスク全解除状態である時にtrue，そうでな
 *  い時にfalseを返す（CPU例外がカーネル管理外の割込み処理中で発生した
 *  場合にもfalseを返す）．
 *
 *  カーネル実行中でない→ (TIPM_LOCK== -7) Iフラグ == 0
 *                         (else)           IPL < IPL_LOCK
 *  タスクコンテキストである→intnest == 0
 *  全割込みロックでない→ Iフラグ == 0
 *  割込み優先度マスクが全解除→IPL == 0
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
 *  CPU例外の発生した時のコンテキストと割込み／CPUロック状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル実行中でなく，タスクコ
 *  ンテキストであり，全割込みロック状態でなく，CPUロック状態でない時
 *  にtrue，そうでない時にfalseを返す（CPU例外がカーネル管理外の割込み
 *  処理中で発生した場合にもfalseを返す）．
 *
 *  カーネル実行中でない→ (TIPM_LOCK== -7) Iフラグ == 0
 *                         (else)           IPL < TIPM_LOCK
 *  タスクコンテキストである→intnest < 1 
 *  全割込みロックでない→ Iフラグ == 0
 *  CPUロック状態でない→(TIPM_LOCK== -7) Iフラグ == 0
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
 *  プロセッサ依存の初期化
 */
extern void	prc_initialize(void);

/*
 *  プロセッサ依存の終了時処理
 */
extern void	prc_terminate(void);


#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */
