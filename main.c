#include "trie.h"
#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Test key-value pairs.
    char key1[4] = "abc";
    char key2[4] = "ab";
    int  value1 = 1 ;
    int  value2 = 2 ;

    // Creates an empty trie.
    Trie* t = tri_mk_trie() ;
    assert(t) ;

    // Insert two pairs.
    printf("===========================\n") ;
    printf("Inserts two key-value pairs\n") ;
    printf("===========================\n") ;
    tri_insert(t, key1, value1) ;
    tri_insert(t, key2, value2) ;
    tri_print(t, 0) ;

    // Queries for key2.
    printf("===========================\n") ;
    printf("Queries for key=%s\n", key2) ;
    printf("===========================\n") ;
    bool result = false;
    int value = tri_find(t, key2, &result) ;
    if (result == true)
        printf("found value %d for key %s\n", value, key2) ;    
    else
        printf("found no value for %s\n", key2) ;

    // Deletes keys from trie.
    printf("===========================\n") ;
    printf("Deletes key=%s\n", key2) ;
    printf("===========================\n") ;
      t = tri_delete(t, key2) ;
    tri_print(t, 0) ;    
    printf("===========================\n") ;
    printf("Deletes key=%s\n", key1) ;
    printf("===========================\n") ;
    t = tri_delete(t, key1) ;
    tri_print(t, 0) ;    
    return 0 ;
} 