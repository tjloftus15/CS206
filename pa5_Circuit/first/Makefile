all: first

first: first.c
	gcc -O3 -Wall -Werror -fsanitize=address first.c -o first

clean:
	rm -rf hello
