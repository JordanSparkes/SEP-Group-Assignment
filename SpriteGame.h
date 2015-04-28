//////////Mikey//////////
#ifndef _SPRITEGAME_H_
#define _SPRITEGAME_H_

#include "SDLLib.h"
#include "SpriteHandler.h"

class FireballSprite;

/*
  Sprite structure
*/
class SpriteGame : public SpriteHandler
{
    protected:

    //Current sprite
    int currentSprite;

    //Status flag
    int statusFlag;

    //Sprite sheet clip arrays
    SDL_Rect* walkRightClips;
    SDL_Rect* walkLeftClips;
    SDL_Rect* walkUpClips;
    SDL_Rect* walkDownClips;

    //diagonals
    SDL_Rect* walkUpRightClips;
    SDL_Rect* walkUpLeftClips;
    SDL_Rect* walkDownRightClips;
    SDL_Rect* walkDownLeftClips;

    //Front facing clip
    SDL_Rect* front;

    //Explode clips
    SDL_Rect* explodeClips;

    int walkRightClipSize;
    int walkLeftClipSize;
    int walkUpClipSize;
    int walkDownClipSize;

    int walkUpRightClipSize;
    int walkUpLeftClipSize;
    int walkDownRightClipSize;
    int walkDownLeftClipSize;

    //Explode clips size
    int explodeClipSize;

    //Pre-loaded fireBall spritesheet
    SDL_Surface *fireBallSpriteSheet;

  

    //Decomposition of update method
    void updateAnimation();
    void updadtePosition(float scalar);

    public:

    //public constants
    static const int SPRITE_X_SPEED=5;
    static const int SPRITE_Y_SPEED=5;

    static const int SPRITE_W = 87;
    static const int SPRITE_H = 80;

    enum mechStates {SPRITE_GO_RIGHT=0,SPRITE_GO_LEFT,
         SPRITE_GO_DOWN,SPRITE_GO_UP,
         SPRITE_GO_UP_LEFT,SPRITE_GO_UP_RIGHT,
         SPRITE_GO_DOWN_LEFT,SPRITE_GO_DOWN_RIGHT,
         SPRITE_STOP,SPRITE_EXPLODE, SPRITE_GONE};

    //Constructor
    ItpSpriteGame();

    //Destructor
    ~ItpSpriteGame();

    void walkLeft();
    void walkRight();
    void walkUp();
    void walkDown();
    void stand();

    void walkUpLeft();
    void walkUpRight();

    void walkDownLeft();
    void walkDownRight();

    void fire();
    void explode();
    void gone();
 
    int getStatus();

    void doState(int);

    //For collsion resolution
    void stepBackwards();
 
    int getDirectionToo(SpriteGame*);

    //Methods - overides
    void init(SDL_Surface* spriteSheet, SDL_Rect* position);

    void blit(SDL_Surface* screen);
    void update(float scalar);
};

#endif
