all: test

test:ninth.c
	gcc -Wall -Werror -fsanitize=address ninth.c -o ninth
	
clean:
	rm -rf ninth
