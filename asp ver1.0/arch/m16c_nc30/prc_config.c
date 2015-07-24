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
 */

#include "kernel_impl.h"

/*
 *  割込み発生回数を保存する変数
 */
uint16_t intnest;

/* activate_contextで使用する一時変数 */
uint8_t *tsk_sp;

/*
 *  CPUロックフラグ実現のための変数
 */
#if TIPM_LOCK != -7
bool_t		lock_flag;		/* CPUロックフラグの値を保持する変数 */
uint16_t	saved_ipl;		/* 割込み優先度レベルを保存する変数 */
#endif	/* TIPM_LOCK != -7	*/

/*
 *  プロセッサ依存の初期化
 */
void
prc_initialize(void)
{
	/*
	 *  CPUロックフラグ実現のための変数の初期化
	 */
#if TIPM_LOCK != -7
	lock_flag = true;
	saved_ipl = IPL_ENAALL;
#endif	/* TIPM_LOCK != -7	*/
}

/*
 *  プロセッサ依存の終了処理
 */
void
prc_terminate(void)
{
	/* 特に必要な処理はない */
}


/*
 *  CPU例外の発生状況のログ出力
 *
 *  CPU例外ハンドラの中から，CPU例外情報ポインタ（p_excinf）を引数とし
 *  て呼び出すことで，CPU例外の発生状況をシステムログに出力する．
 */
#ifdef SUPPORT_XLOG_SYS

void
xlog_sys(void *p_excinf)
{
	syslog(LOG_ERROR , "r0 = %u") , *((uint16_t*)((intptr_t)p_excinf + 0));
	syslog(LOG_ERROR , "r1 = %u") , *((uint16_t*)((intptr_t)p_excinf + 2));
	syslog(LOG_ERROR , "r2 = %u") , *((uint16_t*)((intptr_t)p_excinf + 4));
	syslog(LOG_ERROR , "r3 = %u") , *((uint16_t*)((intptr_t)p_excinf + 6));
	syslog(LOG_ERROR , "a0 = %x") , *((uint16_t*)((intptr_t)p_excinf + 8));
	syslog(LOG_ERROR , "a2 = %x") , *((uint16_t*)((intptr_t)p_excinf + 10));
	syslog(LOG_ERROR , "sb = %x") , *((uint16_t*)((intptr_t)p_excinf + 12));
	syslog(LOG_ERROR , "fb = %x") , *((uint16_t*)((intptr_t)p_excinf + 14));
	syslog(LOG_ERROR , "pc = %x") , *((uint32_t*)((intptr_t)p_excinf + 16));
	syslog(LOG_ERROR , "flg = %x") , *((uint16_t*)((intptr_t)p_excinf + 20));
}

#endif /* SUPPORT_XLOG_SYS */

/*
 *  割込み要求ラインの属性の設定
 *
 *  ASPカーネルでの利用を想定して，パラメータエラーはアサーションでチェッ
 *  クしている．cfg_intサービスコールを設ける場合には，エラーを返すよう
 *  にすべきであろう．
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
	assert(VALID_INTNO_CFGINT(intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);
	
	/*
	 *  割込みのマスク
	 *
	 *  割込みを受け付けたまま，レベルトリガ／エッジトリガの設定や，割
	 *  込み優先度の設定を行うのは危険なため，割込み属性にかかわらず，
	 *  一旦マスクする．
	 */
	(void) x_disable_int(intno);
	
	/* INT端子の場合は割込み検知方法を設定する */
	/* レベルトリガ、INT割込み以外はコンフィグレータで異常とする。 */
	if((intatr & TA_POSEDGE) != 0U)
	{
		/* 立上がりエッジ */
		*(intc_reg[intno]) |= INTC_POLHIGH;
	}
	else
	{
		/* 立下りエッジ */
		*(intc_reg[intno]) &= ~INTC_POLHIGH;

		/* 両エッジ */
		if((intatr & TA_BOTHEDGE) != 0U)
		{
			m16c_config_int(intno);
		}
	}

	/*
	 *  M16Cでは割込み禁止/許可を割込み優先度設定で実現するため、
	 *  ここで割込み優先度の設定は行わない
	 */

	/*
	 *  割込みのマスク解除
 	 */
	if ((intatr & TA_ENAINT) == TA_ENAINT) {
		(void) x_enable_int(intno);
	}
}
