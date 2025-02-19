#include "string"
#include "Tile.h"
#include "map"

class Map
{
public:

    std::map<string, Tile*> map;

    Map() 
    {

    }
    ~Map()
    {

    }

    void GenerateGrid(int gridHeight, int gridWidth, int cellHeight, int cellWidth, int WallCount)
    {
        string tilePos;
        for (int x = 0; x < gridHeight; x += 1)
        {
            for (int y = 0; y < gridWidth; y += 1)
            {
                tilePos = std::to_string(x * cellWidth) + "," + std::to_string(y * cellHeight);

                map[tilePos] = new Tile(x * cellWidth, y * cellHeight, false ,cellWidth,cellHeight);
            }
        }

        srand(time(0));

        //WALLS
        for (int w = 0; w < WallCount; w++)
        {
            string pos;


            int randX = (rand() % gridWidth);
            int randY = (rand() % gridHeight);

            int posX = (randX * cellWidth);
            int posY = (randY * cellHeight);

            pos = std::to_string(posX) + "," + std::to_string(posY);
            map[pos]->isWall = true;
            cout << pos << "\n";
        }
    }

    void Draw()
    {
        for (auto temp : map)
        {
            temp.second->Draw();
        }
    }

    std::map<std::string, Tile*> GetMap()
    {
        return map;
    }
};