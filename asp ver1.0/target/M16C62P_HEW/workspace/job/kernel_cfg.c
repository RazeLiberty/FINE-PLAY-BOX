/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#ifndef TOPPERS_EMPTY_LABEL
#define TOPPERS_EMPTY_LABEL(x,y) x y[0]
#endif

#if TKERNEL_PRID != 0x07u
#error "The kernel does not match this configuration file."
#endif

/*
 *  Include Directives (#include)
 */

#include "target_timer.h"
#include "target_syssvc.h"
#include "syssvc/serial.h"
#include "Apli/job.h"

/*
 *  Default Definitions of Trace Log Macros
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(intno)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(intno)
#endif /* LOG_ISR_LEAVE */

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_stack_INIT_TASK[COUNT_STK_T(STACK_SIZE)];
static STK_T _kernel_stack_FUNC1_TASK[COUNT_STK_T(STACK_SIZE)];

const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (TA_ACT), (intptr_t)(0), (main), INT_PRIORITY(IDLE_PRIORITY), ROUND_STK_T(STACK_SIZE), (_kernel_stack_INIT_TASK), (TA_NULL), (NULL) },
	{ (TA_NULL), (intptr_t)(0), (func1_task), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), (_kernel_stack_FUNC1_TASK), (TA_NULL), (NULL) }
};

TCB _kernel_tcb_table[TNUM_TSKID];

const ID _kernel_torder_table[TNUM_TSKID] = {
	INIT_TASK, FUNC1_TASK
};

/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{ (TA_TPRI), (0), (1) },
	{ (TA_TPRI), (1), (1) },
	{ (TA_TPRI), (0), (1) },
	{ (TA_TPRI), (1), (1) },
	{ (TA_TPRI), (0), (1) },
	{ (TA_TPRI), (1), (1) }
};

SEMCB _kernel_semcb_table[TNUM_SEMID];

/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

const FLGINIB _kernel_flginib_table[TNUM_FLGID] = {
	{ (TA_CLR), (0x0000) }
};

FLGCB _kernel_flgcb_table[TNUM_FLGID];

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

static intptr_t _kernel_dtqmb_UART_DTQ[20];
const DTQINIB _kernel_dtqinib_table[TNUM_DTQID] = {
	{ (TA_NULL), (20), (_kernel_dtqmb_UART_DTQ) }
};

DTQCB _kernel_dtqcb_table[TNUM_DTQID];

/*
 *  Priority Dataqueue Functions
 */

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);

TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);
TOPPERS_EMPTY_LABEL(PDQCB, _kernel_pdqcb_table);

/*
 *  Mailbox Functions
 */

const ID _kernel_tmax_mbxid = (TMIN_MBXID + TNUM_MBXID - 1);

TOPPERS_EMPTY_LABEL(const MBXINIB, _kernel_mbxinib_table);
TOPPERS_EMPTY_LABEL(MBXCB, _kernel_mbxcb_table);

/*
 *  Fixed-sized Memorypool Functions
 */

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);
TOPPERS_EMPTY_LABEL(MPFCB, _kernel_mpfcb_table);

/*
 *  Cyclic Handler Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

TOPPERS_EMPTY_LABEL(const CYCINIB, _kernel_cycinib_table);
TOPPERS_EMPTY_LABEL(CYCCB, _kernel_cyccb_table);

/*
 *  Alarm Handler Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

TOPPERS_EMPTY_LABEL(const ALMINIB, _kernel_alminib_table);
TOPPERS_EMPTY_LABEL(ALMCB, _kernel_almcb_table);

/*
 *  Interrupt Management Functions
 */


#define TNUM_INHNO	3
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

INTHDR_ENTRY(INHNO_TIMER, 21, target_timer_handler)
INTHDR_ENTRY(TINHNO_S0RACK, 18, UART_receive_handler)
INTHDR_ENTRY(TINHNO_S0TNACK, 17, UART_send_handler)

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{ (INHNO_TIMER), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER, target_timer_handler)) },
	{ (TINHNO_S0RACK), (TA_NULL), (FP)(INT_ENTRY(TINHNO_S0RACK, UART_receive_handler)) },
	{ (TINHNO_S0TNACK), (TA_NULL), (FP)(INT_ENTRY(TINHNO_S0TNACK, UART_send_handler)) }
};

#define TNUM_INTNO	3
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTINIB _kernel_intinib_table[TNUM_INTNO] = {
	{ (INTNO_TIMER), (TA_ENAINT | INTATR_TIMER), (INTPRI_TIMER) },
	{ (TINTNO_S0RACK), (TA_EDGE), (INTPRI_UART_recieve) },
	{ (TINTNO_S0TNACK), (TA_EDGE), (INTPRI_UART_send) }
};

/*
 *  CPU Exception Handler
 */

#define TNUM_EXCNO	0
const uint_t _kernel_tnum_excno = TNUM_EXCNO;


TOPPERS_EMPTY_LABEL(const EXCINIB, _kernel_excinib_table);

/*
 *  Stack Area for Non-task Context
 */

#ifdef DEFAULT_ISTK

#define TOPPERS_ISTKSZ		DEFAULT_ISTKSZ
#define TOPPERS_ISTK		DEFAULT_ISTK

#else /* DEAULT_ISTK */

static STK_T				_kernel_istack[COUNT_STK_T(DEFAULT_ISTKSZ)];
#define TOPPERS_ISTKSZ		ROUND_STK_T(DEFAULT_ISTKSZ)
#define TOPPERS_ISTK		_kernel_istack

#endif /* DEAULT_ISTK */

const SIZE		_kernel_istksz = TOPPERS_ISTKSZ;
STK_T *const	_kernel_istk = TOPPERS_ISTK;

#ifdef TOPPERS_ISTKPT
STK_T *const	_kernel_istkpt = TOPPERS_ISTKPT(TOPPERS_ISTK, TOPPERS_ISTKSZ);
#endif /* TOPPERS_ISTKPT */

/*
 *  Time Event Management
 */

TMEVTN   _kernel_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID];

/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
	_kernel_initialize_semaphore();
	_kernel_initialize_eventflag();
	_kernel_initialize_dataqueue();
	_kernel_initialize_interrupt();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_inirtn(void)
{
	((INIRTN)(target_timer_initialize))((intptr_t)(0));
	((INIRTN)(serial_initialize))((intptr_t)(0));
}

/*
 *  Termination Routine
 */

void
_kernel_call_terrtn(void)
{
	((TERRTN)(target_timer_terminate))((intptr_t)(0));
}

const PRI intpri_table[64] = 
{	INT8_C( 0), /* 00 */
	INT8_C( 0), /* 01 */
	INT8_C( 0), /* 02 */
	INT8_C( 0), /* 03 */
	INT8_C( 0), /* 04 */
	INT8_C( 0), /* 05 */
	INT8_C( 0), /* 06 */
	INT8_C( 0), /* 07 */
	INT8_C( 0), /* 08 */
	INT8_C( 0), /* 09 */
	INT8_C( 0), /* 10 */
	INT8_C( 0), /* 11 */
	INT8_C( 0), /* 12 */
	INT8_C( 0), /* 13 */
	INT8_C( 0), /* 14 */
	INT8_C( 0), /* 15 */
	INT8_C( 0), /* 16 */
	INT8_C(INTPRI_UART_send), /* 17 */
	INT8_C(INTPRI_UART_recieve), /* 18 */
	INT8_C( 0), /* 19 */
	INT8_C( 0), /* 20 */
	INT8_C(INTPRI_TIMER), /* 21 */
	INT8_C( 0), /* 22 */
	INT8_C( 0), /* 23 */
	INT8_C( 0), /* 24 */
	INT8_C( 0), /* 25 */
	INT8_C( 0), /* 26 */
	INT8_C( 0), /* 27 */
	INT8_C( 0), /* 28 */
	INT8_C( 0), /* 29 */
	INT8_C( 0), /* 30 */
	INT8_C( 0), /* 31 */
	INT8_C( 0), /* 32 */
	INT8_C( 0), /* 33 */
	INT8_C( 0), /* 34 */
	INT8_C( 0), /* 35 */
	INT8_C( 0), /* 36 */
	INT8_C( 0), /* 37 */
	INT8_C( 0), /* 38 */
	INT8_C( 0), /* 39 */
	INT8_C( 0), /* 40 */
	INT8_C( 0), /* 41 */
	INT8_C( 0), /* 42 */
	INT8_C( 0), /* 43 */
	INT8_C( 0), /* 44 */
	INT8_C( 0), /* 45 */
	INT8_C( 0), /* 46 */
	INT8_C( 0), /* 47 */
	INT8_C( 0), /* 48 */
	INT8_C( 0), /* 49 */
	INT8_C( 0), /* 50 */
	INT8_C( 0), /* 51 */
	INT8_C( 0), /* 52 */
	INT8_C( 0), /* 53 */
	INT8_C( 0), /* 54 */
	INT8_C( 0), /* 55 */
	INT8_C( 0), /* 56 */
	INT8_C( 0), /* 57 */
	INT8_C( 0), /* 58 */
	INT8_C( 0), /* 59 */
	INT8_C( 0), /* 60 */
	INT8_C( 0), /* 61 */
	INT8_C( 0), /* 62 */
	INT8_C( 0), /* 63 */
};


