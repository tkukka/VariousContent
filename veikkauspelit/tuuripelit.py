#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Veikkauksen tuuripelejä kesällä 2022

import math
import random
import itertools
import bisect
# ----------------------------------------------------------------------
# luuppaa (n,k) kombinaatioita ja tulosta yli 10 miljoonan tulokset
def demo():
    for n in range(39, 49):
        for k in range(5, 8):
            c = math.comb(n, k)
            if c > 10000000:
                print(f'N:{n} k:{k} Yhdistelmiä: {c}')
# ----------------------------------------------------------------------
def rivi(n, k, painot=None):

    if painot is None:
        r = random.sample(range(1, (n + 1)), k)
        r.sort();
        return r

    # kasataan arpauurnaan painojen verran kutakin numeroa
    # uurna = []
    # for i in range(len(painot)):
    #     for j in range(painot[i]):
    #         uurna.append(i + 1)

    # # arvotaan rivi
    # r = []
    # for i in range(k):
    #     nro = random.choice(uurna)
    #     r.append(nro)
    #     # poistetaan arvotun numeron kopiot uurnasta
    #     uurna = list(filter(lambda x: x != nro, uurna))

    # toinen tapa tehdä. nopeampi.
    r = []
    # kaikki_nrot = range(1, (n + 1))

    for x in range(k):
        kasa_summa = list(itertools.accumulate(painot))
        i = bisect.bisect(kasa_summa, random.randrange(kasa_summa[-1]))
        nro = i + 1
        # nro = random.choices(kaikki_nrot, cum_weights=kasa_summa)[0]
        r.append(nro)
        painot[i] = 0
        # painot[nro - 1] = 0

    r.sort()
    return r
# ----------------------------------------------------------------------
def lottorivi(painot=None):
    N = 40
    K = 7

    if painot is None:
        return rivi(N, K)

    if (len(painot) != N):
        print('Lotto. Virhe. Painoja', len(painot), 'kpl. Tarvitaan', N, 'kpl.')
        return []

    return rivi(N, K, painot)
# ----------------------------------------------------------------------
def vikinglottorivi(painot=None):
    # päänumerot
    N = 48
    K = 6

    if painot is None:
        r = rivi(N, K)
    elif (len(painot) != N):
        print('VikingLotto. Virhe. Painoja', len(painot), 'kpl. Tarvitaan', N, 'kpl.')
        return []
    else:
        r = rivi(N, K, painot)

    # apunumero
    apu_N = 5
    apu_K = 1
    vn = rivi(apu_N, apu_K)
    return {'päänumerot': r, 'vikingnumero': vn}  # dictionary-tyyppinen
# ----------------------------------------------------------------------
def eurojackpotrivi(painot=None):
    # päänumerot
    N = 50
    K = 5

    if painot is None:
        r = rivi(N, K)
    elif (len(painot) != N):
        print('Eurojackpot. Virhe. Painoja', len(painot), 'kpl. Tarvitaan', N, 'kpl.')
        return []
    else:
        r = rivi(N, K, painot)

    # apunumerot
    apu_N = 12
    apu_K = 2
    tn = rivi(apu_N, apu_K)
    return {'päänumerot': r, 'tähtinumerot': tn}  # dictionary-tyyppinen
# ----------------------------------------------------------------------
def kenorivi(taso, painot=None):
    if taso < 2 or taso > 10:
        print('Virheellinen Kenon taso')
        return []    # tyhjä lista

    N = 70

    if painot is None:
        return rivi(N, taso)

    if (len(painot) != N):
        print('Keno. Virhe. Painoja', len(painot), 'kpl. Tarvitaan', N, 'kpl.')
        return []

    return rivi(N, taso, painot)
# ----------------------------------------------------------------------
# Yleensä vakioveikkauksen ottelua ei arvota
def vakiokohde(painot = None):
    merkit = ['1', 'X', '2']
    if painot is None:
        return random.choice(merkit)   # ilman painoja kaikilla sama painotus
    # painotettu tulos on listan 1. alkio
    return random.choices(merkit, weights=painot)[0]
# ----------------------------------------------------------------------
# pääohjelma
def main():
   #demo()  # kommentoitu ei-aktiiviseksi
   print('Lottorivi:', lottorivi())
   print('Vikinglottorivi:', vikinglottorivi())
   print('Eurojackpot-rivi:', eurojackpotrivi())
   print('Kenorivi:', kenorivi(2))
   print('Kenorivi:', kenorivi(8))
   print('Kenorivi:', kenorivi(16))  # ei sallittu
   print('Vakion kohteeseen arvottu:', vakiokohde())
   print('Vakion kohteeseen arvottu:', vakiokohde((1, 3, 6))) # painoilla

   lottopainot = [0,0,0,0,0,0,1,0,0,1,1,1,10,7,9,1,1,0,1,1,4,7,9,2,4,9,1,1,1,1, 
       12,3,5,6,1,1,1,4,6,6]
   print('Lottorivi:', lottorivi(lottopainot))
   kenopainot = list(itertools.repeat(0, 10)) + list(itertools.repeat(1, 60))
   print('Kenorivi:', kenorivi(8, kenopainot))
# ----------------------------------------------------------------------
if __name__ == "__main__":
    main()
