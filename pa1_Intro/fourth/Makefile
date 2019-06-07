all: test

test: fourth.c
	gcc -Wall -Werror -fsanitize=address fourth.c -o fourth
	
clean:
	rm -rf fourth
