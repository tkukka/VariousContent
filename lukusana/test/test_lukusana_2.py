#!/usr/bin/python3
# -*- coding: utf-8 -*-

import ctypes
import unittest

SO_FILE = '../lib-Debug/liblukusana.so'

# ----------------------------------------------------------------------  
# compose byte string and clear stack to empty state
def compose(pop_func):
    ret = b''
    item = pop_func()
    while not (item is None):
        ret += item
        item = pop_func()
    return ret
# ----------------------------------------------------------------------
class Node(ctypes.Structure):
    pass

Node._fields_ = [('next', ctypes.POINTER(Node)),
                 ('data', ctypes.c_char_p)]


class Stack(ctypes.Structure):
    _fields_ = [('count', ctypes.c_int),
                ('top', ctypes.POINTER(Node))]


class PresentationTestCase(unittest.TestCase):
    def setUp(self):
        self.lib = ctypes.CDLL(SO_FILE)
        self.lib.init_stack.argtypes = None
        self.lib.init_stack.restype = ctypes.POINTER(Stack)
        self.stack_handle = self.lib.init_stack()

        self.lib.push_to_stack.argtypes = [ctypes.POINTER(Stack), ctypes.c_char_p]
        self.lib.push_to_stack.restype = None

        self.lib.pop_from_stack.argtypes = None
        self.lib.pop_from_stack.restype = ctypes.c_char_p

        self.lib.print_stack.argtypes = None
        self.lib.print_stack.restype = None

        self.lib.clear_stack.argtypes = None
        self.lib.clear_stack.restype = None

        self.lib.close_stack.argtypes = None
        self.lib.close_stack.restype = None
        
        self.lib.make_string_presentation.argtypes = [ctypes.c_ulong, ctypes.POINTER(Stack)]
        self.lib.make_string_presentation.restype = None

    def tearDown(self):
        self.lib.clear_stack()
        self.lib.close_stack()
        
    def common_func(self, n, ans):
        self.lib.make_string_presentation(n, self.stack_handle)
        r = compose(self.lib.pop_from_stack)
        self.assertEqual(ans, r)

    def test_000(self):
        n = ctypes.c_ulong(0)
        ans = b'nolla'
        self.common_func(n, ans)

    def test_001(self):
        n = ctypes.c_ulong(1)
        ans = b'yksi'
        self.common_func(n, ans)

    def test_002(self):
        n = ctypes.c_ulong(2)
        ans = b'kaksi'
        self.common_func(n, ans)

    def test_003(self):
        n = ctypes.c_ulong(3)
        ans = b'kolme'
        self.common_func(n, ans)

    def test_004(self):
        n = ctypes.c_ulong(4)
        ans = 'neljä'.encode('utf-8')
        self.common_func(n, ans)

    def test_005(self):
        n = ctypes.c_ulong(5)
        ans = b'viisi'
        self.common_func(n, ans)

    def test_006(self):
        n = ctypes.c_ulong(6)
        ans = b'kuusi'
        self.common_func(n, ans)

    def test_007(self):
        n = ctypes.c_ulong(7)
        ans = 'seitsemän'.encode('utf-8')
        self.common_func(n, ans)

    def test_008(self):
        n = ctypes.c_ulong(8)
        ans = b'kahdeksan'
        self.common_func(n, ans)

    def test_009(self):
        n = ctypes.c_ulong(9)
        ans = 'yhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_010(self):
        n = ctypes.c_ulong(10)
        ans = b'kymmenen'
        self.common_func(n, ans)
    
    def test_011(self):
        n = ctypes.c_ulong(11)
        ans = b'yksitoista'
        self.common_func(n, ans)

    def test_012(self):
        n = ctypes.c_ulong(12)
        ans = b'kaksitoista'
        self.common_func(n, ans)

    def test_013(self):
        n = ctypes.c_ulong(13)
        ans = b'kolmetoista'
        self.common_func(n, ans)

    def test_014(self):
        n = ctypes.c_ulong(14)
        ans = 'neljätoista'.encode('utf-8')
        self.common_func(n, ans)

    def test_015(self):
        n = ctypes.c_ulong(15)
        ans = b'viisitoista'
        self.common_func(n, ans)

    def test_016(self):
        n = ctypes.c_ulong(16)
        ans = b'kuusitoista'
        self.common_func(n, ans)

    def test_017(self):
        n = ctypes.c_ulong(17)
        ans = 'seitsemäntoista'.encode('utf-8')
        self.common_func(n, ans)

    def test_018(self):
        n = ctypes.c_ulong(18)
        ans = b'kahdeksantoista'
        self.common_func(n, ans)

    def test_019(self):
        n = ctypes.c_ulong(19)
        ans = 'yhdeksäntoista'.encode('utf-8')
        self.common_func(n, ans)

    def test_020(self):
        n = ctypes.c_ulong(20)
        ans = 'kaksikymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_021(self):
        n = ctypes.c_ulong(21)
        ans = 'kaksikymmentäyksi'.encode('utf-8')
        self.common_func(n, ans)

    def test_022(self):
        n = ctypes.c_ulong(22)
        ans = 'kaksikymmentäkaksi'.encode('utf-8')
        self.common_func(n, ans)

    def test_023(self):
        n = ctypes.c_ulong(23)
        ans = 'kaksikymmentäkolme'.encode('utf-8')
        self.common_func(n, ans)

    def test_024(self):
        n = ctypes.c_ulong(24)
        ans = 'kaksikymmentäneljä'.encode('utf-8')
        self.common_func(n, ans)

    def test_025(self):
        n = ctypes.c_ulong(25)
        ans = 'kaksikymmentäviisi'.encode('utf-8')
        self.common_func(n, ans)

    def test_026(self):
        n = ctypes.c_ulong(29)
        ans = 'kaksikymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_027(self):
        n = ctypes.c_ulong(30)
        ans = 'kolmekymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_028(self):
        n = ctypes.c_ulong(31)
        ans = 'kolmekymmentäyksi'.encode('utf-8')
        self.common_func(n, ans)

    def test_029(self):
        n = ctypes.c_ulong(32)
        ans = 'kolmekymmentäkaksi'.encode('utf-8')
        self.common_func(n, ans)

    def test_030(self):
        n = ctypes.c_ulong(39)
        ans = 'kolmekymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_031(self):
        n = ctypes.c_ulong(40)
        ans = 'neljäkymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_032(self):
        n = ctypes.c_ulong(41)
        ans = 'neljäkymmentäyksi'.encode('utf-8')
        self.common_func(n, ans)

    def test_033(self):
        n = ctypes.c_ulong(49)
        ans = 'neljäkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_034(self):
        n = ctypes.c_ulong(50)
        ans = 'viisikymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_035(self):
        n = ctypes.c_ulong(55)
        ans = 'viisikymmentäviisi'.encode('utf-8')
        self.common_func(n, ans)

    def test_036(self):
        n = ctypes.c_ulong(60)
        ans = 'kuusikymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_037(self):
        n = ctypes.c_ulong(70)
        ans = 'seitsemänkymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_038(self):
        n = ctypes.c_ulong(80)
        ans = 'kahdeksankymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_039(self):
        n = ctypes.c_ulong(90)
        ans = 'yhdeksänkymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_040(self):
        n = ctypes.c_ulong(99)
        ans = 'yhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_041(self):
        n = ctypes.c_ulong(100)
        ans = b'sata'
        self.common_func(n, ans)

    def test_042(self):
        n = ctypes.c_ulong(101)
        ans = b'satayksi'
        self.common_func(n, ans)

# ----------------------------------------------------------------------
if __name__ == "__main__":
    unittest.main()
        
