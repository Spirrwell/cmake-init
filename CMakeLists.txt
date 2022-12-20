cmake_minimum_required( VERSION 3.22 FATAL_ERROR )

project( cmake-init )

add_executable( cmake-init src/main.cpp )
set_target_properties(
	cmake-init PROPERTIES
	CXX_STANDARD 17
)

install(
	TARGETS cmake-init
	RUNTIME DESTINATION bin
)