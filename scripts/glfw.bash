version="3.4"
archive="glfw-${version}.zip"
source_dir="glfw-${version}"

cd "$DEPS_PATH"

if [[ ! -e "$archive" ]]; then
    curl -#L -o "$DEPS_PATH/$archive" \
         "https://github.com/glfw/glfw/releases/download/${version}/glfw-${version}.zip" || exit 1
fi

if [[ ! -e "$source_dir" ]]; then
    unzip "$archive" || exit 1
fi

cd "$source_dir" && mkdir -p "build" && cd "build"

cmake --fresh \
    -DCMAKE_INSTALL_PREFIX="$DEPS_PATH" \
    -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" \
    -DGLFW_BUILD_EXAMPLES=OFF \
    -DGLFW_BUILD_TESTS=OFF \
    -DGLFW_BUILD_DOCS=OFF \
    ..

cmake --build . -- -j$(nproc) all && cmake --build . -- install
