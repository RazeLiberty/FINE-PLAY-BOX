/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2008 by Witz Corporation, JAPAN
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
 *   M16C UART用 簡易SIOドライバ
 */

#include <sil.h>
#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "m16c_uart.h"

/* 送受信制御レジスタ0 */
#define CRS			UINT_C(0x04)
#define TXEPT		UINT_C(0x08)
#define CRD			UINT_C(0x10)
#define NCH			UINT_C(0x20)
#define CKPOL		UINT_C(0x40)
#define UFORM		UINT_C(0x80)

/* 送受信制御レジスタ1 */

#define TE			UINT_C(0x01)
#define TI			UINT_C(0x02)
#define RE			UINT_C(0x04)
#define RI			UINT_C(0x08)
#define IRS			UINT_C(0x10)
#define RRM			UINT_C(0x20)
#define LCH			UINT_C(0x40)
#define SCLKSTPB	UINT_C(0x80)

/* 送受信モードレジスタ */
#define NO_USE		UINT_C(0x00)
#define SYNC		UINT_C(0x01)
#define IIC			UINT_C(0x10)
#define ASYNC_7BIT	UINT_C(0x04)
#define ASYNC_8BIT	UINT_C(0x05)
#define ASYNC_9BIT	UINT_C(0x06)
#define CKDIR		UINT_C(0x08)
#define STPS		UINT_C(0x10)
#define ODDEVEN		UINT_C(0x20)
#define PARITY		UINT_C(0x40)
#define IOPOL		UINT_C(0x80)

/* UART受信バッファ */
#define RXDATA		UINT_C(0x00ff)
#define ABT			UINT_C(0x0400)
#define OER			UINT_C(0x1000)
#define FER			UINT_C(0x2000)
#define PER			UINT_C(0x4000)
#define SUM			UINT_C(0x8000)

/*
 *  シリアルI/Oポート初期化ブロックの定義
 */
typedef struct sio_port_initialization_block {
	volatile uint8_t	*ctlreg0 , *ctlreg1;	/* 送受信制御レジスタ0,1 */
	volatile uint8_t	*modereg;				/* 送受信モードレジスタ */
	volatile uint8_t	*baudratereg;			/* 転送速度レジスタ */
	volatile uint16_t	*txbufreg;				/* 送信バッファ */
	volatile uint16_t	*rxbufreg;				/* 受信バッファ */
	uint8_t		tx_intno;						/* 送信割り込み番号 */
	uint8_t		rx_intno;						/* 受信割り込み番号 */
} SIOPINIB;

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
struct sio_port_control_block {
	const SIOPINIB	*p_siopinib; 				/* シリアルI/Oポート初期化ブロック */
	intptr_t 	exinf;			 				/* 拡張情報 */
	bool_t		openflag;						/* オープン済みフラグ */
	bool_t		sendflag;						/* 送信割込みイネーブルフラグ */
	bool_t		getready;						/* 文字を受信した状態 */
	bool_t		putready;						/* 文字を送信できる状態 */
	bool_t		is_initialized; 				/* デバイス初期化済みフラグ */
};

/*
 *  シリアルI/Oポート管理ブロックのエリア
 */
static SIOPCB	siopcb_table[TNUM_SIOP];

/* レジスタテーブル */
static const SIOPINIB siopinib_table[TNUM_SIOP] =
{
	{
		(volatile uint8_t *)UART0_UC0_ADDR ,
		(volatile uint8_t *)UART0_UC1_ADDR ,
		(volatile uint8_t *)UART0_MODE_ADDR ,
		(volatile uint8_t *)UART0_BAUD_ADDR ,
		(volatile uint16_t *)UART0_TXBUF_ADDR ,
		(volatile uint16_t *)UART0_RXBUF_ADDR  ,
		UART0_TXINTNO ,
		UART0_RXINTNO ,
	} ,			/* UART0 */
#if TNUM_SIOP > 1
	{
		(volatile uint8_t *)UART1_UC0_ADDR ,
		(volatile uint8_t *)UART1_UC1_ADDR ,
		(volatile uint8_t *)UART1_MODE_ADDR ,
		(volatile uint8_t *)UART1_BAUD_ADDR ,
		(volatile uint16_t *)UART1_TXBUF_ADDR ,
		(volatile uint16_t *)UART1_RXBUF_ADDR ,
		UART1_TXINTNO ,
		UART1_RXINTNO	,
	} ,			/* UART1 */
#endif
#if TNUM_SIOP > 2
	{
		(volatile uint8_t *)UART2_UC0_ADDR ,
		(volatile uint8_t *)UART2_UC1_ADDR ,
		(volatile uint8_t *)UART2_MODE_ADDR ,
		(volatile uint8_t *)UART2_BAUD_ADDR ,
		(volatile uint16_t *)UART2_TXBUF_ADDR ,
		(volatile uint16_t *)UART2_RXBUF_ADDR ,
		UART2_TXINTNO , 
		UART2_RXINTNO	,
	} ,			/* UART2 */
#endif
#if TNUM_SIOP > 3
	{
		(volatile uint8_t *)UART3_UC0_ADDR ,
		(volatile uint8_t *)UART3_UC1_ADDR ,
		(volatile uint8_t *)UART3_MODE_ADDR ,
		(volatile uint8_t *)UART3_BAUD_ADDR ,
		(volatile uint16_t *)UART3_TXBUF_ADDR ,
		(volatile uint16_t *)UART3_RXBUF_ADDR  ,
		UART3_TXINTNO ,
		UART3_RXINTNO	,
	} ,			/* UART3 */
#endif
#if TNUM_SIOP > 4
	{
		(volatile uint8_t *)UART4_UC0_ADDR ,
		(volatile uint8_t *)UART4_UC1_ADDR ,
		(volatile uint8_t *)UART4_MODE_ADDR ,
		(volatile uint8_t *)UART4_BAUD_ADDR ,
		(volatile uint16_t *)UART4_TXBUF_ADDR ,
		(volatile uint16_t *)UART4_RXBUF_ADDR ,
		UART4_TXINTNO ,
		UART4_RXINTNO	,
	  } 			/* UART4 */
#endif
};

/*
 *  シリアルI/OポートIDから管理ブロックを取り出すためのマクロ
 */
#define INDEX_SIOP(siopid)	 ((uint_t)((siopid) - 1))
#define get_siopcb(siopid)	 (&(siopcb_table[INDEX_SIOP(siopid)]))
#define get_siopinib(siopid) (&(siopinib_table[INDEX_SIOP(siopid)]))


static void m16c_uart_setmode(const SIOPINIB *p_siopinib , uint8_t baud , uint8_t clksrc)
{
	/* 送受信禁止 */
	sil_wrb_mem(p_siopinib->ctlreg1 , 0x00U);
	
	/* モードレジスタ、送受信レジスタ0、1の初期化 */
	sil_wrb_mem(p_siopinib->modereg , ASYNC_8BIT);
	sil_wrb_mem(p_siopinib->ctlreg0 , clksrc | CRD);
	sil_wrb_mem(p_siopinib->ctlreg1 , (TE | RE));
	
	/* ボーレート設定 */
	sil_wrb_mem(p_siopinib->baudratereg , baud);
}

/*
 *  SIOドライバの初期化ルーチン
 */
void m16c_uart_initialize(void)
{
	SIOPCB	*p_siopcb;
	uint_t	i;

	/*
	 *  シリアルI/Oポート管理ブロックの初期化
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++)
	{
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->openflag = false;
		p_siopcb->sendflag = false;
	}
}

/*
 * カーネル起動時のバナー出力用の初期化
 */
void m16c_uart_init(ID siopid , uint8_t baud , uint8_t clksrc)
{
	SIOPCB          *p_siopcb   = get_siopcb(siopid);
	const SIOPINIB  *p_siopinib = get_siopinib(siopid);
	/*  この時点では、p_siopcb->p_siopinibは初期化されていない  */
	
	/*  二重初期化の防止  */
	p_siopcb->is_initialized = true;
	
	/*  ハードウェアの初期化処理と送信許可  */
	m16c_uart_setmode(p_siopinib , baud , clksrc);
	sil_wrb_mem(p_siopinib->ctlreg1 , (sil_reb_mem(p_siopinib->ctlreg1) | TE));
}

/*
 *  シリアルI/Oポートへのポーリングでの出力
 */
void m16c_uart_pol_putc(char c, ID siopid)
{
	const SIOPINIB *p_siopinib;
	
	p_siopinib = get_siopinib(siopid);
	
	while((sil_reb_mem(p_siopinib->ctlreg1) & TI) == 0)
		;
	sil_wrh_mem(p_siopinib->txbufreg , (uint16_t)c);
}

/*
 *  シリアルI/Oポートのオープン
 */
SIOPCB *m16c_uart_opn_por
	(ID siopid, intptr_t exinf , uint8_t baud , uint8_t clksrc)
{
	SIOPCB          *p_siopcb;
	const SIOPINIB  *p_siopinib;
	
	p_siopcb = get_siopcb(siopid);
	p_siopinib = p_siopcb->p_siopinib;
	
	/*
	*  ハードウェアの初期化     
	*  既に初期化している場合は、二重に初期化しない。
	*/
	if (!(p_siopcb->is_initialized))
	{
		m16c_uart_setmode(p_siopinib , baud , clksrc);
		p_siopcb->is_initialized = true;
	}
	
	p_siopcb->exinf = exinf;
	p_siopcb->getready = p_siopcb->putready = false;
	p_siopcb->openflag = true;
	
    return(p_siopcb);
}

/*
 *  シリアルI/Oポートのクローズ
 */
void m16c_uart_cls_por(SIOPCB *p_siopcb)
{
	/*
	 * UART停止
	 */
	sil_wrh_mem(p_siopcb->p_siopinib->ctlreg1, 0x00U);
	p_siopcb->openflag = false;
	p_siopcb->is_initialized = false;
}

/*
 *  シリアルI/Oポートへの文字送信
 */
bool_t m16c_uart_snd_chr(SIOPCB *p_siopcb, char_t c)
{
	bool_t ercd = false;
	
	if ((sil_reb_mem(p_siopcb->p_siopinib->ctlreg1) & TI) != 0)
	{
		sil_wrh_mem(p_siopcb->p_siopinib->txbufreg , (uint16_t)c);
		ercd = true;
	}
	return ercd;
}

/*
 *  シリアルI/Oポートからの文字受信
 */
int_t m16c_uart_rcv_chr(SIOPCB *p_siopcb)
{
	int_t c = -1;
	
	if ((sil_reb_mem(p_siopcb->p_siopinib->ctlreg1) & RI) != 0)
	{
		c = (int)(sil_reh_mem(p_siopcb->p_siopinib->rxbufreg) & RXDATA);
	}
	return c;
}

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
void  m16c_uart_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
		case SIO_RDY_SND:
			ena_int(p_siopcb->p_siopinib->tx_intno);
			break;
		case SIO_RDY_RCV:
			ena_int(p_siopcb->p_siopinib->rx_intno);
			break;
		default:
			assert(1);
			break;
	}
}

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
void m16c_uart_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
		case SIO_RDY_SND:
			dis_int(p_siopcb->p_siopinib->tx_intno);
			break;
		case SIO_RDY_RCV:
			dis_int(p_siopcb->p_siopinib->rx_intno);
			break;
		default:
			assert(1);
			break;
	}
}

/*
 *  SIOの割込みサービスルーチン
 */
void m16c_uart_tx_isr(ID siopid)
{
	SIOPCB	*p_siopcb = get_siopcb(siopid);

	if ((sil_reb_mem(p_siopcb->p_siopinib->ctlreg1) & TI) != 0U)
	{
		/*
		 *  送信可能コールバックルーチンを呼び出す．
		 */
		m16c_uart_irdy_snd(p_siopcb->exinf);
	}
}

void m16c_uart_rx_isr(ID siopid)
{
	SIOPCB	*p_siopcb = get_siopcb(siopid);

	if ((sil_reb_mem(p_siopcb->p_siopinib->ctlreg1) & RI) != 0U)
	{
		/*
		 *  受信通知コールバックルーチンを呼び出す．
		 */
		m16c_uart_irdy_rcv(p_siopcb->exinf);
	}
}

