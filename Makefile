CC=gcc

wtf: src/main.c bin/dirs.o bin/path.o
	$(CC) -o wtf src/main.c bin/dirs.o bin/path.o

bin/example-dirs: bin/dirs.o bin/path.o src/dirs.h examples/dirs.c
	$(CC) -o bin/example-dirs bin/dirs.o bin/path.o examples/dirs.c

bin/dirs.o: src/dirs.c src/dirs.h
	$(CC) -c -o bin/dirs.o src/dirs.c

bin/path.o: src/path.c src/path.h
	$(CC) -c -o bin/path.o src/path.c

.PHONY: run-example-dirs
run-example-dirs: bin/example-dirs
	./bin/example-dirs
