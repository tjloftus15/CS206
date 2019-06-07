all: test

test: sixth.c
	gcc -Wall -g -Werror -fsanitize=address sixth.c -o sixth

clean:
	rm -rf sixth
