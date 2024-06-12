cmake_minimum_required(VERSION 3.28)

project(storage_engines LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_subdirectory(third_party)
add_subdirectory(src)

