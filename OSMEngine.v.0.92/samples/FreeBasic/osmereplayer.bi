''
''
'' Oldskool Music Engine Library v0.92 -- static FreeBasic-compatible library
''
'' ported by SLiPPY/VeCTRONiX! on 31.05.2007 last changes: 28.06.2007
'' original concept and base emulation code by Benjamin Gerard's SC68 emulation library
'' have fun using this lib in your productions :)
''
'' Cheers,
''    SLiPPY
''
'' currently activated external replay codes (Motorola 68k asm replayers)
''
'' Atari ST/E:
''  - SNDH
''
'' Amiga:
''  - Future Composer 1.3 / 1.4
''  - JamCrackerPro
''
#inclib "dsound"
#inclib "dxguid"
#inclib "winmm.dll"
#inclib "osmengine4"

type osme_music_info_t
	title as zstring * 80	
	composer as zstring * 60
	author as zstring * 60
	replay as zstring * 40
	hwname as zstring * 20
	time_ms as uinteger
	rate as uinteger
	addr as uinteger	
	channels as uinteger
	max_vu as uinteger
end type

' use this to play in-mem music (return 0 on success)
declare function playOSMEMusicMem cdecl alias "playOSMEMusicMem" (byval pMusic as any ptr, byval length as uinteger, byval trackId as integer) as integer
' same as above - only file-based
declare function playOSMEMusicFile cdecl alias "playOSMEMusicFile" (byval filename as zstring ptr, byval trackId as integer) as integer
' de-initializes the engine
declare sub stopOSMEMusic cdecl alias "stopOSMEMusic" ()
' pauses the current replay
declare sub pauseOSMEMusic cdecl alias "pauseOSMEMusic" ()
' resumes the replay
declare sub resumeOSMEMusic cdecl alias "resumeOSMEMusic" ()
' get current channel-information (for VU bars aso.)
declare function getOSMEChannelVU cdecl alias "getOSMEChannelVU" (byval i as integer) as ubyte
' get's a whole bunch of information about current music file
' in case you want to realize channelVU bars, use info.channels and info.max_vu (for max volume)
declare function getOSMEMusicInfo cdecl alias "getOSMEMusicInfo" () as osme_music_info_t
' set current replay volume in percent
declare sub setOSMEVolume cdecl alias "setOSMEVolume" (byval vol as integer)

' these methods here already exist but ... perhaps in v1.0 :)
'declare sub setQualityFilter cdecl alias "setQualityFilter" (byval onoff as integer)
'declare function getProcResult cdecl alias "getProcResult" () as integer
'declare sub fadeOutOSMEVolume cdecl alias "fadeOutOSMEVolume" (byval fadeOutTimeMS as integer)

