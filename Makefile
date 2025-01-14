CC = gcc
AR = ar

INSTALL_PREFIX = /usr/local

C_SRC = $(shell find src -name "*.c")
C_OBJ = $(patsubst src/%.c,build/%.o,$(C_SRC))
C_OBJ_FLAGS = -c -Iinclude -Wall

LIB = nuterm
AR_LIB = lib$(LIB).a
AR_FLAGS = rcs

.PHONY: clean install uninstall make_lib

$(AR_LIB): $(C_OBJ) build make_lib
	$(AR) $(AR_FLAGS) $(AR_LIB) $(C_OBJ) 

$(C_OBJ): build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(C_OBJ_FLAGS) $< -o $@

test: $(C_OBJ) build make_lib
	gcc -c -Iinclude -Wall tests.c -o build/tests.o
	gcc $(C_OBJ) build/tests.o -o test

build:
	mkdir -p build/

install:
	sudo cp $(AR_LIB) $(INSTALL_PREFIX)/lib
	sudo mkdir -p $(INSTALL_PREFIX)/include/$(LIB)
	sudo cp -r include/* $(INSTALL_PREFIX)/include/$(LIB)

uninstall:
	sudo rm -f $(INSTALL_PREFIX)/lib/$(AR_LIB)
	sudo rm -rf $(INSTALL_PREFIX)/include/$(LIB)

clean:
	rm -rf build
	rm -f $(AR_LIB)
	rm -f compile_commands.json
	rm -f test
