#include <allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>;
#include "objects.h"


const int WIDTH = 800;
const int HEIGHT = 400;
const int NUM_BULLETS = 5; // number of bullets shoot
const int NUM_COMETS = 10;
enum KEYS{ UP, DOWN, LEFT, RIGHT, SPACE };
bool keys[5] = { false, false, false, false, false };

int main()
{


	//primitive var
	bool done = false;
	bool redraw = true; // for  the timer
	const int FPS = 60; // for the timer
	bool isGameOver = false;// we wanna know when game has ended, 1st we need to start updating it and 2nd we need to start showing it to the player


	//object variables
	SpaceShip ship;
	Bullet bullets[NUM_BULLETS];
	Comet comets[NUM_COMETS];

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_BITMAP *shipimage = NULL;






	return 0;
}