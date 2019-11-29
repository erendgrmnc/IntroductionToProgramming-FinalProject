#include "pch.h"
#include <iostream>
#include "windows.h"
#include "ctime"

using namespace std;

enum DIRECTION // Enumeration for directions.
{
	DIRECTION_STOP = 0,
	DIRECTION_LEFT = 1,
	DIRECTION_RIGHT = 2,
	DIRECTION_UP = 3,
	DIRECTION_DOWN = 4

};

struct plane // Struct that contains our plane variables.
{
	int x;
	int y;

	DIRECTION direction;

	char character;

};

struct bullet // Struct that contains our bullet variables.
{
	int x;
	int y;

	DIRECTION direction;

	char character;
};

struct enemy // Struct that contains our enemy variables.
{
	int x;

	int y;

	DIRECTION direction;

	char character;
};

// SCENE VALUES
const int width = 80;
const int height = 20;
char scene[width][height];

//PLANE VALUES
const int max_plane_height = 3;
const int max_plane_width = 3;
int plane_height = 0;
int plane_width = 0;

//KEY VALUES
char keys[256];

//BULLET VALUES
const int max_bullet_lenght = 1;
int bullet_lenght = 0;

//ENEMY VALUES
const int max_enemy_height = 2;
const int max_enemy_width = 2;
int enemy_height = 0;
int enemy_width = 0;


plane plane_size[max_plane_width][max_plane_height] = { NULL }; //Defining the plane.

bullet bullet_size[max_bullet_lenght] = { NULL };//Defining the bullet.

enemy enemy_size[max_enemy_width][max_enemy_height] = { NULL };//Defining the enemy.

//FUNCTION DECLARATIONS.

void set_cursor(int x, int y);

void draw_scene();

void clear_scene();

void set_borders();

void hide_cursor();

void read_keyboard(char tuslar[]);

void keyboard_control();

void create_plane();

void put_plane_to_stage();

void move_plane();

void put_bullet_to_stage();

void fire_bullet();

void create_bullet();

void create_enemy();

void put_enemy_to_stage();

void move_enemy();

void explode_enemy();

void firing();

void explode_plane();

int main()
{

	hide_cursor();
	set_borders();

	create_plane();
	create_enemy();


	while (true)
	{

		clear_scene();
		set_borders();

		move_plane();

		firing();

		keyboard_control();

		put_plane_to_stage();


		put_enemy_to_stage();

		explode_enemy();

		explode_plane();

		set_cursor(0, 0);
		draw_scene();


	}

	cin.get();
}

void set_cursor(int x, int y) //Placing cursor to x,y coordinates of our stage.
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_scene() // Creates a stage.
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			cout << scene[i][j];
		}
		cout << endl;
	}
}

void set_borders() // Put a character we placed to our borders.So game site is clearly seen.
{
	for (int i = 0; i < width; i++)
	{
		scene[i][0] = 219;

		scene[i][height - 1] = 219;

	}

	for (int j = 0; j < height; j++)
	{
		scene[0][j] = 219;

		scene[width - 1][j] = 219;
	}
}

void hide_cursor() //This function hides the cursor.So there will be no lagging in the gametime.
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void clear_scene() // Clears the scene by putting space in our scene char arrays elements.
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			scene[i][j] = ' ';
		}
	}
}

void read_keyboard(char keys[]) // Thıs functions gets keys from keyboard at asynchronous time.
{
	for (int x = 0; x < 256; x++)
		keys[x] = (char)(GetAsyncKeyState(x) >> 8);

}

void keyboard_control() // We define keys to move our plane when we press that key.Thıs function moves our plane when we press the right key.
{
	read_keyboard(keys);

	for (int i = 0; i < plane_height; i++)
	{
		for (int j = 0; j < plane_width; j++)
		{

			if (keys['W'] != 0) //If key w is pressed, decrease plane's y coordination by one.
			{
				plane_size[i][j].direction = DIRECTION_UP;
			}


			else if (keys['S'] != 0)//If key w is pressed, increase plane's y coordination by one.
			{
				plane_size[i][j].direction = DIRECTION_DOWN;
			}

			else // If nothing is pressed, plane will stop.
			{
				plane_size[i][j].direction = DIRECTION_STOP;
			}


		}
	}
}

void create_plane() //Thıs function is creating plane's variables.
{
	plane_width = 3;
	plane_height = 3;

	plane_size[0][0].x = 1;
	plane_size[0][0].y = 10;
	plane_size[0][0].direction = DIRECTION_STOP;
	plane_size[0][0].character = 178;

	plane_size[1][0].x = 1;
	plane_size[1][0].y = 11;
	plane_size[1][0].direction = DIRECTION_STOP;
	plane_size[1][0].character = 178;

	plane_size[2][0].x = 1;
	plane_size[2][0].y = 12;
	plane_size[2][0].direction = DIRECTION_STOP;
	plane_size[2][0].character = 178;

	plane_size[1][1].x = 2;
	plane_size[1][1].y = 11;
	plane_size[1][1].direction = DIRECTION_STOP;
	plane_size[1][1].character = 178;



}

void put_plane_to_stage()
{
	for (int i = 0; i < plane_height; i++) // For planes height,
	{
		for (int j = 0; j < plane_width; j++) // For planes width, Put plane to stage according to plane's values.
		{
			int x = plane_size[i][j].x;
			int y = plane_size[i][j].y;

			scene[x][y] = 178;

		}

	}
}

void move_plane() // Thıs function moves the plane according to the keyboard_control function.
{
	for (int i = 0; i < plane_height; i++)
	{
		for (int j = 0; j < plane_width; j++)
		{
			switch (plane_size[i][j].direction) {


			case DIRECTION_UP: // If direction data is up , decrase plane y coordinate by one.
				plane_size[i][j].y--;
				break;
			case DIRECTION_DOWN:// If direction data is down , increase plane y coordinate by one.
				plane_size[i][j].y++;
				break;
			}
		}

	}
}

void create_bullet() // This function creates the bullet values.
{
	if (keys['K'] != 0)
	{


		bullet_lenght = 1;

		bullet_size[0].x = plane_size[1][1].x;
		bullet_size[0].y = plane_size[1][1].y;

		bullet_size[0].character = 219;
		bullet_size[0].direction = DIRECTION_RIGHT;
	}
}

void put_bullet_to_stage() // This function puts the bullet to the scene according it's values
{




	for (int i = 0; i < bullet_lenght; i++) // For bullets lenght,
	{
		int x = bullet_size[i].x;
		int y = bullet_size[i].y;

		if (bullet_size[i].x == 79) // If bullets put's outside the borders, destroy bullet.
		{
			bullet_size[i].character = { NULL };

			scene[x][y] = ' ';
			return;

		}



		Sleep(2);

		scene[x][y] = 219; // Scene's elements of bullet's x,y coordinates will be printed bullet.


	}


	fire_bullet();


}

void fire_bullet() // This function moves the bullet on the scene. 
{

	for (int i = 0; i < bullet_lenght; i++)
	{


		int x = bullet_size[0].x;
		int y = bullet_size[0].y;

		bullet_size[0].x++; // Increase bullets x coordinate by one.

		scene[x][y] = 219; // After that put bullet to the scene 

		scene[x - 1][y] = ' '; // Remove the old coordinates from bullet.

		Sleep(2);

	}

}

void create_enemy() // This function creates the enemey values.
{
	srand(time(NULL));

	enemy_width = 2;
	enemy_height = 2;

	int enemy_coordinate = 1 + rand() % 19;

	enemy_size[0][0].x = 76;
	enemy_size[0][0].y = enemy_coordinate;
	enemy_size[0][0].direction = DIRECTION_LEFT;
	enemy_size[0][0].character = 219;

	enemy_size[0][1].x = 77;
	enemy_size[0][1].y = enemy_coordinate;
	enemy_size[0][1].direction = DIRECTION_LEFT;
	enemy_size[0][1].character = 219;

	enemy_size[1][0].x = 76;
	enemy_size[1][0].y = enemy_coordinate;
	enemy_size[1][0].direction = DIRECTION_LEFT;
	enemy_size[1][0].character = 219;


	enemy_size[1][1].x = 77;
	enemy_size[1][1].y = enemy_coordinate;
	enemy_size[1][1].direction = DIRECTION_LEFT;
	enemy_size[1][1].character = 219;


}

void put_enemy_to_stage()  // This function puts enemy to the stage according to it's values.
{
	for (int i = 0; i < enemy_width; i++)
	{
		for (int j = 0; j < enemy_height; j++)
		{
			int x = enemy_size[i][j].x;
			int y = enemy_size[i][j].y;

			if (enemy_size[i][j].x == -1)
			{
				enemy_size[i][j].character = { NULL };

				scene[x][y] = ' ';
				return;
			}


			enemy_size[i][j].x--;
			Sleep(2);


			scene[x][y] = 219;


		}

	}
}

void move_enemy() //This function moves enemy on the stage according the enemy values.
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < enemy_height; j++)
		{
			switch (enemy_size[j][j].direction)

				case DIRECTION_LEFT:
					enemy_size[j][j].x--; //Decreases enemey's x coordination by one so it can move left along the stage.

		}
	}
}

void explode_enemy() //This function arranges the enemy destroy condition.
{
	for (int i = 0; i < enemy_width; i++)
	{
		for (int j = 0; j < enemy_height; j++)
		{
			int x = enemy_size[i][j].x;
			int y = enemy_size[i][j].y;

			if (enemy_size[i][j].x == bullet_size[0].x && enemy_size[i][j].y == bullet_size[0].y) //IF bullet's x-y coordinates equal to enemy's x-y coordiinates, destroy them both.
			{
				enemy_size[i][j] = { NULL };
				bullet_size[0] = { NULL };
				enemy_size[i][j].x = -1;
				enemy_size[i][j].y = -1;


				return;

			}
		}

	}
}

void firing() // This function will arange firing mechanism.
{
	if (keys['K'] != 0) //If "K" key is pressed,Function creates a bullet, Than put's it in the stage.
	{

		create_bullet();

	}

	put_bullet_to_stage();
}

void explode_plane() // This funtion arranges the games ending condition.
{
	for (int i = 0; i < enemy_width; i++)
	{
		for (int j = 0; j < enemy_height; j++)
		{
			int x = enemy_size[i][j].x;
			int y = enemy_size[i][j].y;

			if (enemy_size[i][j].x == plane_size[i][j].x && enemy_size[i][j].y == plane_size[i][j].y) // If planes and enemeys x-y coordinates are same, Than stop the application and print game over.
			{

				cout << "GAMEOVER" << endl;

				system("pause");

			}
		}

	}
}
