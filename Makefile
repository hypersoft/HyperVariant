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

BUILD_OUTPUT ?= .
BUILD_BIN ?= bin
BUILD_SOURCE ?= src

BUILD_VERSION_SOURCES = $(BUILD_SOURCE)/HyperVariant.c $(BUILD_SOURCE)/HyperVariant.h

BUILD_OBJECT = $(BUILD_BIN)/HyperVariant.o
BUILD_ARCHIVE = $(BUILD_OUTPUT)/HyperVariant.a
BUILD_HEADER = $(BUILD_OUTPUT)/HyperVariant.h

BUILD_SHARED = $(BUILD_OUTPUT)/libhypervar
BUILD_LIBRARY = $(BUILD_SHARED).so.$(BUILD_TRIPLET)
BUILD_LIBFLAGS = -export-dynamic -shared -soname $(BUILD_SHARED).so.$(BUILD_MAJOR)

BUILD_DEMO = $(BUILD_BIN)/demo
BUILD_DEMO_SRC = $(BUILD_SOURCE)/demo.c
BUILD_DEMO_OBJECT = $(BUILD_BIN)/demo.o

# disable MakeStats notice
BUILD_STATS_NOTICE = FALSE

# enable MakeStats auto commit; Warning noisy commit history!
BUILD_STATS_AUTO_COMMIT ?= TRUE

# include MakeStats
include $(BUILD_SOURCE)/../mktools/MakeStats.mk

BUILD_FLAGS += \
-DHV_VERSION_VENDOR='"$(BUILD_VENDOR)"' \
-DHV_VERSION_TRIPLET='"$(BUILD_TRIPLET)"' \
-DHV_VERSION_DESCRIPTION='"$(BUILD_VENDOR) $(BUILD_NAME) $(BUILD_TRIPLET)"' \
-DHV_VERSION_BUILDNO=$(BUILD_NUMBER)

# System Install Paths for lib & header
SYSTEM_LIBDIR := /usr/local/lib
SYSTEM_INCDIR := /usr/local/include

all: $(BUILD_BIN) $(BUILD_OUTPUT) archive library demo

$(BUILD_OBJECT): CFLAGS += -O3 -fPIC $(BUILD_FLAGS)
$(BUILD_OBJECT): $(BUILD_VERSION_SOURCES)
	@$(make-build-number)
	$(COMPILE.c) -o $@ $<
	@$(make-build-revision)
	@echo

$(BUILD_HEADER): $(BUILD_SOURCE)/HyperVariant.h
	@cp $< $@

$(BUILD_ARCHIVE): $(BUILD_OBJECT) $(BUILD_HEADER)
	@$(make-build-number)
	@echo -e 'Building $(BUILD_NAME) $(BUILD_TRIPLET) archive...\n'
	$(AR) -vr $@ $<
	@echo

$(BUILD_LIBRARY): $(BUILD_OBJECT)
	@$(make-build-number)
	@echo -e 'Building $(BUILD_NAME) $(BUILD_TRIPLET) library...\n'
	ld $(BUILD_LIBFLAGS) -o $@ $<
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

.DEFAULT_GOAL := all
.SUFFIXES:
.PHONY: all clean archive library demo
