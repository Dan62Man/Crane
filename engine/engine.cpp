#include "engine.h"
#include <GL/freeglut.h>
#include <FreeImage.h>

// ------------------------------
//		Environment
// ------------------------------
int windowId;
bool initialized = false;
glm::vec4 backgroundColor;
list<Message> messages;

// ------------------------------
//		Flags
// ------------------------------
bool cullFace = false;
bool wireframe = false;

// ------------------------------
//		Fps
// ------------------------------
int frames = 0;
int fps = 0;
unsigned int timeFPS = 1000;
int valueFPS = 0; 

// ------------------------------
//		Objects
// ------------------------------
List renderList = List("Render list");
OrthographicCamera orthographicCamera = OrthographicCamera("Orthographic camera", 0.0f, 0.0f, 0.0f, 0.0f);
PerspectiveCamera* camera = nullptr;

// --------------------------------------------------------------------------------
//							BASIC FUNCTIONS
// --------------------------------------------------------------------------------

// initialize the environment
void ENGINE_API Engine::init(int argc, char* argv[], const char* title, int posX, int posY, int lenght, int height, float red, float green, float blue, float alpha) {
	cout << "--------------------------------------" << endl;
	cout << "---------[Engine initialized]---------" << endl;
	cout << "--------------------------------------" << endl;

	// Init context:
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(posX, posY);
	glutInitWindowSize(lenght, height);

	glutInit(&argc, argv);

	//Set some optional flags:
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	windowId = glutCreateWindow(title);
	backgroundColor = glm::vec4(red, green, blue, alpha);

	//Enable Lighting
	//glEnable(GL_LIGHTING); // required if I'm not rendering any on-screen text

	//Enable normalize (useful when working with non-uniform transformations)
	glEnable(GL_NORMALIZE);

	//Enable Z-Buffer
	glEnable(GL_DEPTH_TEST);

	//Init FreeImage
	FreeImage_Initialise();
}


// set variable initialized
void ENGINE_API Engine::start() {
	initialized = true;
	glutMainLoop();
}


// sets all callback functions as well as the main FreeGLUT processing loop
void ENGINE_API Engine::setCallbackFunctions() {
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);
	glutTimerFunc(timeFPS, timerCallback, valueFPS);
	glutCloseFunc(closeCallback);
}


// main rendering routine automatically invoked by FreeGLUT
void Engine::displayCallback() {
	glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// rendering scene

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(camera->getProjection()));
	glMatrixMode(GL_MODELVIEW);

	setShadows();

	camera->updateMatrix();
	renderList.render(camera->getMatrix(), camera->getMatrix());

	// writing on screen

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(orthographicCamera.getProjection()));
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(glm::value_ptr(glm::mat4(1.0f)));

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	char textFPS[10];
	float posY = 360.0f;
	sprintf(textFPS, "FPS: %d", fps);

	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos2f(10.f, posY);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*)textFPS);

	//Enable transparency and blend colors based on opacity
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.9f, 0.9f, 0.9f, 0.7f);
	float textLength = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)textFPS);
	glRectf(0.0f, posY, 270.0f, posY + 20.0f);

	writeOnScreen();
	glDisable(GL_BLEND); //Disable blend
	glEnable(GL_LIGHTING);


	//	calculating fps

	++frames;


	glutSwapBuffers();
	glutPostWindowRedisplay(windowId);
}

void Engine::setShadows() {
	
	Node* box01 = renderList.findByName("Box01");
	Node* box02 = renderList.findByName("Box02");
	Node* box03 = renderList.findByName("Box03");
	Node* rotaryMotor = renderList.findByName("RotaryMotor");
	Node* container01 = renderList.findByName("Container01");
	Node* container02 = renderList.findByName("Container02");
	Node* container03 = renderList.findByName("Container03");
	Node* container04 = renderList.findByName("Container04");
	Node* container05 = renderList.findByName("Container05");
	Node* container06 = renderList.findByName("Container06");
	Node* container07 = renderList.findByName("Container07");
	Node* container08 = renderList.findByName("Container08");
	Node* container09 = renderList.findByName("Container09");
	dynamic_cast<Mesh*>(box01)->setHasShadow(true);
	dynamic_cast<Mesh*>(box02)->setHasShadow(true);
	dynamic_cast<Mesh*>(box03)->setHasShadow(true);
	dynamic_cast<Mesh*>(rotaryMotor)->setHasShadow(true);
	dynamic_cast<Mesh*>(container01)->setHasShadow(true);
	dynamic_cast<Mesh*>(container02)->setHasShadow(true);
	dynamic_cast<Mesh*>(container03)->setHasShadow(true);
	dynamic_cast<Mesh*>(container04)->setHasShadow(true);
	dynamic_cast<Mesh*>(container05)->setHasShadow(true);
	dynamic_cast<Mesh*>(container06)->setHasShadow(true);
	dynamic_cast<Mesh*>(container07)->setHasShadow(true);
	dynamic_cast<Mesh*>(container08)->setHasShadow(true);
	dynamic_cast<Mesh*>(container09)->setHasShadow(true);
}


// change status of the environment
void Engine::closeCallback() { 
	initialized = false;
}

// press classic keyboard
void ENGINE_API Engine::setKeyboardCallback(void(*callback)(unsigned char, int, int)) {
	glutKeyboardFunc(callback);

}


// press spacial keyboard
void ENGINE_API Engine::setSpecialCallback(void(*callback)(int, int, int)) {
	glutSpecialFunc(callback);
}


// move mouse 
void ENGINE_API Engine::setMotionCallBack(void(*callback)(int, int))
{
	glutMotionFunc(callback);
}
						

// free memory
void ENGINE_API Engine::free()
{
	cout << "--------------------------------------" << endl;
	cout << "--------[Engine deinitialized]--------" << endl;
	cout << "--------------------------------------" << endl;

	for (const auto &n : renderList.getList())
		delete(n.first);
}


// return status of the environment
bool  ENGINE_API Engine::getInitialized() {
	return initialized; 
}


// set view each time the window gets resized
void ENGINE_API Engine::reshapeCallback(int width, int height) {
	camera->setProjection((float)width / (float)height);
	orthographicCamera.setProjection((float)width, (float)height);
	glViewport(0, 0, width, height);
}

//_________________________________________________________________________________

// --------------------------------------------------------------------------------
//							FPS
// --------------------------------------------------------------------------------

// calculates FPS
void Engine::timerCallback(int value) {
	fps = frames;
	frames = 0;
	glutTimerFunc(timeFPS, timerCallback, valueFPS);
}

//_________________________________________________________________________________

// --------------------------------------------------------------------------------
//							WRITE ON SCREEN
// --------------------------------------------------------------------------------

// write text on screen in a specific position
void Engine::writeOnScreen() {
	for (Message mex: messages) {
		glColor3f(mex.getColorRed(), mex.getColorGreen(), mex.getColorBlue());
		glRasterPos2f(mex.getPosX(), mex.getPosY());
		glutBitmapString(GLUT_BITMAP_8_BY_13, (unsigned char*) mex.getText());

		glColor4f(0.9f, 0.9f, 0.9f, 0.7f);
		float textLength = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)mex.getText());
		glRectf(0.0f, mex.getPosY(), 270.0f, mex.getPosY() + 20.0f);
	}
}

// update the list of message to show on screen 
void Engine::updateMessages(list<Message> newMessages)
{
	messages = newMessages;
}

//_________________________________________________________________________________

// --------------------------------------------------------------------------------
//							RENDERING
// --------------------------------------------------------------------------------

// load model by file.ovo (open, read and save data before to render)
Node ENGINE_API* Engine::loadGraphicScene(const char* fileName) {
    FileReader fileReader = FileReader(fileName);
    Node* root = fileReader.read();
	if (root != nullptr)
		renderList.add(root, root->getWorldMatrix());
    return root;
}

//_________________________________________________________________________________

// --------------------------------------------------------------------------------
//							GET/SET OBJECT
// --------------------------------------------------------------------------------

// get list in which there are objects to render 
List ENGINE_API* Engine::getRenderList()
{
	return &renderList;
}

// change current camera
void ENGINE_API Engine::setCamera(PerspectiveCamera* currentCamera)
{
	if (camera == nullptr)
		camera = currentCamera;
	else
	{ 
		float aspect = camera->getAspect();
		camera = currentCamera;
		camera->setProjection(aspect);
	}
}

//_________________________________________________________________________________

// --------------------------------------------------------------------------------
//							FLAGS
// --------------------------------------------------------------------------------

void ENGINE_API Engine::manageCullFace()
{
	cullFace = !cullFace;
	if (cullFace)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void ENGINE_API Engine::manageWireframe()
{
	wireframe = !wireframe;
	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
