#!/usr/bin/python3
# -*- coding: utf-8 -*-

from word_pair import WordPair

# ----------------------------------------------------------------------
def file_read(name):
    print(f'Lukee tiedostoa: {name}\n')
    word_list = []
    with open(name, 'r', encoding = 'UTF-8') as file:
            for row in file:
               w1, w2 = row.strip().split(sep='\t')
               word_list.append(WordPair(w1, w2))

    print('Luki', len(word_list), 'riviä.\n')
    return word_list
# ----------------------------------------------------------------------
def main():
    wl = file_read('../../venaja/adjektiiveja.txt')
    print(wl)
# ----------------------------------------------------------------------
if __name__ == "__main__":
    main()
