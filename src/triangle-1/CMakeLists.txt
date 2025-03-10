add_executable(
	triangle-1
	main.cpp
)
target_link_libraries(triangle-1 PRIVATE common)
file(COPY "vertex_shader.glsl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "fragment_shader.glsl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
