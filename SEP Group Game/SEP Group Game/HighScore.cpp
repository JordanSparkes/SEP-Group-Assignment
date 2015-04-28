#include "Highscore.h"
#include "SystemManager.h"

//High Score //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void HighScore::load(SystemManager* pSM)
{
	background = pSM->loadImage("images/mainmenu_background.png");
	foreground = pSM->loadImage("images/game_background.png");
	blackbar = pSM->loadImageAlpha("images/menu_blackbar.png");

	backButton = new MButton(1130, 610, "BACK", NULL, pSM);

	backgroundPos = pSM->getBackgroundPos();
}

void HighScore::update(SystemManager* pSM)
{
	//update the background
	if(counter == 7)
	{
		if(movingLeft)
		{
			backgroundPos--;
			if (backgroundPos< -308)
			{
				movingLeft=false;
			}	
		}
		else
		{
			backgroundPos++;
			if(backgroundPos>0)
			{
				movingLeft = true;
			}
		}
		counter = 0;
	}
	counter++;

	handleEvents(pSM);
}

void HighScore::draw(SystemManager* pSM, float interpolation)
{
	int viewPosition = backgroundPos + (interpolation);
	pSM->applySurface(viewPosition, 0, background);
	pSM->applySurface(240, 0, foreground);
	pSM->applySurface(0, 600, blackbar);

	backButton->draw(pSM);
}

void HighScore::unload(SystemManager* pSM)
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(foreground);
	SDL_FreeSurface(blackbar);
	delete backButton;
	backButton = NULL;
}

HighScore* HighScore::instance()
{
	static HighScore instance;
	return &instance;
}

void HighScore::handleEvents(SystemManager* pSM)
{
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			pSM->setQuit();
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			mouseX = event.motion.x;
			mouseY = event.motion.y;

			backButton->mouseEvent(mouseX, mouseY);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				backButton->mouseDown();
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if(backButton->mouseUp() == true)
				{
					pSM->setBackgroundPos(backgroundPos);
					unload(pSM);
					pSM->changeScene(MainMenu::instance());
					return;
				}
				else
				{
			
				}
			}
		}
	}
}