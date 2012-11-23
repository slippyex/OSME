/**
 * @ingroup   file68_devel
 * @file      file68/file68.h
 * @author    Benjamin Gerard
 * @date      1998/09/03
 * @brief     sc68 file header.
 *
 * $Id: file68.h,v 2.6 2003/11/19 00:47:08 benjihan Exp $
 */

/* Copyright (C) 1998-2007 Benjamin Gerard */

#ifndef _FILE68_FILE68_H_
#define _FILE68_FILE68_H_

#define FILE68_API

#include "istream68.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SC68_NOFILENAME "N/A"  /**< SC68 unknown filename or author.        */
#define SC68_LOADADDR   0x8000 /**< Default load address in 68K memory.     */
#define SC68_MAX_TRACK  99     /**< Maximum track per disk (display rules). */


/** @name  Features flag definitions for music68_t.
 *  @{
 */
#define SC68_YM        1     /**< YM-2149 actif.                  */
#define SC68_STE       2     /**< STE sound actif.                */
#define SC68_AMIGA     4     /**< AMIGA sound actif.              */
#define SC68_STECHOICE 8     /**< Optionnal STF/STE (not tested). */
/**@}*/

/** Hardware and features flags. */
typedef union {
  /** Flags bit field. */
  struct {
    unsigned ym:1;        /**< Music uses YM-2149 (ST).          */
    unsigned ste:1;       /**< Music uses STE specific hardware. */
    unsigned amiga:1;     /**< Music uses Paula Amiga hardware.  */
    unsigned stechoice:1; /**< Music allow STF/STE choices.      */
  } bit;
  /** All flags in one. */
  unsigned all;
} hwflags68_t;

/** SC68 music (track) structure. */
typedef struct
{

  /** @name  Music replay parameters.
   *  @{
   */
  unsigned int d0;       /**< D0 value to init this music.            */
  unsigned int a0;       /**< A0 Loading address. @see SC68_LOADADDR. */
  unsigned int frq;      /**< Frequency in Hz (default:50).           */
  unsigned int start_ms; /**< Start time in ms from disk 1st track.   */
  unsigned int time_ms;  /**< Duration in ms.                         */
  unsigned int frames;   /**< Number of frame.                        */
  int loop;              /**< Default number of loop (0:infinite).    */
  int track;             /**< Track remapping number (0:default).     */

  hwflags68_t hwflags;   /**< Hardware and features.                  */

  /**@}*/

  /** @name  Human readable information.
   *  @{
   */
  char * name;          /**< Music name.           */
  char * author;        /**< Author name.          */
  char * composer;      /**< Composer name.        */
  char * replay;        /**< External replay name. */
  /* added for XSC and sndh support */ 
  char * converter;     /**< Converter name.       */
  char * ripper;        /**< Copier name.          */
  /**@}*/

  /** @name  Music data.
   *  @{
   */
  unsigned int datasz;  /**< data size in bytes. */
  char        *data;    /**< Music data.         */
  /**@}*/

} music68_t;


/** SC68 music disk structure.
 *
 *     The disk68_t structure is the memory representation for an SC68 disk. 
 *     Each SC68 file could several music or tracks, in the limit of a
 *     maximum of 99 tracks per file. Each music is independant, but some
 *     information, including music data, could be inherit from previous
 *     track. In a general case, tracks are grouped by theme, that could be
 *     a Demo or a Game.
 *
 */
typedef struct
{
  /* context68_t * context; *//**< Context instance.                       */

  /** @name  Disk information.
   *  @{
   */
  int          default_six; /**< Prefered default music (default is 0).  */
  int          nb_six;      /**< Number of music track in file.          */
  unsigned int time_ms;     /**< Total time for all tracks in ms.        */
  hwflags68_t  hwflags;     /**< All tracks flags ORed.                  */
  char        *name;        /**< Disk name.                              */
  /**@}*/

  /** @name  Music data.
   *  @{
   */
  music68_t mus[SC68_MAX_TRACK]; /**< Information for each music.        */
  char      data[1];             /**< raw data (must be last in struct). */
  /**@}*/

} disk68_t;

FILE68_API
disk68_t * file68_load(istream68_t * is);

int my_valid(disk68_t * mb);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _FILE68_FILE68_H_ */
