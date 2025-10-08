#include "Tile.h"
#include "../scenes/SceneManager.h"
#include <iostream>
#include <SDL2/SDL.h>

Tile::Tile(int tileX, int tileY, int size)
    : x(tileX), y(tileY), size(size)
{

}

int Tile::getTileX() const{
    return x;
}

int Tile::getTileY() const{
    return y;
}

int Tile::getWorldX() const{
    return x * size;
}

int Tile::getWorldY() const{
    return y * size;
}

bool Tile::isBlocked() const{
    for(TilemapLayer& t : sceneManager.getCurrentScene()->colliders){
        return t.isBlocked(getWorldX(), getWorldY());
    }
    return false;
}

Tile Tile::worldToTile(int worldX, int worldY, int size){
    return Tile(worldX / size, worldY / size, size);
}

int Tile::worldToTileX(int worldX, int size){
    return worldX / size;    
}

int Tile::worldToTileY(int worldY, int size){
    return worldY / size;
}

int Tile::tileToWorldX(Tile& t){
    return t.getWorldX();
}

int Tile::tileToWorldY(Tile& t){
    return t.getWorldY();
}