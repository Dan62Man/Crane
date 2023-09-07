#include "CraneModel.h"
#include <glm/gtx/string_cast.hpp>
#include <engine.h>


CraneModel::CraneModel(List* renderList)
{
	initializeModel(renderList);
	initializeCameras();
	Engine::setCamera(cameras[0]);
	selected = TypeSelected::CAMERA;
	Engine::updateMessages(screen.updateAndGetText(getTypeSelected(), cameras[0]));
}

CraneModel::~CraneModel()
{
	cout << "[Destroyed CRANE_MODEL]" << endl;
}

void CraneModel::initializeCameras()
{
	PerspectiveCamera* staticCamera1 = new PerspectiveCamera("Front camera (static)", CameraType::STATIC, glm::vec3(0.0f, 19.0f, 100.0f), glm::vec3(0.0f, 21.0f, 55.0f), 45.0f, 0.0f, 1.0f, 150.0f);
	if (staticCamera1->getIsAvailable())
		cameras.push_back(staticCamera1);

	/*
	PerspectiveCamera* staticCamera2 = new PerspectiveCamera("Back camera (static)", CameraType::STATIC, glm::vec3(6.5f, 24.0f, -108.5f), glm::vec3(6.5f, 26.0f, 46.5f), 45.0f, 0.0f, 1.0f, 150.0f);
	if (staticCamera2->getIsAvailable())
		cameras.push_back(staticCamera2);
	
	PerspectiveCamera* staticCamera3 = new PerspectiveCamera("Left camera (static)", CameraType::STATIC, glm::vec3(-102.0f, 17.5f, 3.0f), glm::vec3(257.0f, 21.0f, 3.0f), 45.0f, 0.0f, 1.0f, 150.0f);
	if (staticCamera3->getIsAvailable())
		cameras.push_back(staticCamera3);
	
	PerspectiveCamera* staticCamera4 = new PerspectiveCamera("Right camera (static)", CameraType::STATIC, glm::vec3(102.0f, 17.5f, -3.0f), glm::vec3(-183.5f, 21.0f, 3.0f), 45.0f, 0.0f, 1.0f, 150.0f);
	if (staticCamera4->getIsAvailable())
		cameras.push_back(staticCamera4);
	*/

	PerspectiveCamera* dynamicCamera1 = new PerspectiveCamera("Observer camera (dynamic)", CameraType::DYNAMIC, glm::vec3(10.5f, 2.5f, 42.5f), glm::vec3(10.5f, 4.5f, -2.5f), 40.0f, 0.0f, 1.0f, 100.0f);
	if (dynamicCamera1->getIsAvailable())
		cameras.push_back(dynamicCamera1);
	

	PerspectiveCamera* cabinCamera1 = new PerspectiveCamera("Cabin camera (cabin)", CameraType::CABIN, glm::vec3(6.7f, 42.9f, 1.7f), glm::vec3(-19.034f, 40.177f, 0.009f), 45.0f, 0.0f, 1.0f, 100.0f);
	if (cabinCamera1->getIsAvailable())
		cameras.push_back(cabinCamera1);

	PerspectiveCamera* cabinCamera2 = new PerspectiveCamera("Cabin camera (cabin)", CameraType::CABIN, glm::vec3(6.7f, 42.9f, 1.7f), glm::vec3(-38.5f, 32.0f, 1.0f), 45.0f, 0.0f, 1.0f, 100.0f);
	if (cabinCamera2->getIsAvailable())
		cameras.push_back(cabinCamera2);
	
}

void CraneModel::initializeModel(List* renderList)
{
	this->cabin = renderList->findByName("Cabin");
	this->rotaryMotor = renderList->findByName("RotaryMotor");
	this->carriage = renderList->findByName("Carriage");
	this->delimiter01 = renderList->findByName("Delimiter01");
	this->delimiter02 = renderList->findByName("Delimiter02");
	this->cable = renderList->findByName("Cable");
	this->hook = renderList->findByName("Hook");
	this->plane = renderList->findByName("Plane");

	this->hookBlock = renderList->findByName("HookBlock");
	if (hookBlock != nullptr)
	{
		this->maxHeightHook = hookBlock->getMatrix()[3][1];
		this->minHeightHook = -41.0f;
	}

	this->box01 = renderList->findByName("Box01");
	if (box01 != nullptr)
		grabbable.push_back(box01);
	this->box02 = renderList->findByName("Box02");
	if (box02 != nullptr)
		grabbable.push_back(box02);
	this->box03 = renderList->findByName("Box03");
	if (box03 != nullptr)
		grabbable.push_back(box03);
}

TypeSelected CraneModel::getTypeSelected()
{
	return selected;
}

void CraneModel::changeTypeSelcted()
{
	if (selected == TypeSelected::CAMERA)
	{
		selected = TypeSelected::MODEL;
		Engine::updateMessages(screen.updateAndGetText(selected));
	}
	else if (selected == TypeSelected::MODEL)
	{
		selected = TypeSelected::CAMERA;
		if (cameras.size() == 0)
			changeTypeSelcted();
		Engine::updateMessages(screen.updateAndGetText(selected, cameras.at(cntCamera)));
	}
}

void CraneModel::changeCamera()
{
	cntCamera++;

	if (cntCamera >= cameras.size())
		cntCamera = 0;

	Engine::setCamera(cameras.at(cntCamera));
	Engine::updateMessages(screen.updateAndGetText(selected, cameras.at(cntCamera)));
}

void CraneModel::moveArm(TypeDirection direction)
{
	if (rotaryMotor == nullptr || cabin == nullptr) return;
	
	float angle;

	if (direction == TypeDirection::LEFT)
		angle = -rotationAngle;
	else if (direction == TypeDirection::RIGHT)
		angle = rotationAngle;
	else 
		return;

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	rotaryMotor->setMatrix(rotaryMotor->getMatrix() * rotation);

	for (int i = 0; i < cameras.size(); i++)
	{
		if (cameras[i]->getType() == CameraType::CABIN)
		{
			cameras[i]->setEye(cabin->getWorldMatrix()[3]);
			glm::vec3 newCenter = hook->getWorldMatrix()[3];
			newCenter[1] = cameras[i]->getCenter()[1];
			cameras[i]->setCenter(newCenter);
		}
	}
	
}

void CraneModel::moveCarriage(TypeDirection direction)
{
	if (carriage == nullptr || delimiter01 == nullptr || delimiter02 == nullptr)
		return;

	float speed;

	if (direction == TypeDirection::FORWARD)
		speed = -speedCarriage;
	else if (direction == TypeDirection::BACKWORD)
		speed = speedCarriage;
	else return;

	if (carriage->getMatrix()[3][0] + speed >= delimiter01->getMatrix()[3][0] && carriage->getMatrix()[3][0] + speed <= delimiter02->getMatrix()[3][0])
	{
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(speed, 0.0f, 0.0f));
		carriage->setMatrix(carriage->getMatrix() * translation);
	}

}

void CraneModel::moveHook(TypeDirection direction)
{
	if (cable == nullptr || hookBlock == nullptr) return;

	float speed;

	if (direction == TypeDirection::DOWN)
		speed = -speedHook;
	else if (direction == TypeDirection::UP)
		speed = speedHook;
	else return;


	if (hookBlock->getMatrix()[3][1] + speed >= minHeightHook && hookBlock->getMatrix()[3][1] + speed <= maxHeightHook)
	{
		float startHookBlock_Y = hookBlock->getWorldMatrix()[3][1];
		float startCable_Y = cable->getWorldMatrix()[3][1];

		glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, speed, 0.0f));
		hookBlock->setMatrix(hookBlock->getMatrix() * translation);

		float factor = (hookBlock->getWorldMatrix()[3][1] - startCable_Y) / (startHookBlock_Y - startCable_Y);
		glm::mat4 scaling = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, factor, 1.0f));
		cable->setMatrix(scaling * cable->getMatrix());
	}

}

void CraneModel::grabOrDrop()
{
	if (hook == nullptr || plane ==  nullptr) return;

	if (grabbed == nullptr)
	{
		for (int i = 0; i < grabbable.size(); i++)
		{
			if (glm::distance(hook->getWorldMatrix()[3], grabbable[i]->getWorldMatrix()[3]) <= distanceToGrab)
			{
				grabbed = grabbable[i];
				originalMatrix = grabbable[i]->getMatrix();
				grabbed->setMatrix(glm::mat4(1.0f));
				hook->attachChild(grabbed);
				break;
			}
		}
	}
	else
	{
		bool drop = true;
		for (int i = 0; i < grabbable.size(); i++) {
			if (grabbable[i]->getId() == grabbed->getId())
				continue;
			if (glm::distance(hook->getWorldMatrix()[3], grabbable[i]->getWorldMatrix()[3]) <= distanceToDrop)
				drop = false;
		}

		if (drop) {
		glm::mat4 matrix = grabbed->getWorldMatrix();
		matrix[3][1] = originalMatrix[3][1];
		grabbed->setMatrix(matrix);
			hook->detachChild(grabbed);		
			grabbed = nullptr;
		}
		else {
			cout << "Not possible: you cannot drop the object here" << endl;
		}
	}
}

void CraneModel::moveCamera(TypeDirection direction) {
	PerspectiveCamera* currentCamera = cameras.at(cntCamera);
	glm::vec3 eye = currentCamera->getEye();
	glm::vec3 center = currentCamera->getCenter();

	if (currentCamera->getType() == CameraType::DYNAMIC) {
		if (direction == TypeDirection::UP) {
			eye[1] += speedCamera;
			center[1] += speedCamera;
		}
		else if (direction == TypeDirection::DOWN) {
			eye[1] -= speedCamera;
			center[1] -= speedCamera;
		}
		else if (direction == TypeDirection::RIGHT) {
			eye[0] += speedCamera;
			center[0] += speedCamera;
		}
		else if (direction == TypeDirection::LEFT) {
			eye[0] -= speedCamera;
			center[0] -= speedCamera;
		}
		else if (direction == TypeDirection::BACKWORD) {
			eye[2] += speedCamera;
			center[2] += speedCamera;
		}
		else if (direction == TypeDirection::FORWARD) {
			eye[2] -= speedCamera;
			center[2] -= speedCamera;
		}
		else 
			return;
	}
	else if (currentCamera->getType() == CameraType::CABIN) {
		if (direction == TypeDirection::UP)
			center[1] += speedCamera;
		else if (direction == TypeDirection::DOWN)
			center[1] -= speedCamera;
/*		else if (direction == TypeDirection::LEFT)
			center[2] += speedCamera;
		else if (direction == TypeDirection::RIGHT) 
			center[2] -= speedCamera; */
		else 
			return;
	}
	currentCamera->setEye(eye);
	currentCamera->setCenter(center);
}

void CraneModel::moveViewingPointCamera(int x, int y)
{
	PerspectiveCamera* currentCamera = cameras.at(cntCamera);;

	if (cameras.at(cntCamera)->getType() == CameraType::DYNAMIC)
	{
		glm::vec3 direction = currentCamera->getCenter();

		float deltaX = x - mouseX;
		float deltaY = y - mouseY;

		mouseX = x;
		mouseY = y;

		direction[1] -= deltaY * 0.5f;
		direction[0] += deltaX * 0.5f;

		if (direction[1] >= 40.0f)
			direction[1] = 40.0f;
		else if (direction[1] <= -40.0f)
			direction[1] = -40.0f;

		if (direction[0] >= 50.0f)
			direction[0] = 50.0f;
		else if (direction[0] <= -50.0f)
			direction[0] = -50.0f;
		
		cameras.at(cntCamera)->setCenter(direction);
	}
}

