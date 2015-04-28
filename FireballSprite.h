//////////Mikey//////////
#ifndef _FIREBALLSPRITE_H_
#define _FIREBALLSPRITE_H_

#include "SDL.h"
#include "Image.h"
#include "Sprite.h"


class SpriteGame;

/*
  fireBall Sprite structure
*/
class FireballSprite : public Sprite
{
    private:

    //Source (mech that fired us)
    SpriteGame* source;

    //Current sprite
    int currentSprite;

    //State flag
    int statusFlag;

    //Sprite sheet clip arrays & sizes
    SDL_Rect* explodeClips;
    int explodeClipSize;
    
    //Horizontal
    SDL_Rect* travelRightClips;
    SDL_Rect* travelLeftClips;
    int travelRightClipSize;
    int travelLeftClipSize;
    
    //Vertical
    SDL_Rect* travelUpClips;
    SDL_Rect* travelDownClips;
    int travelUpClipSize;
    int travelDownClipSize;
    
    //Diagonals
    SDL_Rect* travelUpRightClips;
    SDL_Rect* travelUpLeftClips;
    SDL_Rect* travelDownRightClips;
    SDL_Rect* travelDownLeftClips;
    int travelUpRightClipSize;
    int travelUpLeftClipSize;
    int travelDownRightClipSize;
    int travelDownLeftClipSize;

    /* We can only move to this state once we've eploded (I think)*/
    void gone();

    void updateAnimation();
    void updatePosition(float scalar);

    public:

    //public constants
    static const int FIRE_X_SPEED=16;
    static const int FIRE_Y_SPEED=16;

    static const int FIRE_W = 71;
    static const int FIRE_H = 71;

    /*
     * State descriptions:
     * - FIRE_GO_RIGHT -- fireBall moving to the left
     * - FIRE_GO_LEFT -- fireBall has taken up knitting
     * - FIRE_EXPLODE -- Currently doing explode animation
     * - FIRE_GONE -- Explode animation is done, we're gone (changed this from FIRE_DEAD)
     */
    enum{FIRE_GO_RIGHT=0,FIRE_GO_LEFT,
         FIRE_GO_UP, FIRE_GO_DOWN,
         FIRE_GO_UP_RIGHT, FIRE_GO_UP_LEFT,
         FIRE_GO_DOWN_RIGHT, FIRE_GO_DOWN_LEFT,
         FIRE_EXPLODE,FIRE_GONE};

    //Constructor
    FireballSprite();

    //Destructor
    ~FireballSprite();

    //State changes
    void goLeft();
    void goRight();
    void goUp();
    void goDown();
    void goUpRight();
    void goUpLeft();
    void goDownLeft(); 
    void goDownRight();

    void explode();

    //state checks
    bool isDead();
    bool isLive();

    //Modifiers
    void setSource(SpriteGame* source);
    SpriteGame* getSource();

    //Methods - overides
    void init(SDL_Surface* spriteSheet, SDL_Rect* position);
    void init(SDL_Surface* spriteSheet, SDL_Rect* position,SpriteGame* source);

    void blit(SDL_Surface* screen);
    void update(float scalar);
};

#endif
