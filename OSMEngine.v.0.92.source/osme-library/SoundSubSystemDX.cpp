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

#ifdef __USE_DIRECTX__

#include "SoundSubSystemDX.h"
#pragma	comment(lib,"dsound.lib")
#pragma comment(lib,"dxguid.lib")

static	bool	m_bDoFading;
static	int		m_iFadingSleeper;
static	int		m_iCurrentFadingVolume;
static  CDXSoundSubSystem *pDS = 0;

CDXSoundSubSystem::CDXSoundSubSystem() {
	m_hWnd = GetForegroundWindow();
	reset();
}


CDXSoundSubSystem::~CDXSoundSubSystem() {
	close();
}

void CDXSoundSubSystem::reset(void) {
	m_pDS8 = NULL;
	m_pPrimary = NULL;
	m_pBuffer = NULL;
	m_bThreadRunning = false;
	m_bThreadKillRequired = false;
	m_bDoFading = false;
	m_iCurrentFadingVolume = 100;
	m_hThread = INVALID_HANDLE_VALUE;
	m_hFadeOutThread = INVALID_HANDLE_VALUE;
	m_writePos = 0;
	m_bQualityFilter = false;
}

static	DWORD WINAPI __stdcall threadRout(void *pObject) {
	if(!pDS) {
		pDS = (CDXSoundSubSystem *)pObject;
	}
	if (pDS) {
		while ( pDS->update() ) {
			Sleep(30);
		}
	}
    return 0;
}

static	DWORD WINAPI __stdcall threadDoFade(void *pObject) {
	if(pDS && m_bDoFading) {
		if(m_iCurrentFadingVolume <= 0) {
			m_iCurrentFadingVolume = 100;
			m_bDoFading = false;
			return 0;
		}
		pDS->setVolume(m_iCurrentFadingVolume);
		m_iCurrentFadingVolume--;
		Sleep(m_iFadingSleeper);
	}
    return 0;
}

void CDXSoundSubSystem::fadeOut(int fadeOutTimeMS) {
	if(fadeOutTimeMS > 0) {
		m_iFadingSleeper = fadeOutTimeMS / 100;
		m_bDoFading = true;
	}
}

bool CDXSoundSubSystem::open(DXUSER_CALLBACK pUserCallback,long totalBufferedSoundLen) {
	// First, create a DirectSound object (link your app with DSOUND.LIB)
	m_pUserCallback = pUserCallback;
	HRESULT hRes = ::DirectSoundCreate8(0, &m_pDS8, 0);
	if (hRes == DS_OK) {	// Then we have to set a cool cooperative level :-)
		hRes = m_pDS8->SetCooperativeLevel(m_hWnd,DSSCL_EXCLUSIVE | DSSCL_PRIORITY);
		if (hRes == DS_OK) {	// Create the primary audio buffer.
			DSBUFFERDESC bufferDesc;
			memset(&bufferDesc, 0, sizeof(DSBUFFERDESC));
			bufferDesc.dwSize = sizeof(DSBUFFERDESC);
			bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER|DSBCAPS_STICKYFOCUS|DSBCAPS_CTRLVOLUME;
			bufferDesc.dwBufferBytes = 0;
			bufferDesc.lpwfxFormat = NULL;
			hRes = m_pDS8->CreateSoundBuffer(&bufferDesc,&m_pPrimary, NULL);
			if (hRes == DS_OK) {	// And set its own internal format (44.1Khz, stereo, 16bits)
				WAVEFORMATEX format;
				memset(&format, 0, sizeof(WAVEFORMATEX));
				format.wFormatTag = WAVE_FORMAT_PCM;
				format.nChannels = 2; // stereo
				format.nSamplesPerSec = DXREPLAY_RATE;
				format.nAvgBytesPerSec = DXREPLAY_SAMPLESIZE * DXREPLAY_RATE;
				format.nBlockAlign = DXREPLAY_SAMPLESIZE;
				format.wBitsPerSample = DXREPLAY_DEPTH;
				format.cbSize = 0;
				if (hRes == DS_OK) {	
					// Now create a normal sound buffer.
					DSBUFFERDESC bufferDesc;
					memset(&bufferDesc,0,sizeof(bufferDesc));
					bufferDesc.dwSize = sizeof(bufferDesc);
					bufferDesc.dwFlags = DSBCAPS_GETCURRENTPOSITION2|DSBCAPS_STICKYFOCUS;
					bufferDesc.dwBufferBytes = DXREPLAY_BUFFERLEN;
					bufferDesc.lpwfxFormat = &format; // Same format as primary
					hRes = m_pDS8->CreateSoundBuffer(&bufferDesc,&m_pBuffer,NULL);
					if (hRes == DS_OK) {	
						// Start playing buffer
						hRes = m_pBuffer->Play(0, 0, DSBPLAY_LOOPING);
						if (hRes == DS_OK) {	
							// And finally create and launch the thread routs.
							DWORD	tmp, tmp2;
							m_hThread = (HANDLE)CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)threadRout,(void *)this,0,&tmp);
							m_hFadeOutThread = (HANDLE)CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)threadDoFade,(void *)this,0,&tmp2);
							m_bThreadRunning = true;
							return true;
						}
					}
				}
			}
		}
	}
	return false;	
}

bool CDXSoundSubSystem::update(void) {
	DWORD	playPos,unusedWriteCursor;
	DWORD	writeLen;
	LPVOID	p1,p2;
	DWORD	l1,l2;
	HRESULT hRes;
	hRes = m_pBuffer->GetCurrentPosition(&playPos,&unusedWriteCursor);
	if (hRes != DS_OK) playPos = 0;

	if (m_writePos < playPos)
		writeLen = playPos - m_writePos;
	else
		writeLen = DXREPLAY_BUFFERLEN - (m_writePos - playPos);

    while (DS_OK != m_pBuffer->Lock(m_writePos,writeLen,&p1,&l1,&p2,&l2,0)) {
		m_pBuffer->Restore();
		if(m_bQualityFilter) {
			// do ParamEQ here ...
//			setQualityFilter(m_pBuffer);
		}
		m_pBuffer->Play(0, 0, DSBPLAY_LOOPING);
	}

	if (m_pUserCallback) {
		if ((p1) && (l1>0)) m_pUserCallback(p1,l1);
		if ((p2) && (l2>0)) m_pUserCallback(p2,l2);
	}
	m_pBuffer->Unlock(p1,l1,p2,l2);
	m_writePos += writeLen;

	if (m_writePos >= DXREPLAY_BUFFERLEN) m_writePos -= DXREPLAY_BUFFERLEN;

	if (m_bThreadKillRequired) m_bThreadRunning = false;
	return (!m_bThreadKillRequired);
}

void CDXSoundSubSystem::qualityFilter(bool onoff) {
	m_bQualityFilter = onoff;
}

void CDXSoundSubSystem::close(void) {
	while (m_bThreadRunning) {
		m_bThreadKillRequired = true;
	}
	if (m_hThread != INVALID_HANDLE_VALUE) CloseHandle(m_hThread);
	if (m_pBuffer) m_pBuffer->Release();
	if (m_pPrimary) {
		m_pPrimary->SetVolume(DSBVOLUME_MAX);
		m_pPrimary->Release();
	}
	if (m_pDS8) m_pDS8->Release();
	reset();
}

void CDXSoundSubSystem::pause(bool doPause) {
	// NOP! ;)
}

HRESULT CDXSoundSubSystem::setEcho(LPDIRECTSOUNDBUFFER8 pDSBuffer) {
  HRESULT hr;
  DWORD dwResults[1];  // One element for each effect.
 
  // Describe the effect.
  DSEFFECTDESC dsEffect;
  memset(&dsEffect, 0, sizeof(DSEFFECTDESC));
  dsEffect.dwSize = sizeof(DSEFFECTDESC);
  dsEffect.dwFlags = 0;
  dsEffect.guidDSFXClass = GUID_DSFX_STANDARD_ECHO;
  // Set the effect
  if (SUCCEEDED(hr = pDSBuffer->SetFX(1, &dsEffect, dwResults))) {
  }
  return hr;
}

HRESULT CDXSoundSubSystem::setQualityFilter(LPDIRECTSOUNDBUFFER8 pDSBuffer) {
	HRESULT hr;
	DWORD dwResults[1];  // One element for each effect.

	// Describe the effect.
	DSEFFECTDESC dsEffect;
	memset(&dsEffect, 0, sizeof(DSEFFECTDESC));
	dsEffect.dwSize = sizeof(DSEFFECTDESC);
	dsEffect.dwFlags = 0;
	dsEffect.guidDSFXClass = GUID_DSFX_STANDARD_PARAMEQ;

	// Set the effect
	if (SUCCEEDED(hr = pDSBuffer->SetFX(1, &dsEffect, dwResults))) {
	}
	return hr;
}

void CDXSoundSubSystem::setVolume(int vol) {
	long factor = (DSBVOLUME_MAX - (DSBVOLUME_MIN/2)) / 100;
	long lTest = -(100-vol)*factor;
	if(lTest <= DSBVOLUME_MAX && lTest > DSBVOLUME_MIN) {
		m_pPrimary->SetVolume(lTest);
	}
}

#endif
