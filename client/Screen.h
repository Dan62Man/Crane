#pragma once
#include "engine.h"
#include "TypeSelected.h"
#include "Message.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

class Screen
{
public:
	Screen();
	~Screen();

	list<Message> updateAndGetText(TypeSelected type, Node* currentObj=nullptr);

private:
	list<Message> messages;

	float posX = 10.0f;
	float posY_original = 340.0f;
	static float posY;
	float distance = 20.0f;

	void defaultText();
	void separator();
	void cameraText(Node* currentObj);
	void modelText();
};

