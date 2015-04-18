#ifndef _SDLLIB_H_
#define _SDLLIB_H_

#if defined(WIN32) //If OS is Windows, enable these libraries.
    #include "SDL.h" //Enable SDL Library
    #include "SDL_ttf.h" //Enable SDL custom font Library.
#else //Support for Mac and Linux as they find libraries differently.
    #include "SDL/SDL.h"
    #include "SDL/SDL_ttf.h"
#endif

#endif