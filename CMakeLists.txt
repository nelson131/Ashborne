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
 src/Camera.h
 src/Camera.cpp
 src/character/Player.cpp
 src/character/Player.h
 src/utils/Logger.h
 src/utils/Config.cpp
 src/utils/Config.h
 src/utils/Text.cpp
 src/utils/Text.h
 src/utils/Cursor.h
 src/utils/Cursor.cpp
 src/utils/Tile.cpp
 src/utils/Tile.h
 src/utils/Timer.h
 src/utils/Timer.cpp
 src/scenes/SceneManager.cpp
 src/scenes/SceneManager.h
 src/item/Inventory.cpp
 src/item/Inventory.h
 src/item/ItemHolder.cpp
 src/item/ItemHolder.h
 src/alg/Vector.h
 src/alg/Vector.cpp
 src/entity/Entity.h
 src/entity/Entity.cpp
 src/entity/EntityHolder.h
 src/entity/EntityHolder.cpp
 src/entity/Animation.h
 src/entity/Animation.cpp
 src/entity/Npc.cpp
 src/entity/Npc.h
 src/entity/Behavior.cpp
 src/entity/Behavior.h
 src/entity/Attributes.cpp
 src/entity/Attributes.h
 src/entity/Vision.cpp
 src/entity/Vision.h
 src/ui/UI.cpp
 src/ui/UI.h
 src/ui/UIManager.cpp
 src/ui/UIManager.h
 )

target_link_libraries(Ashborne
    ${SDL2_LIBRARIES}
    SDL2_image
    ${SDL2_TTF_LIBRARIES}
)

add_custom_command(TARGET Ashborne POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Ashborne>/assets)

add_custom_command(TARGET Ashborne POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Ashborne>/resources)