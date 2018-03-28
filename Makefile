default: build

build:
	gcc -o snake screen.h list.h screen.c list.c main.c -lncurses

run: build
	./snake


clean:
#	rm snake run_tests
