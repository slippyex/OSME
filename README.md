About OSME
==========
The Oldskool Musics Engine is a tiny library which enables Win32/Linux users to play all these old chippy sounds from the Amiga/Atari ST(E) – to let it sound as natural as it should be, this library emulates a whole bunch of these old hardware elements which are:

+ MC68000 CPU<br/>
+ Atari YM-2149<br/>
+ Atari MFP-68901<br/>
+ Atari Shifter<br/>
+ Atari Microwire<br/>
+ Amiga Paula<br/>

All these chipsets are emulated almost accurately within this library. To make the usage of it as easy as possible I also included a DirectSound-based sound-subsystem which will be queried by some background threads.
The core library is capable of replaying the following formats natively:

+ Atari SNDH(*)<br/>
+ Amiga FutureComposer 1.3/1.4<br/>
+ Amiga JamCrackerPro<br/>

_``(*)SNDH:: this is a wrapper format which enables almost all different chip-based replayers``_

“Natively” means with their own 68k-asm based replayers as they are all replayed within the emulated environment …
Knowing this and also the fact that its usage is really easy and the library itself is compiled and packed not bigger than 40kb makes the OSMEngine somewhat outstanding IMHO as I’ve been looking for something like that for years … 
The core-emulation is based on a library called __“SC68?__ which has been written by [Benjamin Gerard (Ben/Overlanders)](http://sc68.atari.org/ "SC68 library") back in the year 2003. Its main idea was to replay these sounds – but it only existed as Winamp-Plugin and XMMS-Plugin … also the concept, how it’s been realized wasn’t suitable to integrate this into own productions. 

Anyway – without this SC68 library the OSMEngine would not exist! So big thanks to Ben for this …

#####Here’s some in-depth details to some of the emulated chips:

## Motorola 68000

#### Address bus
The 68000 was a clever compromise. When the 68000 was introduced, 16-bit buses were really the most practical size. However, the 68000 was designed with 32-bit registers and address spaces, on the assumption that hardware prices would fall.
Even though the 68000 had 16-bit ALUs, addresses were always stored as 32-bit quantities, i.e. it had a flat 32-bit address space. This meant that the 68000 was, and is, a 32-bit microprocessor. Contrast this to the 8086, which had 20-bit address space, but could only access 16-bit (64 kilobyte) chunks without manipulating segment registers. The 68000 achieved this functionality using three 16-bit ALUs. In normal operation, two 16-bit ALUs are chained together to perform an address operation, while the third executes the 16-bit arithmetic. 

For example, a 32-bit address register postincrement on a 16-bit ADD.W (An)+,Dn runs without speed penalty.
The original 68000 was internally a 16-bit part, but it was executing and existing within the parameters of a 32-bit ISA, as its instruction set describes a 32-bit architecture. The importance of architecture cannot be emphasized enough. Throughout history, addressing pains have not been hardware implementation problems, but always architectural problems (instruction set problems, i.e. software compatibility problems). The successor 68020 with 32-bit ALU and 32-bit databus runs unchanged 68000 software at “32-bit speed”, manipulating data up to 4 gigabytes, far beyond what software of other “16-bit” CPUs (for example, the 8086) could do. Contrast this with the problems posed by segmented architectures such as the 80286 which eventually had to be emulated entirely in software. It is seen as an act of great foresight for the 68000 series to have been 32-bit from the beginning.

However, forwards-incompatible software sometimes resulted from programmers storing data in the address bits (24 through 31) that weren’t implemented on the bus. When such code was executed on a machine with a wider address bus, bus errors resulted. Software upgrades were required before Macintosh computers could use over 8 MB RAM. This software usually remained backwards compatible. Many applications were written with more foresight, and never had such problems.
The 68000 required word and longword data items to be aligned to an even byte boundary. An attempt to access them at an odd address caused an exception. This restriction was lifted in the 32-bit 68020, although a performance penalty was still inflicted.

#### Internal registers
The CPU had eight 32-bit general-purpose data registers (D0-D7), and eight address registers (A0-A7). The last address register was also the standard stack pointer, and could be called either A7 or SP. This was a good number of registers in many ways. It was small enough to allow the 68000 to respond quickly to interrupts (because only 15 or 16 had to be saved), and yet large enough to make most calculations fast.

Having two types of registers was mildly annoying at times, but not hard to use in practice. Reportedly, it allowed the CPU designers to achieve a higher degree of parallelism, by using an auxiliary execution unit for the address registers.
Integer representation in the 68000 family is big-endian.
##### Status register
The 68000 comparison, arithmetic and logic operations set bits in a status register to record their results for use by later conditional jumps. The bits were “Z”ero, “C”arry, o”V”erflow, e”X”tend, and “N”egative. The e”X”tend bit deserves special mention, because it was separated from the Carry. This permitted the extra bit from arithmetic, logic and shift operations to be separated from the carry for flow-of-control and linkage.
#####The instruction set
The designers attempted to make the assembly language orthogonal. That is, instructions were divided into operations and address modes, and almost all address modes were available for almost all instructions. Many programmers disliked the “near” orthogonality, while others were grateful for the attempt.

At the bit level, the person writing the assembler would clearly see that these “instructions” could become any of several different op-codes. It was quite a good compromise because it gave almost the same convenience as a truly orthogonal machine, and yet also gave the CPU designers freedom to fill in the op-code table.

With only 56 instructions the minimal instruction size was huge for its day at 16 bits. Furthermore, many instructions and addressing modes added extra words on the back for addresses, more address-mode bits, etc.

Many designers believed that the MC68000 architecture had compact code for its cost, especially when produced by compilers. This belief in more compact code led to many of its design wins, and much of its longevity as an architecture.
This belief (or feature, depending on the designer) continued to make design wins for the instruction set (with updated CPUs) up until the ARM architecture introduced the Thumb instruction set that was similarly compact.
#####Privilege levels
The CPU, and later the whole family, implemented exactly two levels of privilege. User mode gave access to everything except the interrupt level control. Supervisor privilege gave access to everything. An interrupt always became supervisory. The supervisor bit was stored in the status register, and visible to user programs.
A real advantage of this system was that the supervisor level had a separate stack pointer. This permitted a multitasking system to use very small stacks for tasks, because the designers did not have to allocate the memory required to hold the stack frames of a maximum stack-up of interrupts.
#####Interrupts
The CPU recognized 7 interrupt levels. Levels 1 through 7 were strictly prioritized. That is, a higher-numbered interrupt could always interrupt a lower-numbered interrupt. In the status register, a privileged instruction allowed one to set the current minimum interrupt level, blocking lower priority interrupts. Level 7 was not maskable – in other words, an NMI. Level 1 could be interrupted by any higher level. Level 0 means no interrupt. The level was stored in the status register, and was visible to user-level programs.

Hardware interrupts are signalled to the CPU using three inputs that encode the highest pending interrupt priority. A separate interrupt controller is usually required to encode the interrupts, though for systems that do not require more than three hardware interrupts it is possible to connect the interrupt signals directly to the encoded inputs at the cost of additional software complexity. The interrupt controller can be as simple as a 74LS148 priority encoder, or may be part of a VLSI peripheral chip such as the MC68901 Multi-Function Peripheral, which also provided a UART, timer, and parallel I/O.
The “exception table” (interrupt vector addresses) was fixed at addresses 0 through 1023, permitting 256 32-bit vectors. The first vector was the starting stack address, and the second was the starting code address. Vectors 3 through 15 were used to report various errors: bus error, address error, illegal instruction, zero division, CHK & CHK2 vector, privilege violation, and some reserved vectors that became line 1010 emulator, line 1111 emulator, and hardware breakpoint. Vector 24 started the real interrupts: spurious interrupt (no hardware acknowledgement), and level 1 through level 7 autovectors, then the 15 TRAP vectors, then some more reserved vectors, then the user defined vectors.

Since at a minimum the starting code address vector must always be valid on reset, systems commonly included some nonvolatile memory (e.g. ROM) starting at address zero to contain the vectors and bootstrap code. However, for a general purpose system it is desirable for the operating system to be able to change the vectors at runtime. This was often accomplished by either pointing the vectors in ROM to a jump table in RAM, or through use of bank-switching to allow the ROM to be replaced by RAM at runtime.
The 68000 did not meet the Popek and Goldberg virtualization requirements for full processor virtualization because it had a single unprivileged instruction “MOVE from SR”, which allowed user-mode software read-only access to a small amount of privileged state.

The 68000 was also unable to easily support virtual memory, which requires the ability to trap and recover from a failed memory access. The 68000 does provide a bus error exception which can be used to trap, but it does not save enough processor state to resume the faulted instruction once the operating system has handled the exception. Several companies did succeed in making 68000 based Unix workstations with virtual memory that worked, by using two 68000 chips running in parallel on different phased clocks. When the “leading” 68000 encountered a bad memory access, extra hardware would interrupt the “main” 68000 to prevent it from also encountering the bad memory access. This interrupt routine would handle the virtual memory functions and restart the “leading” 68000 in the correct state to continue properly synchronized operation when the “main” 68000 returned from the interrupt.

These problems were fixed in the next major revision of the 68K architecture, with the release of the MC68010. The Bus Error and Address Error exceptions pushed a large amount of internal state onto the supervisor stack in order to facilitate recovery, and the MOVE from SR instruction was made privileged. A new unprivileged “MOVE from CCR” instruction was provided for use in its place by user mode software; an operating system could trap and emulate user-mode MOVE from SR instructions if desired.

##AMIGA Paula
The Paula chip is mainly used to produce audio output. The chip has 4 DMA-driven 8-bit PCM sample sound channels. Two sound channels are mixed into the left audio output, and the other two are mixed into the right output, producing stereo audio output. The only supported hardware sample format is signed linear 8-bit two’s complement. Each sound channel has an independent volume and frequency. Internally, the audio hardware is implemented by four state machines each having eight different states.

Additionally the hardware allows one channel in a channel pair to modulate the other channel’s period or amplitude. It is rarely used on Amiga, but could be used to achieve tremolo and vibrato like effects.
With some special programming tricks it is possible to produce 14-bit audio by combining two channels set at different volumes, giving two 14-bit channels instead of four 8-bit channels.

On a regular NTSC or PAL screen display, audio playback is limited to a maximum sampling rate of 28867 Hz, due to the amount of data that can be fetched from memory in the time allocated to Paula. As explained in the discussion of Agnus, memory access is prioritised and only a few slots for memory access are available to Paula’s sound channels. This limit can be overcome in the Enhanced Chip Set by using a higher frequency screen mode, or by using the CPU directly to drive audio output.

The Amiga contains an analog low-pass filter (reconstruction filter) which is external to Paula. The filter is a 12 dB/oct Butterworth low-pass filter at approximately 3.3 kHz. The filter can only be applied globally to all 4 channels. In models after the Amiga 1000, the brightness of the power LED is used to indicate the status of the filter. The filter is active when the LED is at normal brightness, and deactivated when dimmed (on early Amiga 500 models the LED went completely off). Models released before Amiga 1200 also have a static “tone knob” type lowpass filter that is enabled regardless of the optional “LED filter”. This filter is a 6 dB/oct lowpass filter with cutoff frequency at 4.5 or 5 kHz.

##Atari YM-2149
The YM-2149 (aka General Instrument AY-3-8910) was essentially a state machine, with the state being set up in a series of sixteen 8-bit registers. These were programmed over an 8-bit bus that was used both for addressing and data by toggling one of the external pins. For instance, a typical setup cycle would put the bus into “address mode” to select a register, and then switch to “data mode” to set the contents.

Six registers controlled the pitches produced in the three primary channels. The wavelength to generate was held in two eight-bit registers dedicated to each channel, but the value was limited to 12-bits for other reasons, for a total of 4096 different pitches. Another register controlled the period of a pseudo-random noise generator, while another controlled the mixing of this noise into the three primary channels.

Three additional registers controlled the volume of the channels, as well as turning on or off the option envelope controls on them. Finally the last three registers controlled the times of the ADSR envelope controller, by setting the lengths of time for each stage of the cycle. Unlike most systems, the 8910 used fixed times for the sustain and release, and a repeatable attack and decay pattern. For instance, the system could repeat the AD cycle of the sound over and over, or alternately invert it, starting loud and reducing to the sustain level without any attack phase.