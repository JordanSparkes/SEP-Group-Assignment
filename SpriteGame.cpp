//////////Mikey//////////
#include "SpriteGame.h"
#include "FireballSprite.h"
#include "Game.h"

#include <math.h>

#define DEBUG false

ItpSpriteGame::SpriteGame() : SpriteHandler()
{
    //set default direcition
    statusFlag = SPRITE_STOP;

    //Set default current sprite
    currentSprite = 0;

    //Set the number of sprites
    this->walkLeftClipSize = 10;
    this->walkRightClipSize = 10;
    walkDownClipSize = 11;
    walkUpClipSize = 11;

    walkUpRightClipSize = 16;
    walkUpLeftClipSize = 16;
    walkDownRightClipSize = 17;
    walkDownLeftClipSize = 17;

    //explode clips
    explodeClipSize = 17;

    //set pointers to NULL
    walkRightClips = NULL;
    walkLeftClips = NULL;
    front = NULL;

    //explode clips
    explodeClips = NULL;

    walkUpRightClips = NULL;
    walkUpLeftClips = NULL;
    walkDownRightClips = NULL;
    walkDownLeftClips = NULL;

    fireBallSpriteSheet = NULL; 
}

SpriteGame::~SpriteGame()
{
    //Clean up clip memory
    delete [] walkRightClips;
    delete [] walkLeftClips;
    delete front;
    delete [] explodeClips;

    walkRightClips = NULL;
    walkLeftClips = NULL;
    front = NULL;
    explodeClips = NULL;

    //Clear up sprite sheet
    SDL_FreeSurface(fireBallSpriteSheet);
    fireBallSpriteSheet = NULL; 
}

void SpriteGame::init(SDL_Surface* spriteSheet, SDL_Rect* position)
{
    //Set the sprite position
    //Copy works as there is no dynamic info in SDL_Rect
    this->rect = *position;
    rect.w = SPRITE_W; 
    rect.h = SPRITE_H; 

    
    this->walkRightClips = loadClips(this->walkRightClipSize, 6,
                                     this->rect.w, this->rect.h);
    
 
    walkLeftClips = loadClips(walkLeftClipSize, 2, rect.w, rect.h);
    walkUpClips = loadClips(walkUpClipSize, 4, rect.w, rect.h);
    walkDownClips = loadClips(walkDownClipSize, 0, rect.w, rect.h);
    
    walkUpLeftClips = loadClips(walkUpLeftClipSize, 3, rect.w, rect.h);
    walkDownLeftClips = loadClips(walkDownLeftClipSize, 1, rect.w, rect.h);
    walkUpRightClips = loadClips(walkUpRightClipSize, 5, rect.w, rect.h);
    walkDownRightClips = loadClips(walkDownRightClipSize, 7, rect.w, rect.h);

    //Load a single front facing sprite for when the sprite is stopped
    front = loadClips(1, 0, rect.w, rect.h);

    //Load explode clips
    explodeClips = loadClips(explodeClipSize, 8, rect.w, rect.h);

   //setup the sprite sheet
   this->spriteSheet = spriteSheet;
}

void SpriteGame::blit(SDL_Surface* screen)
{
   switch(statusFlag)
   {
        case SPRITE_STOP:
            SDL_BlitSurface(spriteSheet,
        	       front,
        	       screen,
        	       &rect);
        break;
        case SPRITE_EXPLODE:
           SDL_BlitSurface(spriteSheet,
                  &(explodeClips[currentSprite]),
                  screen,
                  &rect);
        break;
        case SPRITE_GONE:
          //Mech dead - don't blit
        break;
        case SPRITE_GO_LEFT:
            SDL_BlitSurface(spriteSheet,
                      &(walkLeftClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case SPRITE_GO_RIGHT:
            SDL_BlitSurface(spriteSheet,
                      &(walkRightClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case SPRITE_GO_UP:
            SDL_BlitSurface(spriteSheet,
                      &(walkUpClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case SPRITE_GO_DOWN:
            SDL_BlitSurface(spriteSheet,
                      &(walkDownClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case SPRITE_GO_UP_RIGHT:
            SDL_BlitSurface(spriteSheet,
                      &(walkUpRightClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case SPRITE_GO_DOWN_RIGHT:
            SDL_BlitSurface(spriteSheet,
                      &(walkDownRightClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case SPRITE_GO_UP_LEFT:
            SDL_BlitSurface(spriteSheet,
                      &(walkUpLeftClips[currentSprite]),
                      screen,
                      &rect);
        break;
        case SPRITE_GO_DOWN_LEFT:
            SDL_BlitSurface(spriteSheet,
                      &(walkDownLeftClips[currentSprite]),
                      screen,
                      &rect);
        break;
        default:
             printf("Something has gone badly wrong\n");
    }
}

void SpriteGame::update(float scalar)
{
   this->updateAnimation();
   this->updadtePosition(scalar);

    if(DEBUG)
    {
        printf("position < %d, %d >\n",rect.x,rect.y);
        printf("speed: < %d, %d >\n",this->getSpeedX(),this->getSpeedY());
    }
}

void SpriteGame::updateAnimation()
{
    switch(statusFlag)
    {
        case SPRITE_GO_LEFT:
            //Update the current clip
            if(currentSprite < walkLeftClipSize-1)
                currentSprite++;
            else
                currentSprite = 0;
        break;
        case SPRITE_GO_RIGHT:
            //Update the current clip
            if(currentSprite < walkRightClipSize-1)
                currentSprite++;
            else
                currentSprite = 0;
        break;
        case SPRITE_GO_UP:
            //Update the current clip
            if(currentSprite < walkUpClipSize-1)
                currentSprite++;
            else
                currentSprite = 0;
        break;
        case SPRITE_GO_DOWN:
            //Update the current clip
            if(currentSprite < walkDownClipSize-1)
                currentSprite++;
            else
                currentSprite = 0;
        break;
        case SPRITE_GO_UP_RIGHT:
            //Update the current clip
            if(currentSprite < walkUpRightClipSize-1)
                currentSprite++;
            else
                currentSprite = 0;
        break;
        case SPRITE_GO_DOWN_RIGHT:
            //Update the current clip
            if(currentSprite < walkDownRightClipSize-1)
                currentSprite++;
            else
                currentSprite = 0;
        break;
        case SPRITE_GO_UP_LEFT:
            //Update the current clip
            if(currentSprite < walkUpLeftClipSize-1)
                currentSprite++;
            else
                currentSprite = 0;
        break;
        case SPRITE_GO_DOWN_LEFT:
            //Update the current clip
            if(currentSprite < walkDownLeftClipSize-1)
                currentSprite++;
            else
                currentSprite = 0;
        break;
        case SPRITE_STOP:
            currentSprite = 0;
        break;
        case SPRITE_EXPLODE:
            if(currentSprite < explodeClipSize-1)
                currentSprite++;
            else
                gone();
        break;
        case SPRITE_GONE:
        break;
    default:
        printf("Something has gone badly wrong\n");
    }
}

void SpriteGame::updadtePosition(float scalar)
{
    //Check bounds & move the sprite
    const int FUDGE = 2;

    if(ySpeed !=0)
    {
        if(this->atWindowBottom())
        {
            // going off bottom of screen
            // This is where scrolling etc. will go
            // At the moment we just constrain

            this->setY(ItpGame::SCREEN_HEIGHT-(this->getHeight()+FUDGE));
        }
        else
        {
             rect.y += (ySpeed*scalar);
        }
    }
    else
    {
        if(this->atWindowTop())
        {
            // going off bottom of screen
            // This is where scrolling etc. will go
            // At the moment we just constrain

            this->setY(0+FUDGE);
        }
        else
        {
             rect.y += (ySpeed*scalar);
        }
    }

    //horizontal

    if(xSpeed !=0)
    {
        if(this->atWindowRight())
        {
            // going off bottom of screen
            // This is where scrolling etc. will go
            // At the moment we just constrain

            this->setX(Game::SCREEN_WIDTH-(this->getWidth()+FUDGE));
        }
        else
        {
             rect.x += (xSpeed*scalar);
        }
    }
    else
    {
        if(this->atWindowLeft())
        {
            // going off bottom of screen
            // This is where scrolling etc. will go
            // At the moment we just constrain

            this->setX(0+FUDGE);
        }
        else
        {
             rect.x += (xSpeed*scalar);
        }
    }
}

// State changes

void SpriteGame::walkLeft()
{
    this->statusFlag = SPRITE_GO_LEFT;
    this->xSpeed = -SPRITE_X_SPEED;
    this->ySpeed = 0;
}

void SpriteGame::walkRight()
{
    statusFlag = SPRITE_GO_RIGHT;
    xSpeed = SPRITE_X_SPEED;
    ySpeed = 0;
}

void SpriteGame::walkUp()
{
   statusFlag = SPRITE_GO_UP;
   xSpeed = 0;
   ySpeed = -SPRITE_Y_SPEED;
}

void SpriteGame::walkDown()
{
   statusFlag = SPRITE_GO_DOWN;
   xSpeed = 0;
   ySpeed = SPRITE_Y_SPEED;
}

void SpriteGame::stand()
{
     statusFlag = SPRITE_STOP;
     xSpeed = 0;
     ySpeed = 0;
}

void SpriteGame::explode()
{
     statusFlag = SPRITE_EXPLODE;
     xSpeed = 0;
     ySpeed = 0;
     currentSprite = 0;
}

void SpriteGame::gone()
{
     statusFlag = SPRITE_GONE;
     xSpeed = 0;
     ySpeed = 0;
}

void SpriteGame::walkUpLeft()
{
     statusFlag = SPRITE_GO_UP_LEFT;
     ySpeed = -SPRITE_Y_SPEED;
     xSpeed = -SPRITE_X_SPEED;
}

void SpriteGame::walkUpRight()
{
     statusFlag = SPRITE_GO_UP_RIGHT;
     ySpeed = -SPRITE_Y_SPEED;
     xSpeed = SPRITE_X_SPEED;
}

void SpriteGame::walkDownLeft()
{
     statusFlag = SPRITE_GO_DOWN_LEFT;
     ySpeed = SPRITE_Y_SPEED;
     xSpeed = -SPRITE_X_SPEED;
}

void SpriteGame::walkDownRight()
{
     statusFlag = SPRITE_GO_DOWN_RIGHT;
     ySpeed = SPRITE_Y_SPEED;
     xSpeed = SPRITE_X_SPEED;
}


int SpriteGame::getStatus()
{
    return statusFlag;
}

void SpriteGame::doState(int inputState)
{
    switch(inputState)
    {
        case SPRITE_GO_RIGHT:
            this->walkRight();
            break;
        case SPRITE_GO_LEFT:
            this->walkLeft();
            break;
        case SPRITE_GO_UP:
            this->walkUp();
            break;
        case SPRITE_GO_DOWN:
            this->walkDown();
            break;
        case SPRITE_GO_UP_RIGHT:
            this->walkUpRight();
            break;
        case SPRITE_GO_DOWN_RIGHT:
            this->walkDownRight();
            break;
        case SPRITE_GO_UP_LEFT:
            this->walkUpLeft();
            break;
        case SPRITE_GO_DOWN_LEFT:
            this->walkDownLeft();
            break;
        default:
            printf("ItpSpriteGame::doState(int) - passed rubbish?\n");
    }
}

void SpriteGame::fire()
{
    FireballSprite* newfireBall = new FireballSprite();
    
    //Load our mech sprite sheet
    SDL_Surface *temp = ItpImage::loadImage("fireBall.bmp",0xFF,0x0,0xFF);
    //Setup a rectangle to position the sprite on the sufrace
    //and Sprite Size
    SDL_Rect spriteRect;
    spriteRect.x = this->rect.x;
    spriteRect.y = this->rect.y;
 
    //Load sprite info
    newfireBall->init(temp, &spriteRect,this);

    //connect fireBall to game
    newfireBall->setGame(game);

    //Speed and direction 
    switch(statusFlag)
    {
        case SPRITE_GO_RIGHT:
            newfireBall->goRight();
            break;
        case SPRITE_GO_LEFT:
            newfireBall->goLeft();
            break;
        case SPRITE_GO_UP:
            newfireBall->goUp();
            break;
        case SPRITE_GO_DOWN:
            newfireBall->goDown();
            break;
        case SPRITE_GO_UP_LEFT:
            newfireBall->goUpLeft();
            break;
        case SPRITE_GO_DOWN_LEFT:
            newfireBall->goDownLeft();
            break;
        case SPRITE_GO_UP_RIGHT:
            newfireBall->goUpRight();
            break;
        case SPRITE_GO_DOWN_RIGHT:
            newfireBall->goDownRight();
            break;
        case SPRITE_STOP:
            newfireBall->goDown();
            break;
        default:
            printf("Unhandled case in ItpSpriteGame::fire() - go fix it \n");
        break;
    }

    game->addfireBallToWorld(newfireBall);
}

void SpriteGame::stepBackwards()
{
    const int FUDGE = 2;

    Sint16 newX = getX();
    newX -= (getSpeedX()*1);

    if(newX > 0)
        if((newX+getWidth()) < Game::SCREEN_WIDTH)
            this->setX(newX);
        else
        {
            newX = Game::SCREEN_WIDTH-this->getWidth()-FUDGE;
            this->setX(newX);
        }
    else
    {
        newX = 0+FUDGE;
        this->setX(newX);
    }

    Sint16 newY = getY();
    newY -= (getSpeedY()*1);

    if(newY > 0)
        if((newY+getHeight()) < Game::SCREEN_HEIGHT)
            this->setY(newY);
        else
        {
            newY = Game::SCREEN_HEIGHT-this->getHeight()-FUDGE;
            this->setY(newY);
        }
    else
    {
        newY = 0+FUDGE;
        this->setY(newY);
    }
}


int SpriteGame::getDirectionToo(SpriteGame* that)
{
    const float PI = 3.14f;
    //cos(theta) = v1 . v2 (where . is DOT)
    float angle;

    //work out v1
    float v1X, v1Y;
    v1X = this->getX() - that->getX();
    v1Y = this->getY() - that->getY();

    //normalise v1  v1' = v1 / lenght v1
    // lenght v1 = square root of ( v1X*v1X + v2Y*v2Y )
    //- note this is pythag

    float lenght = sqrt((v1X*v1X)+(v1Y*v1Y));
    v1X /= lenght;
    v1Y /= lenght;

    float v2X, v2Y;
    v2X = 0.0f;
    v2Y = 1.0f;

    //Calculate dot product
    float dot = (v1X*v2X)+(v1Y*v2Y);

    //Note angle is in radians
    angle = acos(dot);

    if(DEBUG) printf("angle is %f\n",angle);

    //Dotproduct only gives shortest angle 0-pi to
    //need fake dot product.

    //(U,V)=(U.x*V.y-U.y*V.x)
    //Fake cross product (as if 3d vectors)
    float cross = v1X*v2Y - v1Y*v2X;

    //Convert to direction!

    //get up and down out of the way first (don't need direction).
    if(angle < PI/8) return SPRITE_GO_UP;
    if(angle > 7*(PI/8)) return SPRITE_GO_DOWN;

    if(cross < 0.0f)
    {
        if(angle < PI/8)
            return SPRITE_GO_UP;
        else
            if(angle < 3*(PI/8))
                return SPRITE_GO_UP_RIGHT;
            else
                if(angle < 4*(PI/8))
                    return SPRITE_GO_RIGHT;
                else
                    return SPRITE_GO_DOWN_RIGHT;
    }
    else
    {
        if(angle < PI/8)
            return SPRITE_GO_UP;
        else
            if(angle < 3*(PI/8))
                return SPRITE_GO_UP_LEFT;
            else
                if(angle < 4*(PI/8))
                    return SPRITE_GO_LEFT;
                else
                    return SPRITE_GO_DOWN_LEFT;
    }

    //Should never get here
    return SPRITE_STOP;
}
