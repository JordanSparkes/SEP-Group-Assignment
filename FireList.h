//////////Mikey//////////
#ifndef _FIRELIST_H
#define _FIRELIST_H

#include "SDLLib.h"

class FireballSprite;
class Enemy;

/* This is a container class for fireBalls.  This has been 
developed based on the theory that an attribute with meta
data (data about data) should be a seperate class */ 

//fireBall List class glass
class FireList
{
    private:
         //The fireBalls
         static const int MAX_FIRE = 128;
         FireballSprite* fireBalls[MAX_FIRE];
         int fireBallCount;

    public:
        FireList();
        ~FireList();

        //fireBall managmenet
        void add(FireballSprite* fireBall);
        void blit(SDL_Surface* screen);
        void update(float scalar);

        //void crudeCollisionCheck(Player*);
        void crudeCollisionCheck(Enemy*);
       // void crudeCollisionCheck(fireBall*);

};
#endif
