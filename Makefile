#
# Sun Feb 16 22:14:39 CST 2014
#
# Copyright (c) 2014, Triston J. Taylor
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright notice, this
#   list of conditions and the following disclaimer in the documentation and/or
#   other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
# ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

BUILD_VENDOR = Hypersoft Systems

BUILD_HOME ?= .
BUILD_SRC = $(BUILD_HOME)/src
BUILD_PKG = $(BUILD_HOME)/pkg
BUILD_TOOLS = $(BUILD_HOME)/mktools

BUILD_OUTPUT ?= .
BUILD_BIN ?= bin
BUILD_SRC ?= src

BUILD_VERSION_SOURCES = $(BUILD_SRC)/HyperVariant.c $(BUILD_SRC)/HyperVariant.h

BUILD_OBJECT = $(BUILD_BIN)/HyperVariant.o
BUILD_ARCHIVE = $(BUILD_OUTPUT)/HyperVariant.a
BUILD_HEADER = $(BUILD_OUTPUT)/HyperVariant.h

BUILD_LIBRARY_NAME = libHyperVariant
BUILD_SHARED = $(BUILD_OUTPUT)/$(BUILD_LIBRARY_NAME)
BUILD_LIBRARY = $(BUILD_SHARED).$(BUILD_TRIPLET).so
BUILD_LIBRARY_FLAGS = -export-dynamic -shared -soname \
$(BUILD_LIBRARY_NAME).so.$(BUILD_MAJOR)

BUILD_DEMO = $(BUILD_BIN)/demo
BUILD_DEMO_SRC = $(BUILD_SRC)/demo.c
BUILD_DEMO_OBJECT = $(BUILD_BIN)/demo.o

# disable MakeStats notice
BUILD_STATS_NOTICE = FALSE

# enable MakeStats auto commit; Warning noisy commit history!
BUILD_STATS_AUTO_COMMIT ?= TRUE

# include MakeStats
include $(BUILD_TOOLS)/MakeStats.mk

BUILD_FLAGS += \
-DBUILD_VERSION_VENDOR='"$(BUILD_VENDOR)"' \
-DBUILD_VERSION_TRIPLET='"$(BUILD_TRIPLET)"' \
-DBUILD_VERSION_DESCRIPTION='"$(BUILD_VENDOR) $(BUILD_NAME) $(BUILD_TRIPLET)"' \
-DBUILD_VERSION_NUMBER=$(BUILD_NUMBER)

# System Install Paths for lib & header
SYSTEM_LIBDIR := /usr/local/lib
SYSTEM_INCDIR := /usr/local/include

BUILD_SOURCE_ARCHIVE = \
$(BUILD_OUTPUT)/$(BUILD_NAME)-$(BUILD_TRIPLET).tar.gz

BUILD_SOURCE_ARCHIVE_FILES = \
$(BUILD_HOME)/LICENSE \
$(BUILD_HOME)/README.md \
$(BUILD_HOME)/Makefile \
$(BUILD_HOME)/project.ver \
$(BUILD_TOOLS)/MakeStats.mk \
$(BUILD_SRC)/HyperVariant.c \
$(BUILD_SRC)/HyperVariant.h \

all: $(BUILD_BIN) $(BUILD_OUTPUT) archive library demo

$(BUILD_OBJECT): CFLAGS += -O3 -fPIC $(BUILD_FLAGS)
$(BUILD_OBJECT): $(BUILD_VERSION_SOURCES)
	@$(make-build-number)
	$(COMPILE.c) -o $@ $<
	@$(make-build-revision)
	@echo

$(BUILD_HEADER): $(BUILD_SRC)/HyperVariant.h
	@cp $< $@

$(BUILD_ARCHIVE): $(BUILD_OBJECT) $(BUILD_HEADER)
	@$(make-build-number)
	@echo -e 'Building $(BUILD_NAME) $(BUILD_TRIPLET) archive...\n'
	$(AR) -vr $@ $<
	@echo

$(BUILD_LIBRARY): $(BUILD_OBJECT)
	@$(make-build-number)
	@echo -e 'Building $(BUILD_NAME) $(BUILD_TRIPLET) library...\n'
	ld $(BUILD_LIBRARY_FLAGS) -o $@ $<
	@echo

$(BUILD_DEMO_OBJECT): $(BUILD_DEMO_SRC)
	@echo -e 'Building $(BUILD_NAME) $(BUILD_TRIPLET) demo...\n'
	$(COMPILE.c) -o $@ $<
	@echo

$(BUILD_DEMO): $(BUILD_DEMO_OBJECT) $(BUILD_OBJECT)
	$(LINK.c) -o $@ $^
	@echo
	
$(BUILD_BIN) $(BUILD_OUTPUT):
	@mkdir -p $@;

demo: $(BUILD_DEMO)
library: $(BUILD_LIBRARY)
archive: $(BUILD_ARCHIVE)
source-archive: $(BUILD_SOURCE_ARCHIVE)

$(BUILD_SOURCE_ARCHIVE): $(BUILD_SOURCE_ARCHIVE_FILES)
	@echo -e 'Building $@...\n'
	@tar -cvzf $@ $^
	@echo

clean:
	@$(RM) -v $(BUILD_SHARED)*.so $(BUILD_OBJECT) $(BUILD_ARCHIVE) $(BUILD_HEADER) \
		$(BUILD_DEMO) $(BUILD_DEMO_OBJECT) $(BUILD_OUTPUT)/$(BUILD_NAME)*.tar.gz

.DEFAULT_GOAL := all
.SUFFIXES:
.PHONY: all clean archive library demo source-archive
