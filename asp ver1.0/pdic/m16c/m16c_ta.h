/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005,2006 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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

/*
 *  M16C用タイマドライバ
 *
 *  M16C/M32C/R32Cが持つタイマA用ドライバ．
 */

#ifndef TOPPERS_M16C_TA_H
#define TOPPERS_M16C_TA_H

/* タイマモード設定 */
#define MODE_TIMER		UINT_C(0x00)
#define MODE_EVTCNT		UINT_C(0x01)
#define MODE_ONESHOT	UINT_C(0x02)
#define MODE_PWM		UINT_C(0x03)

#define GATE_NONE		UINT_C(0x00)
#define GATE_TAI_L		UINT_C(0x01)
#define GATE_TAI_H		UINT_C(0x02)

#define CNTSRC_F1		UINT_C(0x00)
#define CNTSRC_F8		UINT_C(0x01)
#define CNTSRC_F2N		UINT_C(0x02)
#define CNTSRC_FC32		UINT_C(0x03)


#ifndef TOPPERS_MACRO_ONLY

/*
 *  タイマAドライバの初期化
 */
extern void m16c_ta_initialize(void);

/*
 *  タイマAドライバの終了
 */
extern void m16c_ta_terminate(void);

/*
 *  モード設定
 */
extern void m16c_ta_setmode
	(ID ch , uint8_t mode , uint8_t clksrc , uint8_t opt);

/*
 *  周期動作の開始
 */
extern void m16c_ta_start(ID ch , uint16_t period);

/*
 *  周期動作の停止
 */
extern void m16c_ta_stop(ID ch);

/*
 *  タイマレジスタ値の読み出し
 */
extern uint16_t m16c_ta_getcount(ID ch);

/*
 *  タイマレジスタ値の書き込み
 */
extern void m16c_ta_setcount(ID ch , uint16_t count);

#endif	/* TOPPERS_MACRO_ONLY */
#endif	/* TOPPERS_M16C_TA_H */
