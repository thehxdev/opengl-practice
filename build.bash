#!/usr/bin/env bash

declare -a TO_BUILD=('libcommon' $@)
PROJECT_ROOT="$(pwd)/$(dirname $0)"

build() {
    make PR="$PROJECT_ROOT" $@
}

mkdir -p "$PROJECT_ROOT/lib"

for p in "${TO_BUILD[@]}"; do
    build -C "$PROJECT_ROOT/src/$p"
done
