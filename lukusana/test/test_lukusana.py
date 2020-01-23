#!/usr/bin/python3
# -*- coding: utf-8 -*-

import ctypes
import unittest

SO_FILE = '../lib-Debug/liblukusana.so'
INPUT_OK = 0
INPUT_FAIL_1 = -1
INPUT_FAIL_2 = -2

class InputTestCase(unittest.TestCase):
    def setUp(self):
        self.lib = ctypes.CDLL(SO_FILE)
        self.argtypes = [ctypes.c_char_p, ctypes.POINTER(ctypes.c_ulong)]
        self.restype = ctypes.c_int

    def test_000(self):
        t = ctypes.c_char_p(b'4464')
        null_ptr = ctypes.POINTER(ctypes.c_ulong)()
        self.assertEqual(INPUT_FAIL_2, self.lib.validate_and_convert_input(t, null_ptr))    
    
    def test_001(self):
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        null_ptr = ctypes.POINTER(ctypes.c_char)()
        self.assertEqual(INPUT_FAIL_2, self.lib.validate_and_convert_input(null_ptr, pd))    
    
    def test_002(self):
        t = ctypes.c_char_p(b'')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)
    
    def test_003(self):
        t = ctypes.c_char_p(b'-')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)    
    
    def test_004(self):
        t = ctypes.c_char_p(b'+')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)   
        
    def test_005(self):
        t = ctypes.c_char_p(b'-')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)       
    
    def test_006(self):
        t = ctypes.c_char_p(b'.')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)       
    
    def test_007(self):
        t = ctypes.c_char_p(b'+7')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)  
        
    def test_008(self):
        t = ctypes.c_char_p(b'-8')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value) 
 
    def test_009(self):
        t = ctypes.c_char_p(b'9.')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value) 
    
    def test_010(self):
        t = ctypes.c_char_p(b' ')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value) 
        
    def test_011(self):
        t = ctypes.c_char_p(b'1 1')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)     
    
    def test_012(self):
        t = ctypes.c_char_p(b' 12')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)
    
    def test_013(self):
        t = ctypes.c_char_p(b'13 ')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)
    
    def test_014(self):
        t = ctypes.c_char_p(b'14a')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)
    
    def test_015(self):
        t = ctypes.c_char_p(b'15e0')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(0, d.value)
       
    def test_016(self):
        t = ctypes.c_char_p(b'10000001')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(10000001, d.value)
        
    def test_017(self):
        t = ctypes.c_char_p(b'010000001')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(10000001, d.value)   
    
    def test_018(self):
        t = ctypes.c_char_p(b'0000000000000000000000000000000000000010000001')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(10000001, d.value)       
    
    def test_019(self):
        t = ctypes.c_char_p(b'10000002')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_FAIL_1, self.lib.validate_and_convert_input(t, pd))    
        self.assertEqual(10000002, d.value)
        
    def test_020(self):
        t = ctypes.c_char_p(b'00')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_OK, self.lib.validate_and_convert_input(t, pd))
        self.assertEqual(0, d.value)
        
    def test_021(self):
        t = ctypes.c_char_p(b'000000000000000000000000000000000000000000000')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_OK, self.lib.validate_and_convert_input(t, pd))
        self.assertEqual(0, d.value)

    def test_022(self):
        t = ctypes.c_char_p(b'000000000000000000000000000000000000000000001')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_OK, self.lib.validate_and_convert_input(t, pd))
        self.assertEqual(1, d.value)

    def test_023(self):
        t = ctypes.c_char_p(b'0')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_OK, self.lib.validate_and_convert_input(t, pd))
        self.assertEqual(0, d.value)

    def test_024(self):
        t = ctypes.c_char_p(b'1')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_OK, self.lib.validate_and_convert_input(t, pd))
        self.assertEqual(1, d.value)
        
    def test_025(self):
        t = ctypes.c_char_p(b'499999')
        d = ctypes.c_ulong(0)
        pd = ctypes.pointer(d)
        self.assertEqual(INPUT_OK, self.lib.validate_and_convert_input(t, pd))
        self.assertEqual(499999, d.value)     


# ----------------------------------------------------------------------
if __name__ == "__main__":
    unittest.main()
        
