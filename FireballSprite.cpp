//////////Mikey//////////
#include "FireballSprite.h"


FireballSprite::FireballSprite() : Sprite()
{
    //set default direcition
    statusFlag = FIRE_GO_RIGHT;

    //Set default current sprite
    currentSprite = 0;

    //Set the number of sprites
    this->travelRightClipSize = 18;
    this->travelLeftClipSize = 18;

    this->travelUpClipSize = 18;
    this->travelDownClipSize = 18;

    this->travelUpRightClipSize = 18;
    this->travelUpLeftClipSize = 18;
    this->travelDownRightClipSize = 18;
    this->travelDownLeftClipSize = 18;

    this->explodeClipSize = 18;

    //Set pointers to null
    travelRightClips = NULL;
    travelLeftClips = NULL;

    travelUpClips = NULL;
    travelDownClips = NULL;

    travelUpRightClips = NULL;
    travelUpLeftClips = NULL;
    travelDownRightClips = NULL;
    travelDownLeftClips = NULL;

    explodeClips = NULL;

    source = NULL;
}

FireballSprite::~FireballSprite()
{
    //Clean up memory
    delete travelRightClips;
    delete travelLeftClips;

    delete travelUpClips;
    delete travelDownClips;

    delete travelUpRightClips;
    delete travelUpLeftClips;
    delete travelDownRightClips;
    delete travelDownLeftClips;

    delete explodeClips;

    travelRightClips = NULL;
    travelLeftClips = NULL;

    travelUpClips = NULL;
    travelDownClips = NULL;

    travelUpRightClips = NULL;
    travelDownRightClips = NULL;
    travelUpLeftClips = NULL;
    travelDownLeftClips = NULL;

    explodeClips = NULL;

    //set source to NULL but don't delete
    source = NULL;
}

void FireballSprite::init(SDL_Surface* spriteSheet, SDL_Rect* position)
{
    //Set the sprite position
    //Copy works as there is no dynamic info in SDL_Rect
    this->rect = *position;

    //Came to my senses with this, why should this come infrom outside - its a constant
    //assocated with this clas
    rect.w = FIRE_W; 
    rect.h = FIRE_H; 

    //Create an array for the sprites regions
    this->travelRightClips = loadClips(this->travelRightClipSize, 1,
                                     this->rect.w, this->rect.h);
    
    //If there is no local variable with the same name we don't need to use 'this'
    //this method is part of the class
    travelLeftClips = loadClips(travelLeftClipSize, 2, rect.w, rect.h);

    //Load up/down
    travelUpClips = loadClips(travelUpClipSize, 6, rect.w, rect.h);
    travelDownClips = loadClips(travelDownClipSize, 3, rect.w, rect.h);

    //Load diagonals
    travelUpRightClips = loadClips(travelUpRightClipSize, 8, rect.w, rect.h);
    travelUpLeftClips = loadClips(travelUpLeftClipSize, 7, rect.w, rect.h);
    travelDownRightClips = loadClips(travelDownRightClipSize, 5, rect.w, rect.h);
    travelDownLeftClips = loadClips(travelDownLeftClipSize, 4, rect.w, rect.h);

    //Load a single front facing sprite for when the sprite is stopped
    explodeClips = loadClips(explodeClipSize, 0, rect.w, rect.h);

   //setup the sprite sheet
   this->spriteSheet = spriteSheet;
}

/* Overload with source settting */
void FireballSprite::init(SDL_Surface* spriteSheet, SDL_Rect* position, SpriteGame* mySource)
{
    init(spriteSheet,position);
    setSource(mySource);
}

void FireballSprite::blit(SDL_Surface* screen)
{
   switch(statusFlag)
   {
        case FIRE_EXPLODE:
            SDL_BlitSurface(spriteSheet,
        	       &(explodeClips[currentSprite]),
        	       screen,
        	       &rect);
        break;
        case FIRE_GO_LEFT:
            SDL_BlitSurface(spriteSheet,
                      &(travelLeftClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case FIRE_GO_RIGHT:
            SDL_BlitSurface(spriteSheet,
                      &(travelRightClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case FIRE_GO_DOWN:
            SDL_BlitSurface(spriteSheet,
                      &(travelDownClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case FIRE_GO_UP:
            SDL_BlitSurface(spriteSheet,
                      &(travelUpClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case FIRE_GO_DOWN_RIGHT:
            SDL_BlitSurface(spriteSheet,
                      &(travelDownRightClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case FIRE_GO_UP_RIGHT:
            SDL_BlitSurface(spriteSheet,
                      &(travelUpRightClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case FIRE_GO_DOWN_LEFT:
            SDL_BlitSurface(spriteSheet,
                      &(travelDownLeftClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case FIRE_GO_UP_LEFT:
            SDL_BlitSurface(spriteSheet,
                      &(travelUpLeftClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case FIRE_GONE:
           /* Empty case:  we've finished our animation
              we've reached our effective range */
        break;
        default:
             printf("Something has gone badly wrong\n");
    }
}

/* The update method was getting too large and has
 * been split into two new private methods.  One
 * focuses on the animation (changing the sprite sheet)
 * The other moves the sprite and prevents it moving off
 * screen.
 */
void FireballSprite::update(float scalar)
{
   this->updateAnimation();

   this->updatePosition(scalar);
}

void FireballSprite::updateAnimation()
{
   int clipMax = 0;
   switch(statusFlag)
   {
        case FIRE_GO_LEFT:
            clipMax = travelLeftClipSize-1;
        break;
        case FIRE_GO_RIGHT:
            clipMax = travelRightClipSize-1;
        break;
        case FIRE_GO_UP:
           clipMax = travelUpClipSize-1;
        case FIRE_GO_DOWN_LEFT:
           clipMax = travelDownLeftClipSize-1;
        break;
        case FIRE_GO_UP_LEFT:
            clipMax = travelUpLeftClipSize-1;
        break;
        case FIRE_GO_DOWN_RIGHT:
            clipMax = travelDownLeftClipSize-1;
        break;
        case FIRE_GO_UP_RIGHT:
            clipMax = travelUpRightClipSize-1;
        break;
        case FIRE_GO_DOWN:
            clipMax = travelRightClipSize-1;
        break;
        case FIRE_EXPLODE:
             clipMax = explodeClipSize-1;
         break;
         case FIRE_GONE:
           /* Empty case:  we've finished our animation
              we've reached our effective range */
        break;
        default:
             printf("Something has gone badly wrong\n");
    }

   //Update animation
   if(currentSprite < clipMax)
       currentSprite++;
   else
       gone();
}

void FireballSprite::updatePosition(float scalar)
{
    //Check boundaries!
    if(statusFlag != FIRE_EXPLODE && statusFlag != FIRE_GONE)
    {
        if(this->atWindowBottom() || this->atWindowTop() || this->atWindowRight() || this->atWindowLeft())
            this->explode();
        else
        {
            //Move the sprite
            rect.x += (xSpeed*scalar);
            rect.y += (ySpeed*scalar);
        }
     }
}

// State changes

void FireballSprite::goLeft()
{
    this->statusFlag = FIRE_GO_LEFT;
    this->xSpeed = -FIRE_X_SPEED;
    this->ySpeed = 0;

}

void FireballSprite::goRight()
{
    statusFlag = FIRE_GO_RIGHT;
    xSpeed = FIRE_X_SPEED;
    ySpeed = 0;
}

void FireballSprite::goUp()
{
    statusFlag = FIRE_GO_UP;
    xSpeed = 0;
    ySpeed = -FIRE_Y_SPEED;
}

void FireballSprite::goDown()
{
    statusFlag = FIRE_GO_DOWN;
    xSpeed = 0;
    ySpeed = FIRE_Y_SPEED;
}

void FireballSprite::goUpRight()
{
    statusFlag = FIRE_GO_UP_RIGHT;
    xSpeed = FIRE_X_SPEED;
    ySpeed = -FIRE_Y_SPEED;
}

void FireballSprite::goUpLeft()
{
    statusFlag = FIRE_GO_UP_LEFT;
    xSpeed = -FIRE_X_SPEED;
    ySpeed = -FIRE_Y_SPEED;
}

void FireballSprite::goDownLeft()
{
    statusFlag = FIRE_GO_DOWN_LEFT;
    xSpeed = -FIRE_X_SPEED;
    ySpeed = FIRE_Y_SPEED;
}

void FireballSprite::goDownRight()
{
    statusFlag = FIRE_GO_DOWN_RIGHT;
    xSpeed = FIRE_X_SPEED;
    ySpeed = FIRE_Y_SPEED;
}

void FireballSprite::explode()
{
     statusFlag = FIRE_EXPLODE;
     xSpeed = 0;
     ySpeed = 0;
     currentSprite=0; //need to start animation at the begining. 
}

void FireballSprite::gone()
{
    statusFlag = FIRE_GONE;
    xSpeed = 0;
    ySpeed = 0;
    currentSprite=0;
}

bool FireballSprite::isDead()
{
    if(statusFlag == FIRE_GONE) return true;
    else return false;
}

bool FireballSprite::isLive()
{
    if(statusFlag == FIRE_GONE || statusFlag == FIRE_EXPLODE) return false;
    else return true;
}

void FireballSprite::setSource(SpriteGame* source)
{
    this->source = source;
}

SpriteGame* FireballSprite::getSource()
{
    return source;
}
