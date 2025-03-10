include(GlfwImport.cmake)
include(GlmImport.cmake)

add_library(glpractice_interface INTERFACE)
target_include_directories(glpractice_interface INTERFACE "${GLPRACTICE_INCLUDE_DIR}")
target_compile_features(glpractice_interface INTERFACE cxx_std_17)
target_link_libraries(glpractice_interface INTERFACE glfw glm)

add_subdirectory(common)
add_subdirectory(triangle-0)
add_subdirectory(triangle-1)
