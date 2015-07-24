/* This file is generated from target_rename.def by genrename. */

#ifndef TOPPERS_TARGET_RENAME_H
#define TOPPERS_TARGET_RENAME_H

/*
 *  prc_config.c, prc_support.a30
 */
#define prc_initialize				_kernel_prc_initialize
#define prc_terminate				_kernel_prc_terminate


#ifdef TOPPERS_LABEL_ASM

/*
 *  prc_config.c, prc_support.a30
 */
#define _prc_initialize				__kernel_prc_initialize
#define _prc_terminate				__kernel_prc_terminate


#endif /* TOPPERS_LABEL_ASM */

#include "m16c_nc30/prc_rename.h"

#endif /* TOPPERS_TARGET_RENAME_H */
