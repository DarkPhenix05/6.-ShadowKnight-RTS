#include "GameObject.h"

GameObject::GameObject(Vector2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
	IsVisible = true;
}

GameObject::~GameObject()
{

}

void GameObject::Update(float& DT)
{
}
