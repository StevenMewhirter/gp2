#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	ViewScreen* _gameDisplay = new ViewScreen(); //new display
    MeshCreator* mesh1();
	MeshCreator* mesh2();
	Audio* audioDevice();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initViewScreen(); 
	whistle = audioDevice.loadSound("..\\res\\bang.wav");
	backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	
	mesh1.load_Model("..\\res\\monkey3.obj");
	mesh2.load_Model("..\\res\\monkey3.obj");
	
	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidthOfScreen()/_gameDisplay.getHeightOfScreen(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		collision(mesh1.get_SPosition(), mesh1.get_SRadius(), mesh2.get_SPosition(), mesh2.get_SRadius());
		playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		audioDevice.setlistener(myCamera.getPosition(), m1Pos); //add bool to mesh
		playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
{
	
	ALint state; 
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		audioDevice.playSound(Source, pos);
	}
}

void MainGame::drawGame()
{
	_gameDisplay.clearScreen(0.0f, 0.0f, 0.0f, 1.0f);
	
	GameShaders gameShader("..\\res\\shader"); //new shader
	TextureHolder texture("..\\res\\bricks.jpg"); //load texture
	TextureHolder texture1("..\\res\\water.jpg"); //load texture
	
	transform.SetPosition(glm::vec3(sinf(counter), 0.5, 0.0));
	transform.SetRotation(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	gameShader.BindShader();
	gameShader.UpdateShader(transform, myCamera);
	texture.BindTextures(0);
	mesh1.drawMesh();
	mesh1.update_SData(*transform.GetPosition(), 0.62f);
	

	transform.SetPosition(glm::vec3(-sinf(counter), -0.5, -sinf(counter)*5));
	transform.SetRotation(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	gameShader.BindShader();
	gameShader.UpdateShader(transform, myCamera);
	texture.BindTextures(0);
	mesh2.drawMesh();
	mesh2.update_SData(*transform.GetPosition(), 0.62f);
	counter = counter + 0.05f;

				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swappingBuffers();
} 