#!/usr/bin/env bash

log_run() {
    echo "[X] $@"
    $@
}

ROOT_PATH=$(dirname "$(realpath "$0")")
DEPS_PATH="$ROOT_PATH/_deps"
BUILD_PATH="$ROOT_PATH/_build"
SRC_PATH="$ROOT_PATH/src"

BUILD_TYPE="Debug"

CXXFLAGS=(-std=c++20 -Wall -Wextra -Wshadow)
LDFLAGS=()
LIBS=(-l:libglfw3.a -l:libglm.a)
INCLUDES=(-I"$DEPS_PATH/include" -I"$ROOT_PATH/src" -I"$ROOT_PATH/include")
LIBRARIES=(-L"$DEPS_PATH/lib")

if [[ "$BUILD_TYPE" = "Release" ]]; then
    CXXFLAGS+=(-O3 -DNDEBUG)
else
    CXXFLAGS+=(-Og -g3)
fi

if [[ -z $CXX ]]; then
    CXX=c++
fi

mkdir -p "$BUILD_PATH"
echo '*' > "$BUILD_PATH/.gitignore"


for target in $(find "$SRC_PATH" -type d | grep -P "\d\d-.+"); do
    log_run \
        $CXX \
        "${CXXFLAGS[@]}" "${LDFLAGS[@]}" \
        "${INCLUDES[@]}" "${LIBRARIES[@]}" \
        -o "$BUILD_PATH/${target##*/}" \
        "$target/build.cpp" \
        "${LIBS[@]}" &
done

wait
