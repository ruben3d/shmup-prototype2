cmake_minimum_required (VERSION 2.8)
project (shmup)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message (STATUS "C++11 support required.")
endif()

set (APPLICATION_NAME "Super Shmup!")
set (APPLICATION_PATH_DATA "data")
set (APPLICATION_VERSION_MAJOR 0)
set (APPLICATION_VERSION_MINOR 2)
set (APPLICATION_VERSION_REVISION 0)

set (EXTRA_LIBS sfml-graphics sfml-window sfml-system)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# For the .in files
include_directories("${PROJECT_BINARY_DIR}")

# Libraries
include_directories("${PROJECT_SOURCE_DIR}/lib/json")

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

add_executable(shmup ${SOURCE})
target_link_libraries (shmup ${EXTRA_LIBS})

add_custom_command(TARGET shmup
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/bin/${APPLICATION_PATH_DATA}
)

add_custom_command(TARGET shmup
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/${APPLICATION_PATH_DATA} $<TARGET_FILE_DIR:shmup>/${APPLICATION_PATH_DATA}
)
