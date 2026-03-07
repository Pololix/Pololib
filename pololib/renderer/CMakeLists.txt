# renderer submodule

add_library(renderer STATIC
	src/opengl/opengl_context.cpp
)

target_include_directories(renderer
	PUBLIC
		include
)

find_package(OpenGL REQUIRED)

target_link_libraries(renderer
	PUBLIC
		core
		OpenGL::GL
		glad
)