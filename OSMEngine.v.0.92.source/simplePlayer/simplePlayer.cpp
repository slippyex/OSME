/*
 *                     OldSkoolMusaxxsEngine - Sample
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
#include <windows.h>
#include <stdio.h>
#include "../osme-library/osme-funcs.h"
#include "../osme-library/config.h"

#include "optimizer.h"

#ifdef __USE_DIRECTX__
	#pragma comment(lib, "dsound.lib")
#else
	#pragma comment(lib, "winmm.lib")
#endif

static int  paused = 0;

static osme_music_info_t info;

void clrbars(int x, int y, int amount) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {x, y};
	DWORD count;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	FillConsoleOutputCharacter(hStdOut, '-', amount, coord, &count);
	SetConsoleCursorPosition(hStdOut, coord);
}

void setCursor(int x, int y) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {x, y};
	SetConsoleCursorPosition(hStdOut, coord);
}

void cls() {
	DWORD hWrittenChars;
	CONSOLE_SCREEN_BUFFER_INFO strConsoleInfo;
	COORD Home;
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleHandle, &strConsoleInfo);
	FillConsoleOutputCharacter(hConsoleHandle, ' ', strConsoleInfo.dwSize.X * strConsoleInfo.dwSize.Y, Home, &hWrittenChars);
	SetConsoleCursorPosition(hConsoleHandle, Home);

}
int main(int na, char **a)
{
	cls();
	printf("OSME library v0.92 (2007/06/28) by SLiPPY/VeCTRONiX! ...\n");
	printf("========================================================\n\n");
	// start playing
	int success = -1;
	if(a[1] != NULL) {
		success = playOSMEMusicFile(a[1],1);
	} else {
		printf("filename is missing!\n");
	}
	if(success == 0) {
		info = getOSMEMusicInfo();
		printf("Now playing %s from %s\non %s using %s with %dHz\n", info.title, info.author, info.hwname, info.replay, info.rate);
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
			} else if(GetAsyncKeyState(VK_F9) < 0) {
				printf("Fading out in 5000ms...\n");
	//			fadeOutOSMEVolume(5000);
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
			setCursor(0,8);
			printf("ThreadProc Result :: %d\n\n", getProcResult());
			if(info.channels == 4) {
				printf("ch A:[%02d] ch B:[%02d] ch C:[%02d] ch D:[%02d]\n\n", getOSMEChannelVU(0), getOSMEChannelVU(1), getOSMEChannelVU(2), getOSMEChannelVU(3));
			} else {
				printf("ch A:[%02d] ch B:[%02d] ch C:[%02d]\n\n", getOSMEChannelVU(0), getOSMEChannelVU(1), getOSMEChannelVU(2));
			}
			int i, j, val;
			for(i = 0; i < info.channels; i++) {
				clrbars(10, 8+9+i, info.max_vu);
				setCursor(0, 8+9+i);
				printf("Channel %d [", i);
				val = getOSMEChannelVU(i);
				for(j = 0; j < val; j++) {
					if(j > 8 && j < 11) {
						printf("|");
					} else if (j >=11) {
						printf(":");
					} else {
						printf("#");
					}
				}
				printf("\n");
			}
		}
		// stop and deinit the player
		stopOSMEMusic();
		cls();
	} else {
		printf("OSME:: error while trying to initialize...");
		return -1;
	}
	return 0;
}

