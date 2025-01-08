#!/usr/bin/env bash

set -x

PROJECT_DIR=$(dirname "$0")
DEPS_DIR="$PROJECT_DIR/_deps"
DEPS_INSTALL="$DEPS_DIR/_root"

download_if_not_exist() {
    if [[ ! -e "$1" ]]; then
        curl -L -o "$1" "$2" || exit 1
    fi
}

setup_glfw() {
    local GLFW_VERSION=3.4
    local GLFW_DIR="$DEPS_DIR/glfw-$GLFW_VERSION"
    local GLFW_ZIP_FILE="$DEPS_DIR/glfw-$GLFW_VERSION.zip"
    local GLFW_BUILD_DIR="$GLFW_DIR/build"
    download_if_not_exist "$GLFW_ZIP_FILE" "https://github.com/glfw/glfw/releases/download/$GLFW_VERSION/glfw-$GLFW_VERSION.zip"
    unzip -d "$DEPS_DIR" "$GLFW_ZIP_FILE"
    mkdir -p "$GLFW_BUILD_DIR"
    cmake --fresh \
        -DCMAKE_INSTALL_PREFIX="$DEPS_INSTALL" \
        -DGLFW_BUILD_DOCS=OFF \
        -DGLFW_BUILD_EXAMPLES=OFF \
        -B "$GLFW_BUILD_DIR" -S "$GLFW_DIR" || exit 1
    cmake --build "$GLFW_BUILD_DIR" -- -B -j$(nproc) || exit 1
    cmake --install "$GLFW_BUILD_DIR" || exit 1
    rm -rf "$GLFW_DIR"
}

setup_glm() {
    local GLM_VERSION=1.0.1
    local GLM_DIR="$DEPS_DIR/glm"
    local GLM_ZIP_FILE="$DEPS_DIR/glm-$GLM_VERSION-light.zip"
    local GLM_BUILD_DIR="$GLM_DIR/build"

    download_if_not_exist "$GLM_ZIP_FILE" "https://github.com/g-truc/glm/releases/download/$GLM_VERSION/glm-$GLM_VERSION-light.zip"

    unzip -d "$DEPS_INSTALL/include" "$GLM_ZIP_FILE"
}

mkdir -p "$DEPS_DIR"
setup_glfw
setup_glm
ln -rsf "$DEPS_INSTALL/lib64" "$DEPS_INSTALL/lib"
