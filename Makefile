all: trie.o main.o
	gcc -o main trie.o main.o

trie.o: trie.c
	gcc -c -g -gdwarf-4 -g3 trie.c

main.o: main.c
	gcc -c -g -gdwarf-4 -g3 main.c