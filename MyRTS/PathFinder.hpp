#include "raylib.h"
#include "list"
#include "map"
#include "Tile.h"
#pragma once

class PathFinder
{
public:
    int GridHeight = 0;
    int GridWidth = 0;
    int cellHeight = 0;
    int cellWidth = 0;


    bool generatePath;
    bool visualiceGrid;
    bool pathGenerated;


    Vector2 curPos;
    Vector2 endPos;

    std::map<string, Tile*> Tiles; //MAPA

    Vector2 connection; //Saber con cual se conecta
    bool isWall;

    std::list<string> cellsToSearch;
    std::list<string> cellsSearched;
    std::list<string> findPath;
    Vector2 cellPos;
    Vector2 point1;
    Vector2 point2;

public:
    PathFinder(int Gheight, int Gwith, int height, int with)
    {
        GridWidth = Gwith;
        GridHeight = Gheight;
        cellHeight = height;
        cellWidth = with;
    }

    ~PathFinder()
    {

    }

    void GetMap(std::map<string, Tile*> map)
    {
        Tiles = map;
    }

    void ClearMap()
    {
        for (std::map<std::string, Tile*>::iterator it = Tiles.begin(); it != Tiles.end(); ++it)
        {
            it->second->SetGcos(std::numeric_limits<int>::max());
            it->second->SetHcos(std::numeric_limits<int>::max());
            it->second->SetFcos();

            it->second->SetConection({ -1,-1 });
        }
    }

    void FindPath(Vector2 startPos, Vector2 endPos)
    {
        //LIMPIAR LISTAS
        this->cellsToSearch.clear();
        this->cellsSearched.clear();
        this->findPath.clear();

        //ROUND PLAYER POS
        startPos.x = (int(round(startPos.x / cellWidth)) * cellWidth);
        startPos.y = (int(round(startPos.y / cellHeight)) * cellHeight);

        endPos.x = (int(round(endPos.x / cellWidth)) * cellWidth);
        endPos.y = (int(round(endPos.y / cellHeight)) * cellHeight);

        
        string _startPos = std::to_string(static_cast<int>(startPos.x)) + "," + std::to_string(static_cast<int>(startPos.y));
        string _endPos = std::to_string(static_cast<int>(endPos.x)) + "," + std::to_string(static_cast<int>(endPos.y));

        this->cellsToSearch.push_back(_startPos);


        Tile* startCell = Tiles[_startPos];
        startCell->gCost = 0;
        startCell->hCost = GetDistance(startPos, endPos);
        startCell->fCost = GetDistance(startPos, endPos);

        std::string currentCell = cellsToSearch.front();

        while (cellsToSearch.size() > 0)
        {
            currentCell = cellsToSearch.front();
            for (auto pos : cellsToSearch)
            {
                Tile* c = Tiles[pos];
                if (c->fCost < Tiles[currentCell]->fCost ||
                    c->fCost == Tiles[currentCell]->fCost && c->hCost < Tiles[currentCell]->hCost)
                {
                    currentCell = pos;
                }
            }
            cellsToSearch.remove(currentCell);
            cellsSearched.push_back(currentCell);
            if (Tiles[currentCell]->position.x == endPos.x && 
                Tiles[currentCell]->position.y == endPos.y)
            {
                Tile* pathCell = Tiles[_endPos];
                while (pathCell->position.x != startPos.x &&
                    pathCell->position.y != startPos.y)
                {
                    std::string tempstr = to_string((int)pathCell->connection.x) + "," + to_string((int)pathCell->connection.y);
                    findPath.push_back(tempstr);
                    pathCell = Tiles[tempstr];
                }
                findPath.push_back(_startPos);
                return;
            }
            Vector2 serchCellNeighbors = Tiles[currentCell]->position;
            SearchNeighborCells(serchCellNeighbors, endPos);
        }
    }

    void SearchNeighborCells(Vector2 cellPos, Vector2 endPos)
    {
        //BUSCO LOS VECINOS
        for (int x = cellPos.x - cellWidth;
            x <= cellWidth + cellPos.x; x += cellWidth)
        {
            for (int y = cellPos.y - cellHeight;
                y <= cellHeight + cellPos.y; y += cellHeight)
            {
                std::string neighbors = std::to_string(x) + "," + std::to_string(y);
                Vector2 neighbourPos{ x, y };

                if (Tiles.find(neighbors) != Tiles.end() &&
                    !Tiles[neighbors]->isWall)
                {
                    auto f = std::find(cellsSearched.begin(), cellsSearched.end(), neighbors);
                    if (f != cellsSearched.end())
                    {
                        continue;
                    }
                    else
                    {
                        string tempstr = std::to_string((int)cellPos.x) + "," + to_string((int)cellPos.y);
                        int gCostNeighbor = Tiles[tempstr]->gCost + GetDistance(cellPos, neighbourPos);

                        if (gCostNeighbor < Tiles[neighbors]->gCost)
                        {
                            Tile* node = Tiles[neighbors];
                            node->connection = cellPos;
                            node->SetGcos(gCostNeighbor);
                            node->SetHcos(GetDistance(neighbourPos, endPos));
                            node->SetFcos();


                            auto f = std::find(cellsToSearch.begin(), cellsToSearch.end(), neighbors);
                            if (f != cellsToSearch.end())
                            {
                                continue;
                            }
                            else
                            {
                                cellsToSearch.push_back(neighbors);
                            }
                        }
                    }
                }
            }
        }
    }

    int GetDistance(Vector2 point1, Vector2 point2)
    {
        Vector2 dist = { abs(point1.x - point2.x), abs(point1.y - point2.y) };

        int lowest = std::min(dist.x, dist.y);
        int higest = std::max(dist.x, dist.y);
        int horizontalMove = higest - lowest;

        return lowest * 12 + horizontalMove * 10;
    }

    std::list<std::string> GeneratePath(Vector2 startPos, Vector2 endPos)
    {
        endPos.x = (int(round(endPos.x / cellWidth)) * cellWidth);
        endPos.y = (int(round(endPos.y / cellHeight)) * cellHeight);
        FindPath(startPos, endPos);
        return findPath;
    }

    std::list<std::string> GetPath()
    {
        return findPath;
    }
};

