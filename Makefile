default: build

build:
	gcc -o snake screen.h screen.c list.h  list.c main.c -lncurses

run: build
	./snake


clean:
#	rm snake run_tests
