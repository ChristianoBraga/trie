from ctypes import *
from json import loads

_triem = cdll.LoadLibrary("./trie.so")

_triem.trie_insert.argtypes = [c_char_p, c_int]
_triem.trie_insert.restype  = None

_triem.trie_find.argtypes = [c_char_p, POINTER(c_int)]
_triem.trie_find.restype  = c_bool

_triem.trie_delete.argtypes = [c_char_p]
_triem.trie_delete.restype  = c_bool

_triem.trie_is_empty.argtypes = None
_triem.trie_is_empty.restype  = c_bool

_triem.trie_free.argtypes = None
_triem.trie_free.restype  = None

class Trie:
    def insert(self, key, value):
        _triem.trie_insert(bytes(key, 'ascii'), c_int(value))

    def find(self, key):
        val = c_int(-1)
        found =_triem.trie_find(bytes(key, 'ascii'), byref(val))
        return (found, val.value)

    def delete(self, key):
        return _triem.trie_delete(bytes(key, 'ascii'))

    # def isEmpty(self):
    #     res = c_bool(False)
    #     res = _triem.trie_is_empty()
    #     return res.value

    # def __del__(self):
    #     _triem.trie_free()