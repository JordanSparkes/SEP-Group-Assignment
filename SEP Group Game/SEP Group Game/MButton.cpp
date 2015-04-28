#include "MButton.h"
#include "SystemManager.h"

MButton::MButton(int xPos, int yPos, char* buttonText, char* otherButtonText, SystemManager* pSM)
{
	x = xPos;
	y = yPos;
	downPos = yPos + 2;
	upPos = yPos;
	width = 120;
	height = 80;
	mouseOver = false;

	font = TTF_OpenFont("images/spaceranger.ttf", 25);

	SDL_Color testColour = {229, 114, 0};
	textColour = testColour;

	text = TTF_RenderText_Solid(font, buttonText, textColour);

	if (otherButtonText != NULL)
	{
		otherText = TTF_RenderText_Solid(font, otherButtonText, textColour);
	}
	else
	{
		otherText = NULL;
	}

	SDL_Color testaColour = {229, 0, 229};
	textColour = testaColour;

	textDown = TTF_RenderText_Solid(font, buttonText, textColour);

	if(otherButtonText != NULL)
	{
		otherTextDown = TTF_RenderText_Solid(font, otherButtonText, textColour);
	} 
	else
	{
		otherTextDown = NULL;
	}

	textXPos = x + (width - text->w - 15) / 2;
	textYPos = y + (height - 8 )/ 2;

	loadImages(pSM);
	toDraw = buttonOff;
}

MButton::~MButton()
{
	SDL_FreeSurface(text);
	if(otherText != NULL)
	{
		SDL_FreeSurface(otherText);
	}
	SDL_FreeSurface(textDown);
	if(otherTextDown != NULL)
	{
		SDL_FreeSurface(otherTextDown);
	}
	SDL_FreeSurface(buttonOn);
	SDL_FreeSurface(buttonOff);
	TTF_CloseFont(font);
}

void MButton::loadImages(SystemManager* pSM)
{
	buttonOn = pSM->loadImageAlpha("images/menu_button_on.png");
	buttonOff = pSM->loadImageAlpha("images/menu_button_off.png");
}

void MButton::draw(SystemManager* pSM)
{
	pSM->applySurface(x, y, toDraw);
	
	if(mouseOver == false)
	{
		if(otherText != NULL)
		{
			pSM->applySurface(textXPos, textYPos - 16, text);
			pSM->applySurface(textXPos, textYPos, otherText);
		}
		else
		{
			pSM->applySurface(textXPos, textYPos - 10, text);
		}
	}
	else
	{
		if(otherText != NULL)
		{
			pSM->applySurface(textXPos, textYPos - 16, textDown);
			pSM->applySurface(textXPos, textYPos, otherTextDown);
		}
		else
		{
			pSM->applySurface(textXPos, textYPos - 10, textDown);
		}
	}
}

void MButton::mouseEvent(int mouseX, int mouseY)
{
	if((mouseX > x) && (mouseX < x + width) && (mouseY > y) && (mouseY < y + height))
	{
		toDraw = buttonOn;
		mouseOver = true;
	}
	else
	{
		toDraw = buttonOff;
		mouseOver = false;
		y = upPos;
	}
}

void MButton::mouseDown()
{
	if(mouseOver == true)
	{
		y = downPos;
		mouseD = true;
	}
	else
	{
		y = upPos;
		mouseD = false;
	}
}

bool MButton::mouseUp()
{
	if ((mouseD == true) && (mouseOver == true))
	{
		mouseD = false;
		return true;
	}
	else
	{
		y = upPos;
		return false;
	}
}