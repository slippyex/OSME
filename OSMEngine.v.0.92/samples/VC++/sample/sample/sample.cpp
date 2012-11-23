/*
 *                     OldSkoolMusaxxsEngine - Sample
 *      Copyright (C) 2007 SLiPPY/VeCTRONiX! <slippy@vectronixhq.de>
 *
 */
#pragma comment(lib, "dsound.lib")

#include <windows.h>
#include <stdio.h>

#include "../../../../static_libs/osme-funcs.h"

// include some music 
#include "dthingssndh.h"

static int  paused = 0;
static osme_music_info_t info;

int main(int na, char **a)
{
	printf("OSME library v0.92 (2007/06/28) by SLiPPY/VeCTRONiX! ...\n");
	printf("========================================================\n\n");
	// start playing
	int success = -1;
	success = playOSMEMusicMem(zaxxs, sizeof(zaxxs),1);
	if(success == 0) {
		info = getOSMEMusicInfo();
		printf("\n\npress ESC to quit\n");
		while (GetAsyncKeyState(VK_ESCAPE)>=0) 
		{ 
			if(GetAsyncKeyState(VK_F1) < 0) {
				if(paused == 0) {
					paused = 1;
					printf("Pause...\n");
					pauseOSMEMusic();
				}
			} else if(GetAsyncKeyState(VK_F2) < 0) {
				if(paused == 1) {
					paused = 0;
					printf("Resume...\n");
					resumeOSMEMusic();
				}
			} else if(GetAsyncKeyState(VK_F10) < 0) {
				printf("Set volume 50%...\n");
				setOSMEVolume(50);
			} else if(GetAsyncKeyState(VK_F11) < 0) {
				printf("Set volume 70%...\n");
				setOSMEVolume(70);
			} else if(GetAsyncKeyState(VK_F12) < 0) {
				printf("Set volume 100%...\n");
				setOSMEVolume(100);
			}
		}
		// stop and deinit the player
		stopOSMEMusic();
	} else {
		printf("OSME:: error while trying to initialize...");
		return -1;
	}
	return 0;
}

