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

#ifndef	__MMSOUNDSUBSYSTEM__
#define	__MMSOUNDSUBSYSTEM__


#define	REPLAY_RATE				44100
#define	REPLAY_DEPTH			16
#define	REPLAY_SAMPLELEN		(REPLAY_DEPTH/4)
#define	REPLAY_NBSOUNDBUFFER	2

typedef void (*USER_CALLBACK) (void *pBuffer,long bufferLen);
static BOOL m_doPause;
class	CMMSoundSubSystem {

public:
		CMMSoundSubSystem();
		~CMMSoundSubSystem();
		bool	open(USER_CALLBACK pUserCallback, long totalBufferedSoundLen=4000);		// Buffered sound, in ms
		bool	IsRunning()	{ 
			return m_pUserCallback != NULL; 
		}
		void	close(void);
		void	pause(BOOL doPause);
		void	fillNextBuffer(void);
		void	qualityFilter(bool onoff);
		void	setVolume(int vol);
		void	fadeOut(int fadeOutTimeMS);
		HRESULT	setEcho(void* pDSBuffer);
		HRESULT	setQualityFilter(void* pDSBuffer);
private:
		HWND							m_hWnd;
		long							m_bufferSize;
		long							m_currentBuffer;
		void						*	m_pSoundBuffer[REPLAY_NBSOUNDBUFFER];
		volatile	USER_CALLBACK		m_pUserCallback;
		HWAVEOUT						m_hWaveOut;
		WAVEHDR							m_waveHeader[REPLAY_NBSOUNDBUFFER];
};


#endif
