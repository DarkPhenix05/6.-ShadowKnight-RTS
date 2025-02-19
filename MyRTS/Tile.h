#include <string>
#include "raylib.h"
#include "random"
#include "list"
#include "map"
#include <limits>
#pragma once

using namespace std;
class Tile
{
public:
	Tile(int x, int y, bool isWall, int _with, int _height);
	Tile(int x, int y);
	void Draw();

	~Tile();

	void SetGcos(int g);
	void SetHcos(int h);
	void SetFcos();

	void SetConection(Vector2 connection);
    
   
public:
	int with;
	int height;
	bool isWall;
	Vector2 position;
	Vector2 connection;
	int GridHeight;
	int GridWidth;
	std::map<string, Tile>* Tiles;

	Color groundColor;

	int gCost; //Cuanto me alejo, cuanto llevo
	int hCost; //Cuanto me acerco, cuanto me falta
	int fCost; //Suma de los dos anteriores
};