# PR -> Project Root: relative path to project root directory from a sub-project
# Example: make PR=../.. -C ./src/triangle-1
# the `../..` part is path to project root relative to `src/triangle-1`
# or if you are in `src/triangle-1` directory the build command will be the following:
# make PR=../..
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
