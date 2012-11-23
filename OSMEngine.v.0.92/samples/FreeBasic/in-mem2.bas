' simple file-based test
#include "osmereplayer.bi"
#include "media/dthings.bi"
#include "windows.bi"

playOSMEMusicMem(@zaxxs(0), 1007, 1)

'    playOSMEMusicFile("no.fc",1)
    print "Press any key to exit..."
	sleep
    stopOSMEMusic()