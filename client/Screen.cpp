#include "Screen.h"

float Screen::posY;

Screen::Screen() { }

Screen::~Screen()
{
	cout << "[Destroyed SCREEN]" << endl;
}

list<Message> Screen::updateAndGetText(TypeSelected type, Node* currentObj)
{
	messages.clear();
	posY = posY_original;
	separator();

	defaultText();

	if (type == TypeSelected::CAMERA)
		cameraText(currentObj);

	else if (type == TypeSelected::MODEL)
		modelText();

	separator();
	
	return messages;
}

void Screen::defaultText()
{
	Message cullFace = Message((char*)"F1: enable/disable cull face", posX, posY);
	messages.push_back(cullFace);
	posY -= distance;

	Message wireframe = Message((char*)"F2: enable/disable wireframe", posX, posY);
	messages.push_back(wireframe);
	posY -= distance;

	Message changeType = Message((char*)"TAB: change type of object", posX, posY);
	messages.push_back(changeType);
	posY -= distance;

	Message changeObject = Message((char*)" . : change object selected", posX, posY);
	messages.push_back(changeObject);
	posY -= distance;
}

void Screen::separator()
{
	Message separator = Message((char*)"---------------------", posX, posY, 1.0f);
	messages.push_back(separator);
	posY -= distance;

}

void Screen::cameraText(Node* currentObj)
{
	Message typeObj = Message((char*)"Selected: [Camera]", posX, posY, 1.0f);
	messages.push_back(typeObj);
	posY -= distance;

	string tempNameObj = "Object: [" + currentObj->getName() + "]";
	char* text = new char[tempNameObj.length() + 1];
	std::strcpy(text, tempNameObj.c_str());
	Message nameObj = Message(text, posX, posY, 1.0f);
	messages.push_back(nameObj);
	posY -= distance;

	PerspectiveCamera* camera = dynamic_cast<PerspectiveCamera*>(currentObj);
	if (camera->getType() == CameraType::CABIN)
	{
		Message up = Message((char*)"W: up", posX, posY);
		messages.push_back(up);
		posY -= distance;

		Message down = Message((char*)"S: down", posX, posY);
		messages.push_back(down);
		posY -= distance;

		Message left = Message((char*)"A: left", posX, posY);
		messages.push_back(left);
		posY -= distance;

		Message right = Message((char*)"D: right", posX, posY);
		messages.push_back(right);
		posY -= distance;
	}

	if (camera->getType() == CameraType::DYNAMIC)
	{
		Message up = Message((char*)"W: up", posX, posY);
		messages.push_back(up);
		posY -= distance;

		Message down = Message((char*)"S: down", posX, posY);
		messages.push_back(down);
		posY -= distance;

		Message left = Message((char*)"A: left", posX, posY);
		messages.push_back(left);
		posY -= distance;

		Message right = Message((char*)"D: right", posX, posY);
		messages.push_back(right);
		posY -= distance;

		Message forward = Message((char*)"Q: forward", posX, posY);
		messages.push_back(forward);
		posY -= distance;

		Message backward = Message((char*)"E: backward", posX, posY);
		messages.push_back(backward);
		posY -= distance;

		Message mouse = Message((char*)"MOUSE: change of viewing point", posX, posY);
		messages.push_back(mouse);
		posY -= distance;
	}
}

void Screen::modelText()
{
	Message typeObj = Message((char*)"Selected: [Model]", posX, posY, 1.0f);
	messages.push_back(typeObj);
	posY -= distance;

	Message nameObj = Message((char*)"Object: [Crane]", posX, posY, 1.0f);
	messages.push_back(nameObj);
	posY -= distance;

	Message raise = Message((char*)"W: raise the hook", posX, posY);
	messages.push_back(raise);
	posY -= distance;

	Message lower = Message((char*)"S: lower the hook", posX, posY);
	messages.push_back(lower);
	posY -= distance;

	Message left = Message((char*)"A: rotate to the left", posX, posY);
	messages.push_back(left);
	posY -= distance;

	Message right = Message((char*)"D: rotate to the right", posX, posY);
	messages.push_back(right);
	posY -= distance;

	Message forward = Message((char*)"Q: move the carriage forward", posX, posY);
	messages.push_back(forward);
	posY -= distance;

	Message backward = Message((char*)"E: move the carriage backward", posX, posY);
	messages.push_back(backward);
	posY -= distance;

	Message grabdrop = Message((char*)"SPACE: grab/drop object", posX, posY);
	messages.push_back(grabdrop);
	posY -= distance;

	Message mouse = Message((char*)"MOUSE: change of viewing point", posX, posY);
	messages.push_back(mouse);
	posY -= distance;

	Message mouse2 = Message((char*)"(only for dynamic camera view)", posX, posY);
	messages.push_back(mouse2);
	posY -= distance;
}
