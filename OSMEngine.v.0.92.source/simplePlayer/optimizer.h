#ifndef _AGGRESSIVEOPTIMIZE_H_
#define _AGGRESSIVEOPTIMIZE_H_

#pragma warning(disable:4711)

#ifdef NDEBUG
// /Og (global optimizations), /Os (favor small code), /Oy (no frame pointers)
#pragma optimize("gsy",on)

#if (_MSC_VER<1300)
	#pragma comment(linker,"/RELEASE")
#endif

// Note that merging the .rdata section will result in LARGER exe's if you using
// MFC (esp. static link). If this is desirable, define _MERGE_RDATA_ in your project.
#ifdef _MERGE_RDATA_
#pragma comment(linker,"/merge:.rdata=.data")
#endif // _MERGE_RDATA_

#pragma comment(linker,"/merge:.text=.data")
#if (_MSC_VER<1300)
	// In VC7, this causes problems with the relocation and data tables, so best to not merge them
	#pragma comment(linker,"/merge:.reloc=.data")
#endif

// Merging sections with different attributes causes a linker warning, so
// turn off the warning. From Michael Geary. Undocumented, as usual!
#if (_MSC_VER<1300)
	// In VC7, you will need to put this in your project settings
	#pragma comment(linker,"/ignore:4078")
#endif

// With Visual C++ 5, you already get the 512-byte alignment, so you will only need
// it for VC6, and maybe later.
#if _MSC_VER >= 1000

// Option #1: use /filealign
// Totally undocumented! And if you set it lower than 512 bytes, the program crashes.
// Either leave at 0x200 or 0x1000
#pragma comment(linker,"/FILEALIGN:0x200")

// Option #2: use /opt:nowin98
// See KB:Q235956 or the READMEVC.htm in your VC directory for info on this one.
// This is our currently preferred option, since it is fully documented and unlikely
// to break in service packs and updates.
#if (_MSC_VER<1300)
	// In VC7, you will need to put this in your project settings
	#pragma comment(linker,"/opt:nowin98")
#else

// Option #3: use /align:4096
// A side effect of using the default align value is that it turns on the above switch.
// Does nothing under Vc7 that /opt:nowin98 doesn't already give you
// #pragma comment(linker,"/ALIGN:512")
#endif

#endif // _MSC_VER >= 1000

#endif // NDEBUG

#endif //  _AGGRESSIVEOPTIMIZE_H_
