# Yleistä

Windows 7 SP1 (64-bit)  
Visual Studio 2019  
   * 32-bit: Microsoft Macro Assembler Version 14.24.28316.0
   * 64-bit: Microsoft Macro Assembler (x64) Version 14.24.28316.0

### Muita assemblereita

### Muita linkereitä

### Muita debuggereita


### Dokumentit

[Microsoft Macro Assembler reference](https://docs.microsoft.com/en-us/cpp/assembler/masm/microsoft-macro-assembler-reference)  
[Microsoft Macro Assembler (MASM) Unofficial Changelist](http://bytepointer.com/masm/index.htm)  
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
Ääkköset: Windowsin komentokehotteeseen komento: ```chcp 1252``` ja exe:n suoritus.

# 64-bittinen kehitys 64-bittisellä alustalla

[x64 software conventions](https://docs.microsoft.com/en-us/cpp/build/x64-software-conventions)  
[x64 calling convention](https://docs.microsoft.com/en-us/cpp/build/x64-calling-convention)  
[x86 calling conventions](https://en.wikipedia.org/wiki/X86_calling_conventions)  

### eka_64.asm

Tulostetaan tekstiä WriteConsoleA-funktiota käyttäen (ANSI teksti, koodisivu 1252). Ei käytetä standardi C/C++ -funktioita. 
Ääkköset: Windowsin komentokehotteeseen komento: ```chcp 1252``` ja exe:n suoritus.
