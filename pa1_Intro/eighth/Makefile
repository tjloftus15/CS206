all: test

test: eighth.c
	gcc -g -Wall -Werror -fsanitize=address eighth.c -o eighth
	
clean:
	rm -rf eighth
