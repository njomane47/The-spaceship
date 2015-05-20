#include <allegro5\allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
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


void Initenemy(enemy enemys[], int size);
void Drawenemy(enemy eneyms[], int size);
void Startenemy(enemy enemys[], int size);
void Updateenemy(enemy enemys[], int size);
void Collideenemy(enemy enemys[], int cSize, SpaceShip &ship);


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

	//Initialization Functions
	if (!al_init())
	{
		return -1;								//init Allegro
	}

	display = al_create_display(WIDTH, HEIGHT);//create our display

	if (!display)
	{
		return -1;
	}

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);

	shipimage = al_load_bitmap("Kepler-sprite.png");
	al_convert_mask_to_alpha(shipimage, al_map_rgb(255, 0, 255));



	srand(time(NULL));// seeds the randam num generator with the current time
	InitShip(ship, shipimage);//init ship object
	InitBullet(bullets, NUM_BULLETS);
	InitComet(comets, NUM_COMETS);

	font18 = al_load_font("Yorkville.ttf", 18, NULL);

	al_register_event_source(event_queue, al_get_keyboard_event_source());//register keyboard
	al_register_event_source(event_queue, al_get_timer_event_source(timer));//register timer
	al_register_event_source(event_queue, al_get_display_event_source(display));//register display






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
	al_draw_filled_rectangle(ship.x, ship.y - 9, ship.x + 10, ship.y - 7, al_map_rgb(255, 255, 0));
	al_draw_filled_rectangle(ship.x, ship.y + 9, ship.x + 10, ship.y + 7, al_map_rgb(255, 255, 0));

	al_draw_filled_triangle(ship.x - 12, ship.y - 17, ship.x + 12, ship.y, ship.x - 12, ship.y + 17, al_map_rgb(0, 255, 0));
	al_draw_filled_rectangle(ship.x - 12, ship.y - 2, ship.x + 15, ship.y + 2, al_map_rgb(255, 255, 0));*/

	int fx = (ship.curFrame % ship.animationColumns)*ship.frameWidth;
	int fy = ship.animationRow*ship.frameHeight;

	al_draw_bitmap_region(ship.image, fx, fy, ship.frameWidth, ship.frameHeight, ship.x - ship.frameWidth / 2, ship.y - ship.frameHeight / 2, 0);

	al_draw_filled_rectangle(ship.x - ship.boundx, ship.y - ship.boundy, ship.x + ship.boundx, ship.y + ship.boundy, al_map_rgba(255, 0, 255,100)); //helps you get the boundry box of your ship or any bit map


}
void MoveShipUp(SpaceShip &ship)
{
	ship.animationRow = 0;
	ship.y -= ship.speed;
	if (ship.y < 0) // if it trys to go off the screen
		ship.y = 0;

}
void MoveShipDown(SpaceShip &ship)
{
	ship.animationRow = 2;
	ship.y += ship.speed;
	if (ship.y > HEIGHT) // greater then the screen hieght 
		ship.y = HEIGHT;
}
void MoveShipLeft(SpaceShip &ship)
{
	ship.curFrame = 2;
	ship.x -= ship.speed;
	if (ship.x < 0)
		ship.x = 0;
}
void MoveShipRight(SpaceShip &ship)
{
	ship.curFrame = 1;
	ship.x += ship.speed;
	if (ship.x > 300) // limmits how far the user is gonna go
		ship.x = 300;
}

void InitBullet(Bullet bullet[], int size)
{
	for (int i = 0; i < size; i++)
	{
		bullet[i].ID = BULLET;
		bullet[i].speed = 10;
		bullet[i].live = false;

	}
}
void DrawBullet(Bullet bullet[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		al_draw_filled_circle(bullet[i].x, bullet[i].y, 2, al_map_rgb(255, 255, 255));
	}
}
void FireBullet(Bullet bullet[], int size, SpaceShip &ship)
{
	for (int i = 0; i < size; i++)
	{
		if (!bullet[i].live)
		{
			bullet[i].x = ship.x + 17;
			bullet[i].y = ship.y;
			bullet[i].live = true;
			break;
		}
	}
}
void UpdateBullet(Bullet bullet[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (bullet[i].live)
		{
			bullet[i].x += bullet[i].speed;
			if (bullet[i].x > WIDTH)
			{
				bullet[i].live = false;
			}
		}
	}
}
void CollideBullet(Bullet bullet[], int bSize, Comet comets[], int cSize, SpaceShip &ship)
{
	for (int i = 0; i < bSize; i++)
	{
		if (bullet[i].live)
		{
			for (int j = 0; j < cSize; j++)
			{ //bulet dont have a bounding box
				if (comets[j].live)
				{	//the bullets x position has to be greater then the comets left side ||| * |
					if (bullet[i].x >(comets[j].x - comets[j].boundx) && bullet[i].y < (comets[j].y + comets[j].boundy) && bullet[i].x <(comets[j].x + comets[j].boundx) && bullet[i].y >(comets[j].y - comets[j].boundy))
					{
						bullet[i].live = false;
						comets[j].live = false;
						ship.score++;
					}
				}
			}
		}
	}
}

void InitComet(Comet comets[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		comets[i].ID = ENEMY;
		comets[i].live = false;
		comets[i].speed = 8;
		comets[i].boundx = 18;
		comets[i].boundy = 18;
	}

}
void DrawComet(Comet comets[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (comets[i].live) // we only want to draw them when they are live
		{
			al_draw_filled_circle(comets[i].x, comets[i].y, 20, al_map_rgb(255, 0, 0));
		}
	}

}
void StartComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!comets[i].live)
		{
			if (rand() % 500 == 0) // if the random number ranging form 0 to 500 is equal to 0
			{
				comets[i].live = true;
				comets[i].x = WIDTH;
				comets[i].y = 30 + rand() % (HEIGHT - 60);
				break;
			}
		}
	}
}
void UpdateComet(Comet comets[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (comets[i].live)
		{
			comets[i].x -= comets[i].speed;
			if (comets[i].x < 0)// as we update if is at the end of the screen kill the comet
			{
				comets[i].live = false;
			}
		}
	}
}
void CollideComet(Comet comets[], int cSize, SpaceShip &ship)
{
	for (int i = 0; i < cSize; ++i)
	{
		if (comets[i].live)
		{
			if (comets[i].x - comets[i].boundx < ship.x + ship.boundx && comets[i].x + comets[i].boundx > ship.x - ship.boundx && comets[i].y - comets[i].boundy < ship.y + ship.boundy && comets[i].y + comets[i].boundx > ship.y - ship.boundy)
			{
				ship.lives--;
				comets[i].live = false;
			}
		}
		else if (comets[i].x < 0)
		{

			comets[i].live = false;
			//ship.lives--;
		}
	}
}
