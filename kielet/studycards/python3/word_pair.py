#!/usr/bin/python3
# -*- coding: utf-8 -*-
# Python 3.6+

from typing import NamedTuple

# ----------------------------------------------------------------------
class WordPair(NamedTuple):
    word1: str
    word2: str

# ----------------------------------------------------------------------
def main():
    test = WordPair('ре́дкий', 'harvinainen, harva')
    print(test)

# ----------------------------------------------------------------------
if __name__ == "__main__":
    main()

