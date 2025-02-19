#include "Tile.h"
#include "random"

Tile::Tile(int x, int y, bool isWall, int _with, int _height)
{
    this->position.x = x;
    this->position.y = y;
    this->isWall = isWall;
    this->groundColor = WHITE;
    this->with = _with;
    this->height = _height;

    this->fCost = std::numeric_limits<int>::max();
    this->hCost = std::numeric_limits<int>::max();
    this->gCost = std::numeric_limits<int>::max();
}

Tile::Tile(int x, int y)
{
    this->position.x = x;
    this->position.y = y;

    this->fCost = std::numeric_limits<int>::max();
    this->hCost = std::numeric_limits<int>::max();
    this->gCost = std::numeric_limits<int>::max();
}

Tile::~Tile()
{
}

void Tile::SetGcos(int g)
{
    gCost = g;
}

void Tile::SetHcos(int h)
{
    hCost = h;
}

void Tile::SetFcos()
{
    fCost == gCost + hCost;
}

void Tile::SetConection(Vector2 connection)
{
    this->connection = connection;
}

void Tile::Draw()
{
    if (isWall == false)
    {
        groundColor = GREEN;
    }
    else if (isWall == true)
    {
        groundColor = BLUE;
    }

    DrawRectangle(position.x, position.y, with, height, groundColor);
    DrawRectangleLines(position.x, position.y, with, height, BLACK);
}
