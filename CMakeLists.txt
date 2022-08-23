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
set(GAME_DIR ${CMAKE_SOURCE_DIR}/game)

# include dirs
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/extern/GameAPI/CPP/GameAPI)
include_directories(${CMAKE_SOURCE_DIR}/extern/GameAPI/CPP/GameAPI/RSDKv5)

# Add `DEBUG` macro definition if compiling under Debug or RelWithDebInfo
# configuration
add_compile_definitions(
	$<$<CONFIG:Debug,RelWithDebInfo>:DEBUG>
)

set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")

# call this function to automatically add a new mod
function(addmod)
	set_target_properties(${ARGV0} PROPERTIES PREFIX "")
	configure_file(${CMAKE_SOURCE_DIR}/src/${ARGV0}/mod.ini ${GAME_DIR}/mods/${ARGV0}/mod.ini COPYONLY)
	configure_file(${CMAKE_BINARY_DIR}/${ARGV0}.dll ${GAME_DIR}/mods/${ARGV0}/${ARGV0}.dll COPYONLY)
endfunction()

# make test mod
add_library(testmod SHARED
	"extern/GameAPI/CPP/GameAPI/Game.cpp"

	"src/testmod/main.cpp"
)

addmod(testmod)
