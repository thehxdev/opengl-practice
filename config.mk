# PR -> Project Root: absolute path to project root directory
DEPS_LIB_DIR := $(PR)/_deps/_root/lib
DEPS_INCLUDE_DIR := $(PR)/_deps/_root/include

LOCAL_LIB_DIR := $(PR)/lib
LOCAL_INCLUDE_DIR := $(PR)/include

INCLUDE_FLAGS := -I$(LOCAL_INCLUDE_DIR) -I$(DEPS_INCLUDE_DIR)

CXX ?= clang++

CXXFLAGS := -std=gnu++17 -Wall -Wextra -Wno-unused-result
CXXFLAGS += $(INCLUDE_FLAGS)

LDFLAGS := -Wl,-rpath,$(LOCAL_LIB_DIR) -Wl,-rpath,$(DEPS_LIB_DIR) -L$(DEPS_LIB_DIR) -L$(LOCAL_LIB_DIR)
LIBS := -lcommon -lglfw3 -lGL -lm
