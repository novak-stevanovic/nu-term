# Dependencies: GDS, math

LIB_TYPE = STATIC

# -----------------------------------------------------------------------------------------------

EXTERNAL_INCLUDE_FLAGS = -Iinclude/lib/gds
OPTIMIZATION_FLAG = -O0

# -----------------------------------------------------------------------------------------------

CC = gcc

C_SRC = $(shell find src -name "*.c")
C_OBJ = $(patsubst src/%.c,build/%.o,$(C_SRC))

BASE_C_FLAGS = -c -Wall -Iinclude $(EXTERNAL_INCLUDE_FLAGS) -fPIC -MMD -MP -g $(OPTIMIZATION_FLAG)

define get_complete_base_cflags
$(BASE_C_FLAGS) -MF build/dependencies/$(1).d
endef

# ------------------------------------------------------------

LIB = nuterm
INSTALL_PREFIX = /usr/local

EXTERNAL_LIB_FLAGS = -Llib -lgds -lm -Wl,-rpath,lib

ifeq ($(LIB_TYPE), DYNAMIC)
	LIB_FILE = lib$(LIB).so
	LIB_FLAGS = -shared $(OPTIMIZATION_FLAG)
	LIB_MAKE_COMMAND = $(CC) $(LIB_FLAGS) $(C_OBJ) -o $(LIB_FILE)
else
	LIB_FILE = lib$(LIB).a
	LIB_FLAGS = rcs -lm
	LIB_MAKE_COMMAND = ar $(LIB_FLAGS) $(LIB_FILE) $(C_OBJ)
endif

# ------------------------------------------------------------

TEST_BIN = main
TEST_BIN_LIB_FLAGS = $(EXTERNAL_LIB_FLAGS)
TEST_C_FLAGS = -c -Iinclude $(EXTERNAL_INCLUDE_FLAGS) -MMD -MP -g $(OPTIMIZATION_FLAG)

define get_complete_test_cflags
$(TEST_C_FLAGS) -MF build/dependencies/$(1).d
endef

# ------------------------------------------------------------

.PHONY: clean install all uninstall dirs test

# ------------------------------------------------------------

all: dirs $(LIB_FILE)

dirs: | build build/dependencies

build:
	mkdir -p $@

build/dependencies:
	mkdir -p $@

$(LIB_FILE): $(C_OBJ)
	$(LIB_MAKE_COMMAND)

$(C_OBJ): build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(call get_complete_base_cflags,$(basename $(notdir $@))) $< -o $@

test: dirs $(TEST_BIN)

$(TEST_BIN): build/tests.o $(C_OBJ)
	$(CC) $^ -o $(TEST_BIN) $(TEST_BIN_LIB_FLAGS)

build/tests.o: tests.c
	$(CC) $(call get_complete_test_cflags,$(basename $(notdir $@))) $< -o $@

install:
	sudo cp $(LIB_FILE) $(INSTALL_PREFIX)/lib
	sudo mkdir -p $(INSTALL_PREFIX)/include/$(LIB)
	sudo cp -r include/* $(INSTALL_PREFIX)/include/$(LIB)

uninstall:
	sudo rm -f $(INSTALL_PREFIX)/lib/$(LIB_FILE)
	sudo rm -rf $(INSTALL_PREFIX)/include/$(LIB)

clean:
	rm -rf build
	rm -f $(LIB_FILE)
	rm -f compile_commands.json
	rm -f $(TEST_BIN)

-include $(wildcard build/dependencies/*.d)
