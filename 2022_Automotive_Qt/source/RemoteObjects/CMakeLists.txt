cmake_minimum_required(VERSION 3.16)

project(RemoteObjects VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_custom_target(rep_file ALL
    SOURCES
		car.rep
)

add_subdirectory(Source)
add_subdirectory(Replica)
