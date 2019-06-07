all: second

second: second.c
	gcc -O3 -Wall -Werror -fsanitize=address second.c -o second

clean:
	rm -rf hello
