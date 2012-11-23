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
#inclib "unice68"
#inclib "file68"
#inclib "sc68"
#inclib "osme"




' use this to play in-mem music (return 0 on success)
declare function playOSMEMusicMem cdecl alias "playOSMEMusicMem" (byval pMusic as any ptr, byval length as uinteger, byval trackId as integer) as integer
' same as above - only file-based
declare function playOSMEMusicFile cdecl alias "playOSMEMusicFile" (byval filename as zstring ptr, byval trackId as integer) as integer
' de-initializes the engine
declare sub stopOSMEMusic cdecl alias "stopOSMEMusic" ()

' these methods here already exist but ... perhaps in v1.0 :)
'declare sub setQualityFilter cdecl alias "setQualityFilter" (byval onoff as integer)
'declare function getProcResult cdecl alias "getProcResult" () as integer
'declare sub fadeOutOSMEVolume cdecl alias "fadeOutOSMEVolume" (byval fadeOutTimeMS as integer)

