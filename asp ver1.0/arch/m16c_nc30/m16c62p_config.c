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
 *  割込み要求ラインの属性の設定(プロセッサ依存部)
 */
void
m16c_config_int(INTNO intno)
{
	/* 割込み要因選択レジスタを設定する */
	switch(intno)
	{
		case	TINTNO_INT0:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x01;
		break;
		case	TINTNO_INT1:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x02;
		break;
		case	TINTNO_INT2:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x04;
		break;
		case	TINTNO_INT3:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x08;
		break;
		case	TINTNO_INT4:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x10;
		break;
		case	TINTNO_INT5:
		*((volatile uint8_t *) TADR_SFR_IFSR) |= 0x20;
		break;
		default:
		/* INT割込み以外はコンフィギュレータで異常とする。 */
		break;
	}
}

/* 割込み要因レジスタ */
volatile uint8_t * const intc_reg[INHNO_MAX] = 
{
	/* 0- */
	NULL ,	/* BRK */
	NULL ,	/* Reserve */
	NULL ,	/* Reserve */
	NULL ,	/* Reserve */
	(volatile uint8_t *)TADR_SFR_INT3IC ,	/* INT3	*/
	(volatile uint8_t *)TADR_SFR_TB5IC ,	/* タイマB5	*/
	(volatile uint8_t *)TADR_SFR_TB4IC ,	/* タイマB4	*/
	(volatile uint8_t *)TADR_SFR_TB3IC ,	/* タイマB3	*/
	/* 8- */
	(volatile uint8_t *)TADR_SFR_INT5IC ,	/* SIO4,INT5 */
	(volatile uint8_t *)TADR_SFR_INT4IC ,	/* SIO3,INT4 */
	(volatile uint8_t *)TADR_SFR_BCNIC ,	/* UARTバス衝突検出 */
	(volatile uint8_t *)TADR_SFR_DM0IC ,	/* DMA0 */
	(volatile uint8_t *)TADR_SFR_DM1IC ,	/* DMA1 */
	(volatile uint8_t *)TADR_SFR_KUPIC ,	/* キー入力割込み */
	(volatile uint8_t *)TADR_SFR_ADIC  ,	/* A/D */
	(volatile uint8_t *)TADR_SFR_S2TIC ,	/* UART2送信 */
	/* 16- */
	(volatile uint8_t *)TADR_SFR_S2RIC ,	/* UART2受信 */
	(volatile uint8_t *)TADR_SFR_S0TIC ,	/* UART0送信 */
	(volatile uint8_t *)TADR_SFR_S0RIC ,	/* UART0受信 */
	(volatile uint8_t *)TADR_SFR_S1TIC ,	/* UART1送信 */
	(volatile uint8_t *)TADR_SFR_S1RIC ,	/* UART1受信 */
	(volatile uint8_t *)TADR_SFR_TA0IC ,	/* タイマA0	*/
	(volatile uint8_t *)TADR_SFR_TA1IC ,	/* タイマA1	*/
	(volatile uint8_t *)TADR_SFR_TA2IC ,	/* タイマA2	*/
	/* 24- */
	(volatile uint8_t *)TADR_SFR_TA3IC ,	/* タイマA3	*/
	(volatile uint8_t *)TADR_SFR_TA4IC ,	/* タイマA4	*/
	(volatile uint8_t *)TADR_SFR_TB0IC ,	/* タイマB0	*/
	(volatile uint8_t *)TADR_SFR_TB1IC ,	/* タイマB1	*/
	(volatile uint8_t *)TADR_SFR_TB2IC ,	/* タイマB2	*/
	(volatile uint8_t *)TADR_SFR_INT0IC ,	/* INT0	*/
	(volatile uint8_t *)TADR_SFR_INT1IC ,	/* INT1	*/
	(volatile uint8_t *)TADR_SFR_INT2IC ,	/* INT2	*/
	/* 32- */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	/* 40- */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	/* 48- */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	/* 56- */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
	NULL ,	/* INT */
};
