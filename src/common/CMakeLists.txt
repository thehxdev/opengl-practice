add_library(
	common STATIC
	common.cpp
	gl.cpp
)
target_link_libraries(common PUBLIC glpractice_interface)
