cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_COMPILER g++)
project(Ashborne VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    /usr/include/SDL2      
)

add_executable(Ashborne
 src/main.cpp
 src/Ashborne.cpp
 src/Ashborne.h
 src/TextureManager.cpp
 src/TextureManager.h
 src/character/Player.cpp
 src/character/Player.h
 src/utils/Logger.cpp
 src/utils/Logger.h
 src/utils/Config.cpp
 src/utils/Config.h
 )

target_link_libraries(Ashborne
    ${SDL2_LIBRARIES}
    SDL2_image
)

add_custom_command(TARGET Ashborne POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Ashborne>/assets)
