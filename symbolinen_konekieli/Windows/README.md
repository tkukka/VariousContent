# Yleistä

Windows 7 SP1 (64-bit)  
Visual Studio 2019  
   * 32-bit: Microsoft Macro Assembler Version 14.24.28316.0
   * 64-bit: Microsoft Macro Assembler (x64) Version 14.24.28316.0

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
[Add an assembler-language file to a Visual Studio C++ project](https://docs.microsoft.com/en-us/cpp/assembler/masm/masm-for-x64-ml64-exe?view=vs-2019#add-an-assembler-language-file-to-a-visual-studio-c-project)  
[/STACK (Stack Allocations)](https://docs.microsoft.com/en-us/cpp/build/reference/stack-stack-allocations)  
[.STACK (32-bit MASM)](https://docs.microsoft.com/en-us/cpp/assembler/masm/dot-stack)  

### Muita assemblereita

[as - the GNU assembler, MSYS2](https://www.msys2.org/)  
[Asmc Macro Assembler](https://github.com/nidud/asmc)  
[EuroAssembler](https://euroassembler.eu/eadoc/)  
[flat assembler](http://flatassembler.net/download.php)  
[GoAsm](http://www.godevtool.com/)  
[JWasm](https://github.com/JWasm/jwasm.github.io)  
[MASM32 SDK](https://www.masm32.com/)  (ei Microsoftin tuotos)  
[NASM](https://nasm.us/)  
[Open Watcom Assembler](http://openwatcom.org/download.php)  
[Pelles Macro Assembler](http://www.smorgasbordet.com/pellesc/)  
[Solar Assembler](http://www.oby.ro/sol_asm/)  
[UASM](http://www.terraspace.co.uk/uasm.html)  

[Easy Code - Visual Assembler](http://www.easycode.cat/English/Help/EasyCode.htm)  
[Visual MASM](http://www.visualmasm.com/)  

Kykenevät luomaan .exen ilman linkeriä: Asmc, EuroAssembler, flat assembler, JWasm, Solar Assembler, UASM

### Muita linkereitä

[GoLink](http://www.godevtool.com/)  
[JWlink](https://github.com/JWasm/jwasm.github.io)  
[ld - The GNU linker, MYS2](https://www.msys2.org/)  
[lld](https://releases.llvm.org/)  
[Open Watcom Linker](http://openwatcom.org/download.php)  
[Pelles Linker polink](http://www.smorgasbordet.com/pellesc/)  

### Muita debuggereita

[Eclipse CDT/Standalone Debugger](https://www.eclipse.org/cdt/downloads.php)  
[edb](https://github.com/eteran/edb-debugger)  
[GDB the GNU Debugger, MSYS2](https://www.msys2.org/)  
[gdbgui](https://www.gdbgui.com/)  
[GoBug ](http://www.godevtool.com/)  
[OllyDbg](http://www.ollydbg.de/)  
[Open Watcom Debugger](http://openwatcom.org/download.php)  
[x64dbg](https://x64dbg.com/)  

### Muut

[Matt Godbolt's Compiler Explorer](https://godbolt.org/)  
[Free Code Manipulation Library](http://www.fcml-lib.com/)  
[ModernUI](https://github.com/mrfearless/ModernUI64)  

### Dokumentit

[Microsoft Macro Assembler reference](https://docs.microsoft.com/en-us/cpp/assembler/masm/microsoft-macro-assembler-reference)  
[Microsoft Macro Assembler (MASM) Unofficial Changelist](http://bytepointer.com/masm/index.htm)  
[MASM 6.0 References](https://www.pcjs.org/documents/books/mspl13/masm/)  
[Agner Fog blogi](https://www.agner.org/optimize/)  
[AMD](https://www.amd.com/en/support/tech-docs)  
[Intel](https://software.intel.com/en-us/articles/intel-sdm)  
[Windows API Index](https://docs.microsoft.com/en-us/windows/win32/apiindex/windows-api-list)  
[Calling conventions for different C++ compilers and operating systems By Agner Fog](https://www.agner.org/optimize/calling_conventions.pdf)

# 32-bittinen kehitys 64-bittisellä alustalla

[Argument Passing and Naming Conventions](https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions)  
[__stdcall](https://docs.microsoft.com/en-us/cpp/cpp/stdcall)  
[__cdecl](https://docs.microsoft.com/en-us/cpp/cpp/cdecl)  
[x86 calling conventions](https://en.wikipedia.org/wiki/X86_calling_conventions)  

Muita asm-apuja  
[How to write hello world in assembler under Windows? - winapi](https://php.developreference.com/article/27378914/How+to+write+hello+world+in+assembler+under+Windows%3f)

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
[PROC](https://docs.microsoft.com/en-us/cpp/assembler/masm/proc)  
[Procedures](http://www.c-jump.com/CIS77/ASM/Procedures/lecture.html)  

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
[RtlGenRandom function](https://docs.microsoft.com/en-us/windows/win32/api/ntsecapi/nf-ntsecapi-rtlgenrandom)  
[GetProcAddress function](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress)  
[LoadLibraryA function](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya)  
[FreeLibrary function](https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-freelibrary)  

### kasi_32.asm

Tehdään tekstin sekoitusta ja sekoituksen purkua käyttäen Tritheimin taulukkoa ja juoksevaa avainta.

Linkit:  
[Tabula recta](https://en.wikipedia.org/wiki/Tabula_recta)  
[Running key cipher](https://en.wikipedia.org/wiki/Running_key_cipher)  
[Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher)  

# 64-bittinen kehitys

[x64 software conventions](https://docs.microsoft.com/en-us/cpp/build/x64-software-conventions)  
[x64 calling convention](https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention)  
[x86 calling conventions](https://en.wikipedia.org/wiki/X86_calling_conventions)  
[Moving to Windows Vista x64](https://www.codeproject.com/Articles/17263/Moving-to-Windows-Vista-x64)  

### eka_64.asm

Tulostetaan tekstiä WriteConsoleA-funktiota käyttäen (ANSI teksti, koodisivu 1252). Ei käytetä standardi C/C++ -funktioita. 
Ääkköset: Windowsin komentokehotteeseen komento: ```chcp 1252``` ja exe:n suoritus.
