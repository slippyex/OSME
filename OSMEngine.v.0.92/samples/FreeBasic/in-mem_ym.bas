' simple in-mem test
'#include "osmereplayer.bi"

#include "osme3.0.bi"
#include "media/dthings.bi"
#include "windows.bi"

    dim chVal, i, j as integer

playOSMEMusicMem(@zaxxs(0), 1007, 1)

'playOSMEMusicFile("media/P7_Action.sndh",1)
    print "Now playing "
    do
    loop until inkey$<> ""
        
    stopOSMEMusic()