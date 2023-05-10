# Trie in C

This is an implementation of the [Trie](https://en.wikipedia.org/wiki/Trie) datatype in C.

```shell
❯ ./main
===========================
Inserts two key-value pairs
===========================
value: -1
is terminal: false
children:
 index: a
  value: -1
  is terminal: false
  children:
   index: b
    value: 2
    is terminal: true
    children:
     index: c
      value: 1
      is terminal: true
      children:
===========================
Queries for key=ab
===========================
found value 2 for key ab
===========================
Deletes key=ab
===========================
value: -1
is terminal: false
children:
 index: a
  value: -1
  is terminal: false
  children:
   index: b
    value: -1
    is terminal: false
    children:
     index: c
      value: 1
      is terminal: true
      children:
===========================
Deletes key=abc
===========================
Empty trie
```