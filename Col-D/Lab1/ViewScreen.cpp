#include "ViewScreen.h"

ViewScreen::ViewScreen()
{
	sdl_Screen = nullptr; //initialise to generate null access violation for debugging. 
	displayWidth = 1024.0f; //sets the width of the display
	displayHeight = 768.0f;//sets the height of the display
}
ViewScreen::~ViewScreen()
{
	SDL_GL_DeleteContext(gl_Cont); // delete context
	SDL_DestroyWindow(sdl_Screen); // detete window 
	SDL_Quit();
}
float ViewScreen::getWidthOfScreen() { return displayWidth; } //getters for height and width
float ViewScreen::getHeightOfScreen() { return displayHeight; }

void ViewScreen::returnErrorMessage(std::string errorMessageString) // sets an error message to prompt if the screen display wont load.
{
	std::cout << errorMessageString << std::endl;
	std::cout << "press any  key to quit the current application...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void ViewScreen::swappingBuffers()
{
	SDL_GL_SwapWindow(sdl_Screen); //swaps the buffers
}

void ViewScreen::clearScreen(float r, float g, float b, float a) // clears the screen
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

void ViewScreen::initViewScreen()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything to the screen

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	sdl_Screen = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)displayWidth, (int)displayHeight, SDL_WINDOW_OPENGL); // creates the window of the game

	if (sdl_Screen == nullptr)
	{
		returnErrorMessage("window failed to create"); // returns an error if window does not load
	}

	gl_Cont = SDL_GL_CreateContext(sdl_Screen);//Creates SDL context

	if (gl_Cont == nullptr)
	{
		returnErrorMessage("SDL_GL context failed to create"); // returns an error if context fails to create
		
	}

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		returnErrorMessage("GLEW failed to initialise"); // returns error if glew fails to initialise 
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}