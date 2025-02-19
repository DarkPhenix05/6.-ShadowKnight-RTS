#pragma once
#include "raylib.h"
#include "list"
#include "Button.h"

class GameObject
{
private:
	Vector2 position;
	bool IsVisible;

public:
	GameObject(Vector2 pos);

	~GameObject();

	virtual void Update(float& DT); //Pasa el UPDATE a los hijos que hereden, este objeto no tiene un update determinado.

	virtual void Draw(bool cur) = 0;

	Vector2 GetPos() { return position; }

	bool GetVisible() { return IsVisible; }

	void SetPosition(Vector2 pos) { position = pos; }

	void SetVisible(bool val) { IsVisible = val; }
};

