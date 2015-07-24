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
 *		プロセッサの特殊命令のインライン関数定義（M16C用）
 */

#ifndef	TOPPERS_PRC_INSN_H
#define	TOPPERS_PRC_INSN_H

#define FLG_I_MASK		(0x0040u)
#define FLG_IPL_MASK	(0x7000u)

Inline volatile unsigned short current_flgreg(void);
Inline uint16_t current_ipl( void );


/*
 *  フラグレジスタ(FLG)の現在値の読出し
 */

Inline volatile uint16_t
current_flgreg(void)
{
	volatile uint16_t flg;
	Asm("	stc flg, $$[FB]", flg);
	return(flg);
}


/*
 *  フラグレジスタ（FLG）の現在値の読出し
 */
Inline uint16_t
current_ipl( void )
{
	volatile uint16_t	ipl;
	Asm("	stc flg, $$[FB]", ipl);
	return ipl;
}

/*
 *  フラグレジスタ（FLG）の現在値の設定
 */

/*
 *  IPLの設定
 */
Inline void
set_ipl(uint16_t ipl)
{
	volatile uint16_t flg_reg = ipl;
	Asm("	ldc $$[FB], flg", flg_reg);
}

/*
 *  NMIを除くすべての割込みの禁止
 */
Inline void
disint(void)
{
	Asm("	fclr	i");
}

/*
 *  すべての割込みの許可
 */
Inline void
enaint(void)
{
	Asm("	fset	i");
}

#endif /* TOPPERS_PRC_INSN_H */
