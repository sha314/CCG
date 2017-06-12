##########################
#	run command
#	cmake . && make
#	from a directory where the all output files should be created
##########################

cmake_minimum_required(VERSION 3.0)
project(CCG)

#set(CMAKE_MAJOR_VERSION 1)
#set(CMAKE_MINOR_VERSION 0)
#set(CMAKE_PATCH_VERSION 0)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
	src/flags.h
	src/ccg.h
	src/ccg.cpp
	src/parse_args.h
	src/parse_args.cpp
	src/main.cpp
)


#set(EXECUTABLE_OUTPUT_PATH "cmake-build-debug") # adds executables to "cmake-build-debug" directory

# this one is important
# SET(CMAKE_SYSTEM_NAME Windows)
# SET(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_BINARY_DIR ".")

# set(dir ${CMAKE_CURRENT_SOURCE_DIR}/../Compile/)
# set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
# set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
# set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
# set(CMAKE_BUILD_DIRECTORY ${dir})
# SET(EXECUTABLE_OUTPUT_PATH ${dir})
# SET(LIBRARY_OUTPUT_PATH ${dir}lib)
# SET(CMAKE_CACHEFILE_DIR ${dir})

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(ccg ${SOURCE_FILES})
