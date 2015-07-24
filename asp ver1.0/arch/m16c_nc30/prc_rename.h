/* This file is generated from prc_rename.def by genrename. */

#ifndef TOPPERS_PRC_RENAME_H
#define TOPPERS_PRC_RENAME_H

#define start_r		_kernel_start_r
#define ret_int		_kernel_ret_int
#define ret_exc		_kernel_ret_exc
#define lock_flag	_kernel_lock_flag
#define saved_iipm	_kernel_saved_iipm
#define intnest		_kernel_intnest
#define tsk_sp		_kernel_tsk_sp
#define intc_reg	_kernel_intc_reg

#ifdef TOPPERS_LABEL_ASM

#define _start_r	__kernel_start_r
#define _ret_int	__kernel_ret_int
#define _ret_exc	__kernel_ret_exc
#define _lock_flag	__kernel_lock_flag
#define _saved_iipm	__kernel_saved_iipm
#define _intnest	__kernel_intnest
#define _tsk_sp		__kernel_tsk_sp
#define _intc_reg	__kernel_intc_reg

#endif /* TOPPERS_LABEL_ASM */


#endif /* TOPPERS_PRC_RENAME_H */
