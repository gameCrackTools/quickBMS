#
# Centaurean SpookyHash
#
# Copyright (c) 2015, Guillaume Voirin
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of Centaurean nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# 6/02/15 14:38
#

TARGET = spookyhash
CFLAGS = -Ofast -fomit-frame-pointer -w -flto -std=c99

SRC_DIRECTORY = ./src/

ifeq ($(OS),Windows_NT)
    bold =
    normal =
    DYN_EXT = .dll
    STAT_EXT = .lib
    ARROW = ^-^>
else
    bold = `tput bold`
    normal = `tput sgr0`
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        DYN_EXT = .so
    endif
    ifeq ($(UNAME_S),Darwin)
        DYN_EXT = .dylib
    endif
    STAT_EXT = .a
    ARROW = \-\>
endif

SPOOKYHASH_SRC = $(wildcard $(SRC_DIRECTORY)*.c)
SPOOKYHASH_OBJ = $(SPOOKYHASH_SRC:.c=.o)
ALL_OBJ = $(SPOOKYHASH_OBJ)

.PHONY: compile-header compile-library-header link-header

all: $(TARGET)$(DYN_EXT) $(TARGET)$(STAT_EXT)

%.o: %.c
	@echo $^ $(ARROW) $@
	@$(CC) -c $(CFLAGS) $< -o $@

compile-header:
	@echo ${bold}Compiling SpookyHash${normal} ...

compile-library-header:
	@$(eval CFLAGS = $(CFLAGS) -fPIC)
	@echo ${bold}Compiling SpookyHash as a library${normal} ...

compile: compile-header $(SPOOKYHASH_OBJ)
	@echo Done.
	@echo

compile-library: compile-library-header $(SPOOKYHASH_OBJ)
	@echo Done.
	@echo

link-header: compile-library
	@echo ${bold}Linking SpookyHash${normal} ...

$(TARGET)$(DYN_EXT): link-header $(ALL_OBJ)
	@echo *.o $(ARROW) ${bold}$(TARGET)$(DYN_EXT)${normal}
	@$(CC) -shared -o $(TARGET)$(DYN_EXT) $(ALL_OBJ)
	@echo Done.
	@echo

$(TARGET)$(STAT_EXT): link-header $(ALL_OBJ)
	@echo *.o $(ARROW) ${bold}$(TARGET)$(STAT_EXT)${normal}
	@ar r $(TARGET)$(STAT_EXT) $(ALL_OBJ)
	@ranlib $(TARGET)$(STAT_EXT)
	@echo Done.
	@echo

clean:
	@echo ${bold}Cleaning SpookyHash objects${normal} ...
	@rm -f $(SPOOKYHASH_OBJ)
	@rm -f $(TARGET)$(DYN_EXT)
	@rm -f $(TARGET)$(STAT_EXT)
	@echo Done.
	@echo