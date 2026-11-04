# Yleistä

Windows 7 SP1 (64-bit)  
Visual Studio 2019  
   * 32-bit: Microsoft Macro Assembler Version 14.24.28316.0  
   * 64-bit: Microsoft Macro Assembler (x64) Version 14.24.28316.0  

Windows 11  
Visual Studio 2022  

[Microsoft Macro Assembler (MASM)](https://learn.microsoft.com/en-us/cpp/assembler/masm/microsoft-macro-assembler-reference)  
[Microsoft Linker](https://learn.microsoft.com/en-us/cpp/build/reference/linking?view=msvc-170)  

**Projektin perusasetukset**  
Oletus: Debug-moodi (x86 tai x64).  
Kohdat 2-3: projektin on oltava valittu aktiiviseksi Solution Explorer:ssa. Epäaktiivinen -> valikkovalintoja piiloutuu.  
Kohdat 4-7: Project Properties  
1. New Empty Project (Windows, C++, Console)  
2. .asm tuki: valikosta Project, Build Customization. Rastitaan masm.  
3. Project, Add New Item (C++ ,.cpp tiedosto). Lisää .asm tiedosto ja tallenna  (pikanäppäin Ctrl-Shift-A)  
4. Linker : Debugging: Generate Map File:Yes (/MAP)  
5. 64 bit-koodin pinon koko. Linker: System (oletuspino 1M)  
6. Microsoft Macro Assembler: Listing File. Enable Assembly Generated Code Listing: Yes (/Sq)  
7. Microsoft Macro Assembler: Listing File. Assembled Code Listing File: $(IntDir)%(FileName).lst  

Linkit:  
[Add an assembler-language file to a Visual Studio C++ project](https://learn.microsoft.com/en-us/cpp/assembler/masm/masm-for-x64-ml64-exe?view=msvc-170#add-an-assembler-language-file-to-a-visual-studio-c-project)  
[/STACK (Stack Allocations)](https://learn.microsoft.com/en-us/cpp/build/reference/stack-stack-allocations?view=msvc-170)  
[.STACK (32-bit MASM)](https://learn.microsoft.com/en-us/cpp/assembler/masm/dot-stack?view=msvc-170)  

### Muita assemblereita

[as - the GNU assembler: MSYS2:n binutils-paketissa](https://www.msys2.org/)  
[Asmc Macro Assembler](https://github.com/nidud/asmc)  
[EuroAssembler](https://euroassembler.eu/eadoc/)  
[flat assembler](https://flatassembler.net/download.php)  
[GoAsm](https://www.godevtool.com/)  
[JWasm](https://github.com/JWasm/jwasm.github.io)  
[MASM32 SDK](https://masm32.com/index.htm)  (ei Microsoftin tuotos)  
[NASM](https://nasm.us/)  
[Open Watcom v2 Fork: Assembler](https://github.com/open-watcom/open-watcom-v2)  
[Pelles C: Macro Assembler](https://www.pellesc.se/)  
[SASM - Scriptable ASseMbler ](https://git.rosseaux.net/BeRo1985/sasm)  
[Solar Assembler](http://www.oby.ro/sol_asm/)  
[UASM](https://www.terraspace.co.uk/uasm.html)  

[Easy Code - Visual Assembler](https://www.easycode.cat/English/Help/EasyCode.htm)  
[RadASM2](https://github.com/mrfearless/RadASM2)  
[Visual MASM](https://www.visualmasm.com/)  

Kykenevät luomaan .exen ilman erillistä linkeriä: Asmc, EuroAssembler, flat assembler, JWasm, SASM, Solar Assembler, UASM

### Muita linkereitä

[GoLink](https://www.godevtool.com/)  
[JWlink](https://github.com/JWasm/JWlink)  
[ld - The GNU linker, MSYS2:n binutils-paketissa](https://www.msys2.org/)  
[lld](https://releases.llvm.org/)  
[mold](https://github.com/rui314/mold)  
[Open Watcom v2 Fork: Linker](https://github.com/open-watcom/open-watcom-v2)  
[Pelles C: polink](https://www.pellesc.se/)  
[wild](https://github.com/wild-linker/wild)  

### Muita debuggereita

[Eclipse CDT/Standalone Debugger](https://www.eclipse.org/cdt/downloads.php)  
[edb](https://github.com/eteran/edb-debugger)  
[GDB the GNU Debugger, MSYS2:n gdb paketti](https://www.msys2.org/)  
[gdbgui](https://www.gdbgui.com/)  
[GoBug ](https://www.godevtool.com/)  
[OllyDbg](https://www.ollydbg.de/)  
[Open Watcom v2 Fork: Debugger](https://github.com/open-watcom/open-watcom-v2)  
[x64dbg](https://x64dbg.com/)  

### Muut  

[C++ Insights](https://cppinsights.io/)  
[Library to Instrument Executable Formats (LIEF)](https://lief.re/)  
[LLVM Explorer](https://llvm-explorer.dev/)  
[Matt Godbolt's Compiler Explorer](https://godbolt.org/)  
[Free Code Manipulation Library](https://www.fcml-lib.com/)  
[x86-64 Playground](https://x64.halb.it/)  

[ModernUI](https://github.com/mrfearless/ModernUI64)  

### Dokumentit

[Eclipse CDT/Standalone Debugger](https://github.com/eclipse-cdt/cdt/blob/main/StandaloneDebugger.md)  
[Microsoft Macro Assembler reference](https://learn.microsoft.com/en-us/cpp/assembler/masm/microsoft-macro-assembler-reference)  
[Microsoft Macro Assembler (MASM) Unofficial Changelist](https://web.archive.org/web/20210624210202/bytepointer.com/masm/index.htm)  
[MASM 6.0 References](https://www.pcjs.org/documents/books/mspl13/masm/)  
[Agner Fog blogi](https://www.agner.org/optimize/)   
[AMD](https://docs.amd.com/search/all?query=programmer%27s&content-lang=en-US)  
[Intel](https://software.intel.com/en-us/articles/intel-sdm)  
[Windows API Index](https://learn.microsoft.com/en-us/windows/win32/apiindex/windows-api-list)  
[Calling conventions for different C++ compilers and operating systems By Agner Fog](https://www.agner.org/optimize/calling_conventions.pdf)  
[Assembly Hello World: Windows Edition](https://www.codermusings.com/windows-hello-world-assembly-x64-arm64/)  
 
# 32-bittinen kehitys 64-bittisellä alustalla

[Argument Passing and Naming Conventions](https://learn.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-170)  
[__stdcall](https://learn.microsoft.com/en-us/cpp/cpp/stdcall?view=msvc-170)  
[__cdecl](https://learn.microsoft.com/en-us/cpp/cpp/cdecl?view=msvc-170)  
[x86 calling conventions](https://en.wikipedia.org/wiki/X86_calling_conventions)  

Muita asm-apuja  
[Setup an Assembly Project on Visual Studio 2019 & 2022 - x86 & x64](https://programminghaven.home.blog/2020/02/16/setup-an-assembly-project-on-visual-studio-2019/)  

### eka_32.asm

Tulostetaan tekstiä WriteConsoleA-funktiota käyttäen (ANSI teksti, koodisivu 1252). Ei käytetä standardi C/C++ -funktioita. 
Ääkköset: Windowsin komentokehotteeseen komento: ```chcp 1252``` ja exe:n suoritus. Fontiksi Lucida Console.

### toka_32.asm

Sama kuin edellinen mutta käytetään Windows API kutsuihin PROTO ja INVOKE-direktiivejä. Generoitunut koodi tarkasteltavissa debuggerissa.  

INVOKE  GetStdHandle, STD_OUTPUT_HANDLE  
INVOKE  WriteConsoleA, [hConsole], ADDR teksti, SIZEOF teksti, 0, 0  
INVOKE  WriteConsoleA, [hConsole], ADDR teksti2, SIZEOF teksti2, 0, 0  

```asm
_start:
00831010  push        0FFFFFFF5h  
00831012  call        _GetStdHandle@4 (0831071h)  
00831017  cmp         eax,0  
0083101A  je          lopeta (0831057h)  
0083101C  cmp         eax,0FFFFFFFFh  
0083101F  je          lopeta (0831057h)  
00831021  mov         dword ptr [hConsole (0834000h)],eax  
00831026  push        0  
00831028  push        0  
0083102A  push        1Bh  
0083102C  push        offset teksti (0833000h)  
00831031  push        dword ptr [hConsole (0834000h)]  
00831037  call        _WriteConsoleA@20 (083107Dh)  
0083103C  cmp         eax,0  
0083103F  je          lopeta (0831057h)  
00831041  push        0  
00831043  push        0  
00831045  push        22h  
00831047  push        offset teksti2 (083301Bh)  
0083104C  push        dword ptr [hConsole (0834000h)]  
00831052  call        _WriteConsoleA@20 (083107Dh)  
lopeta:
00831057  push        0  
00831059  call        _ExitProcess@4 (0831077h)
```
### kolmas_32.asm

Vaihtaa konsolin koodisivua tekstin tulostusta varten. Toimii ainakin komentokehotteessa (fontiksi Lucida Console). 
Visual Studion debuggerissa ilmestyvän konsolin fontiksi Lucida Console, ja uusi suoritus Debug-tilassa.

### nelonen_32.asm

Tutkitaan MASM-direktiivien vaikutusta funktioiden koodiin. Tehdään eri tavoilla funktiokutsuja (käsin koodattu kutsu tai INVOKE). 

1. PROC  USES edx, kerrottava:DWORD, kertoja:DWORD   
```asm
  push        ebp  
  mov         ebp,esp  
  push        edx  
  mov         eax,dword ptr [kerrottava]  
  mul         eax,dword ptr [kertoja]  
  pop         edx  
  leave  
  ret
```

Ilman symboleja  
```asm
  push        ebp  
  mov         ebp,esp  
  push        edx  
  mov         eax,dword ptr [ebp+8]  
  mul         eax,dword ptr [ebp+0Ch]  
  pop         edx  
  leave  
  ret
```

2. PROC  
   LOCAL   lukuA:DWORD, lukuB:DWORD  
```asm
  push        ebp  
  mov         ebp,esp  
  add         esp,0FFFFFFF8h  
  mov         dword ptr [lukuA],2  
  mov         dword ptr [lukuB],3  
  mov         eax,dword ptr [lukuA]  
  add         eax,dword ptr [lukuB]  
  leave  
  ret
```

Ilman symboleja  
```asm
  push        ebp  
  mov         ebp,esp  
  add         esp,0FFFFFFF8h  
  mov         dword ptr [ebp-4],2  
  mov         dword ptr [ebp-8],3  
  mov         eax,dword ptr [ebp-4]  
  add         eax,dword ptr [ebp-8]  
  leave  
  ret
```

3. PROC  jaettava:DWORD, jakaja:DWORD  
```asm
  push        ebp  
  mov         ebp,esp  
  xor         edx,edx  
  mov         eax,dword ptr [jaettava]  
  div         eax,dword ptr [jakaja]  
  leave  
  ret
```

Ilman symboleja  
```asm
  push        ebp  
  mov         ebp,esp  
  xor         edx,edx  
  mov         eax,dword ptr [ebp+8]  
  div         eax,dword ptr [ebp+0Ch]  
  leave  
  ret
```

4. PROC    USES eax ebx, parametri:DWORD
   LOCAL   pinomuuttujaA:DWORD
```asm
  push        ebp  
  mov         ebp,esp  
  add         esp,0FFFFFFFCh  
  push        eax  
  push        ebx  
  mov         dword ptr [pinomuuttujaA],63h  
  mov         eax,dword ptr [pinomuuttujaA]  
  mov         ebx,dword ptr [parametri]  
  pop         ebx  
  pop         eax  
  leave  
  ret
```
Ilman symboleja  
```asm
  push        ebp  
  mov         ebp,esp  
  add         esp,0FFFFFFFCh  
  push        eax  
  push        ebx  
  mov         dword ptr [ebp-4],63h  
  mov         eax,dword ptr [ebp-4]  
  mov         ebx,dword ptr [ebp+8]  
  pop         ebx  
  pop         eax  
  leave  
  ret
```

Linkit:  
[PROC](https://learn.microsoft.com/en-us/cpp/assembler/masm/proc?view=msvc-170)  
[Procedures](https://www.c-jump.com/CIS77/ASM/Procedures/lecture.html)  

### vitonen_32.asm

Funktiot konsoli-I/O:n käyttämiseksi.

### kuudes_32.asm, konsoli_io_32.asm

Konsolin I/O-funktiot omaan tiedostoon. Makrot omiin tekstitiedostoihin. x87 liukulukuyksiköllä laskentaa ja funktioiden määrittelyjä.

Linkit:  
[Complex logarithm](https://en.wikipedia.org/wiki/Complex_logarithm)  
[Exponential_function Complex_plane](https://en.wikipedia.org/wiki/Exponential_function#Complex_plane)  
[KAlgebra](https://en.wikipedia.org/wiki/KAlgebra)  

### seiska_32.asm

Linkitetään DLL-kirjasto ajon aikana. Kutsutaan haluttua funktiota. Sovelluksena vakioveikkauksen rivin ja lottorivin arvonta.

Linkit:  
[RtlGenRandom function](https://learn.microsoft.com/en-us/windows/win32/api/ntsecapi/nf-ntsecapi-rtlgenrandom)  
[GetProcAddress function](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress)  
[LoadLibraryA function](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya)  
[FreeLibrary function](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-freelibrary)  

### kasi_32.asm

Tehdään tekstin sekoitusta ja sekoituksen purkua käyttäen Tritheimin taulukkoa ja juoksevaa avainta.

Linkit:  
[Tabula recta](https://en.wikipedia.org/wiki/Tabula_recta)  
[Running key cipher](https://en.wikipedia.org/wiki/Running_key_cipher)  
[Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher)  

# 64-bittinen kehitys

[x64 software conventions](https://learn.microsoft.com/en-us/cpp/build/x64-software-conventions?view=msvc-170)  
[x64 calling convention](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention?view=msvc-170)  
[x86 calling conventions](https://en.wikipedia.org/wiki/X86_calling_conventions)  
[Moving to Windows Vista x64](https://web.archive.org/web/20220705180913/https://www.codeproject.com/Articles/17263/Moving-to-Windows-Vista-x64)  

### eka_64.asm

Tulostetaan tekstiä WriteConsoleA-funktiota käyttäen (ANSI teksti, koodisivu 1252). Ei käytetä standardi C/C++ -funktioita. 
Ääkköset: Windowsin komentokehotteeseen komento: ```chcp 1252``` ja exe:n suoritus.
