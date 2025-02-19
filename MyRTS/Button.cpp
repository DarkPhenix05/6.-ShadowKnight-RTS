#include "Button.h"

Button::Button()
{
}

Button::Button(int x, int y, float width, float height, std::string text, 
	unsigned charSize, Color iddleColor, Color iddleText,
	Color hoverColor, Color hoverText,
	Color pressColor, Color pressText,
	Color unactiveColor, Color unactiveText)
{
	//COLORS SET
	this->IddleColor = iddleColor;
	this->IddleText = iddleText;

	this->HoverColor = hoverColor;
	this->HoverText = hoverText;

	this->PressColor = pressColor;
	this->PressText = pressText;

	this->UnactiveColor = unactiveColor;
	this->UnactiveText = unactiveText;

	//TRANSFORM SET
	this->position.x = x;
	this->position.y = y;

	this->width = width;
	this->height = height;

	//TEXT
	this->text = text;
	this->charSize = charSize;

	this->CurrentColor = iddleColor;
	this->CurrentText = iddleText;
}

Button::~Button()
{
}

void Button::Update(Vector2 mousePos)
{
	buttonState = BTN_INDDLE;
	if (mousePos.x > position.x &&
		mousePos.x < position.x + width &&
		mousePos.y < position.y + height &&
		mousePos.y > position.y)
	{
		buttonState = BTN_HOVER;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			buttonState = BTN_PRESS;
		}
	}

	switch (buttonState)
	{
	case BTN_INDDLE:
		CurrentColor = IddleColor;
		CurrentText = IddleText;
		break;

	case BTN_HOVER:
		CurrentColor = HoverColor;
		CurrentText = HoverText;
		break;

	case BTN_PRESS:
		CurrentColor = PressColor;
		CurrentText = PressText;
		break;

	case BTN_UNACTIVE:
		CurrentColor = UnactiveColor;
		CurrentText = UnactiveText;
		break;

	default:
		CurrentColor = IddleColor;
		CurrentText = IddleText;
	}
}

void Button::Draw()
{
	DrawRectangle(position.x, position.y, width, height, CurrentColor);
	DrawText(text.c_str(), position.x, position.y, charSize, CurrentText);
}

const bool Button::GetButtonPress()
{
	if (buttonState == BTN_PRESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}
