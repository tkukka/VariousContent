# Yleistä

Ubuntu 18.04 LTS (64-bit)  
Netwide Assembler [NASM](https://nasm.us/ "nasm") v. 2.14.02 Stable  
Linkkeri: GNU ld (GNU Binutils for Ubuntu) 2.30  
C-kääntäjä: GCC 7.5 tai 8.3  

[GNU Project debugger ohjetta](http://sourceware.org/gdb/download/onlinedocs/gdb/index.html)  
[Eclipse Stand-alone C/C++ GDB Graphical Debugger](https://www.eclipse.org/cdt/downloads.php)  

### Dokumentit  

[Sample nasm programs](https://www.csee.umbc.edu/portal/help/nasm/sample.shtml )  

[Agner Fog blogi](https://www.agner.org/optimize/)  
[System V Application Binary Interface](https://github.com/hjl-tools/x86-psABI/wiki/X86-psABI)  
[AMD](https://www.amd.com/en/support/tech-docs)  
[Intel](https://software.intel.com/en-us/articles/intel-sdm)


# Eclipse Stand-alone C/C++ GDB Graphical Debugger

![Kuva debuggerista](./image-cdt-debug.png)

Toimii, hieman tahmea käynnistys; Java-pohjainen??  
Konfiguroitavissa: värit, ikkunat, ...  
Toimii parhaiten käynnistämällä ilman parametreja, ja hakee binäärin käynnistysdialogiin. Debuggerissa avataan lähdekoodi lisäksi. 
Lähdekoodin hakupolkuja voi määritellä myös.

Intel-syntaksi GDB:ssä:  
Kotihakemistoon tiedosto .gdbinit, johon rivi: set disassembly-flavor intel  

Intel-syntaksi myös Eclipsen C/C++ debuggeriin:  
Window: Preferences, sieltä C/C++: Debug: GDB. Debug Configuration Defaults, kenttä: GDB command file. 
Browse:lla haetaan .gdbinit. Ilmestyy koko polku tiedostoon. Pelkkä .gdbinit kentässä ei riitä.


Koko [Eclpse CDT](https://www.eclipse.org/cdt/) softan debuggeri toiminnee samoin.

# 32-bittinen kehitys 64-bittisellä alustalla

Systeemikutsujen numerot: /usr/include/x86_64-linux-gnu/asm/unistd_32.h  
Paketit: gcc-multilib libc6-dev-i386 (gcc-8: gcc-8-multilib, jos oletus gcc on 7.x)  
[System V Application Binary Interface - Intel386](https://github.com/hjl-tools/x86-psABI/wiki/X86-psABI)  

Komentoriviparametrit:  
1. assembler nasm: -w +all -f elf32 -g -F dwarf -l listaus.lst -o objektitiedosto.o lähdekoodi.asm  
2. linker ld: -m elf_i386 objektitiedosto(t) -o binääri --Map tiedosto.map -dynamic-linker /lib/ld-linux.so.2
3. gcc: -m32 (jos gcc myös 'linkkerinä', niin muuta ei tarvitse C+asm -projekteissa )

### eka_32.asm

Tulostetaan tekstiä (UTF-8) käyttäen perinteistä ohjelmistopohjaista keskeytystä int 80h.  
Ei käytetä GNU C-kirjastoa glibc:  
```Shell Session
$ ldd eka32
   not a dynamic executable
```
Ei näy: linux-gate.so.1

### toka_32.asm

Haetaan vDSO:n (virtual dynamic shared object) tarjoama funktio __kernel_vsyscall().  
Tulostetaan tekstiä sitä käyttäen. Käytetaan funktion haussa tunnistetta AT_SYSINFO.  
Ei käytetä GNU C-kirjastoa glibc:  
```Shell Session
$ ldd toka_32
   not a dynamic executable
```
Ei näy: linux-gate.so.1  

Hyödylliset linkit:  
[Linux Programmer's Manual - VDSO](http://man7.org/linux/man-pages/man7/vdso.7.html)  
[About ELF Auxiliary Vectors](http://articles.manugarg.com/aboutelfauxiliaryvectors.html)  
[Anatomy of a system call, part 2](https://lwn.net/Articles/604515/)  
[The Definitive Guide to Linux System Calls](https://blog.packagecloud.io/eng/2016/04/05/the-definitive-guide-to-linux-system-calls/)  
The flat assembler Message Board: [[Linux32] vDSO, auxv, vsyscall, int 0x80, calling the kernel](https://board.flatassembler.net/topic.php?t=20926)

### kolmas_32.asm, kolmas_funktio_32.asm

Käytetään aliohjelmia, samasta lähdekooditiedostosta ja toisesta .asm-tiedostosta. Kokeillaan parametrien välitystä pinon kautta. 
Paluuarvo EAX- tai st0-rekisteriin. Kokeillaan x87 liukulukuyksikköä. Ei käytetä GNU C-kirjastoa glibc.

**GDB**  
```gdb ./binääri```  
komennot   
   * file <binääri>  # lataa uudestaan jos koodi käännetty uusiksi session aikana
   * directory <dir>  # lähdekoodin sijainti
   * b <funktio>  # breakpoint: pysäytä funktion alussa
   * disassembly <funktio> # näkyykö sopivia rivejä breakpointin sijoitteluun
   * b *funktio + N   # breakpoint funktiossa riville N. disassembly näyttää.
   * b osoite  # breakpoint. Osoite esim. disassemblystä.
   * run   # suorita alusta
   * delete N  # poista breakpoint nro N
   * info breakpoints  # lista breakpointeista
   * n  # askella
   * continue  # suorita. seuraavaan breakpointiin tai loppuun normaalisti
   * info registers [all]  # yleisrekisterit ( tai kaikki )
   * p(rint) /x $esp  # ESP heksana
   * p /d $eax  # EAX 10-järjestelmän lukuna
   * p /f (double) symboli  # double-tyypin 'symboli' desimaalilukuna
   * p /d *($ebx)  # EBX:n osoittaman muistipaikan sisältö 10-järj.
   * p /d *($ebx + N) # EBX:n osoittaman muistipaikan arvoon + N tavua, ja sisältö 10-järj.

Hyödylliset linkit:  
[GNU GDB Debugger Command Cheat Sheet](http://www.yolinux.com/TUTORIALS/GDB-Commands.html)

### neljas.asm

Lasketaan ympyrän pinta-ala SSE2 (Streaming SIMD Extensions) -(skalaari)käskyillä aliohjelmassa. Käskyjen operandi: 
64-bittinen, C-kielen double. Laskentaparametrit pinon kautta ja muistista. Paluuarvo xmm0-rekisteriin. Skriptataan GDB-debuggeria 
komentotiedostolla ja shell-komennoilla. Ei käytetä GNU C-kirjastoa glibc.  

Hyödylliset linkit:  
[x86/x64 SIMD Instruction List (SSE to AVX512)](https://www.officedaytime.com/simd512e/)  
[Gem #119 : GDB Scripting— Part 1](https://www.adacore.com/gems/gem-119-gdb-scripting-part-1)  
[Core Dumped - Scripting GDB](https://amazingdim.wordpress.com/2014/02/01/gdb-script/)

### viides.asm

Haetaan funktio __kernel_vsyscall() AT_SYSINFO-tunnisteen avulla. Verrataan funktion osoitetta GNU C kirjaston (glibc) 
säiekohtaiseen dataan (TCB) kirjoittaman osoitteen kanssa. Nyt on **int 80h**:n lisäksi kaksi muuta tapaa tehdä 
systeemikutsuja 32-bittisessä suoritusympäristössä.  

ld-linkkerille uusi parametri: -lc  
(linkitetään GNU C-kirjastoon)

```Shell Session
$ ldd viides_32
  	linux-gate.so.1 (0xf7f57000)
	libc.so.6 => /lib32/libc.so.6 (0xf7d53000)
	/lib/ld-linux.so.2 (0xf7f59000)
```

Hyödylliset linkit:  
[Linux syscall ABI](http://esec-lab.sogeti.com/posts/2011/07/05/linux-syscall-abi.html)  
[The Definitive Guide to Linux System Calls](https://blog.packagecloud.io/eng/2016/04/05/the-definitive-guide-to-linux-system-calls/)  
[Sysenter Based System Call Mechanism in Linux 2.6](http://articles.manugarg.com/systemcallinlinux2_6.html)  
[GNU C Library. Native POSIX Thread Library (NPTL). i386](https://github.molgen.mpg.de/git-mirror/glibc/tree/master/sysdeps/i386/nptl)  
[GNU C Library. Definition for thread-local data handling. nptl i386 version.](https://github.molgen.mpg.de/git-mirror/glibc/blob/master/sysdeps/i386/nptl/tls.h)  
[GNU C Library. Linux i386 macros](https://github.molgen.mpg.de/git-mirror/glibc/blob/master/sysdeps/unix/sysv/linux/i386/sysdep.h)  
[Porting the GNU C Library to Unix Systems](https://www.gnu.org/software/libc/manual/html_node/Porting-to-Unix.html)  
[The GS segment and stack smashing protection](https://www.software-architect.net/blog/article/date/2015/03/31/the-gs-segment-and-stack-smashing-protection-1.html)

### kuudes_sse_32.asm, kuudes_x87_32.asm, kuudes_c_fun_32.asm, kuudes_main_32.c

C + asm-projekti. Kutsutaan funktioita C => asm => C (System V ABI i386). Lasketaan ympyrän ala x87- ja SSE2-käskyillä. 
Kutsutaan assembly-koodissa standardi C funktiota strtoul tietylle merkkijonolle. 

x87-versio: ```make```  
SSE-versio: ```make USE_SSE=1```  

### seiska_32.asm, seiska_main_32.c

C + asm-projekti. C-kielisessä ohjelman osassa on const char [] -teksti, jonka päälle assembler-koodissa yritetään kirjoittaa.  

```Shell Session
$ ./seiska_32
C main: alkuperäinen teksti: ei voi muokata
asm kirjoittaa...
Segmentation fault (core dumped)
```

# 64-bittinen kehitys 64-bittisellä alustalla

Systeemikutsujen numerot: /usr/include/x86_64-linux-gnu/asm/unistd_64.h  
Systeemikutsujen parametrit: man 2 <funktio> , esim. man 2 write  
Paketit: oletuksena asennetut  
[System V Application Binary Interface - AMD64](https://github.com/hjl-tools/x86-psABI/wiki/X86-psABI)  

Komentoriviparametrit:  
1. assembler nasm: -w +all -f elf64 -g -F dwarf -l listaus.lst -o objektitiedosto.o lähdekoodi.asm  
2. linker ld: -o binääri --Map tiedosto.map  

Kääntäminen:  
```make BITS=64 ```

Käännöksen (binäärit, objektit, listaukset,...) poisto  
```make BITS=64 clean```

### eka_64.asm

Tulostetaan tekstiä (UTF-8) käyttäen syscall-käskyä.  
Ei käytetä GNU C-kirjastoa glibc:  
```Shell Session
$ ldd eka_64
   not a dynamic executable
```

### toka_64.asm, toka_funktio_64.asm
Käytetään aliohjelmia, samasta lähdekooditiedostosta ja toisesta .asm-tiedostosta. 
Kokeillaan parametrien välitystä rekisterien kautta (x64 API). Paluuarvo EAX- tai XMM0-rekisteriin. 
Tehdään liukulukulaskentaa SSE2-skalaarikäskyillä.  

Ei käytetä GNU C-kirjastoa glibc:  
```Shell Session
$ ldd toka_64
   not a dynamic executable
```

### kolmas_c_fun_64.asm, kolmas_64.asm, kolmas_main_64.c

x64 C + asm-projekti. Kutsutaan funktioita C => asm => C (System V ABI x64). Lasketaan ympyrän ala liukuluvuilla (SSE). 
Kutsutaan assembly-koodissa standardi C funktiota strtoul tietylle merkkijonolle.  

Hyödylliset linkit:  
[NASM Calling Procedures Outside the Library](https://www.nasm.us/xdoc/2.14.02/html/nasmdoc9.html#section-9.2.5)  
[NASM REL & ABS: RIP-relative addressing](https://www.nasm.us/xdoc/2.14.02/html/nasmdoc6.html#section-6.2.1)  
[NASM Position-Independent Code: macho Special Symbols and WRT](https://www.nasm.us/xdoc/2.14.02/html/nasmdoc7.html#section-7.9.3)  


