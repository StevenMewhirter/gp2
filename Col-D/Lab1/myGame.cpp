#include "myGame.h"
#include "MainCamera.h"
#include <iostream>
#include <string>


Transform transform;

myGame::myGame()
{
	_currentGameState = CurrentGameState::PLAY;//plays the games state
	ViewScreen* _currentGameDisplay = new ViewScreen(); //new display
	MeshCreator* mesh1();
	MeshCreator* mesh2();
	MeshCreator* mesh3();
	GameAudio* audioDevice();
}

myGame::~myGame()
{
}

void myGame::runSystems()
{
	initSystems();
	gamesCurrentLoop();
}

void myGame::initSystems() // gets all the systems started 
{
	_currentGameDisplay.initViewScreen();//displays the screen
	Coin = audioDevice.loadingOfSound("..\\res\\Score.wav");//loads the sound source
	gameMusic = audioDevice.loadingOfSound("..\\res\\GameMusic.wav");

	mesh1.load_Model("..\\res\\Crab.obj");//loads in the object models 
	mesh2.load_Model("..\\res\\Bucket1.obj");
	mesh3.load_Model("..\\res\\GameNet.obj");
	//sets the camera width/height and pos
	myCamera.initiliaseTheCamera(glm::vec3(0, 0, -5), 70.0f, (float)_currentGameDisplay.getWidthOfScreen() / _currentGameDisplay.getHeightOfScreen(), 0.01f, 1000.0f);
	//counter for moving objects
	counter = 1.0f;
}

void myGame::gamesCurrentLoop()
{
	while (_currentGameState != CurrentGameState::EXIT)//do the below functions if game is in play state
	{
		processPlayerInput();//check player input
		drawTheGame();//draw the game to the screen
		collision(mesh1.get_SPosition(), mesh1.get_SRadius(), mesh3.get_SPosition(), mesh3.get_SRadius());//check collisions
		playAudio(gameMusic, glm::vec3(0.0f, 0.0f, 0.0f));//check for audio
	}
}

void myGame::processPlayerInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_currentGameState = CurrentGameState::EXIT;
			break;

		case SDL_KEYDOWN: // checks for any key down button
			switch (evnt.key.keysym.sym)
			{
			case SDLK_LEFT://if left arrow key is pressed move left
				NetX += 0.5f;
				break;
			case SDLK_RIGHT://if right arrow key is pressed move right
				NetX -= 0.5f;
				break;
			case SDLK_UP://if the up arrow key is pressed swipe net
				NetY += 2.0f;
				break;
			case SDLK_DOWN://if the down arrow key is pressed bring net back up
				NetY -= 2.0f;
				break;
			case SDLK_BACKSPACE://if backspace is pressed exit application
				_currentGameState = CurrentGameState::EXIT;
				break;

			}
		}
	}


}


bool myGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m3Pos, float m3Rad) // creating collision for when mesh 1 collides with mesh 3
{
	//mathemetacal equation for distance
	float distance = glm::sqrt((m3Pos.x - m1Pos.x) * (m3Pos.x - m1Pos.x) + (m3Pos.y - m1Pos.y) * (m3Pos.y - m1Pos.y) + (m3Pos.z - m1Pos.z) * (m3Pos.z - m1Pos.z));
	//checking the distance of m1 and m3 
	if (distance < (m1Rad + m3Rad))
	{
		audioDevice.setupThelistener(myCamera.getCameraPosition(), m3Pos); //add bool to mesh
		playAudio(Coin, m3Pos);// plays the audio source if they collide
		return true;
	}
	else
	{
		return false;
	}
}

void myGame::playAudio(unsigned int Source, glm::vec3 pos)
{

	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);

	if (AL_PLAYING != state)
	{
		audioDevice.playingTheSound(Source, pos);
	}
}

void myGame::drawTheGame()
{
	_currentGameDisplay.clearScreen(0.0f, 0.0f, 0.0f, 1.0f);//clears the screen 

	GameShaders gameShader("..\\res\\shader"); //new shader
	TextureHolder texture("..\\res\\bricks.jpg"); //load texture
	TextureHolder texture1("..\\res\\water.jpg"); //load texture
	TextureHolder texture2("..\\res\\Wood.jpg"); //load texture

	transform.SetPosition(glm::vec3(sinf(counter * 3), -0.8, -2.0));//sets the position of mesh1 (i.e crab)
	transform.SetRotation(glm::vec3(0.0, 0.0, 0.0)); // sets if the crab is to have rotation
	transform.SetScale(glm::vec3(1.0, 1.0, 1.0)); // sets the scale of the model 
	//the section below binds the mesh to the screen and adds the appropriate texture, for the crab model also it adds movement counter and updates its position each time it moves
	gameShader.BindShader();
	gameShader.UpdateShader(transform, myCamera);
	texture.BindTextures(0);
	mesh1.drawMesh();
	mesh1.update_SData(*transform.GetPosition(), 0.62f);
	counter = counter + 0.05f;

	transform.SetPosition(glm::vec3(1.0, -1.0, 0.0));
	transform.SetRotation(glm::vec3(0.0, 0.0, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	gameShader.BindShader();
	gameShader.UpdateShader(transform, myCamera);
	texture1.BindTextures(0);
	mesh2.drawMesh();
	mesh2.update_SData(*transform.GetPosition(), 0.62f);


	transform.SetPosition(glm::vec3(NetX, -0.2, -1.1));
	transform.SetRotation(glm::vec3(NetY, 0.0, 0.0));
	transform.SetScale(glm::vec3(0.07, 0.07, 0.07));

	gameShader.BindShader();
	gameShader.UpdateShader(transform, myCamera);
	texture2.BindTextures(0);
	mesh3.drawMesh();
	mesh3.update_SData(*transform.GetPosition(), 0.62f);



	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_currentGameDisplay.swappingBuffers();
}