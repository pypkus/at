cmake_minimum_required(VERSION 3.10)

project(at_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	test.cpp
)

target_link_libraries(${PROJECT_NAME}
PRIVATE 
	at
)