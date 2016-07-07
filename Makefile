# Copyright (c) 2013 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

#
# GNU Make based build file.  For details on GNU Make see:
# http://www.gnu.org/software/make/manual/make.html
#

#
# Get pepper directory for toolchain and includes.
#
# If NACL_SDK_ROOT is not set, then assume it can be found three directories up.
#
THIS_MAKEFILE := $(abspath $(lastword $(MAKEFILE_LIST)))
NACL_SDK_ROOT ?= $(abspath $(dir $(THIS_MAKEFILE))../..)

# Project Config
PROJECT := DataSand
BUILD_FOLDER := intermediates
SOURCE_FOLDER := src_cpp
PRODUCT_FOLDER := demo
CXX_SOURCES := $(shell find ./$(SOURCE_FOLDER) -name *.cpp)
CXX_OBJECTS := $(patsubst ./$(SOURCE_FOLDER)/%.cpp,$(BUILD_FOLDER)/%.o,$(CXX_SOURCES))
CXX_SOURCES := $(patsubst ./$(SOURCE_FOLDER)/%.cpp,%.cpp,$(CXX_SOURCES))

# Project Build flags
WARNINGS := -Wno-long-long -Wall -Wswitch-enum -pedantic -Werror
CXXFLAGS := -pthread -std=c++0x $(WARNINGS)

#
# Compute tool paths
#
GETOS := python $(NACL_SDK_ROOT)/tools/getos.py
OSHELPERS = python $(NACL_SDK_ROOT)/tools/oshelpers.py
OSNAME := $(shell $(GETOS))
RM := $(OSHELPERS) rm

PNACL_TC_PATH := $(abspath $(NACL_SDK_ROOT)/toolchain/$(OSNAME)_pnacl)
PNACL_CXX := $(PNACL_TC_PATH)/bin/pnacl-clang++
PNACL_FINALIZE := $(PNACL_TC_PATH)/bin/pnacl-finalize
CXXFLAGS := -I$(NACL_SDK_ROOT)/include -I$(NACL_SDK_ROOT)/include/newlib
LDFLAGS := -L$(NACL_SDK_ROOT)/lib/pnacl/Release -lppapi_cpp -lppapi -lppapi_gles2

#
# Disable DOS PATH warning when using Cygwin based tools Windows
#
CYGWIN ?= nodosfilewarning
export CYGWIN

.PHONY: all clean

# Declare the ALL target first, to make the 'all' target the default build
all: $(PROJECT)

define make-object
    $(BUILD_FOLDER)/$1.o: $(SOURCE_FOLDER)/$1.cpp
	mkdir -p $(dir $(BUILD_FOLDER)/$1.o)
	$(PNACL_CXX) -o $(BUILD_FOLDER)/$1.o $(SOURCE_FOLDER)/$1.cpp -O2 $(CXXFLAGS) $(LDFLAGS) -c
endef

$(foreach file,$(CXX_SOURCES),$(eval $(call make-object,$(basename $(file)))))

clean:
	$(RM) $(CXX_OBJECTS)
	$(RM) ./$(PRODUCT_FOLDER)/$(PROJECT).raw.pexe
	$(RM) ./$(PRODUCT_FOLDER)/$(PROJECT).pexe

$(PROJECT): $(CXX_OBJECTS)
	$(PNACL_CXX) -o $(PRODUCT_FOLDER)/$@.raw.pexe $(CXX_OBJECTS) -O2 $(CXXFLAGS) $(LDFLAGS)
	$(PNACL_FINALIZE) -o $(PRODUCT_FOLDER)/$@.pexe $(PRODUCT_FOLDER)/$@.raw.pexe
