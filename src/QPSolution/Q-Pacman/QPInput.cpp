#include "QPInput.h"

QPInput::QPInput()
	: keysState(0)
{
}

QPInput::~QPInput()
{
}

//if isPressed is false, then the key is was released
void QPInput::inputEvent(uint16_t keyFlag)
{
	if (keyFlag == KEY_0) keysState = KEY_0; //Wipe clean input
	else keysState = keyFlag; //No Multiple Input yet

}

bool QPInput::isKeyPressed(uint16_t keyFlag) const
{
	if ((keysState & keyFlag) > 0) return true;
	else return false;
}

bool QPInput::isKey1Pressed() const
{
	return isKeyPressed(KEY_1);
}

bool QPInput::isKey2Pressed() const
{
	return isKeyPressed(KEY_2);
}

bool QPInput::isKey3Pressed() const
{
	return isKeyPressed(KEY_3);
}

bool QPInput::isKey4Pressed() const
{
	return isKeyPressed(KEY_4);
}

bool QPInput::isKey5Pressed() const
{
	return isKeyPressed(KEY_5);
}

bool QPInput::isKey6Pressed() const
{
	return isKeyPressed(KEY_6);
}

bool QPInput::isKey7Pressed() const
{
	return isKeyPressed(KEY_7);
}

bool QPInput::isKey8Pressed() const
{
	return isKeyPressed(KEY_8);
}

bool QPInput::isKey9Pressed() const
{
	return isKeyPressed(KEY_9);
}


