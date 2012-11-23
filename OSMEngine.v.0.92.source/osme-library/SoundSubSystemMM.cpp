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

#include "config.h"
#ifndef __USE_DIRECTX__
#include <windows.h>
#include "SoundSubSystemMM.h"
#include <stdio.h>

#pragma	comment(lib,"winmm.lib")

static	void CALLBACK waveOutProc(HWAVEOUT hwo,UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2) {
	if (WOM_DONE == uMsg) {
		CMMSoundSubSystem *pSoundSys = (CMMSoundSubSystem*)dwInstance;
		if (pSoundSys) {
			if (pSoundSys->IsRunning()) {
				pSoundSys->fillNextBuffer();
			}
		}
	}
}

CMMSoundSubSystem::CMMSoundSubSystem() {
		m_pUserCallback = NULL;
		m_currentBuffer = 0;
}

CMMSoundSubSystem::~CMMSoundSubSystem() {
		close();
}

bool CMMSoundSubSystem::open(USER_CALLBACK pUserCallback,long totalBufferedSoundLen) {
		m_pUserCallback = pUserCallback;
		m_bufferSize = ((totalBufferedSoundLen * REPLAY_RATE) / 1000) * REPLAY_SAMPLELEN;
		m_bufferSize /= REPLAY_NBSOUNDBUFFER;

		WAVEFORMATEX	wfx;
		wfx.wFormatTag = 1;		// PCM standart.
		wfx.nChannels = 2;		// Mono
		wfx.nSamplesPerSec = REPLAY_RATE;
		wfx.nAvgBytesPerSec = REPLAY_RATE*REPLAY_SAMPLELEN;
		wfx.nBlockAlign = REPLAY_SAMPLELEN;
		wfx.wBitsPerSample = REPLAY_DEPTH;
		wfx.cbSize = 0;
		MMRESULT errCode = waveOutOpen(	&m_hWaveOut,
										WAVE_MAPPER,
										&wfx,
										(DWORD)waveOutProc,
										(DWORD)this,					// User data.
										(DWORD)CALLBACK_FUNCTION);
		if (errCode != MMSYSERR_NOERROR) {
			printf(" -> OSME::sound callback-errCode : %d\n", errCode);
			return FALSE;
		}
		// Alloc the sample buffers.
		for (int i=0;i<REPLAY_NBSOUNDBUFFER;i++) {
			m_pSoundBuffer[i] = malloc(m_bufferSize);
			memset(&m_waveHeader[i],0,sizeof(WAVEHDR));
			memset(m_pSoundBuffer[i],0,m_bufferSize);
		}

		// Fill all the sound buffers
		m_currentBuffer = 0;
		for (int i=0;i<REPLAY_NBSOUNDBUFFER;i++) {
			fillNextBuffer();
		}

		return TRUE;
}

void CMMSoundSubSystem::close(void) {

		if (IsRunning()) {
			m_pUserCallback = NULL;
			waveOutReset(m_hWaveOut);					// Reset tout.
			for (int i=0;i<REPLAY_NBSOUNDBUFFER;i++) {
				if (m_waveHeader[i].dwFlags & WHDR_PREPARED) {
					waveOutUnprepareHeader(m_hWaveOut,&m_waveHeader[i],sizeof(WAVEHDR));
				}
				free(m_pSoundBuffer[i]);
			}
			waveOutClose(m_hWaveOut);
		}
}

void CMMSoundSubSystem::fillNextBuffer(void) {

		// check if the buffer is already prepared (should not !)
		if (m_waveHeader[m_currentBuffer].dwFlags&WHDR_PREPARED) {
			waveOutUnprepareHeader(m_hWaveOut,&m_waveHeader[m_currentBuffer],sizeof(WAVEHDR));
		}
		// Call the user function to fill the buffer with anything you want ! :-)
		if (m_pUserCallback) {
			m_pUserCallback(m_pSoundBuffer[m_currentBuffer],m_bufferSize);
		}
		// Prepare the buffer to be sent to the WaveOut API
		m_waveHeader[m_currentBuffer].lpData = (char*)m_pSoundBuffer[m_currentBuffer];
		m_waveHeader[m_currentBuffer].dwBufferLength = m_bufferSize;
		waveOutPrepareHeader(m_hWaveOut,&m_waveHeader[m_currentBuffer],sizeof(WAVEHDR));
		// Send the buffer the the WaveOut queue
		waveOutWrite(m_hWaveOut,&m_waveHeader[m_currentBuffer],sizeof(WAVEHDR));
		m_currentBuffer++;
		if (m_currentBuffer >= REPLAY_NBSOUNDBUFFER) m_currentBuffer = 0;
}
void CMMSoundSubSystem::pause(BOOL doPause) {
	m_doPause = doPause;
}

// still to be done for this sound subsystem :)
HRESULT	CMMSoundSubSystem::setEcho(void* pDSBuffer) {
	return 0;
}

HRESULT	CMMSoundSubSystem::setQualityFilter(void* pDSBuffer) {
	return 0;
}
void CMMSoundSubSystem::setVolume(int vol) {
	// TBD!
}

void CMMSoundSubSystem::fadeOut(int fadeOutTimeMS) {
	// TBD!
}

void CMMSoundSubSystem::qualityFilter(bool onoff) {
	// TBD!
}

#endif
