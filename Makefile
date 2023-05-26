trie.o: trie.c
	gcc -c -g -gdwarf-4 -g3 -fPIC trie.c

trie.so: trie.o
	gcc -shared trie.o -o trie.so

test: trie.c
	gcc trie.c -o test_trie -g -gdwarf-4 -g3 -fPIC -D _THEFT -I /data/theft/inc/ -L /data/theft/build/ -ltheft  

clean:
	rm trie.o
	rm trie.so
	rm test_trie
