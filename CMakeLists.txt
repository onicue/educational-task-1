cmake_minimum_required(VERSION 3.10)
project(Project LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES src/main.cpp)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(graphic ${SOURCES})
target_link_libraries(graphic ${GTK3_LIBRARIES})

target_include_directories(graphic PRIVATE ${CMAKE_SOURCE_DIR}/include)
