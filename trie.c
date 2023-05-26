#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#ifdef _THEFT
#include <theft.h>
#endif

typedef struct _Trie {
    bool is_terminal ;
    int value ;
    struct _Trie* children[UCHAR_MAX] ;
} Trie ;

Trie* _the_trie = NULL ;

Trie* _trie_mk_trie(void) {
    Trie* t = (Trie*) malloc(sizeof(Trie)) ;
    assert(t) ;
    t->is_terminal = false ;
    t->value = -1 ;
    for (int i = 0; i < 4; i++) {
        t->children[i] = NULL ;
    }
    return t ;
}

void _trie_insert(Trie* t, const char* key, int value) {
    assert(t) ;
    Trie* aux = t ;
    for (int i = 0; i < strlen(key); i++) {
        if (aux->children[key[i]] == NULL) 
            aux->children[key[i]] = _trie_mk_trie() ;
        aux = aux->children[key[i]] ;
    }
    aux->is_terminal = true ;
    aux->value = value ;
}

bool _trie_find(Trie* t, const char* key, int* value) {
    Trie* aux = t;
    for (int i = 0; i < strlen(key); i++) {
        if (aux->children[key[i]] == NULL) {
            return false;
        }
        aux = aux->children[key[i]];
    }
    *value = aux->value ;
    return (aux != NULL && aux->is_terminal);
}

void _trie_free(Trie* t) {
    if (t == NULL) {
        return;
    }
    for (int i = 0; i < UCHAR_MAX; i++) {
        if (t->children[i] != NULL) {
            _trie_free(t->children[i]);
        }
    }
    free(t);
}

bool _trie_is_empty(Trie* t) {
    for (int i = 0; i < UCHAR_MAX; i++) {
        if (t->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

bool _trie_delete_aux(Trie* t, const char* key, int depth, bool* result) {
    if (t == NULL) {
        return false;
    }
    if (key[depth] == '\0') {
        if (t->is_terminal) {
            t->is_terminal = false;
            t->value = -1 ;
            *result = true ;
            return _trie_is_empty(t);
        }
        return false;
    }
    int index = key[depth] ;
    if (_trie_delete_aux(t->children[index], key, depth + 1, result)) {
        free(t->children[index]);
        t->children[index] = NULL;
        return (!t->is_terminal && _trie_is_empty(t));
    }
    return false;
}

bool _trie_delete(Trie* t, const char* key, bool* result) {
    return _trie_delete_aux(t, key, 0, result);
}

void trie_insert(char key[], int value) {
    if (_the_trie == NULL)
        _the_trie = _trie_mk_trie() ;
    _trie_insert(_the_trie, key, value) ;
}

bool trie_delete(char key[]) {
    bool result ;
    _trie_delete(_the_trie, key, &result) ;
    return result ;
}

bool trie_find(char key[], int* value) {
    return _trie_find(_the_trie, key, value) ;
}

bool trie_is_empty(void) {   
    if (_the_trie)
        return _trie_is_empty(_the_trie) ;
    else 
        return true ;
}

void trie_free(void) {
    if (_the_trie)
        _trie_free(_the_trie) ;
}

#ifdef  _THEFT
#define KEY_SIZE_LIMIT 10
#define VALUE_LIMIT   100

enum theft_alloc_res allocate_trie(struct theft *, void *, void **) ;

struct theft_type_info random_trie_info = {
    .alloc = allocate_trie,
    .free  = theft_generic_free_cb,
    .autoshrink_config = {
        .enable = true,
    }
} ;

enum theft_alloc_res allocate_trie(struct theft *t, void *data, void **result) {
    Trie* trie = _trie_mk_trie() ;
    assert(t) ;
    int height = theft_random_choice(t, KEY_SIZE_LIMIT) ;
    Trie* aux = trie ;
    for (int h = 0; h < height; h ++) {
        int child = theft_random_choice(t, UCHAR_MAX) ;
        aux->children[child] = _trie_mk_trie() ;
        aux->children[child]->is_terminal = theft_random_choice(t, 1) ;
        aux->children[child]->value = theft_random_choice(t, VALUE_LIMIT) ;
        aux = aux->children[child] ;
    }
    (Trie*) *result ;
    *result = trie;
    return (trie ? THEFT_ALLOC_OK : THEFT_ALLOC_ERROR) ;
}

char* mk_random_key(struct theft *t) {
    unsigned char key_size = theft_random_choice(t, KEY_SIZE_LIMIT); 
    char* some_key = (char*) malloc(key_size * sizeof(char) + 1) ;
    for (int i = 0; i < key_size ; i++) {
        some_key[i] = (char) (97 + theft_random_choice(t, 25));
    }
    some_key[key_size] = '\0' ;
    return some_key ;
}

enum theft_trial_res property_insert_delete_find(struct theft *t, void *test_input)
{
    Trie* trie = (Trie*) test_input ;
    unsigned char key_size = theft_random_choice(t, KEY_SIZE_LIMIT) ; 
    if (key_size == 0) {
        key_size = 1 ;
    }
    char* some_key = mk_random_key(t) ;
    int some_value = theft_random_choice(t, VALUE_LIMIT); 
    _trie_insert(trie, some_key, some_value) ;
    _trie_delete(trie, some_key) ;
    bool found = false ;
    found = _trie_find(trie, some_key) ;
    free(some_key) ;
    some_key = NULL ;
    return !found? THEFT_TRIAL_PASS : THEFT_TRIAL_FAIL ; 
}

int main(void) {
    theft_seed seed = theft_seed_of_time();
    struct theft_run_config config = {
        .name = __func__,
        .prop1 = property_insert_delete_find,
        .type_info = { &random_trie_info },
        .seed = seed
    } ;
    return (theft_run(&config) == THEFT_RUN_PASS) ? EXIT_SUCCESS : EXIT_FAILURE ;
}
#endif