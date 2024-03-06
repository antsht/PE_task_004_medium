BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean find_duplicates cryptography 

rebuild: clean_all find_duplicates cryptography clean

find_duplicates: clean find_duplicates.c data.c errors.c
	$(CC) $(CFLAGS) find_duplicates.c data.c errors.c -o  $(BUILD_PATH)find_duplicates 
	
cryptography: clean cryptography.c data.c errors.c
	$(CC) $(CFLAGS) cryptography.c data.c errors.c -o  $(BUILD_PATH)cryptography 
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  cryptography.c data.c errors.c -o  $(BUILD_PATH)cryptography_extra 

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

test:
	cd ../	
	pytest --color=yes -v --tb=short  

test_config:
	python3 -m venv ../test-env  
	source ../test-env/bin/activate 
	pip install -r ../tests/requirements.txt



