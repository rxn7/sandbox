cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # .exe and .dll
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # .exe and .dll
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # .so and .dylib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") # .lib and .a

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(sandbox ${SOURCES})
target_compile_options(sandbox PRIVATE -Wall -Wpedantic -Wno-c++98-compat -Wno-c++98-compat-pedantic)

target_link_libraries(sandbox PRIVATE glad glfw glm ImGui::imgui)

add_custom_target(copy_res
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_EXECUTABLE_OUTPUT_DIRECTORY}/res
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/res ${CMAKE_EXECUTABLE_OUTPUT_DIRECTORY}/res
)

install(TARGETS sandbox)
add_dependencies(sandbox copy_res)
