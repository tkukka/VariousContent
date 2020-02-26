#!/usr/bin/python3
# -*- coding: utf-8 -*-
import tkinter as tk
from tkinter import filedialog
from tkinter import font
from tkinter import ttk
from random import shuffle
from file_read import file_read


# ----------------------------------------------------------------------
class Application(ttk.Frame):

    def __init__(self, master=None,):
        super(Application, self).__init__(master)
        self.master.anchor(tk.CENTER)
        self.master.resizable(True, True)
        self.master.columnconfigure(0, weight=1)
        self.master.rowconfigure(0, weight=1)
        self.master.option_add('*tearOff', tk.FALSE)
        self.create_widgets()

        self.grid( sticky=((tk.N, tk.W, tk.S, tk.E) ))
        self.columnconfigure(0, weight=1)
        self.rowconfigure(0, weight=1)
        self.anchor(tk.CENTER)

#        self.master.protocol("WM_DELETE_WINDOW", self._delete_window)
        self.master.bind('<Destroy>', self._destroy)
        self.wordlist = []
        self.current_item = 0
        self.display_next = True
# ----------------------------------------------------------------------
    def create_widgets(self):
        style = ttk.Style()
        style.configure('my.TButton', font='TkFixedFont 16')

        style2 = ttk.Style()
        style2.configure('my.TLabel', font=('Arial', 16, tk.font.NORMAL),  
                         background='dark gray')

        frame1 = ttk.Frame(self)
        frame1['padding'] = (4, 4)
        frame1['borderwidth'] = 2
        frame1['relief'] = 'groove'
        frame1.columnconfigure(0, weight=1)
        frame1.columnconfigure(1, weight=1)
        frame1.rowconfigure(0, weight=2, pad=8)
        frame1.rowconfigure(1, weight=2, pad=8)


        l1 = ttk.Label(frame1, text='(Tyhjä)', anchor='center', width=-55)
        l1.grid(row=0, sticky=(tk.N, tk.W, tk.S, tk.E), pady=4, columnspan=2)
        l1['style'] = 'my.TLabel'
        self.label = l1

        button = ttk.Button(frame1, text='Näytä vastaus', command=self.answer_next)
        button2 = ttk.Button(frame1, text='Poista', command=self.remove)
        button['style'] = 'my.TButton'
        button2['style'] = 'my.TButton'
        self.button = button

        frame1.grid(sticky=(tk.N, tk.W, tk.S, tk.E))
        button.grid(row=1, column=0, padx=4, pady=4)
        button2.grid(row=1, column=1, padx=4, pady=4)
        self.create_menus()
# ----------------------------------------------------------------------
    def create_menus(self):
        menubar = tk.Menu(self.master)

        filemenu = tk.Menu(menubar, tearoff=0)
        filemenu.add_command(label='Lue sanalista...', command=self.read)
        filemenu.add_command(label='Lopeta', command=self.master.destroy)
        menubar.add_cascade(label='Tiedosto', menu=filemenu)

        settings_menu = tk.Menu(menubar, tearoff=0)
        self.check = tk.IntVar(self, 0)
        settings_menu.add_checkbutton(label='Käänteinen suunta',
                                      variable=self.check, onvalue=1,
                                      offvalue=0)

        menubar.add_cascade(label='Asetukset', menu=settings_menu)

        self.master.config(menu=menubar)

# ----------------------------------------------------------------------
    def read(self):

        filename = filedialog.askopenfilename(title="Valitse sanalista",
                                       filetypes=(('Tekstitiedostot','.txt'),
                                            ('Kaikki tiedostot', '*')))

        if len(filename) != 0:
#            print(filename)
            self.wordlist = file_read(filename)
            shuffle(self.wordlist)
            self.current_item = 0
            self.display_next = True
            self.button['text'] = 'Näytä vastaus'
            item = self.wordlist[self.current_item]
            if self.check.get():
                self.label['text'] = item.word2
            else:
                self.label['text'] = item.word1
# ----------------------------------------------------------------------
    def display(self):
        if len(self.wordlist) != 0:
            item = self.wordlist[self.current_item]
            if self.display_next:
                self.button['text'] = 'Seuraava'
                if self.check.get():
                    self.label['text'] = item.word2 + ' = ' + item.word1
                else:
                    self.label['text'] = item.word1 + ' = ' + item.word2
                self.current_item = (self.current_item + 1) % len(self.wordlist)
                #print(item.word1 + ' = ' + item.word2)
            else:
                self.button['text'] = 'Näytä vastaus'
                #print(item.word1)
                if self.check.get():
                    self.label['text'] = item.word2
                else:
                    self.label['text'] = item.word1
            self.display_next = not self.display_next

# ----------------------------------------------------------------------
    def answer_next(self):
#        for name in sorted(tk.font.families()):
#            print(name)
        self.display()

# ----------------------------------------------------------------------
    def remove(self):
        if len(self.wordlist) != 0:
            if self.button['text'] == 'Seuraava':
                self.current_item = (self.current_item - 1) % len(self.wordlist)
            del self.wordlist[self.current_item]

            if len(self.wordlist) == 0:
                self.label['text'] = '(Loppu)'
            else:
                if self.current_item >= len(self.wordlist):
                    self.current_item = 0
                self.display_next = False
                self.display()

# ----------------------------------------------------------------------
    def _destroy(self, event):
        pass
# ----------------------------------------------------------------------
def main():

    app = Application()
    app.master.title('Sanasto')
    app.mainloop()
    print()

# ----------------------------------------------------------------------
if __name__ == "__main__":
    main()
