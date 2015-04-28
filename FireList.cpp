//////////Mikey//////////
#include "FireList.h"
#include "FireballSprite.h"
#include "Enemy.h"


FireList::FireList()
{
    fireBallCount = 0;
}

FireList::~FireList()
{
    //delete fireBalls
    for(int i=0; i<fireBallCount; i++)
    {
        delete fireBalls[i]; //don't need to check for NULL can delete a zero poniter (its ignored). 
        fireBalls[i] = NULL;
    }
}

void FireList::add(FireballSprite* newfireBall)
{
     bool insert = false;
    if(fireBallCount < MAX_FIRE) //add to the end
    {
        fireBalls[fireBallCount] = newfireBall;    
        fireBallCount++;   
        insert = true;  
    }
    else  //look for dead fireBall
    {
        int i =0;
        
        //At this point we've filled the whole fireBall array
        //so to add another we're going to replace stuff. 
        while(i<fireBallCount && insert != true)
        {
           if(fireBalls[i]->isDead() == true)
           {
               delete fireBalls[i];
               fireBalls[i] = newfireBall;
               insert = true;
               //Don't increase fireBallCount 
           }
           i++;
        }
   }

   //If there is no space in the array, drop the fireBall. 
   if(insert == false) delete newfireBall;
}

void FireList::blit(SDL_Surface* screen)
{
    if(fireBallCount > 0)
    {
        for(int i=0; i<fireBallCount; i++)
        {
            if(fireBalls[i] != NULL)
            {   
                fireBalls[i]->blit(screen);
            }
        }

    }
}

void FireList::update(float scalar)
{
    if(fireBallCount > 0)
    {
        for(int i=0; i<fireBallCount; i++)
        {
            if(fireBalls[i] != NULL)
            {    
                fireBalls[i]->update(scalar);
            }
        }
    }
}


void FireList::crudeCollisionCheck(Enemy* target)
{
    for(int i=0; i<fireBallCount; i++)
    {
        if(fireBalls[i]->isLive())
        {
            int targetStatus = target->getStatus();
            if(targetStatus != Enemy::SPRITE_EXPLODE && targetStatus != Enemy::SPRITE_GONE)
            {
                if(fireBalls[i]->getSource() != target) //don't let mech shoot itself ;-)
                {
                    if(fireBalls[i]->circularCollisionCheck(target))
                    {
                        //Inform fireBall its explode time!
                        //will change this to hit at some point
                        //so I can inform the mech that fired.
                        fireBalls[i]->explode();

                        //inform target he's hit
                        target->explode();
                    }
                }
            }
        }
    }
}



