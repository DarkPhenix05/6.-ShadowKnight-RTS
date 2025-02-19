#include "Character.h"
#pragma once

Character::Character(CharacterType _unitType, Vector2 pos, int sice) 
	:GameObject(pos)
{
	unitType = _unitType;
	unitState = CharacterState::WAITING;
	
	_pos.x = pos.x;
	_pos.y = pos.y;
	_sice = sice;

	BT_MOVE = new Button(5, 205, 90, 45, "MOVE", 20, GRAY, BLACK,
		LIGHTGRAY, BLACK, WHITE, GRAY, RED, BLACK);
	BT_ATTACK = new Button(105, 205, 90, 45, "ATTACK", 20, GRAY, BLACK,
		LIGHTGRAY, BLACK, WHITE, GRAY, RED, BLACK);
	BT_CANCEL = new Button(5, 255, 90, 45, "CANCEL", 20, GRAY, BLACK,
		LIGHTGRAY, BLACK, WHITE, GRAY, RED, BLACK);

	switch (unitType)
	{
	case CharacterType::WARRIOR:
		_sprite = LoadTexture("data/knight.png");
		_HP = 10;
		_atk = 5;
		_def = 5;
		_moveSpeed = 2.0f;
		break;
	case CharacterType::DEFENDER:
		_sprite = LoadTexture("data/magician.png");
		_HP = 8;
		_atk = 5;
		_def = 5;
		_moveSpeed = 2.0f;
		break;
	case CharacterType::BUILDER:
		_sprite = LoadTexture("data/man.png");
		_HP = 8;
		_atk = 5;
		_def = 5;
		_moveSpeed = 2.0f;
		break;
	default:
		_sprite = LoadTexture("data/ghost.png");
		_HP = 8;
		_atk = 5;
		_def = 5;
		_moveSpeed = 2.0f;
		break;
	}
}

Character::~Character()
{
}

void Character::Update(float& DT)
{
	if (!points.empty())
	{
		GetMoveVal();
		Move(_movingTo.x * (DT * _moveSpeed), _movingTo.y * (DT * _moveSpeed));

		std::cout << GetDistance(_movingTo.x, _movingTo.y) << std::endl;
		
		if (GetDistance(_PointPos.x, _PointPos.y) <= 1)
		{
			points.pop_back();
		}
	}

	SetPosition(_pos);
}

void Character::Move(float x, float y)
{
	_pos.x += x;
	_pos.y += y;
}

void Character::UpdatePos(float x, float y)
{
	_pos.x = x;
	_pos.y = y;
}

void Character :: GetMoveVal()
{
	std::string point = points.back();
	int comma = point.find(","); //Lo pasa a su valor ALFA NUMERICO
	_PointPos.x = std::stoi(point.substr(0, comma)); // STOI = Strin to int    //SUBSTR = Substraer caracteres entre
	_PointPos.y = std::stoi(point.substr(comma + 1, point.length() - 1));

	_PointPos.x += 6.2f;
	_PointPos.y += 6.2f;

	_movingTo.x = _PointPos.x - _pos.x;
	_movingTo.y = _PointPos.y - _pos.y;

	std::cout << point << std::endl;
}

float Character::GetDistance(int x, int y)
{
	float xD = _pos.x - x;
	float yD = _pos.y - y;

	return sqrt((xD * xD) + (yD * yD));
}

std::list<std::string> Character::GetPoints()
{
	return points;
}

void Character::SetPoints(std::list<std::string> pathFound)
{
	points = pathFound;
}

void Character::UpdateInputs(Vector2 mouse_pos)
{
	BT_MOVE->Update(mouse_pos);
	BT_ATTACK->Update(mouse_pos);
	BT_CANCEL->Update(mouse_pos);
}

void Character::Draw(bool cur)
{
	if (cur)
	{
		DrawTextureEx(_sprite,_pos, 0, 1, WHITE);
	}
	else
	{
		DrawTextureEx(_sprite,_pos, 0, 1, GRAY);
	}
}

void Character::DrawButtons()
{
	BT_MOVE->Draw();
	BT_ATTACK->Draw();
	BT_CANCEL->Draw();
}
