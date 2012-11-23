/**
 * @ingroup file68_istream68_devel
 * @file    file68/istream68_mem.h
 * @author  Benjamin Gerard
 * @date    2003/08/08
 * @brief   Memory stream header.
 *
 * $Id: istream68_mem.h,v 2.4 2003/10/07 06:58:44 benjihan Exp $
 *
 */

/* Copyright (C) 1998-2003 Benjamin Gerard */

#ifndef _ISTREAM68_MEM_H_
#define _ISTREAM68_MEM_H_

#include "file68/istream68.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @name      Memory stream
 *  @ingroup   file68_istream68_devel
 *
 *    Implements istream_t for memory buffer.
 *
 *  @{
 */

/** Creates a stream for memory buffer.
 *
 *  @param  addr   Buffer base address.
 *  @param  len    Buffer length.
 *  @param  mode   Allowed open mode.
 *
 *  @return stream
 *  @retval 0 on error
 *
 *  @note   filename is build with memory range.
 */
istream_t * istream_mem_create(const void * addr, int len, int mode);
#define istream68_mem_create istream_mem_create

/**@}*/

#ifdef __cplusplus
}
#endif


#endif /* #define _ISTREAM68_MEM_H_ */
