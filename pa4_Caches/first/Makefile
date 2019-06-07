all: test

test: first.c
	gcc -Wall -Werror -fsanitize=address first.c -o first

clean:
	rm -rf test
