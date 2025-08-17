#ifndef TILE_H
#define TILE_H

class Tile {
    
    public:
    Tile(int tileX, int tileY, int size);

    int getTileX() const;
    int getTileY() const;


    int getWorldX() const;
    int getWorldY() const;
    
    int getScreenX() const;
    int getScreenY() const;

    bool isBlocked() const;

    static Tile worldToTile(int worldX, int worldY, int size);
    static int worldToTileX(int worldX, int size);
    static int worldToTileY(int worldY, int size);
    
    static int tileToWorldX(Tile& t);
    static int tileToWorldY(Tile& t);

    bool operator==(const Tile& other){
        return x = other.x && y == other.y;
    }

    private:
    int x, y;
    int size;
    bool blocked;
};

#endif