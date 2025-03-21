# Dependencies: math, sarena

# SETTINGS --------------------------------------------------------------------

# GLOBAL

# D(ynamic) or S(tatic)
LIB_TYPE = S

CC = gcc

C_SRC = $(shell find src -name "*.c")
C_OBJ = $(patsubst src/%.c,build/%.o,$(C_SRC))

_DEBUG_FLAGS =
_OPTIMIZATION_FLAGS = -O2
_WARN_FLAGS = -Wall
_M_FLAGS = -MMD -MP
_I_FLAGS = -Iinclude -Ilib/include

_BASE_CFLAGS = -c $(_I_FLAGS) $(_M_FLAGS) $(_WARN_FLAGS) \
$(_DEBUG_FLAGS) $(_OPTIMIZATION_FLAGS)

# SRC

SRC_CFLAGS = $(_BASE_CFLAGS)

define get_complete_src_cflags
$(SRC_CFLAGS) -MF build/dependencies/$(1).d
endef

# TEST

TEST_CFLAGS = $(_BASE_CFLAGS)
TEST_LFLAGS = -Wl,-rpath,lib/so -Llib/so -Llib/ar -lsarena -lm

# LIB SETTINGS

LIB_NAME = nuterm

ifeq ($(LIB_TYPE), D)
	LIB_FILE = lib$(LIB_NAME).so
	LIB_FLAGS = -shared
	SRC_CFLAGS += -fPIC
	LIB_MAKE_COMMAND = $(CC) $(LIB_FLAGS) $(C_OBJ) -o $(LIB_FILE)
else
	LIB_FILE = lib$(LIB_NAME).a
	LIB_FLAGS = rcs
	LIB_MAKE_COMMAND = ar $(LIB_FLAGS) $(LIB_FILE) $(C_OBJ)
endif

# INSTALL

INSTALL_PREFIX = /usr/local
# TODO
INSTALL_HFILES =

# ------------------------------------------------------------------------------

.PHONY: clean install all uninstall dirs

# MISC

all: dirs $(LIB_FILE)

dirs: | build build/dependencies

build:
	mkdir -p $@

build/dependencies:
	mkdir -p $@

# MAIN

$(LIB_FILE): $(C_OBJ)
	$(LIB_MAKE_COMMAND)

$(C_OBJ): build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(call get_complete_src_cflags,$(basename $(notdir $@))) $< -o $@

# TEST

test: dirs build/tests.o $(C_OBJ)
	$(CC) build/tests.o $(C_OBJ) -o $@ $(TEST_LFLAGS)

build/tests.o: tests.c
	$(CC) $(TEST_CFLAGS) $< -o $@

# INSTALL / UNINSTALL

install:
	sudo mkdir -p $(INSTALL_PREFIX)/lib
	sudo mkdir -p $(INSTALL_PREFIX)/include
	sudo cp $(LIB_FILE) $(INSTALL_PREFIX)/lib
	sudo mkdir -p $(INSTALL_PREFIX)/include/$(LIB_NAME)
	sudo cp -r $(INSTALL_HFILES) $(INSTALL_PREFIX)/include/$(LIB_NAME)

uninstall:
	sudo rm -f $(INSTALL_PREFIX)/lib/$(LIB_FILE)
	sudo rm -rf $(INSTALL_PREFIX)/include/$(LIB_NAME)

# CLEAN

clean:
	rm -rf build
	rm -f $(LIB_FILE)
	rm -f compile_commands.json
	rm -f test

-include $(wildcard build/dependencies/*.d)
