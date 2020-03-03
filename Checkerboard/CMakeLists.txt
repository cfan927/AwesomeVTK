cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(Checkerboard)
set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR})

#VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(srcs
	main.cpp
)

set(hdrs
)

add_executable(${PROJECT_NAME} ${srcs} ${hdrs})

target_link_libraries(${PROJECT_NAME}
	${VTK_LIBRARIES}
)

