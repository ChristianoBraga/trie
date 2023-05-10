#include "trie.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

struct _Trie {
    int value ;
    bool is_terminal ; 
    struct _Trie* children [UCHAR_MAX] ; 
} ;

Trie* tri_mk_trie(void) {
    Trie* t = (Trie*) malloc(sizeof(Trie)) ;
    assert(t != NULL) ;
    for (int i ; i = 0 ; i < UCHAR_MAX) {
        t->children[i] = EMPTY_TRIE ;
    } 
    t->is_terminal = false ;
    t->value = -1 ;
    return t ;
}

int tri_find(Trie* t, char key[], bool* result) {
    assert(t != NULL) ;
    assert(key != NULL) ;
    for (int i = 0 ; i < strlen(key) ; i++) {
        if (t->children[key[i]] != EMPTY_TRIE) 
            t = t->children[key[i]] ;
        else
            break ;
    }
    *result = t->is_terminal ? true : false ;
    return t->value ;
}

void tri_insert(Trie* t, char key[], int value) {
    assert(key != NULL) ;
    assert(t != NULL)   ;
    for (int i = 0; i < strlen(key); i++) {
        if (t->children[key[i]] == NULL) {
            t->children[key[i]] = tri_mk_trie() ;
            assert(t->children[key[i]] != NULL) ;}
        t = t->children[key[i]] ;
    }
    t->value = value ;
    t->is_terminal = true ;
}

void _nprint(char c, unsigned int n) {
    for (int i = 0; i < n; i ++)
        printf("%c", c) ;
}

void tri_print(Trie* t, int ident) {
    if (t == NULL) {
        printf("Empty trie\n") ;
        return ;
    }
    _nprint(' ', ident) ;
    printf("value: %d\n", t->value) ;
    _nprint(' ', ident) ;
    printf("is terminal: %s\n", t->is_terminal? "true" : "false") ;
    _nprint(' ', ident) ;
    printf("children:\n") ;
    for (unsigned char i = 0; i < UCHAR_MAX ; i++) {
        if (t->children[i] != NULL) {
            _nprint(' ', ident + 1) ;
            printf("index: %c\n", i) ;
            tri_print(t->children[i], ident + 2) ;
        }
    }
}

char* _tail(char* str) {
    if ((str == NULL) || (strlen(str) == 1)) {
        return NULL ;
    }
    else {
        assert(strlen(str) > 1) ;
        return &str[1] ;
    }
}

Trie* tri_delete(Trie* t, char key[]) {
    assert(t) ;
    if (key == NULL) {
        if (t->is_terminal == true) {
            t->is_terminal = false ;
            t->value = -1 ;
        }
    }
    else {
        t->children[(int)key[0]] = tri_delete(t->children[(int)key[0]], _tail(key)) ;
    }
    for (int i = 0; i < UCHAR_MAX; i++) {
        if (t->children[i] != EMPTY_TRIE)
            return t ;
    }
    free(t) ;
    t = EMPTY_TRIE ;
    return EMPTY_TRIE ;
}
