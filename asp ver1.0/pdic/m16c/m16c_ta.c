/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
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
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 */

#include <sil.h>
#include "target_syssvc.h"
#include "m16c/m16c_ta.h"

/* タイマレジスタ情報 */
typedef struct _M16C_TIMERREG
{
	volatile uint8_t	*mode;				/* タイマモードレジスタ */
	volatile uint16_t	*counter;			/* カウンタレジスタ */
	volatile uint8_t	*start;				/* カウント開始レジスタ */
	volatile uint8_t	*updown;			/* アップカウント/ダウンカウント選択レジスタ */
	volatile uint8_t	*oneshot;			/* ワンショット開始レジスタ */
	volatile uint8_t	*trigsel;			/* トリガ選択レジスタ */
	uint8_t				bitmsk;				/* スタートレジスタ操作用のビットマスク */
	uint8_t				trig_bitmask;		/* トリガ選択レジスタ用のビット位置オフセット */
	uint8_t				intno;				/* 割り込み要因番号 */
} M16C_TIMERREG;                    

/* レジスタテーブル */
static M16C_TIMERREG const timerreg_table[TNUM_M16C_TA] =
{
	/* タイマA0 */
	{
		(volatile uint8_t *)TA0MR_ADDR ,		/* タイマモードレジスタ */
		(volatile uint16_t *)TA0_ADDR ,	/* カウンタレジスタ */
		(volatile uint8_t *)TABSR_ADDR ,	/* カウント開始レジスタ */
		(volatile uint8_t *)UDF_ADDR ,		/* アップカウント/ダウンカウント選択レジスタ */
		(volatile uint8_t *)ONSF_ADDR ,		/* ワンショット開始レジスタ */
		(volatile uint8_t *)ONSF_ADDR ,		/* トリガ選択レジスタ */
		TA0_START_BIT ,						/* カウント開始レジスタ操作用ビットマスク */
		TA0_TRIGSEL_OFFSET ,					/* トリガ選択レジスタ用のビット位置オフセット */
		(INT_TA0) ,							/* 割り込み要因番号 */
	} ,
#if	TNUM_M16C_TA > 2
	/* タイマA1 */
	{
		(volatile uint8_t *)TA1MR_ADDR ,		/* タイマモードレジスタ */
		(volatile uint16_t *)TA1_ADDR ,	/* カウンタレジスタ */
		(volatile uint8_t *)TABSR_ADDR ,	/* カウント開始レジスタ */
		(volatile uint8_t *)UDF_ADDR ,		/* アップカウント/ダウンカウント選択レジスタ */
		(volatile uint8_t *)ONSF_ADDR ,		/* ワンショット開始レジスタ */
		(volatile uint8_t *)TAGSR_ADDR ,	/* トリガ選択レジスタ */
		TA1_START_BIT ,						/* レジスタ操作用のビットマスク */
		TA1_TRIGSEL_OFFSET ,				/* トリガ選択レジスタ用のビット位置オフセット */
		(INT_TA1) ,							/* 割り込み要因番号 */
	} ,
#endif
#if	TNUM_M16C_TA > 3
	/* タイマA2 */
	{
		(volatile uint8_t *)TA2MR_ADDR ,		/* タイマモードレジスタ */
		(volatile uint16_t *)TA2_ADDR ,	/* カウンタレジスタ */
		(volatile uint8_t *)TABSR_ADDR ,	/* カウント開始レジスタ */
		(volatile uint8_t *)UDF_ADDR ,		/* アップカウント/ダウンカウント選択レジスタ */
		(volatile uint8_t *)ONSF_ADDR ,		/* ワンショット開始レジスタ */
		(volatile uint8_t *)TAGSR_ADDR ,	/* トリガ選択レジスタ */
		TA2_START_BIT ,						/* レジスタ操作用のビットマスク */
		TA2_TRIGSEL_OFFSET ,				/* トリガ選択レジスタ用のビット位置オフセット */
		(INT_TA2) ,							/* 割り込み要因番号 */
	} ,
#endif
#if	TNUM_M16C_TA > 4
	/* タイマA3 */
	{
		(volatile uint8_t *)TA3MR_ADDR ,		/* タイマモードレジスタ */
		(volatile uint16_t *)TA3_ADDR ,	/* カウンタレジスタ */
		(volatile uint8_t *)TABSR_ADDR ,	/* カウント開始レジスタ */
		(volatile uint8_t *)UDF_ADDR ,		/* アップカウント/ダウンカウント選択レジスタ */
		(volatile uint8_t *)ONSF_ADDR ,		/* ワンショット開始レジスタ */
		(volatile uint8_t *)TAGSR_ADDR ,	/* トリガ選択レジスタ */
		TA3_START_BIT ,						/* レジスタ操作用のビットマスク */
		TA3_TRIGSEL_OFFSET ,				/* トリガ選択レジスタ用のビット位置オフセット */
		(INT_TA3) ,							/* 割り込み要因番号 */
	} ,
#endif
#if	TNUM_M16C_TA > 5
	/* タイマA4 */
	{
		(volatile uint8_t *)TA4MR_ADDR ,		/* タイマモードレジスタ */
		(volatile uint16_t *)TA4_ADDR ,	/* カウンタレジスタ */
		(volatile uint8_t *)TABSR_ADDR ,	/* カウント開始レジスタ */
		(volatile uint8_t *)UDF_ADDR ,		/* アップカウント/ダウンカウント選択レジスタ */
		(volatile uint8_t *)ONSF_ADDR ,		/* ワンショット開始レジスタ */
		(volatile uint8_t *)TAGSR_ADDR ,	/* トリガ選択レジスタ */
		TA4_START_BIT ,						/* レジスタ操作用のビットマスク */
		TA4_TRIGSEL_OFFSET ,				/* トリガ選択レジスタ用のビット位置オフセット */
		(INT_TA3) ,							/* 割り込み要因番号 */
	} ,
#endif
};

/*
 *  レジスタ情報の取得
 */
#define get_timerreg(ch)	(&(timerreg_table[(ch)]))

/*
 *  タイマAドライバの初期化
 */
void m16c_ta_initialize(void)
{
	const M16C_TIMERREG *tmreg;
	uint8_t i;
	
	for(i = 0 ; i < TNUM_M16C_TA ; i++)
	{
		tmreg = get_timerreg(i);
		/* タイマ停止 */
		*(tmreg->start) &= ~(tmreg->bitmsk);
	}
	
}

/*
 *  タイマAドライバの終了
 */
void m16c_ta_terminate(void)
{
	const M16C_TIMERREG *tmreg;
	uint8_t i;
	
	for(i = 0 ; i < TNUM_M16C_TA ; i++)
	{
		tmreg = get_timerreg(i);
		/* タイマ停止 */
		*(tmreg->start) &= ~(tmreg->bitmsk);
	}
}

/*
 *  モード設定
 */
void m16c_ta_setmode(ID ch , uint8_t mode , uint8_t clksrc , uint8_t opt)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	/* モードレジスタへの設定 */
	sil_wrb_mem(tmreg->mode , mode | (clksrc << 6U) | (opt << 3U));
}

/*
 *  周期動作の開始
 */
void m16c_ta_start(ID ch , uint16_t period)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	/* 周期設定 */
	sil_wrh_mem(tmreg->counter , period);
	/* タイマスタート */
	sil_wrb_mem(tmreg->start , 
		(sil_reb_mem(tmreg->start) | tmreg->bitmsk));
}

/*
 *  周期動作の停止
 */
void m16c_ta_stop(ID ch)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	/* タイマストップ */
	*(tmreg->start) &= ~(tmreg->bitmsk);
}

/*
 *  タイマレジスタ値の読み出し
 */
uint16_t m16c_ta_getcount(ID ch)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	return sil_reh_mem(tmreg->counter);
}

/*
 *  タイマレジスタ値の書き込み
 */
void m16c_ta_setcount(ID ch , uint16_t count)
{
	const M16C_TIMERREG *tmreg = get_timerreg(ch);
	
	sil_wrh_mem(tmreg->counter , count);
}

