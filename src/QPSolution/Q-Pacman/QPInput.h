#pragma once

#include <cstdint>

/*
* They are 10 recognized inputs, not all are mapped a an action yet
* Keypas from 1 to 9 are valid inputs
* Keypad 0 is a special input (for now it send a reset signal so pressed key can be reset)
* No multi-input yet, but strickly speaking code allows it
* Current mapping:
*	5 -> Hadamar 
*	2 -> Inverse
*	4 -> Turn Left
*	6 -> Turn RIght
*   1 -> swap
*   0 -> reset
*/

// REMINDER: For each new input, you have to add the corresponding code in the ghost AI (Ghosts.cpp)

class QPInput
{
public:
	//Statics
	static const uint16_t KEY_0 = 0x0000; //0 is special and has a value of 0
	static const uint16_t KEY_1 = 0x0001;
	static const uint16_t KEY_2 = 0x0002;
	static const uint16_t KEY_3 = 0x0004;
	static const uint16_t KEY_4 = 0x0008;
	static const uint16_t KEY_5 = 0x0010;
	static const uint16_t KEY_6 = 0x0020;
	static const uint16_t KEY_7 = 0x0040;
	static const uint16_t KEY_8 = 0x0080;
	static const uint16_t KEY_9 = 0x0100;

	//Locals
	QPInput();
	~QPInput();

	void inputEvent(uint16_t keyFlag);

	//getter
	bool isKeyPressed(uint16_t keyFlag) const;
	bool isKey1Pressed() const;
	bool isKey2Pressed() const;
	bool isKey3Pressed() const;
	bool isKey4Pressed() const;
	bool isKey5Pressed() const;
	bool isKey6Pressed() const;
	bool isKey7Pressed() const;
	bool isKey8Pressed() const;
	bool isKey9Pressed() const;

private:
	uint16_t keysState;
};