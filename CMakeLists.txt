cmake_minimum_required(VERSION 4.1.2)
set(CMAKE_CXX_COMPILER g++)
project(Ashborne VERSION 0.1.0 LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    /usr/include/SDL2
    ${SDL2_TTF_INCLUDE_DIRS}
    /usr/include/SDL2_ttf      
)

add_executable(Ashborne
 src/main.cpp
 src/ashborne.cpp
 src/utils/error_handler.cpp
 src/utils/log.cpp
 src/utils/config.cpp
 )

target_link_libraries(Ashborne
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)

add_custom_command(TARGET Ashborne POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Ashborne>/assets)

add_custom_command(TARGET Ashborne POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Ashborne>/resources)
