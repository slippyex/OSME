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

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "libctiny.lib")

// DLL function signatures
typedef int (*importPlay)(const char*, int);
typedef void (*importStop)();
static importPlay playOSMEMusicFile;
static importStop stopOSMEMusic;

static HINSTANCE hinstLib;

// VC needs this symbol as soon as something uses floating point numbers
extern "C" int _fltused;
int _fltused;

int loadEngineDLL() {
	
    // Load DLL file
    hinstLib = LoadLibrary(TEXT("osmengine.dll"));
    if (hinstLib == NULL) {
		printf("osmengine.dll not found");
        return -1;
    }

    // Get function pointer
    playOSMEMusicFile = (importPlay)GetProcAddress(hinstLib, "playOSMEMusicFile");
	stopOSMEMusic = (importStop)GetProcAddress(hinstLib, "stopOSMEMusic");

    if (playOSMEMusicFile == NULL) {
		FreeLibrary(hinstLib);
		printf("error while trying to initiale dll functions");
        return -1;
    }
	return 1;
}

extern "C" int main(int argc, char *argv[])
{
	int iResult = loadEngineDLL();
	if(iResult > 0) {
		printf("OSME library (DLL version) v0.92 (2007/06/28) by SLiPPY/VeCTRONiX! ...\n");
		// start playing
		int success = -1;
		if(argv[1] != NULL) {
			iResult = playOSMEMusicFile(argv[1],1);
		} else {
			printf("filename is missing!\n");
		}
		if(iResult == 0) {
			printf("\n\npress ESC to quit\n");
			while (GetAsyncKeyState(VK_ESCAPE)>=0) 
			{ 

			}
			// stop and deinit the player
			stopOSMEMusic();
		} else {
			iResult = -1;
		}
		// Unload DLL file
		FreeLibrary(hinstLib);
	}
	return iResult;
}

