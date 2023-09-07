#include "Message.h"

Message::Message(const char* text, float posX, float posY, float colorRed, float colorGreen, float colorBlue) {
	this->text = text;
	this->posX = posX;
	this->posY = posY;
	this->colorRed = colorRed;
	this->colorGreen = colorGreen;
	this->colorBlue = colorBlue;
}


const char* Message::getText() {
	return text;
}

void Message::setText(const char* newText) {
	text = newText;
}


float Message::getPosX() {
	return posX;
}

float Message::getPosY() {
	return posY;
}


float Message::getColorRed() {
	return colorRed;
}

float Message::getColorGreen() {
	return colorGreen;
}

float Message::getColorBlue() {
	return colorBlue;
}
