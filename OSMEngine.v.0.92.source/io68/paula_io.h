/**
 * @ingroup   io68_paula_devel
 * @file      io68/paula_io.h
 * @author    Benjamin Gerard <ben@sashipa.com>
 * @date      1998/06/18
 * @brief     Paula IO plugin header.
 *
 * $Id: paula_io.h,v 2.1 2003/10/11 04:40:25 benjihan Exp $
 */

/* Copyright (C) 1998-2003 Benjamin Gerard */

#ifndef _PAULA_IO_H_
#define _PAULA_IO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "emu68/struct68.h"

/** @addtogroup  io68_paula_devel
 *  @{
 */

/** @name Paula (Amiga soundchip) IO plugin
 *  @{
 */

/** Paula IO plugin instance. */
extern io68_t paula_io;

/**@}*/

/**
 *@}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _PAULA_IO_H_ */
