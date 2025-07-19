cmake_minimum_required(VERSION 3.10.0)
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
 src/Ashborne.cpp
 src/Ashborne.h
 src/TextureManager.cpp
 src/TextureManager.h
 src/Tilemap.cpp
 src/Tilemap.h
 src/character/Player.cpp
 src/character/Player.h
 src/utils/Logger.h
 src/utils/Config.cpp
 src/utils/Config.h
 src/utils/Text.cpp
 src/utils/Text.h
 src/scenes/SceneManager.cpp
 src/scenes/SceneManager.h
 src/scenes/SceneHolder.cpp
 src/item/Inventory.cpp
 src/item/Inventory.h
 src/item/ItemHolder.cpp
 src/item/ItemHolder.h
 src/alg/Vector.h
 src/alg/Vector.cpp
 src/entity/Entity.h
 src/entity/Entity.cpp
 src/entity/EntityHolder.h
 src/entity/Animation.h
 src/entity/Animation.cpp
 )

target_link_libraries(Ashborne
    ${SDL2_LIBRARIES}
    SDL2_image
    ${SDL2_TTF_LIBRARIES}
)

add_custom_command(TARGET Ashborne POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Ashborne>/assets)
