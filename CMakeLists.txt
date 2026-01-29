cmake_minimum_required(VERSION 4.1.2)
set(CMAKE_CXX_COMPILER g++)
project(Ashborne VERSION 0.1.0 LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3 REQUIRED sdl3)
pkg_check_modules(SDL3_IMAGE REQUIRED sdl3-image)
pkg_check_modules(SDL3_TTF REQUIRED sdl3-ttf)

include_directories(
    ${SDL3_INCLUDE_DIRS}
    /usr/include/SDL3
    ${SDL3_TTF_INCLUDE_DIRS}
    /usr/include/SDL3_ttf      
)

add_executable(Ashborne
 src/main.cpp
 src/ashborne.cpp
 src/utils/error_handler.cpp
 src/utils/log.cpp
 src/utils/config.cpp
 )

target_link_libraries(Ashborne
    ${SDL3_LIBRARIES}
    ${SDL3_IMAGE_LIBRARIES}
    ${SDL3_TTF_LIBRARIES}
)

add_custom_command(TARGET Ashborne POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Ashborne>/assets)

add_custom_command(TARGET Ashborne POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Ashborne>/resources)
