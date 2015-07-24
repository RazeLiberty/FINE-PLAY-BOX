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
 *  上記著作権者は，Free Software Foundation によって公表されている 
 *  GNU General Public License の Version 2 に記述されている条件か，以
 *  下の(1)～(4)の条件を満たす場合に限り，本ソフトウェア（本ソフトウェ
 *  アを改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを再利用可能なバイナリコード（リロケータブルオブ
 *      ジェクトファイルやライブラリなど）の形で利用する場合には，利用
 *      に伴うドキュメント（利用者マニュアルなど）に，上記の著作権表示，
 *      この利用条件および下記の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを再利用不可能なバイナリコードの形または機器に組
 *      み込んだ形で利用する場合には，次のいずれかの条件を満たすこと．
 *    (a) 利用に伴うドキュメント（利用者マニュアルなど）に，上記の著作
 *        権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 利用の形態を，別に定める方法によって，上記著作権者に報告する
 *        こと．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者を免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者は，
 *  本ソフトウェアに関して，その適用可能性も含めて，いかなる保証も行わ
 *  ない．また，本ソフトウェアの利用により直接的または間接的に生じたい
 *  かなる損害に関しても，その責任を負わない．
 * 
 */

/*
 *	RSK-M16C-62P UART用シリアルI/Oモジュール
 */

#include <kernel.h>
#include <sil.h>
#include <t_syslog.h>
#include "RSK-M16C-62P.h"
#include "target_serial.h"

/*
 *  SIOドライバの初期化
 */
void
sio_initialize(intptr_t exinf)
{
#ifndef	USE_KD3083
	m16c_uart_initialize();
#endif
}

/*
 *  シリアルI/Oポートのオープン
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB  *p_siopcb;
	ER      ercd;
	
	/*
	 *  シリアルI/O割込みをマスクする．
	 */
	ercd = dis_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
	ercd = dis_int(INTNO_SIO_RX);
	assert(ercd == E_OK);
	
#ifndef	USE_KD3083
	/*
	 *  デバイス依存のオープン処理．
	 */
	p_siopcb = 
		m16c_uart_opn_por(siopid , exinf , UART_BAUDRATE , UART_CLKSRC);
	
	/*
	 *  シリアルI/O割込みのマスクを解除する．
	 */
	ercd = ena_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
	ercd = ena_int(INTNO_SIO_RX);
	assert(ercd == E_OK);
#endif
	return(p_siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	ER        ercd;
	
#ifndef	USE_KD3083
	/*
	 *  デバイス依存のクローズ処理．
	 */
	m16c_uart_cls_por(p_siopcb);
#endif
	
	/*
	 *  シリアルI/O割込みをマスクする．
	 */
	ercd = dis_int(INTNO_SIO_TX);
	assert(ercd == E_OK);
	ercd = dis_int(INTNO_SIO_RX);
	assert(ercd == E_OK);
}

/*
 *  SIOの割込みハンドラ
 */
void
sio_tx_isr(intptr_t exinf)
{
#ifndef	USE_KD3083
	m16c_uart_tx_isr(exinf);
#endif
}


/*
 *  SIOの割込みハンドラ
 */
void
sio_rx_isr(intptr_t exinf)
{
#ifndef	USE_KD3083
	m16c_uart_rx_isr(exinf);
#endif
}

/*
 *  シリアルI/Oポートへの文字送信
 */
bool_t
sio_snd_chr(SIOPCB *siopcb, char_t c)
{
#ifndef	USE_KD3083
	return(m16c_uart_snd_chr(siopcb, c));
#else
	return true;
#endif
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t
sio_rcv_chr(SIOPCB *siopcb)
{
#ifndef	USE_KD3083
	return(m16c_uart_rcv_chr(siopcb));
#else
	return 0;
#endif
}

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
void
sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
#ifndef	USE_KD3083
	m16c_uart_ena_cbr(siopcb, cbrtn);
#endif
}

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
void
sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
#ifndef	USE_KD3083
	m16c_uart_dis_cbr(siopcb, cbrtn);
#endif
}

/*
 *  シリアルI/Oポートからの送信可能コールバック
 */
void
m16c_uart_irdy_snd(intptr_t exinf)
{
#ifndef	USE_KD3083
	sio_irdy_snd(exinf);
#endif
}

/*
 *  シリアルI/Oポートからの受信通知コールバック
 */
void
m16c_uart_irdy_rcv(intptr_t exinf)
{
#ifndef	USE_KD3083
	sio_irdy_rcv(exinf);
#endif
}

