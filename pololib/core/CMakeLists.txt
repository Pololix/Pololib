# core submodule

add_library(core STATIC
	src/debug/logger.cpp
	src/events/base_event.cpp
	src/events/event_system.cpp
	src/application.cpp
	src/base_window.cpp
 "src/layers/layer_stack.cpp")

target_include_directories(core
	PUBLIC
		include
)

target_link_libraries(core
	PUBLIC
		renderer
		config
)