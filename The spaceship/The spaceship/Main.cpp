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

//prototypes
void InitShip(SpaceShip &ship, ALLEGRO_BITMAP *image);
void DrawShip(SpaceShip &ship);
void MoveShipUp(SpaceShip &ship);
void MoveShipDown(SpaceShip &ship);
void MoveShipLeft(SpaceShip &ship);
void MoveShipRight(SpaceShip &ship);
void ResetShipAnimation(SpaceShip &ship, int position);


void InitBullet(Bullet bullet[], int size);
void DrawBullet(Bullet bullet[], int size);
void FireBullet(Bullet bullet[], int size, SpaceShip &ship);
void UpdateBullet(Bullet bullet[], int size);
void CollideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize, SpaceShip &ship);


void InitComet(Comet comets[], int size);
void DrawComet(Comet comets[], int size);
void StartComet(Comet comets[], int size);
void UpdateComet(Comet comets[], int size);
void CollideComet(Comet comets[], int cSize, SpaceShip &ship);

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

//definition

void InitShip(SpaceShip &ship, ALLEGRO_BITMAP *image)
{
	ship.x = 20;
	ship.y = HEIGHT / 2;
	ship.ID = PLAYER;
	ship.lives = 4;
	ship.speed = 6;
	ship.boundx = 10;
	ship.boundy = 12;
	ship.score = 0;

	ship.maxFrame = 3;
	ship.curFrame = 0;
	ship.frameCount = 0;
	ship.frameDelay = 50;
	ship.frameWidth = 45; //of each block
	ship.frameHeight = 42;//of each block

	ship.animationColumns = 3;
	ship.animationDirection = 1;
	ship.animationRow = 1;

	ship.image = image;


}
void ResetShipAnimation(SpaceShip &ship, int position)
{
	if (position == 1)
		ship.animationRow = 1;
	else
		ship.curFrame = 0;

}
void DrawShip(SpaceShip &ship)
{
	/*al_draw_filled_rectangle(ship.x, ship.y - 9, ship.x + 10, ship.y - 7, al_map_rgb(255, 255, 0));
	al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7, al_map_rgb(255, 255, 0));

	al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x + 12, ship.y, ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x + 15, ship.y + 2, al_map_rgb(255, 255, 0));*/

	int fx = (ship.curFrame % ship.animationColumns)*ship.frameWidth;
	int fy = ship.animationRow*ship.frameHeight;

	al_draw_bitmap_region(ship.image, fx, fy, ship.frameWidth, ship.frameHeight, ship.x - ship.frameWidth / 2, ship.y - ship.frameHeight / 2, 0);

	//al_draw_filled_rectangle(ship.x - ship.boundx, ship.y - ship.boundy, ship.x + ship.boundx, ship.y + ship.boundy, al_map_rgba(255, 0, 255,100)); //helps you get the boundry box of your ship or any bit map


