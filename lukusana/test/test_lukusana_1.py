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
        self.lib.validate_and_convert_input.argtypes = [ctypes.c_char_p, ctypes.POINTER(ctypes.c_ulong)]
        self.lib.validate_and_convert_input.restype = ctypes.c_int

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

# ---------------------------------------------------------------------
class Node(ctypes.Structure):
    pass

Node._fields_ = [('next', ctypes.POINTER(Node)),
                 ('data', ctypes.c_char_p)]


class Stack(ctypes.Structure):
    _fields_ = [('count', ctypes.c_int),
                ('top', ctypes.POINTER(Node))]


class StackTestCase(unittest.TestCase):
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

        self.lib.get_stack_size.argtypes = None
        self.lib.get_stack_size.restype = ctypes.c_int

    def tearDown(self):
        self.lib.clear_stack()
        self.lib.close_stack()


    def test_000(self):
        self.lib.print_stack()

    def test_001(self):
        t = ctypes.c_char_p(b' - 1. test\n')
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.print_stack()

    def test_002(self):
        t = ctypes.c_char_p(b'2. test')
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.print_stack()
        r = self.lib.pop_from_stack()
        self.assertEqual(r, b'2. test')

    def test_003(self):
        t = ctypes.c_char_p(b'3. test')
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.print_stack()
        self.lib.clear_stack()
        r = self.lib.pop_from_stack()
        self.assertIs(r, None)

    def test_004(self):
        t = ctypes.c_char_p(b'test 4')
        self.lib.push_to_stack(self.stack_handle, t)
        t2 = ctypes.c_char_p(b'test -')
        self.lib.push_to_stack(self.stack_handle, t2)
        r = self.lib.pop_from_stack()
        r = self.lib.pop_from_stack()
        self.assertEqual(r, b'test 4')

    def test_005(self):
        self.assertEqual(0, self.lib.get_stack_size())
        t = ctypes.c_char_p(b'test 5')
        self.lib.push_to_stack(self.stack_handle, t)
        self.assertEqual(1, self.lib.get_stack_size())

    def test_006(self):
        t = ctypes.c_char_p(b'test 6')
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.assertEqual(2, self.lib.get_stack_size())

    def test_007(self):
        t = ctypes.c_char_p(b'test 7')
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.lib.push_to_stack(self.stack_handle, t)
        self.assertEqual(8, self.lib.get_stack_size())
        r = self.lib.pop_from_stack()
        self.assertEqual(7, self.lib.get_stack_size())
        r = self.lib.pop_from_stack()
        r = self.lib.pop_from_stack()
        r = self.lib.pop_from_stack()
        self.assertEqual(4, self.lib.get_stack_size())

# ----------------------------------------------------------------------
if __name__ == "__main__":
    unittest.main()
        
