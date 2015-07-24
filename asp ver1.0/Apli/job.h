/* 
 *  job ヘッダファイル
 *  UART0サンプルプログラム用
 */
#define FOREVER 1

/* タスク優先度の設定 */
#define IDLE_PRIORITY 16	//最下位優先度
#define HI_PRIORITY 10
#define MID_PRIORITY 11
#define LOW_PRIORITY 12

/*  UART割込みハンドラの優先度 */
#define	INTPRI_UART_send	-4	
#define	INTPRI_UART_recieve	-5	

/*
 *  ターゲットに依存する可能性のある定数の定義
 *  スタックサイズ
 */
#ifdef STACK_SIZE
#undef STACK_SIZE
#endif /* STACK_SIZE */
#define	STACK_SIZE	386	/* タスクのスタックサイズ */

/*
 *  関数のプロトタイプ宣言
 */
#ifndef _MACRO_ONLY

extern void	main(intptr_t exinf);
extern void func1_task(intptr_t exinf);
//extern void func2_task(intptr_t exinf);

extern void UART_send_DD_task(intptr_t exinf);
extern void UART_receive_DD_task(intptr_t exinf);

#endif /* _MACRO_ONLY */


/************* End *************/