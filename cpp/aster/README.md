Aster

An Asteroids clone using C++ and SDL/SDL_Draw

Compile from terminal with 'make'

SDL\_Draw Library: http://sdl-draw.sourceforge.net/

To do:
 - stop asteroids from insta-murdering the player when program starts
 - limit fire rate?
 		Done. Decreased maximum number of projectiles on-screen to 3
 - Improve ending animation (want to add a 'shatter' effect on ship)
 
Known issues:
 - Memory leak. Seems to be originating from the Draw\_Line() function in SDL\_Draw, but
 	only causes a problem when called from the asteroid class's draw() function
