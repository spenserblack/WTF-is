CC=gcc

bin/example-dirs: bin/dirs.o src/dirs.h examples/dirs.c
	$(CC) -o bin/example-dirs bin/dirs.o examples/dirs.c

bin/dirs.o: src/dirs.c src/dirs.h
	$(CC) -c -o bin/dirs.o src/dirs.c

.PHONY: run-example-dirs
run-example-dirs: bin/example-dirs
	./bin/example-dirs
