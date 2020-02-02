#!/usr/bin/python3
# -*- coding: utf-8 -*-
FILE = './eng-uk_web_2002_1M-words.txt'

#------------------------------------------------------------------
def read_file(name):
    with open(name, 'r', encoding = 'utf-8') as f:
        x = f.readlines()
    print('Lines: ', len(x))
#------------------------------------------------------------------
def read_file2():
    with open(FILE, 'r', encoding = 'utf-8') as f:
        x = f.readlines()
#------------------------------------------------------------------
def main():
    print(f'Python file reading "{FILE}"...')
    read_file(FILE)
    print('Python exit')
# -----------------------------------------------------------------
if __name__ == '__main__':
    main()

