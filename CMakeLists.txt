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

add_library(testmod SHARED
	"extern/GameAPI/CPP/GameAPI/Game.cpp"

	"src/testmod/main.cpp"
)

set_target_properties(testmod PROPERTIES PREFIX "")
configure_file(${CMAKE_SOURCE_DIR}/src/testmod/mod.ini ${CMAKE_BINARY_DIR}/mods/testmod/mod.ini COPYONLY)
configure_file(${CMAKE_BINARY_DIR}/testmod.dll ${CMAKE_BINARY_DIR}/mods/testmod/testmod.dll COPYONLY)
