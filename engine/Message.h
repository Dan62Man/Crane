#pragma once
#include "LibraryInfo.h"
#include <string>

using namespace std;

class ENGINE_API Message
{
public:
	Message(const char* text, float posX, float posY, float colorRed = 0.0f, float colorGreen = 0.0f, float colorBlue = 0.0f);
	const char* getText();
	void setText(const char* newText);
	float getPosX();
	float getPosY();
	float getColorRed();
	float getColorGreen();
	float getColorBlue();

private:
	const char* text;
	float posX;
	float posY;
	float colorRed;
	float colorGreen;
	float colorBlue;
};

