add_executable(
	triangle-0
	main.cpp
)
target_link_libraries(triangle-0 PRIVATE common)
file(COPY "vertex_shader.glsl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "fragment_shader.glsl" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
