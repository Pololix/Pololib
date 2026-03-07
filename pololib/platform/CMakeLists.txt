# platform submodule

add_library(platform STATIC
	"src/windows/wnd_window.cpp"
   "src/window_factory.cpp")

target_include_directories(platform
	PUBLIC
		include
)

target_link_libraries(platform
	PUBLIC
		core
		glfw
		glad
)