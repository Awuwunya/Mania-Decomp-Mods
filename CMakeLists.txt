cmake_minimum_required(VERSION 3.18)

project(Fractal-Tools
	# Version number can be used to generate header file with version info
	LANGUAGES C CXX
)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

enable_testing()

# requires at least C11/C++17-compatible compiler to compile the code
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# build options
set(GAME_DIR ${CMAKE_SOURCE_DIR}/game CACHE STRING "GAME_DIR")

# include dirs
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/extern/GameAPI/CPP/GameAPI)
include_directories(${CMAKE_SOURCE_DIR}/extern/GameAPI/CPP/GameAPI/RSDKv5)
include_directories(${CMAKE_SOURCE_DIR}/extern/Mania)

# Add `DEBUG` macro definition if compiling under Debug or RelWithDebInfo
# configuration
add_compile_definitions(
	$<$<CONFIG:Debug,RelWithDebInfo>:DEBUG>
)

set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")

# generate custom command for the specific mod
function(genmod mod)
	set_target_properties(${mod} PROPERTIES PREFIX "")

	add_custom_command(TARGET ${mod} POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-DTARGET_NAME=${mod}
		-DTARGET_PATH=${CMAKE_CURRENT_SOURCE_DIR}
		-DGAME_DIR:STRING=${GAME_DIR}
		-DINI_DIR:STRING=${CMAKE_SOURCE_DIR}
		-P ${CMAKE_SOURCE_DIR}/addmod.cmake
	)
endfunction()

# make test mod
add_library(extraplayers SHARED
	"extern/GameAPI/CPP/GameAPI/Game.cpp"

	"src/extraplayers/main.cpp"
)

genmod(extraplayers)
