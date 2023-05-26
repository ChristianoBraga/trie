#ifndef _TRIE
#define _TRIE

#include <stdbool.h>

bool trie_find(char key[], int* value) ;
void trie_insert(char key[], int value) ;
bool trie_delete(char key[]) ;
bool trie_is_empty(void) ;
void trie_free(void) ;
#endif