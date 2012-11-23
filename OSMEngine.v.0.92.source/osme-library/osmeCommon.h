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
#pragma once
#include "osme-funcs.h"

class osmeCommon
	{
	public:
		osmeCommon(void);
		~osmeCommon(void);
		int		getProcResult();
		void	closeSoundServer();
		void	pauseOutput(bool);
		void	setQualityFilter(bool);
		void	setVolume(int);
		void	shutdownOSME();
		unsigned char	getInternalVolume(int);
		int		internalPlaySC68Music(void *pMusic, unsigned int length, int trackId, const char * filename );
		osme_music_info_t	fillMusicInfo(void);

	private:
		void	initialize(void);
		int		loadGeneric(void * pMusic, int size, int type); 
		int		loadFromMemory(void *pMusic, unsigned int length);
		int		loadFromFile(const char * fname, int * size);
	};
