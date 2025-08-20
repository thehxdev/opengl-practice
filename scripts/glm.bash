version="1.0.1"
source_dir="glm"

cd "$DEPS_PATH"

if [[ ! -e "$source_dir" ]]; then
    git clone --depth=1 --branch="$version" \
        "https://github.com/g-truc/glm" "$source_dir"
fi

cd "$source_dir" && mkdir -p "build" && cd "build"

cmake --fresh \
      -DCMAKE_INSTALL_PREFIX="$DEPS_PATH" \
      -DGLM_BUILD_LIBRARY=ON \
      -DGLM_BUILD_TESTS=OFF \
      -DBUILD_SHARED_LIBS=OFF \
      ..

cmake --build . -- -j$(nproc) all && cmake --build . -- install
