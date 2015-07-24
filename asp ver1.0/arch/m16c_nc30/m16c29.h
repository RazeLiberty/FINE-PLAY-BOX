/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2008 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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


#ifndef TOPPERS_M16C29_H
#define TOPPERS_M16C29_H

/* プロセッサ依存の情報定義 */

/*1
 *  SFRアドレス定義
 */
#define TADR_SFR_PM0     0x0004 /* プロセッサモードレジスタ0 */
#define TADR_SFR_PM1     0x0005 /* プロセッサモードレジスタ1 */
#define TADR_SFR_CM0     0x0006 /* システムクロック制御レジスタ0 */
#define TADR_SFR_CM1     0x0007 /* システムクロック制御レジスタ1 */
#define TADR_SFR_CSR     0x0008 /* チップセレクト制御レジスタ */
#define TADR_SFR_AIER    0x0009 /* アドレス一致割り込み許可レジスタ */
#define TADR_SFR_PRCR    0x000A /* プロテクトレジスタ */
#define TADR_SFR_DBR     0x000B /* データバンクレジスタ */
#define TADR_SFR_CM2     0x000C /* 発振停止検出レジスタ */
#define TADR_SFR_WDTS    0x000E /* ウォッチドッグタイマスタートレジスタ */
#define TADR_SFR_WDC     0x000F /* ウォッチドッグタイマ制御レジスタ */
#define TADR_SFR_RMAD0   0x0010 /* アドレス一致割り込みレジスタ0 */
#define TADR_SFR_RMAD1   0x0014 /* アドレス一致割り込みレジスタ1 */
#define TADR_SFR_VCR1    0x0019 /* 電圧検出レジスタ1 (注5、6) */
#define TADR_SFR_VCR2    0x001A /* 電圧検出レジスタ2 (注5、6) */
#define TADR_SFR_CSE     0x001B /* チップセレクト拡張制御レジスタ */
#define TADR_SFR_PLC0    0x001C /* PLL制御レジスタ0 */
#define TADR_SFR_PM2     0x001E /* プロセッサモードレジスタ2 */
#define TADR_SFR_D4INT   0x001F /* 電圧低下検出割り込みレジスタ */
#define TADR_SFR_SAR0    0x0020 /* DMA0ソ－スポインタ */
#define TADR_SFR_DAR0    0x0024 /* DMA0ディスティネ－ションポインタ */
#define TADR_SFR_TCR0    0x0028 /* DMA0転送カウンタ */
#define TADR_SFR_DM0CON  0x002C /* DMA0制御レジスタ */
#define TADR_SFR_SAR1    0x0030 /* DMA1ソ－スポインタ */
#define TADR_SFR_DAR1    0x0034 /* DMA1ディスティネ－ションポインタ */
#define TADR_SFR_TCR1    0x0038 /* DMA1転送カウンタ */
#define TADR_SFR_DM1CON  0x003C /* DMA1制御レジスタ */
#define TADR_SFR_C01WKIC 0x0041 /* CAN0ウェイクアップ割り込み制御レジスタ */
#define TADR_SFR_C0RECIC 0x0042 /* CAN0受信完了割り込み制御レジスタ */
#define TADR_SFR_C0TRMIC 0x0043 /* CAN0送信信完了割り込み制御レジスタ */
#define TADR_SFR_INT3IC  0x0044 /* INT3割り込み制御レジスタ */
#define TADR_SFR_TB5IC   0x0045 /* タイマB5割り込み制御レジスタ */
#define TADR_SFR_TB4IC   0x0046 /* タイマB4割り込み制御レジスタ */
#define TADR_SFR_U1BCNIC 0x0046 /* バス衝突検出割り込み制御レジスタ */
#define TADR_SFR_TB3IC   0x0047 /* タイマB3割り込み制御レジスタ */
#define TADR_SFR_U0BCNIC 0x0047 /* UART0バス衝突検出割り込み制御レジスタ */
#define TADR_SFR_S4IC    0x0048 /* SI/O4割り込み制御レジスタ */
#define TADR_SFR_INT5IC  0x0048 /* INT5割り込み制御レジスタ */
#define TADR_SFR_S3IC    0x0049 /* SI/O3割り込み制御レジスタ */
#define TADR_SFR_INT4IC  0x0049 /* INT4割り込み制御レジスタ */
#define TADR_SFR_BCNIC   0x004A /* UART2バス衝突検出割り込み制御レジスタ */
#define TADR_SFR_DM0IC   0x004B /* DMA0割り込み制御レジスタ */
#define TADR_SFR_DM1IC   0x004C /* DMA1割り込み制御レジスタ */
#define TADR_SFR_KUPIC   0x004D /* キ－入力割り込み制御レジスタ */
#define TADR_SFR_ADIC    0x004E /* A/D変換割り込み制御レジスタ */
#define TADR_SFR_S2TIC   0x004F /* UART2送信割り込み制御レジスタ */
#define TADR_SFR_S2RIC   0x0050 /* UART2受信割り込み制御レジスタ */
#define TADR_SFR_S0TIC   0x0051 /* UART0送信割り込み制御レジスタ */
#define TADR_SFR_S0RIC   0x0052 /* UART0受信割り込み制御レジスタ */
#define TADR_SFR_S1TIC   0x0053 /* UART1送信割り込み制御レジスタ */
#define TADR_SFR_S1RIC   0x0054 /* UART1受信割り込み制御レジスタ */
#define TADR_SFR_TA0IC   0x0055 /* タイマA0割り込み制御レジスタ */
#define TADR_SFR_TA1IC   0x0056 /* タイマA1割り込み制御レジスタ */
#define TADR_SFR_TA2IC   0x0057 /* タイマA2割り込み制御レジスタ */
#define TADR_SFR_TA3IC   0x0058 /* タイマA3割り込み制御レジスタ */
#define TADR_SFR_TA4IC   0x0059 /* タイマA4割り込み制御レジスタ */
#define TADR_SFR_TB0IC   0x005A /* タイマB0割り込み制御レジスタ */
#define TADR_SFR_TB1IC   0x005B /* タイマB1割り込み制御レジスタ */
#define TADR_SFR_TB2IC   0x005C /* タイマB2割り込み制御レジスタ */
#define TADR_SFR_INT0IC  0x005D /* INT0割り込み制御レジスタ */
#define TADR_SFR_INT1IC  0x005E /* INT1割り込み制御レジスタ */
#define TADR_SFR_INT2IC  0x005F /* INT2割り込み制御レジスタ */
#define TADR_SFR_FIDR    0x01B4 /* フラッシュ識別レジスタ */
#define TADR_SFR_FMR1    0x01B5 /* フラッシュメモリ制御レジスタ1 */
#define TADR_SFR_FMR0    0x01B7 /* フラッシュメモリ制御レジスタ0 */
#define TADR_SFR_RMAD2   0x01B8 /* アドレス一致割り込みレジスタ2 */
#define TADR_SFR_AIER2   0x01BB /* アドレス一致割り込み許可レジスタ2 */
#define TADR_SFR_RMAD3   0x01BC /* アドレス一致割り込みレジスタ3 */
#define TADR_SFR_PCLKR   0x025E /* 周辺クロック選択レジスタ*/
#define TADR_SFR_TBSR    0x0340 /* タイマB3,4,5カウント開始フラグ */
#define TADR_SFR_TA11    0x0342 /* タイマA1-1レジスタ */
#define TADR_SFR_TA21    0x0344 /* タイマA2-1レジスタ */
#define TADR_SFR_TA41    0x0346 /* タイマA4-1レジスタ */
#define TADR_SFR_INVC0   0x0348 /* 三相PWM制御レジスタ0 */
#define TADR_SFR_INVC1   0x0349 /* 三相PWM制御レジスタ1 */
#define TADR_SFR_IDB0    0x034A /* 三相出力バッファレジスタ0 */
#define TADR_SFR_IDB1    0x034B /* 三相出力バッファレジスタ1 */
#define TADR_SFR_DTT     0x034C /* 短絡防止タイマ */
#define TADR_SFR_ICTB2   0x034D /* タイマB2割り込み発生頻度設定カウンタ */
#define TADR_SFR_TB3     0x0350 /* タイマB3レジスタ */
#define TADR_SFR_TB4     0x0352 /* タイマB4レジスタ */
#define TADR_SFR_TB5     0x0354 /* タイマB5レジスタ */
#define TADR_SFR_TB3MR   0x035B /* タイマB3モードレジスタ */
#define TADR_SFR_TB4MR   0x035C /* タイマB4モードレジスタ */
#define TADR_SFR_TB5MR   0x035D /* タイマB5モードレジスタ */
#define TADR_SFR_IFSR2A  0x035E /* 割り込み要因選択レジスタ2 */
#define TADR_SFR_IFSR    0x035F /* 割り込み要因選択レジスタ */
#define TADR_SFR_S3TRR   0x0360 /* SI/O3送受信レジスタ */
#define TADR_SFR_S3C     0x0362 /* SI/O3制御レジスタ */
#define TADR_SFR_S3BRG   0x0363 /* SI/O3ビットレートレジスタ */
#define TADR_SFR_S4TRR   0x0364 /* SI/O4送受信レジスタ */
#define TADR_SFR_S4C     0x0366 /* SI/O4制御レジスタ */
#define TADR_SFR_S4BRG   0x0367 /* SI/O4ビットレートレジスタ */
#define TADR_SFR_U0SMR4  0x036C /* UART0特殊モードレジスタ4 */
#define TADR_SFR_U0SMR3  0x036D /* UART0特殊モードレジスタ3 */
#define TADR_SFR_U0SMR2  0x036E /* UART0特殊モードレジスタ2 */
#define TADR_SFR_U0SMR   0x036F /* UART0特殊モードレジスタ */
#define TADR_SFR_U1SMR4  0x0370 /* UART1特殊モードレジスタ4 */
#define TADR_SFR_U1SMR3  0x0371 /* UART1特殊モードレジスタ3 */
#define TADR_SFR_U1SMR2  0x0372 /* UART1特殊モードレジスタ2 */
#define TADR_SFR_U1SMR   0x0373 /* UART1特殊モードレジスタ */
#define TADR_SFR_U2SMR4  0x0374 /* UART2特殊モードレジスタ4 */
#define TADR_SFR_U2SMR3  0x0375 /* UART2特殊モードレジスタ3 */
#define TADR_SFR_U2SMR2  0x0376 /* UART2特殊モードレジスタ2 */
#define TADR_SFR_U2SMR   0x0377 /* UART2特殊モードレジスタ */
#define TADR_SFR_U2MR    0x0378 /* UART2送受信モードレジスタ */
#define TADR_SFR_U2BRG   0x0379 /* UART2ビットレートレジスタ */
#define TADR_SFR_U2TB    0x037A /* UART2送信バッファレジスタ */
#define TADR_SFR_U2C0    0x037C /* UART2送受信制御レジスタ0 */
#define TADR_SFR_U2C1    0x037D /* UART2送受信制御レジスタ1 */
#define TADR_SFR_U2RB    0x037E /* UART2受信バッファレジスタ */

/*
 *  DMAC
 */ 
#define TADR_SFR_DM0SL   0x03B8 /* DMA0要因選択レジスタ */
#define TADR_SFR_DM1SL   0x03BA /* DMA1要因選択レジスタ */

/*
 *  タイマ
 */
#define TADR_SFR_TABSR   0x0380 /* カウント開始フラグ */
#define TADR_SFR_CPSRF   0x0381 /* 時計用プリスケーラリセットフラグ */
#define TADR_SFR_ONSF    0x0382 /* ワンショット開始フラグ */
#define TADR_SFR_TRGSR   0x0383 /* トリガ選択レジスタ */
#define TADR_SFR_UDF     0x0384 /* アップダウンフラグ */
#define TADR_SFR_TA0     0x0386 /* タイマA0レジスタ */
#define TADR_SFR_TA1     0x0388 /* タイマA1レジスタ */
#define TADR_SFR_TA2     0x038A /* タイマA2レジスタ */
#define TADR_SFR_TA3     0x038C /* タイマA3レジスタ */
#define TADR_SFR_TA4     0x038E /* タイマA4レジスタ */
#define TADR_SFR_TB0     0x0390 /* タイマB0レジスタ */
#define TADR_SFR_TB1     0x0392 /* タイマB1レジスタ */
#define TADR_SFR_TB2     0x0394 /* タイマB2レジスタ */
#define TADR_SFR_TA0MR   0x0396 /* タイマA0モ－ドレジスタ */
#define TADR_SFR_TA1MR   0x0397 /* タイマA1モ－ドレジスタ */
#define TADR_SFR_TA2MR   0x0398 /* タイマA2モ－ドレジスタ */
#define TADR_SFR_TA3MR   0x0399 /* タイマA3モ－ドレジスタ */
#define TADR_SFR_TA4MR   0x039A /* タイマA4モ－ドレジスタ */
#define TADR_SFR_TB0MR   0x039B /* タイマB0モ－ドレジスタ */
#define TADR_SFR_TB1MR   0x039C /* タイマB1モ－ドレジスタ */
#define TADR_SFR_TB2MR   0x039D /* タイマB2モ－ドレジスタ */
#define TADR_SFR_TB2SC   0x039E /* タイマB2特殊モ－ドレジスタ */

/*
 *  CRC演算
 */
#define TADR_SFR_CRCD    0x03BC /* CRCデータレジスタ */
#define TADR_SFR_CRCIN   0x03BE /* CRCインプットレジスタ */

/*
 *  シリアルインタフェース
 */
#define TADR_SFR_UART0_BASE    0x03A0 /* UART0送受信モ－ドレジスタ */
#define TADR_SFR_UART1_BASE    0x03A8 /* UART1送受信モ－ドレジスタ */
#define TADR_SFR_UART2_BASE    0x0378 /* UART2送受信モ－ドレジスタ */

#define TADR_SFR_UMR_OFFSET         0 /* 送受信モ－ドレジスタ */
#define TADR_SFR_UBRG_OFFSET        1 /* ビットレートレジスタ */
#define TADR_SFR_UTB_OFFSET         2 /* 送信バッファレジスタ */
#define TADR_SFR_UC0_OFFSET         4 /* 送受信制御レジスタ０*/
#define TADR_SFR_UC1_OFFSET         5 /* 送受信制御レジスタ１ */
#define TADR_SFR_URB_OFFSET         6 /* 受信バッファレジスタ */
#define TADR_SFR_UCON          0x03B0 /* UART送受信制御レジスタ２ */

/*
 *  A-D/D-Aコンバータ
 */
#define TADR_SFR_AD0     0x03C0 /* A/Dレジスタ0 */
#define TADR_SFR_AD1     0x03C2 /* A/Dレジスタ1 */
#define TADR_SFR_AD2     0x03C4 /* A/Dレジスタ2 */
#define TADR_SFR_AD3     0x03C6 /* A/Dレジスタ3 */
#define TADR_SFR_AD4     0x03C8 /* A/Dレジスタ4 */
#define TADR_SFR_AD5     0x03CA /* A/Dレジスタ5 */
#define TADR_SFR_AD6     0x03CC /* A/Dレジスタ6 */
#define TADR_SFR_AD7     0x03CE /* A/Dレジスタ7 */
#define TADR_SFR_ADCON2  0x03D4 /* A/D制御レジスタ2 */
#define TADR_SFR_ADCON0  0x03D6 /* A/D制御レジスタ0 */
#define TADR_SFR_ADCON1  0x03D7 /* A/D制御レジスタ1 */
#define TADR_SFR_DA0     0x03D8 /* D/Aレジスタ0 */
#define TADR_SFR_DA1     0x03DA /* D/Aレジスタ1 */
#define TADR_SFR_DACON   0x03DC /* D/A制御レジスタ*/

/*
 *  プログラマブル入出力ポート
 */

#define TADR_SFR_PC14    0x03DE /* ポートP14制御レジスタ */
#define TADR_SFR_PUR3    0x03DF /* プルアップ制御レジスタ3 */
#define TADR_SFR_P0      0x03E0 /* ポートP0レジスタ */
#define TADR_SFR_P1      0x03E1 /* ポートP1レジスタ */
#define TADR_SFR_PD0     0x03E2 /* ポートP0方向レジスタ */
#define TADR_SFR_PD1     0x03E3 /* ポートP1方向レジスタ */
#define TADR_SFR_P2      0x03E4 /* ポートP2レジスタ */
#define TADR_SFR_P3      0x03E5 /* ポートP3レジスタ */
#define TADR_SFR_PD2     0x03E6 /* ポートP2方向レジスタ */
#define TADR_SFR_PD3     0x03E7 /* ポートP3方向レジスタ */
#define TADR_SFR_P4      0x03E8 /* ポートP4レジスタ */
#define TADR_SFR_P5      0x03E9 /* ポートP5レジスタ */
#define TADR_SFR_PD4     0x03EA /* ポートP4方向レジスタ */
#define TADR_SFR_PD5     0x03EB /* ポートP5方向レジスタ */
#define TADR_SFR_P6      0x03EC /* ポートP6レジスタ */
#define TADR_SFR_P7      0x03ED /* ポートP7レジスタ */
#define TADR_SFR_PD6     0x03EE /* ポートP6方向レジスタ */
#define TADR_SFR_PD7     0x03EF /* ポートP7方向レジスタ */
#define TADR_SFR_P8      0x03F0 /* ポートP8レジスタ */
#define TADR_SFR_P9      0x03F1 /* ポートP9レジスタ */
#define TADR_SFR_PD8     0x03F2 /* ポートP8方向レジスタ */
#define TADR_SFR_PD9     0x03F3 /* ポートP9方向レジスタ */
#define TADR_SFR_P10     0x03F4 /* ポートP10レジスタ */
#define TADR_SFR_P11     0x03F5 /* ポートP11レジスタ */
#define TADR_SFR_PD10    0x03F6 /* ポートP10方向レジスタ */
#define TADR_SFR_PD11    0x03F7 /* ポートP11方向レジスタ */
#define TADR_SFR_P12     0x03F8 /* ポートP12レジスタ */
#define TADR_SFR_P13     0x03F9 /* ポートP13レジスタ */
#define TADR_SFR_PD12    0x03FA /* ポートP12方向レジスタ */
#define TADR_SFR_PD13    0x03FB /* ポートP13方向レジスタ */
#define TADR_SFR_PUR0    0x03FC /* プルアップ制御レジスタ0 */
#define TADR_SFR_PUR1    0x03FD /* プルアップ制御レジスタ1 */
#define TADR_SFR_PUR2    0x03FE /* プルアップ制御レジスタ2 */
#define TADR_SFR_PCR     0x03FF /* ポート制御レジスタ */

/*
 *  CPU例外ハンドラ番号の定義
 */

#define INT_UNDEF_INSTRUNCTION	0		/* 未定義命令 */
#define INT_OVERFLOW			1		/* オーバーフロー */
#define INT_BRK_INSTRUCTION		2		/* BRK命令 */
#define INT_ADDRESS_MATCH		3		/* アドレス一致 */
#define INT_WDT					5		/* ウォッチドッグタイマ */
#define INT_XIN_STOP			5		/* 発振停止検出 */
#define INT_LOW_VOLT_DETECT		5		/* 電圧低下検出 */
#define INT_NMI					7		/* NMI */
#define INT_RESET				8		/* リセット */

/*
 *  割込みハンドラ番号の定義
 */
#define	TINHNO_BRK      0		/* BRK */
#define TINHNO_CAN0WUP  1  		/* CAN0ウエイクアップ */
#define TINHNO_CAN0R    2 		/* CAN0受信完了 */
#define TINHNO_CAN0S    3 		/* CAN0送信完了 */
#define TINHNO_INT3     4		/* INT3 */
#define TINHNO_TB5      5		/* タイマB5 */
#define TINHNO_TB4      6		/* タイマB4 */
#define TINHNO_TB3      7		/* タイマB3 */
#define TINHNO_SIO4     8		/* SIO4 */
#define TINHNO_INT5     8		/* INT5 */
#define TINHNO_SIO3     9		/* SIO3 */
#define TINHNO_INT4     9		/* INT4 */
#define TINHNO_BCN     10		/* UARTバス衝突検出 */
#define TINHNO_DMA0    11		/* DMA0 */
#define TINHNO_DMA1    12		/* DMA1 */
#define TINHNO_KEY     13		/* キー入力割込み */
#define TINHNO_AD      14		/* A/D */
#define TINHNO_S2TNACK 15		/* UART2送信,NACK */
#define TINHNO_S2RACK  16		/* UART2受信,ACK */
#define TINHNO_S0TNACK 17		/* UART0送信,NACK */
#define TINHNO_S0RACK  18		/* UART0受信,ACK */
#define TINHNO_S1TNACK 19		/* UART1送信,NACK */
#define TINHNO_S1RACK  20		/* UART1受信,ACK */
#define TINHNO_TA0     21		/* タイマA0 */
#define TINHNO_TA1     22		/* タイマA1 */
#define TINHNO_TA2     23		/* タイマA2 */
#define TINHNO_TA3     24		/* タイマA3 */
#define TINHNO_TA4     25		/* タイマA4 */
#define TINHNO_TB0     26		/* タイマB0 */
#define TINHNO_TB1     27		/* タイマB1 */
#define TINHNO_TB2     28		/* タイマB2 */
#define TINHNO_INT0    29		/* INT0 */
#define TINHNO_INT1    30		/* INT1 */
#define TINHNO_INT2    31		/* INT2 */

/*
 *  割込み番号の定義
 */
#define	TINTNO_BRK      0		/* BRK */
#define TINTNO_INT3     4		/* INT3 */
#define TINTNO_TB5      5		/* タイマB5 */
#define TINTNO_TB4      6		/* タイマB4 */
#define TINTNO_TB3      7		/* タイマB3 */
#define TINTNO_SIO4     8		/* SIO4 */
#define TINTNO_INT5     8		/* INT5 */
#define TINTNO_SIO3     9		/* SIO3 */
#define TINTNO_INT4     9		/* INT4 */
#define TINTNO_BCN     10		/* UARTバス衝突検出 */
#define TINTNO_DMA0    11		/* DMA0 */
#define TINTNO_DMA1    12		/* DMA1 */
#define TINTNO_KEY     13		/* キー入力割込み */
#define TINTNO_AD      14		/* A/D */
#define TINTNO_S2TNACK 15		/* UART2送信,NACK */
#define TINTNO_S2RACK  16		/* UART2受信,ACK */
#define TINTNO_S0TNACK 17		/* UART0送信,NACK */
#define TINTNO_S0RACK  18		/* UART0受信,ACK */
#define TINTNO_S1TNACK 19		/* UART1送信,NACK */
#define TINTNO_S1RACK  20		/* UART1受信,ACK */
#define TINTNO_TA0     21		/* タイマA0 */
#define TINTNO_TA1     22		/* タイマA1 */
#define TINTNO_TA2     23		/* タイマA2 */
#define TINTNO_TA3     24		/* タイマA3 */
#define TINTNO_TA4     25		/* タイマA4 */
#define TINTNO_TB0     26		/* タイマB0 */
#define TINTNO_TB1     27		/* タイマB1 */
#define TINTNO_TB2     28		/* タイマB2 */
#define TINTNO_INT0    29		/* INT0 */
#define TINTNO_INT1    30		/* INT1 */
#define TINTNO_INT2    31		/* INT2 */



/*
 *  タイマA情報
 *
 *  pdicのm16c/m16c_ta.cで使用する．
 */

/*
 *  タイマAの個数
 */
#define TNUM_M16C_TA		(5)

/*
 *  pdic用の定義値にリネーム
 */
#define TABSR_ADDR		TADR_SFR_TABSR
#define UDF_ADDR		TADR_SFR_UDF
#define ONSF_ADDR		TADR_SFR_ONSF
#define TAGSR_ADDR		TADR_SFR_TRGSR

#define INT_TA0			TINHNO_TA0
#define INT_TA1			TINHNO_TA1
#define INT_TA2			TINHNO_TA2
#define INT_TA3			TINHNO_TA3

/*
 *  各チャンネルのレジスタ及び設定ビット情報
 */
#define TA0_ADDR			(TADR_SFR_TA0)
#define TA0MR_ADDR			(TADR_SFR_TA0MR)
#define TA0_START_BIT		(0x01U << 0U)
#define TA0_ONESHOT_BIT		(0x01U << 0U)
#define TA0_UDSEL_BIT		(0x01U << 0U)
#define TA0_TRIGSEL_OFFSET	(6U)

#define TA1_ADDR			(TADR_SFR_TA1)
#define TA1MR_ADDR			(TADR_SFR_TA1MR)
#define TA1_START_BIT		(0x01U << 1U)
#define TA1_ONESHOT_BIT		(0x01U << 1U)
#define TA1_UDSEL_BIT		(0x01U << 1U)
#define TA1_TRIGSEL_OFFSET	(0U)

#define TA2_ADDR			(TADR_SFR_TA2)
#define TA2MR_ADDR			(TADR_SFR_TA2MR)
#define TA2_START_BIT		(0x01U << 2U)
#define TA2_ONESHOT_BIT		(0x01U << 2U)
#define TA2_UDSEL_BIT		(0x01U << 2U)
#define TA2_TRIGSEL_OFFSET	(2U)

#define TA3_ADDR			(TADR_SFR_TA3)
#define TA3MR_ADDR			(TADR_SFR_TA3MR)
#define TA3_START_BIT		(0x01U << 3U)
#define TA3_ONESHOT_BIT		(0x01U << 3U)
#define TA3_UDSEL_BIT		(0x01U << 3U)
#define TA3_TRIGSEL_OFFSET	(4U)

#define TA4_ADDR			(TADR_SFR_TA4)
#define TA4MR_ADDR			(TADR_SFR_TA4MR)
#define TA4_START_BIT		(0x01U << 4U)
#define TA4_ONESHOT_BIT		(0x01U << 4U)
#define TA4_UDSEL_BIT		(0x01U << 4U)
#define TA4_TRIGSEL_OFFSET	(6U)

/*
 *  UART関連の定義
 *
 *  pdicのm16c/m16c_uart.cで使用する．
 */

/*
 *  シリアルI/Oの個数
 */
#define TNUM_SIOP			(3)

/*
 *  各ポートのレジスタ及び設定ビット情報
 */
#define UART0_UC0_ADDR		(TADR_SFR_UART0_BASE+TADR_SFR_UC0_OFFSET)
#define UART0_UC1_ADDR		(TADR_SFR_UART0_BASE+TADR_SFR_UC1_OFFSET)
#define UART0_MODE_ADDR		(TADR_SFR_UART0_BASE+TADR_SFR_UMR_OFFSET)
#define UART0_BAUD_ADDR		(TADR_SFR_UART0_BASE+TADR_SFR_UBRG_OFFSET)
#define UART0_TXBUF_ADDR	(TADR_SFR_UART0_BASE+TADR_SFR_UTB_OFFSET)
#define UART0_RXBUF_ADDR	(TADR_SFR_UART0_BASE+TADR_SFR_URB_OFFSET)
#define UART0_TXINTNO		(TINHNO_S0TNACK)
#define UART0_RXINTNO		(TINHNO_S0TNACK)

#define UART1_UC0_ADDR		(TADR_SFR_UART1_BASE+TADR_SFR_UC0_OFFSET)
#define UART1_UC1_ADDR		(TADR_SFR_UART1_BASE+TADR_SFR_UC1_OFFSET)
#define UART1_MODE_ADDR		(TADR_SFR_UART1_BASE+TADR_SFR_UMR_OFFSET)
#define UART1_BAUD_ADDR		(TADR_SFR_UART1_BASE+TADR_SFR_UBRG_OFFSET)
#define UART1_TXBUF_ADDR	(TADR_SFR_UART1_BASE+TADR_SFR_UTB_OFFSET)
#define UART1_RXBUF_ADDR	(TADR_SFR_UART1_BASE+TADR_SFR_URB_OFFSET)
#define UART1_TXINTNO		(TINHNO_S1TNACK)
#define UART1_RXINTNO		(TINHNO_S1RACK)

#define UART2_UC0_ADDR		(TADR_SFR_UART2_BASE+TADR_SFR_UC0_OFFSET)
#define UART2_UC1_ADDR		(TADR_SFR_UART2_BASE+TADR_SFR_UC1_OFFSET)
#define UART2_MODE_ADDR		(TADR_SFR_UART2_BASE+TADR_SFR_UMR_OFFSET)
#define UART2_BAUD_ADDR		(TADR_SFR_UART2_BASE+TADR_SFR_UBRG_OFFSET)
#define UART2_TXBUF_ADDR	(TADR_SFR_UART2_BASE+TADR_SFR_UTB_OFFSET)
#define UART2_RXBUF_ADDR	(TADR_SFR_UART2_BASE+TADR_SFR_URB_OFFSET)
#define UART2_TXINTNO		(TINHNO_S2TNACK)
#define UART2_RXINTNO		(TINHNO_S2RACK)


#endif	/* TOPPERS_M16C29_H */
