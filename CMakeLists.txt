cmake_minimum_required(VERSION 3.10)

project(at)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_library(${PROJECT_NAME} STATIC)
add_library(${NAMESPACE_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	src/file_service.cpp
	src/service.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC 
${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(test)