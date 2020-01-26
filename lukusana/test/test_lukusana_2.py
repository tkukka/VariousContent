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
        self.lib.push_to_stack.restype = ctypes.c_int

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

    def test_043(self):
        n = ctypes.c_ulong(119)
        ans = 'satayhdeksäntoista'.encode('utf-8')
        self.common_func(n, ans)

    def test_044(self):
        n = ctypes.c_ulong(120)
        ans = 'satakaksikymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_045(self):
        n = ctypes.c_ulong(121)
        ans = 'satakaksikymmentäyksi'.encode('utf-8')
        self.common_func(n, ans)

    def test_046(self):
        n = ctypes.c_ulong(159)
        ans = 'sataviisikymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_047(self):
        n = ctypes.c_ulong(199)
        ans = 'satayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_048(self):
        n = ctypes.c_ulong(200)
        ans = b'kaksisataa'
        self.common_func(n, ans)

    def test_049(self):
        n = ctypes.c_ulong(218)
        ans = b'kaksisataakahdeksantoista'
        self.common_func(n, ans)

    def test_050(self):
        n = ctypes.c_ulong(318)
        ans = b'kolmesataakahdeksantoista'
        self.common_func(n, ans)

    def test_051(self):
        n = ctypes.c_ulong(569)
        ans = 'viisisataakuusikymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_052(self):
        n = ctypes.c_ulong(999)
        ans = 'yhdeksänsataayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_053(self):
        n = ctypes.c_ulong(1000)
        ans = b'tuhat'
        self.common_func(n, ans)
        
    def test_054(self):
        n = ctypes.c_ulong(1001)
        ans = b'tuhat yksi'
        self.common_func(n, ans)

    def test_055(self):
        n = ctypes.c_ulong(1019)
        ans = 'tuhat yhdeksäntoista'.encode('utf-8')
        self.common_func(n, ans)

    def test_056(self):
        n = ctypes.c_ulong(1020)
        ans = 'tuhat kaksikymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_057(self):
        n = ctypes.c_ulong(1021)
        ans = 'tuhat kaksikymmentäyksi'.encode('utf-8')
        self.common_func(n, ans)

    def test_058(self):
        n = ctypes.c_ulong(1099)
        ans = 'tuhat yhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_059(self):
        n = ctypes.c_ulong(1100)
        ans = b'tuhat sata'
        self.common_func(n, ans)

    def test_060(self):
        n = ctypes.c_ulong(1102)
        ans = b'tuhat satakaksi'
        self.common_func(n, ans)

    def test_061(self):
        n = ctypes.c_ulong(1199)
        ans = 'tuhat satayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_062(self):
        n = ctypes.c_ulong(1200)
        ans = b'tuhat kaksisataa'
        self.common_func(n, ans)

    def test_063(self):
        n = ctypes.c_ulong(1205)
        ans = b'tuhat kaksisataaviisi'
        self.common_func(n, ans)

    def test_064(self):
        n = ctypes.c_ulong(1250)
        ans = 'tuhat kaksisataaviisikymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_065(self):
        n = ctypes.c_ulong(1299)
        ans = 'tuhat kaksisataayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_066(self):
        n = ctypes.c_ulong(1300)
        ans = b'tuhat kolmesataa'
        self.common_func(n, ans)

    def test_067(self):
        n = ctypes.c_ulong(1999)
        ans = 'tuhat yhdeksänsataayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_068(self):
        n = ctypes.c_ulong(2000)
        ans = b'kaksituhatta'
        self.common_func(n, ans)

    def test_069(self):
        n = ctypes.c_ulong(2020)
        ans = 'kaksituhatta kaksikymmentä'.encode('utf-8')
        self.common_func(n, ans)

    def test_070(self):
        n = ctypes.c_ulong(2501)
        ans = b'kaksituhatta viisisataayksi'
        self.common_func(n, ans)

    def test_071(self):
        n = ctypes.c_ulong(3000)
        ans = b'kolmetuhatta'
        self.common_func(n, ans)

    def test_072(self):
        n = ctypes.c_ulong(3018)
        ans = b'kolmetuhatta kahdeksantoista'
        self.common_func(n, ans)

    def test_073(self):
        n = ctypes.c_ulong(9999)
        ans = 'yhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_074(self):
        n = ctypes.c_ulong(10000)
        ans = b'kymmenentuhatta'
        self.common_func(n, ans)

    def test_075(self):
        n = ctypes.c_ulong(15000)
        ans = b'viisitoistatuhatta'
        self.common_func(n, ans)

    def test_076(self):
        n = ctypes.c_ulong(21999)
        ans = 'kaksikymmentäyksituhatta yhdeksänsataayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_077(self):
        n = ctypes.c_ulong(30000)
        ans = 'kolmekymmentätuhatta'.encode('utf-8')
        self.common_func(n, ans)

    def test_078(self):
        n = ctypes.c_ulong(52879)
        ans = 'viisikymmentäkaksituhatta kahdeksansataaseitsemänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_079(self):
        n = ctypes.c_ulong(72009)
        ans = 'seitsemänkymmentäkaksituhatta yhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_080(self):
        n = ctypes.c_ulong(99999)
        ans = 'yhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_081(self):
        n = ctypes.c_ulong(100000)
        ans = b'satatuhatta'
        self.common_func(n, ans)

    def test_082(self):
        n = ctypes.c_ulong(100001)
        ans = b'satatuhatta yksi'
        self.common_func(n, ans)

    def test_083(self):
        n = ctypes.c_ulong(100100)
        ans = b'satatuhatta sata'
        self.common_func(n, ans)

    def test_084(self):
        n = ctypes.c_ulong(550310)
        ans = 'viisisataaviisikymmentätuhatta kolmesataakymmenen'.encode('utf-8')
        self.common_func(n, ans)

    def test_085(self):
        n = ctypes.c_ulong(990800)
        ans = 'yhdeksänsataayhdeksänkymmentätuhatta kahdeksansataa'.encode('utf-8')
        self.common_func(n, ans)

    def test_086(self):
        n = ctypes.c_ulong(999999)
        ans = 'yhdeksänsataayhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_087(self):
        n = ctypes.c_ulong(1000000)
        ans = b'miljoona'
        self.common_func(n, ans)

    def test_088(self):
        n = ctypes.c_ulong(1000001)
        ans = b'miljoona yksi'
        self.common_func(n, ans)

    def test_089(self):
        n = ctypes.c_ulong(1001000)
        ans = b'miljoona tuhat'
        self.common_func(n, ans)

    def test_090(self):
        n = ctypes.c_ulong(1100000)
        ans = b'miljoona satatuhatta'
        self.common_func(n, ans)

    def test_091(self):
        n = ctypes.c_ulong(1500000)
        ans = b'miljoona viisisataatuhatta'
        self.common_func(n, ans)

    def test_092(self):
        n = ctypes.c_ulong(1500001)
        ans = b'miljoona viisisataatuhatta yksi'
        self.common_func(n, ans)

    def test_093(self):
        n = ctypes.c_ulong(5000674)
        ans = 'viisimiljoonaa kuusisataaseitsemänkymmentäneljä'.encode('utf-8')
        self.common_func(n, ans)

    def test_094(self):
        n = ctypes.c_ulong(5426674)
        ans = 'viisimiljoonaa neljäsataakaksikymmentäkuusituhatta kuusisataaseitsemänkymmentäneljä'.encode('utf-8')
        self.common_func(n, ans)

    def test_095(self):
        n = ctypes.c_ulong(45000000)
        ans = 'neljäkymmentäviisimiljoonaa'.encode('utf-8')
        self.common_func(n, ans)

    def test_096(self):
        n = ctypes.c_ulong(99000099)
        ans = 'yhdeksänkymmentäyhdeksänmiljoonaa yhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_097(self):
        n = ctypes.c_ulong(99999999)
        ans = 'yhdeksänkymmentäyhdeksänmiljoonaa yhdeksänsataayhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän'.encode('utf-8')
        self.common_func(n, ans)

    def test_098(self):
        n = ctypes.c_ulong(100000000)
        ans = b'satamiljoonaa'
        self.common_func(n, ans)

    def test_099(self):
        n = ctypes.c_ulong(945000000)
        ans = 'yhdeksänsataaneljäkymmentäviisimiljoonaa'.encode('utf-8')
        self.common_func(n, ans)

    def test_100(self):
        n = ctypes.c_ulong(1000000000)
        ans = b'miljardi'
        self.common_func(n, ans)

    def test_101(self):
        n = ctypes.c_ulong(1000000001)
        ans = b'miljardi yksi'
        self.common_func(n, ans)

    def test_102(self):
        n = ctypes.c_ulong(1000001000)
        ans = b'miljardi tuhat'
        self.common_func(n, ans)

    def test_103(self):
        n = ctypes.c_ulong(1001000000)
        ans = b'miljardi miljoona'
        self.common_func(n, ans)

    def test_104(self):
        n = ctypes.c_ulong(1001001000)
        ans = b'miljardi miljoona tuhat'
        self.common_func(n, ans)

    def test_105(self):
        n = ctypes.c_ulong(2000000000)
        ans = b'kaksimiljardia'
        self.common_func(n, ans)

    def test_106(self):
        n = ctypes.c_ulong(2000000001)
        ans = b'kaksimiljardia yksi'
        self.common_func(n, ans)

    def test_107(self):
        n = ctypes.c_ulong(2000001000)
        ans = b'kaksimiljardia tuhat'
        self.common_func(n, ans)

    def test_108(self):
        n = ctypes.c_ulong(2000100000)
        ans = b'kaksimiljardia satatuhatta'
        self.common_func(n, ans)

    def test_109(self):
        n = ctypes.c_ulong(2001000000)
        ans = b'kaksimiljardia miljoona'
        self.common_func(n, ans)

# ----------------------------------------------------------------------
if __name__ == "__main__":
    unittest.main()
        
