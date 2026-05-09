cmake_minimum_required(VERSION 3.20)
project(hegemon_v0.0.1)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/cmake")

find_package(SDL3 REQUIRED)

#add_executable(hegemon_v0_0_1 WIN32 src/main.cpp
add_executable(hegemon_v0_0_1 src/main.cpp
        src/core/save.cpp
        include/core/save.h
        include/map/map.h
        src/map/map.cpp)


target_include_directories(hegemon_v0_0_1 PRIVATE include)
target_link_libraries(hegemon_v0_0_1 PRIVATE SDL3::SDL3)
#target_link_options(hegemon_v0_0_1 PRIVATE -static-libgcc -static-libstdc++ -static)

add_custom_command(TARGET hegemon_v0_0_1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:hegemon_v0_0_1>
)

