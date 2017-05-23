##########################
#	run command
#	cmake ../ && make
#	from a directory where the all output files should be created
##########################

cmake_minimum_required(VERSION 3.6)
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

SET(RESOURCES
	manual/rccg_manual.txt
)

#set(EXECUTABLE_OUTPUT_PATH "cmake-build-debug") # adds executables to "cmake-build-debug" directory

set(CMAKE_BINARY_DIR ".")

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(ccg ${SOURCE_FILES} ${RESOURCES})
