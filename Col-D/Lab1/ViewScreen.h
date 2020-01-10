#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

class ViewScreen
{
public:
	ViewScreen();//constructors
	~ViewScreen();
	void initViewScreen();//used initialise the screen
	void swappingBuffers();//used for swapping buffers
	void clearScreen(float r, float g, float b, float a);

	float getWidthOfScreen();// float that holds the width of the screen
	float getHeightOfScreen();//float that holds the height of the screen

private:

	void returnErrorMessage(std::string errorMessageString); // returns an error message

	SDL_GLContext gl_Cont; //global variable holds context
	SDL_Window* sdl_Screen; //holds pointer to the screen
	float displayWidth; // display the width to the screen
	float displayHeight;//displays the height to the screen.
};
