cmake_minimum_required(VERSION 3.15)

project(
	opengl-practice
	LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES 
      ${CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES})
endif()

set(GLPRACTICE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(src glpractice)
