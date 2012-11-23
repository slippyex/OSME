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

#ifdef USE_CLASS

#include <config68.h>
#include <windows.h>
#include <stdio.h>
#include "config.h"
#include "osmeCommon.h"
#include "api68/api68.h"
#include "file68/file68.h"
#include "file68/alloc68.h"
#include "file68/istream68_mem.h"
#include "unice68/unice68.h"
#include "io68/ymemul.h"
#include "io68/paulaemul.h"
#include "emu68/emu68.h"
#include "osme-funcs.h"

#ifdef __USE_DIRECTX__
#include "SoundSubSystemDX.h"
static	CDXSoundSubSystem soundSubSys;
#else
#include "SoundSubSystemMM.h"
static	CMMSoundSubSystem soundSubSys;
#endif


static api68_t * sc68 = 0;
static int dbgShowInfo = 0;
static char * pNewMusic = 0;
static int initDone = 0;
static int iPause = 0;
static bool bStopped;
static int sRet = 0;
static bool bDoFillSoundInfo;
static char * pInternalMusicBuffer;
static bool bFreeInternalBuffer;
static bool bReady;

static api68_music_info_t info;
static bool bInfoSet;
static osme_music_info_t musicInfo;

static	void	soundSubSysCallback(void *pBuffer,long bufferLen)
{
	int ret;
	char *pSample = (char*)pBuffer;
	if(iPause == 0) {
		if(!bStopped) {
			ret = api68_process(sc68, pSample, bufferLen >> 2, iPause);
		} else {
			memset(pSample, 0, bufferLen);
			ret = 0;
		}
	} else {
		ret = 0;
		memset(pSample, 0, bufferLen);
	}
	int seeks = 0;
	if(ret == -1 || ret >= 4) {
		api68_seek(sc68, 1, &seeks);
	}
	sRet = ret;

}

osmeCommon::osmeCommon(void) {
	initialize();
}

osmeCommon::~osmeCommon(void) {
}

unsigned char osmeCommon::getInternalVolume(int i) {
	unsigned char v;
	if(i < 0) i = 0;
	if(!bInfoSet) {
		api68_music_info(sc68,&info,1,0);
		bInfoSet = true;
	}
#if AMIGA && ATARI
	if(strncmp(info.hwname, "Yamaha", 5) != 0) {
		if(i > 3) i = 3;
		v = paula[0xA9 + (i<<4)] & 0x7f; /* c is channel [0..3] not sure about the bitwise and */
		return (v > 64) ? 64 : v; 
	} else {
		if(i > 2) i = 2;
		v = ym.data[8+i] & 0x1f;  
		return v > 15 ? 15:v; 
	}
#endif
#if AMIGA && !ATARI
	if(i > 3) i = 3;
	v = paula[0xA9 + (i<<4)] & 0x7f; /* c is channel [0..3] not sure about the bitwise and */
	return (v > 64) ? 64 : v; 
#endif
#if ATARI && !AMIGA
	if(i > 2) i = 2;
	v = ym.data[8+i] & 0x1f;  
	return v > 15 ? 15:v; 
#endif

}
void osmeCommon::shutdownOSME() {
	api68_shutdown(sc68);
	bStopped = true;
	soundSubSys.close();
	if(bFreeInternalBuffer) {
		free(pInternalMusicBuffer);
	}
}
void osmeCommon::pauseOutput(bool bPause) {
	iPause = bPause == true ? 1:0;
	soundSubSys.pause(bPause);
}
void osmeCommon::setQualityFilter(bool bQuality) {
	soundSubSys.qualityFilter(bQuality);
}

void osmeCommon::setVolume(int iVol) {
	soundSubSys.setVolume(iVol);
}
int	osmeCommon::getProcResult() {
	return sRet;
}
void osmeCommon::initialize() {
   	api68_init_t init68;
	memset(&init68, 0, sizeof(init68));
	init68.alloc = malloc;
	init68.free = free;
	sc68 = api68_init(&init68);
	initDone = 1;
}

osme_music_info_t	osmeCommon::fillMusicInfo() {
	// only allowed if loaded music file is no generic format (except sndh)
	if(bDoFillSoundInfo) {
		if(!bInfoSet) {
			api68_music_info(sc68,&info,1,0);
			strcpy((char*)musicInfo.composer, info.composer);
			strcpy((char*)musicInfo.author, info.author);
			strcpy((char*)musicInfo.hwname, info.hwname);
			strcpy((char*)musicInfo.title, info.title);
			strcpy((char*)musicInfo.replay, info.replay);
			musicInfo.addr = info.addr;
			musicInfo.rate = info.rate;
			musicInfo.time_ms = info.time_ms;
			if(strncmp(info.hwname, "Yamaha", 5) != 0) {
				musicInfo.max_vu = 64;
				musicInfo.channels = 4;
			} else {
				musicInfo.max_vu = 16;
				musicInfo.channels = 3;
			}
			bInfoSet = true;
		}
	}
	return musicInfo;
}
int osmeCommon::loadGeneric(void * pMusic, int size, int type) {  
	music68_t mus;
	disk68_t * disk;
	disk = (disk68_t*)alloc68(sizeof(*disk) + size);

	// stuff the music data into the 1-char array ^^
	istream68_t * is;
	is = istream68_mem_create((void *)pMusic,size,1);
	istream68_open(is);
	istream68_read(is, disk->data, size);
	istream68_close(is);
	free68(is);
	mus.author = "unknown";
	mus.composer = "unknown";
	mus.name = "unknown music";
	if(type == 0) {
		mus.name = "Generic FC tune";
		mus.replay = "fc13_14";
	} else if(type == 1) {
		mus.name = "Generic JamCrackerPro tune";
		mus.replay = "JamCrackerPro";
#ifdef ahx_test
	} else if(type == 2) {
		mus.name = "Generic AHX/THX tune";
		mus.replay = "ahx";
#endif
	} else {
		mus.name = "unknown";
		mus.replay = "n/a";
		return OSME_UNKNOWN_REPLAYER;
	}
	// and fill up the rest with usable data ...
	mus.hwflags.all = SC68_AMIGA;
	mus.datasz = size;
	mus.data = (char*)pMusic;
	mus.d0 = 0;
	mus.a0 = SC68_LOADADDR;
	mus.frq = 50;
	mus.start_ms = 0;
	mus.time_ms = 0;//3*60*1000;
	mus.loop = -1;
	mus.frames = 0;
	mus.track = 1;

	disk->default_six = 1;
	disk->nb_six = 1;
	disk->time_ms = 0;//3*60*1000;
	disk->mus[0] = mus;
	disk->hwflags.all = SC68_AMIGA;
	disk->name = mus.name;
	if(my_valid(disk) == 0) {
		load_mydisk(sc68, disk);
	} else {
		return OSME_DISK_VALIDATION_FAILED;
	}
	// building up the information
	musicInfo.addr = SC68_LOADADDR;
	strcpy(musicInfo.author, mus.author);
	strcpy(musicInfo.composer, mus.composer);
	strcpy(musicInfo.title, mus.name);
	strcpy(musicInfo.replay, mus.replay);
	strcpy(musicInfo.hwname, "Amiga/Paula");
	musicInfo.channels = 4;
	musicInfo.max_vu = 64;
	musicInfo.rate = 50;

	// do not allow sound info from underlying api68 ...
	bDoFillSoundInfo = false;
	return OSME_SUCCESS;
}

int osmeCommon::loadFromMemory(void *pMusic, unsigned int length) {
	if(!memcmp(pMusic, "FC1", 3)) {
		return loadGeneric(pMusic, length, 0);
	} else if(!memcmp(pMusic, "BeEp", 4)) {
		return loadGeneric(pMusic, length, 1);
#ifdef ahx_test
	} else if(!memcmp(pMusic, "THX", 3)) {
		return loadGeneric(pMusic, length, 2);
#endif
	} else {
		return api68_load_mem(sc68, pMusic, length);
	}
}

int	osmeCommon::loadFromFile(const char * fname, int * size) {
	FILE * pFile;
	long lSize;
	size_t result;
	pFile = fopen ( fname , "rb" );
	if (pFile==NULL) {
		fputs ("File error",stderr); 
		return OSME_FILE_ERROR;
	}
	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	*size = (int)lSize;
	rewind (pFile);

	// allocate memory to contain the whole file:
	pInternalMusicBuffer = (char*) malloc (sizeof(char)*lSize);
	if (pInternalMusicBuffer == NULL) {
		return OSME_FILE_MEMORY_ERROR;
	}

	// copy the file into the buffer:
	result = fread (pInternalMusicBuffer,1,lSize,pFile);
	if (result != lSize) {
		return OSME_FILE_READ_ERROR;
	}
	bFreeInternalBuffer = true;
	// terminate
	fclose (pFile);
	return OSME_SUCCESS;
}

int	osmeCommon::internalPlaySC68Music(void *pMusic, unsigned int length, int trackId, const char * filename ) {
	bDoFillSoundInfo = true;
	if(initDone == 0) initialize();
    if(pMusic != NULL) {
		if(loadFromMemory(pMusic, length) == 0) {
			bReady = true;
		}
    } else if (filename != NULL) {
		int mySize;
		if(loadFromFile(filename, &mySize) == 0) {
			if(loadFromMemory(pInternalMusicBuffer, mySize) == 0) {
				bReady = true;
			}
		} else {
			return OSME_FILE_NOT_FOUND_ERROR;
		}
	} else {
		return OSME_USER_ERROR;
    }
	bInfoSet = false;
	if(bReady) {
		api68_play(sc68,trackId, 1);  
		if(!soundSubSys.open(soundSubSysCallback,2500)) {
			return OSME_SOUNDSUBSYSTEM_ERROR;
		}
		return 0;
	} else {
		return OSME_INITIALIZATION_ERROR;
	}
}
#endif
