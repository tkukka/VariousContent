# Symbolinen konekieli

## Paikka ja aika

Raahen tietokonealan oppilaitos (Ratol) 1998

## Suoritus

Luennot ja käytännön harjoitukset ATK-luokassa.  
Kaksi välikoetta: kirjallinen osa + ohjelmointitehtävät ATK-luokassa.

## Kurssin kirjallisuus

Wolfgang Link: Assembler-ohjelmointi. Pagina. 1997. ( 2. korj. p. 1998. ). Kirjoittajan Microsoft MASM-esimerkit levykkeellä.  
Lisäksi  
   * Gunvald Hedemalm: 486 ohjelmointi. Pagina. 1993
   * Mark Goodwin: Teach Yourself Assembler. Mis Press. 1991
   * opettajan monisteita ja esimerkkejä

## Ohjelmisto

MS-DOS / Windows 9x  
Borland Turbo Assembler (TASM) 16-bit v4.1  
Borland Turbo Link (TLINK) 16-bit v7.1  
Borland Turbo Debugger (TD) 16-bit v5.0  
Borland C++ v5.02

## Lähdekoodi aikajärjestyksessä

Syntaksi: Intel. TASM Ideal Mode.  
Alkuperäisen lähdekoodin merkistö: MS-DOS koodisivu 850 / 437 (cp437, cp850, DOS Latin 1 ...). 
Borland C++:n Windows C/ASM-projekteissa koodisivuna 1252.  
Merkistö Git:issä: UTF-8 (rivinvaihtona LF)  
Komennot:  
1. ```tasm /w /zi /l tiedosto.asm```  
2. ```tlink /v /Tde tiedosto.obj```   
3. ```td tiedosto.exe```

iy01.asm [tarkastele](./iy01.asm)  

iy02.asm [tarkastele](./iy02.asm)  

iy03.asm [tarkastele](./iy03.asm)  

macro.asm (iy04.asm) [tarkastele](./macro.asm)  

malli.asm [tarkastele](./malli.asm)  

teht12.asm [tarkastele](./teht12.asm)  

teht13.asm [tarkastele](./teht13.asm)  

teht14.asm [tarkastele](./teht14.asm)  

teht15.asm [tarkastele](./teht15.asm)  

teht16.asm [tarkastele](./teht16.asm)  

teht21a.asm [tarkastele](./teht21a.asm)  

teht21b.asm [tarkastele](./teht21b.asm)  

teht23a.asm [tarkastele](./teht23a.asm)  

_ali1.asm [tarkastele](./_ali1.asm)  
_ali2.asm [tarkastele](./_ali2.asm)  
teht22.asm [tarkastele](./teht22.asm)  

summaa1.asm [tarkastele](./summaa1.asm)  
teht23.asm [tarkastele](./teht23.asm)  
summaa2.asm [tarkastele](./summaa2.asm)  
summaa3.asm [tarkastele](./summaa3.asm)  

teht30.asm [tarkastele](./teht30.asm)  
tuplaa.asm [tarkastele](./tuplaa.asm)  

koe1.asm (1. välikoe) [tarkastele](./koe1.asm)  
koe2.asm (1. välikoe) [tarkastele](./koe2.asm)  
laske.asm (1. välikoe) [tarkastele](./laske.asm)  

etsi.asm [tarkastele](./etsi.asm)  
teht31.asm [tarkastele](./teht31.asm)  

strcpy.asm [tarkastele](./strcpy.asm)  
teht40.asm [tarkastele](./teht40.asm)  

makrot.txt [tarkastele](./makrot.txt)  

teht32.asm [tarkastele](./teht32.asm)   

teht33.asm [tarkastele](./teht33.asm)  
print.asm [tarkastele](./print.asm)  

printa.asm [tarkastele](./printa.asm)  

teht41.asm [tarkastele](./teht41.asm)  
tulot.asm [tarkastele](./tulot.asm)  

tuljonot.asm [tarkastele](./tuljonot.asm)  
teht42.asm [tarkastele](./teht42.asm)  
luenimet.asm [tarkastele](./luenimet.asm)  
teht43.asm [tarkastele](./teht43.asm)  
teht44.asm [tarkastele](./teht44.asm)  
etsinimi.asm [tarkastele](./etsinimi.asm)  
vrtjono.asm [tarkastele](./vrtjono.asm)  
(tarvitaan strcpy.asm uudestaan)

proj/oma1.cpp [tarkastele](./proj/oma1.cpp)  
proj/ali2.asm [tarkastele](./proj/ali2.asm)  

proj2/h50a.cpp [tarkastele](./proj2/h50a.cpp)  
proj2/esittely.h [tarkastele](./proj2/esittely.h)  
proj2/h50a.asm [tarkastele](./proj2/h50a.asm)  
proj2/h50.cpp [tarkastele](./proj2/h50.cpp)  

tulnimi.asm [tarkastele](./tulnimi.asm)  
teht52.asm [tarkastele](./teht52.asm)  
luekesk.asm [tarkastele](./luekesk.asm)  
asekesk.asm [tarkastele](./asekesk.asm)  

proj3/h53paa.cpp [tarkastele](./proj3/h53paa.cpp)  
proj3/header.h [tarkastele](./proj3/header.h)  
proj3/tulosta.cpp [tarkastele](./proj3/tulosta.cpp)  
proj3/lue.cpp [tarkastele](./proj3/lue.cpp)  
proj3/lajittel.asm [tarkastele](./proj3/lajittel.asm)  

struc.asm [tarkastele](./struc.asm)  
paivita.asm [tarkastele](./paivita.asm)  
hex2dec.asm [tarkastele](./hex2dec.asm)  
dec2hex.asm [tarkastele](./dec2hex.asm)  
palv54.asm [tarkastele](./palv54.asm)  
lueasc.asm [tarkastele](./lueasc.asm)  
teht54.asm [tarkastele](./teht54.asm)  
lueaika.asm [tarkastele](./lueaika.asm)  

ali.asm (pohja?) [tarkastele](./ali.asm)  
testmain.asm (pohja?) [tarkastele](./testmain.asm)  

koepaa1.asm (2. välikoe) [tarkastele](./koepaa1.asm)  
koeali1.asm (2. välikoe)  [tarkastele](./koeali1.asm)  
koekesk3.asm (2. välikoe) [tarkastele](./koekesk3.asm)  
palvelu.asm (2. välikoe) [tarkastele](./palvelu.asm)  
koe/oma.h (2. välikoe) [tarkastele](./koe/oma.h)  
koe/k2.cpp (2. välikoe) [tarkastele](./koe/k2.cpp)  
koe/alik2.asm (2. välikoe) [tarkastele](./koe/alik2.asm)

