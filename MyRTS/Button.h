#include <iostream>
#include "raylib.h"
#pragma once

enum BUTTONSTATE{BTN_INDDLE = 0, BTN_PRESS, BTN_HOVER, BTN_UNACTIVE};

class Button
{
private:
	short unsigned buttonState;
	Vector2 position;
	float width;
	float height;
	std::string text;
	unsigned charSize;

	Color CurrentColor;
	Color CurrentText;

	Color IddleColor;
	Color IddleText;

	Color HoverColor;
	Color HoverText;

	Color PressColor;
	Color PressText;

	Color UnactiveColor;
	Color UnactiveText;

public:
	Button();

	Button(int x, int y, float width, float height,
		std::string text, unsigned charSize, 
		Color iddleColor, Color iddleText, 
		Color hoverColor, Color hoverText,
		Color pressColor, Color pressText,
		Color unactiveColor, Color unactiveText);
	~Button();

	void Update(Vector2 mousePos);

	void Draw();

	const bool GetButtonPress();
};

