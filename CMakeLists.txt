cmake_minimum_required(VERSION 3.20)
project(hegemon_v0_0_1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/cmake")

find_package(SDL3 REQUIRED)

#add_executable(hegemon_v0_0_1 WIN32 src/main.cpp
add_executable(hegemon_v0_0_1 WIN32
        src/main.cpp
        src/core/save.cpp
        src/map/map.cpp
        include/core/save.h
        include/map/map.h
)

target_include_directories(hegemon_v0_0_1 PRIVATE include)
target_link_libraries(hegemon_v0_0_1 PRIVATE SDL3::SDL3)
if (CMAKE_BUILD_TYPE STREQUAL "Release")

    # максимальная оптимизация размера
    target_compile_options(hegemon_v0_0_1 PRIVATE
            -Os
            -ffunction-sections
            -fdata-sections
    )

    target_link_options(hegemon_v0_0_1 PRIVATE
            -Wl,--gc-sections
            -s
            -static-libgcc
            -static-libstdc++
            -static
    )

endif()
add_custom_command(TARGET hegemon_v0_0_1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL3/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:hegemon_v0_0_1>
)