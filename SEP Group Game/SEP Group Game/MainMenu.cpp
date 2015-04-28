#include "MainMenu.h"
#include "SystemManager.h"

//MainMenu Scene //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void MainMenu::load(SystemManager* pSM)
{
	background = pSM->loadImage("images/mainmenu_background.png");
	blackbar = pSM->loadImageAlpha("images/menu_blackbar.png");
	
	levelSelect = new MButton(20, 610, "LEVEL", "SELECT", pSM);
	highscore = new MButton(180, 610, "HIGH", "SCORE", pSM);
	quitgame = new MButton(1130, 610, "QUIT", NULL, pSM);

	backgroundPos = pSM->getBackgroundPos();
}

void MainMenu::update(SystemManager* pSM)
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

	//handle events for buttons
	handleEvents(pSM);
}

void MainMenu::draw(SystemManager* pSM, float interpolation)
{
	int viewPosition = backgroundPos + (interpolation);
	pSM->applySurface(viewPosition, 0, background);
	pSM->applySurface(0, 600, blackbar);
	levelSelect->draw(pSM);
	highscore->draw(pSM);
	quitgame->draw(pSM);
}

void MainMenu::unload(SystemManager* pSM)
{
	SDL_FreeSurface(background);
	SDL_FreeSurface(blackbar);
	delete levelSelect;	
	levelSelect = NULL;
	delete highscore;
	highscore = NULL;
	delete quitgame;
	quitgame = NULL;
}

MainMenu* MainMenu::instance()
{
	static MainMenu instance;
	return &instance;
	//return new MainMenu();
}

void MainMenu::handleEvents(SystemManager* pSM)
{
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			unload(pSM);
			pSM->setQuit();
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			mouseX = event.motion.x;
			mouseY = event.motion.y;

			levelSelect->mouseEvent(mouseX, mouseY);
			highscore->mouseEvent(mouseX, mouseY);
			quitgame->mouseEvent(mouseX, mouseY);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				levelSelect->mouseDown();
				highscore->mouseDown();
				quitgame->mouseDown();
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if(levelSelect->mouseUp() == true)
				{
					pSM->setBackgroundPos(backgroundPos);
					unload(pSM);
					//pSM->changeScene(LevelSelect::instance());
					return;
				}
				else 
				{
					if (highscore->mouseUp() == true)
					{
						pSM->setBackgroundPos(backgroundPos);
						unload(pSM);
						pSM->changeScene(HighScore::instance());
						return;
					}
					else if (quitgame->mouseUp() == true)
					{
						unload(pSM); 
						pSM->setQuit();
						return;
				    }
					else
					{

					}
				}
			}
		}
	}
}