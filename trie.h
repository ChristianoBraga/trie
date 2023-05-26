#ifndef _TRIE
#define _TRIE

#include <stdbool.h>

bool trie_find(char key[]) ;
void trie_insert(char key[], int value) ;
bool trie_delete(char key[]) ;
#endif