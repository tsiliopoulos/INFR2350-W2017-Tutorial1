// Core Libraries
#include <iostream>
#include <string>
#include <math.h>
#include <map> // for std::map
#include <memory> // for std::shared_ptr

// 3rd Party Libraries
#include <GLEW\glew.h>
#include <GLUT\glut.h>
#include <TTK\OBJMesh.h> // tutorials toolkit
#include <TTK\Camera.h> // first person camera 
#include <IL/il.h> // for ilInit() - Image LIbrary - Loads textures
#include <glm\vec3.hpp> // OpenGL Mathematics

// User Libraries
#include "Shader.h" 
#include "ShaderProgram.h"
#include "GameObject.h"


// Defines and Core variables
#define FRAMES_PER_SECOND 60
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND; // Milliseconds per frame

int windowWidth = 800;
int windowHeight = 600;

glm::vec3 mousePosition; // x,y,0
glm::vec3 mousePositionFlipped; // x, height - y, 0

// A few conversions to know
const float degToRad = 3.14159f / 180.0f;
const float radToDeg = 180.0f / 3.14159f;

float deltaTime = 0.0f; // amount of time since last update (set every frame in timer callback)

glm::vec3 position;
float movementSpeed = 5.0f;

TTK::Camera camera;

std::map<std::string, std::shared_ptr<TTK::OBJMesh>> meshes;
std::map<std::string, std::shared_ptr<GameObject>> gameobjects;

std::shared_ptr<Material> defaultMaterial;

void initializeShaders()
{
	std::string shaderPath = "../../Assets/Shaders/";

	Shader vShader;
	//vShader.loadShaderFromFile(shaderPath + "default_100_v.glsl", GL_VERTEX_SHADER); // OLD GL
	vShader.loadShaderFromFile(shaderPath + "default_v.glsl", GL_VERTEX_SHADER); // NEW GL

	Shader fShader;
	//fShader.loadShaderFromFile(shaderPath + "default_100_f.glsl", GL_FRAGMENT_SHADER); // OLD GL
	fShader.loadShaderFromFile(shaderPath + "default_f.glsl", GL_FRAGMENT_SHADER); // NEW GL

	
	defaultMaterial = std::make_shared<Material>();
	defaultMaterial->shader->attachShader(vShader);
	defaultMaterial->shader->attachShader(fShader);
	defaultMaterial->shader->linkProgram();
	
}

void initializeScene()
{
	std::string meshPath = "../../Assets/Models/";
	
	std::shared_ptr<TTK::OBJMesh> floorMesh = std::make_shared<TTK::OBJMesh>();
	std::shared_ptr<TTK::OBJMesh> sphereMesh = std::make_shared<TTK::OBJMesh>();
	std::shared_ptr<TTK::OBJMesh> torusMesh = std::make_shared<TTK::OBJMesh>();

	floorMesh->loadMesh(meshPath + "floor.obj");
	sphereMesh->loadMesh(meshPath + "sphere.obj");
	torusMesh->loadMesh(meshPath + "torus.obj");

	// Note: looking up a mesh by it's string name is not the fastest thing,
	// you don't want to do this every frame, once in a while (like now) is fine.
	// If you need you need constant access to a mesh (i.e. you need it every frame),
	// store a reference to it so you don't need to look it up every time.
	meshes["floor"] = floorMesh;
	meshes["sphere"] = sphereMesh;
	meshes["torus"] = torusMesh;

	gameobjects["floor"] = std::make_shared<GameObject>(glm::vec3(0.0f, 0.0f, 0.0f), floorMesh, defaultMaterial);
	gameobjects["sphere"] = std::make_shared<GameObject>(glm::vec3(0.0f, 5.0f, 0.0f), sphereMesh, defaultMaterial);
	gameobjects["torus"] = std::make_shared<GameObject>(glm::vec3(5.0f, 5.0f, 0.0f), torusMesh, defaultMaterial);

	gameobjects["sphere"]->colour = glm::vec4(1.0f);
}

// This is where we draw stuff
void DisplayCallbackFunction(void)
{
	// Set background colour and clear screen
	// Note: try to keep GL calls wrapped in classes / functions
	// Next week we will make an FBO class which will handle these two
	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.update();

	// Update material properties

	// Move light in simple circular path
	static float ang = 0.0f;
	static glm::vec4 lightPos;
	ang += deltaTime;
	lightPos.x = cos(ang) * 15.0f;
	lightPos.y = 10.0f;
	lightPos.z = sin(ang) * 15.0f;
	lightPos.w = 1.0f;

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT0, GL_POSITION, &lightPos[0]);

	defaultMaterial->vec4Uniforms["u_lightPos"] = camera.viewMatrix * lightPos;
	 
	gameobjects["sphere"]->setPosition(lightPos);

	// Update and draw all game objects
	for (auto itr = gameobjects.begin(); itr != gameobjects.end(); ++itr)
	{
		auto gameobject = itr->second;
		
		// Remember: root nodes are responsible for updating all of its children
		// So we need to make sure to only invoke update() for the root nodes.
		// Otherwise some objects would get updated twice in a frame!
		if (gameobject->isRoot())
		{
			gameobject->update(deltaTime);
			gameobject->draw(camera);
		}
	}

	/* Swap Buffers to Make it show up on screen */
	glutSwapBuffers();
}

/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // the escape key
	case 'q': // the 'q' key
	case 'Q':
		camera.moveUp();
		break;
	case 'e':
	case 'E':
		camera.moveDown();
	case 'W':
	case 'w':
		camera.moveForward();
		break;
	case 'S':
	case 's':
		camera.moveBackward();
		break;
	case 'A':
	case 'a':
		camera.moveRight();
		break;
	case 'D':
	case 'd':
		camera.moveLeft();
		break;
	}
}

/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	}
}

/* function TimerCallbackFunction(int value)
* Description:
*  - this is called many times per second
*  - this enables you to animate things
*  - no drawing, just changing the state
*  - changes the frame number and calls for a redisplay
*  - FRAME_DELAY is the number of milliseconds to wait before calling the timer again
*/
void TimerCallbackFunction(int value)
{
	// Calculate new deltaT for potential updates and physics calculations
	static int elapsedTimeAtLastTick = 0;
	int totalElapsedTime = glutGet(GLUT_ELAPSED_TIME);

	deltaTime = totalElapsedTime - elapsedTimeAtLastTick;
	deltaTime /= 1000.0f;
	elapsedTimeAtLastTick = totalElapsedTime;

	/* this call makes it actually show up on screen */
	glutPostRedisplay();
	/* this call gives it a proper frame delay to hit our target FPS */
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);
}

/* function WindowReshapeCallbackFunction()
* Description:
*  - this is called whenever the window is resized
*  - and sets up the projection matrix properly
*/
void WindowReshapeCallbackFunction(int w, int h)
{
	/* Update our Window Properties */
	windowWidth = w;
	windowHeight = h;

	camera.winHeight = h;
	camera.winWidth = w;
}


void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;

	mousePositionFlipped = mousePosition;
	mousePositionFlipped.y = windowHeight - mousePosition.y;
}

void SpecialInputCallbackFunction(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		position.z += movementSpeed * deltaTime;
		break;
	case GLUT_KEY_DOWN:
		position.z -= movementSpeed * deltaTime;
		break;
	case GLUT_KEY_LEFT:
		position.x += movementSpeed * deltaTime;
		break;
	case GLUT_KEY_RIGHT:
		position.x -= movementSpeed * deltaTime;
		break;
	}
}

// Called when the mouse is clicked and moves
void MouseMotionCallbackFunction(int x, int y)
{
	if (mousePosition.length() > 0)
		camera.processMouseMotion(x, y, mousePosition.x, mousePosition.y, deltaTime);

	mousePosition.x = x;
	mousePosition.y = y;

	mousePositionFlipped = mousePosition;
	mousePositionFlipped.y = windowHeight - mousePosition.y;
}

/* function main()
* Description:
*  - this is the main function
*  - does initialization and then calls glutMainLoop() to start the event handler
*/
int main(int argc, char **argv)
{
	// Memory Leak Detection
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Tutorial");

	/* set up our function callbacks */
	glutDisplayFunc(DisplayCallbackFunction);
	glutKeyboardFunc(KeyboardCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutReshapeFunc(WindowReshapeCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutMotionFunc(MouseMotionCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);
	glutSpecialFunc(SpecialInputCallbackFunction);

	// Init GLEW
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		std::cout << "TTK::InitializeTTK Error: GLEW failed to init" << std::endl;
	}
	printf("OpenGL version: %s, GLSL version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Init IL
	ilInit();

	// Init GL
	glEnable(GL_DEPTH_TEST); // checks if objects are obscured and should be rendered
	glDepthFunc(GL_LEQUAL);

	// Initialize scene
	initializeShaders(); // loads in the shaders
	initializeScene();

	/* Start Game Loop */
	deltaTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime /= 1000.0f;

	glutMainLoop();

	return 0;
}