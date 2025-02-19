#include "raylib.h"
#include "GameObject.h"
#include "Button.h"
#include "list"
#include "string"

#pragma once

enum class CharacterType {
	WARRIOR,
	DEFENDER,
	BUILDER
};

enum class CharacterState {
	WAITING,
	WALKING,
	WORKING,
	ATTACKING,
	TAKINGDAMAGE
};

class Character :public GameObject
{
public:
	Character(CharacterType _unitType, Vector2 pos, int sice);

	~Character();

	void Update(float& DT) override;

	void Move(float x, float y);

	void UpdatePos(float x, float y);

	void Draw(bool cur) override;

	void DrawButtons();

	void GetMoveVal();

	float GetDistance(int x, int y);

	std::list<std::string> GetPoints();

	void SetPoints(std::list<std::string> pathFound);

	void UpdateInputs(Vector2 mouse_pos);


	Button* BT_MOVE;
	Button* BT_ATTACK;
	Button* BT_CANCEL;

private:
	CharacterType unitType;
	CharacterState unitState;
	Texture2D _sprite;
	
	Vector2 _PointPos;
	Vector2 _movingTo;
	std::list<std::string> points;
	
	int _HP = 0;
	int _atk = 0;
	int _def = 0;
	float _moveSpeed = 2;

public:
	Vector2 _pos;
	float _sice;
};

