/*
 *                      OldSkoolMusaxxsEngine - API
 *      Copyright (C) 2007 SLiPPY/VeCTRONiX! <slippy@vectronixhq.de>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or (at your
 *  option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#ifndef _OSME_FUNCS_H_
#define _OSME_FUNCS_H_

#define OSME_SUCCESS 0;
#define OSME_FILE_ERROR -1001;
#define OSME_FILE_READ_ERROR -1002;
#define OSME_FILE_MEMORY_ERROR -1003;
#define OSME_FILE_NOT_FOUND_ERROR -1004;

#define OSME_UNKNOWN_REPLAYER -2001;

#define OSME_INITIALIZATION_ERROR -3001;
#define OSME_SOUNDSUBSYSTEM_ERROR -3002;
#define OSME_DISK_VALIDATION_FAILED -3003;

#define OSME_USER_ERROR -4000;

#include "myConfig.h"

#ifdef IS_DLL
#define EXPORT_DECL extern "C" __declspec(dllexport)
#else
#define EXPORT_DECL extern "C" 
#endif

#ifdef USE_DLL
#undef EXPORT_DECL
#define EXPORT_DECL extern "C" __declspec(dllimport)
#endif

EXPORT_DECL typedef struct {
  char title[80];			/**< Disk or track title.                */
  char author[60];			/**< Author name.                        */
  char composer[60];		/**< Composer name.                      */
  char replay[40];			/**< Replay name.                        */
  char hwname[20];			/**< Hardware description.               */
  unsigned int time_ms;		/**< Duration in ms.                    */
  unsigned int rate;		/**< Replay rate.                       */
  unsigned int addr;		/**< Load address.                      */
  unsigned int channels;	/**< Channels for VU					  */
  unsigned int max_vu;		/**< max. amount of volume per channel  */
} osme_music_info_t;


EXPORT_DECL int playOSMEMusicMem(void *pMusic, unsigned int length, int trackId);
EXPORT_DECL int playOSMEMusicFile(const char * filename, int trackId);

EXPORT_DECL void stopOSMEMusic();
EXPORT_DECL void pauseOSMEMusic();
EXPORT_DECL void resumeOSMEMusic();
EXPORT_DECL unsigned char getOSMEChannelVU(int i);
EXPORT_DECL void setQualityFilter(bool onoff);
EXPORT_DECL int getProcResult();
EXPORT_DECL void setOSMEVolume(int vol);
EXPORT_DECL void fadeOutOSMEVolume(int fadeOutTimeMS);
EXPORT_DECL osme_music_info_t getOSMEMusicInfo();

#endif
