#ifndef _TRIE
#define _TRIE

#include <stdbool.h>

#define EMPTY_TRIE NULL

typedef struct _Trie Trie ;

int  tri_find(Trie* t, char key[], bool* result) ;
Trie* tri_mk_trie(void) ;
void tri_insert(Trie* t, char key[], int value) ;
Trie* tri_remove(Trie* t, char key[]) ;
void tri_print(Trie* t, int ident) ;
Trie* tri_delete(Trie* t, char key[]) ;
#endif