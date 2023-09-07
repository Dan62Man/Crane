#pragma once
#ifndef ENGINE
    #define ENGINE

// Build Options:
#ifdef _WINDOWS
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
#else
#define ENGINE_API
#endif

#include "LibraryInfo.h"
#include <iostream>
#include <string>
#include <list>
#include <glm/glm.hpp>
#include "Message.h"
#include "OvType.h"
#include "FileReader.h"
#include "Node.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "OmniLight.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"
#include "CameraType.h"
#include "List.h"

using namespace std;

class ENGINE_API Engine {

public:
    static void init(int argc, char* argv[], const char* title, int posX, int posY, int width, int height, float red = 0.7f, float green = 0.7f, float blue = 0.7f, float alpha = 1.0f);
    static void start(); 
    static void setCallbackFunctions();
    static void setKeyboardCallback(void(*callback)(unsigned char, int, int));
    static void setSpecialCallback(void (*callback)(int, int, int));
    static void setMotionCallBack(void (*callback)(int, int));
    static void free();
    static bool getInitialized();
    static void reshapeCallback(int width, int height);
    static void timerCallback(int value);
    
    static void writeOnScreen();
    static void updateMessages(list<Message> newMessage);

    static Node* loadGraphicScene(const char* fileName);
   
    static List* getRenderList();
    static void setCamera(PerspectiveCamera* camera);

    static void manageCullFace();
    static void manageWireframe();

private:
    static void displayCallback();
    static void closeCallback();
    static void setShadows();
};

#endif