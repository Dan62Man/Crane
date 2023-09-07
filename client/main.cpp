#include "CraneModel.h"
#include "KeyDefinition.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

// ------------------------------
//		File 
// ------------------------------
const char* fileOvO = "CraneModel.ovo";

// ------------------------------
//		Environment 
// ------------------------------
const char* windowTitle = "The crane";
int windowPosX = 350;
int windowPosY = 100;
int windowdLength = 900;
int windowdHeight = 600;
float colorRed = 153.0f / 255.0f;
float colorGreen = 221.0f / 255.0f;
float colorBlue = 255.0f / 255.0f;
float colorAlpha = 1.0f;

// ------------------------------
//		Objects
// ------------------------------
CraneModel* crane;

// --------------------------------------------------------------------------------
//							KEYBOARD FUNCTIONS
// --------------------------------------------------------------------------------

void keyboardCallback(unsigned char key, int mouseX, int mouseY) {
    
    switch (key) {
    case KEY_TAB:
        crane->changeTypeSelcted();
        break;
    case KEY_A: case KEY_a:
        if (crane->getTypeSelected() == TypeSelected::MODEL)
            crane->moveArm(TypeDirection::LEFT);
        else if (crane->getTypeSelected() == TypeSelected::CAMERA)
            crane->moveCamera(TypeDirection::LEFT);
        break;
    case KEY_D: case KEY_d :
        if (crane->getTypeSelected() == TypeSelected::MODEL)
            crane->moveArm(TypeDirection::RIGHT);
        else if (crane->getTypeSelected() == TypeSelected::CAMERA)
            crane->moveCamera(TypeDirection::RIGHT);
        break;   
    case KEY_W: case KEY_w:
        if (crane->getTypeSelected() == TypeSelected::MODEL)
            crane->moveHook(TypeDirection::UP);
        else if (crane->getTypeSelected() == TypeSelected::CAMERA)
            crane->moveCamera(TypeDirection::UP);
        break;
    case KEY_S: case KEY_s :
        if (crane->getTypeSelected() == TypeSelected::MODEL)
            crane->moveHook(TypeDirection::DOWN);
        else if (crane->getTypeSelected() == TypeSelected::CAMERA)
            crane->moveCamera(TypeDirection::DOWN);
        break;
    case KEY_Q: case KEY_q:
        if (crane->getTypeSelected() == TypeSelected::MODEL)
            crane->moveCarriage(TypeDirection::FORWARD);
        else if (crane->getTypeSelected() == TypeSelected::CAMERA)
            crane->moveCamera(TypeDirection::FORWARD);
    break;
    case KEY_E: case KEY_e:
        if (crane->getTypeSelected() == TypeSelected::MODEL)
            crane->moveCarriage(TypeDirection::BACKWORD);
        else if (crane->getTypeSelected() == TypeSelected::CAMERA)
            crane->moveCamera(TypeDirection::BACKWORD);
        break;    
    case KEY_SPACE:
        if (crane->getTypeSelected() == TypeSelected::MODEL)
            crane->grabOrDrop();
        break;
    case KEY_DOT:
        if (crane->getTypeSelected() == TypeSelected::CAMERA)
            crane->changeCamera();
        break;
    default:
        break;
    }
}

void specialCallback(int key, int mouseX, int mouseY) {
    switch (key) {
    case KEY_F1:
        Engine::manageCullFace();
        break;
    case KEY_F2:
        Engine::manageWireframe();
        break;
    default:
        break;
    }
}

void mouseCallback(int x, int y) {
        crane->moveViewingPointCamera(x, y);
}

//_________________________________________________________________________________

// --------------------------------------------------------------------------------
//							MAIN FUNCTION
// --------------------------------------------------------------------------------

int main(int argc, char* argv[]) {

    // initialize environment
    Engine::init(argc, argv, windowTitle, windowPosX, windowPosY, windowdLength, windowdHeight, colorRed, colorGreen, colorBlue, colorAlpha);

    // objects
    Node* root = Engine::loadGraphicScene(fileOvO);

    if (root != nullptr)
        crane = new CraneModel(Engine::getRenderList());
    else
    {
        cout << "[No objects to render]" << endl;
        return 1;
    }
    
    // set callback functions
    Engine::setKeyboardCallback(keyboardCallback);
    Engine::setSpecialCallback(specialCallback);
    Engine::setMotionCallBack(mouseCallback);
    Engine::setCallbackFunctions();

    // start glut main loop
    Engine::start();

    // close program
    if (!Engine::getInitialized()) Engine::free();

    // free memory
    delete(crane);
    
    return 0;
}