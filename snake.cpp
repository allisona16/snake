
/*
This is my first snake game. I am using ncurses to show the game on the terminal.

[X]Part 1: To make the field and basic set up/skeleton of the game.
[X]Part 2: To show the head of snake and fruits along with some game logic.
[]Part 3: To finish game logic and tail.
*/

#include <ncurses.h>
#include <iostream>
//#include <stdlib>
using namespace std;

bool gameOver;
const int width = 40, height = 40;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

int tailX[100], tailY[100];
int nTail = 0;

void Setup()
{
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);

	gameOver = false;
	dir = STOP;
	x = width/2;
	y = height/2;
	fruitX = (rand()%width) + 1;
	fruitY = (rand()%height) + 1;
	score = 0;
}
void Draw()
{
	clear();

	for(int i = 0; i < width+2; i++)
	{
		mvprintw(0,i,"+");
	}
	
	for(int i = 0; i < width+2; i++)
	{
		for(int j = 0; j < height+2; j++)
		{
			if(i == 0 || i == 41)
				mvprintw(i,j,"+");
			else if(j == 0 || j == 41)
				mvprintw(i,j,"|");
			else if(i == y && j == x)
				mvprintw(i,j,"O");
			else if(i == fruitY && j == fruitX)
				mvprintw(i,j,"@");
			else
				for(int k = 0; k < nTail; k++)
					if(tailX[k] == j && tailY[k] == i)
						mvprintw(i,j,"o");
		}
	}

	mvprintw(width + 3,0,"score: %d",score);
	refresh();

	//getch();
	//endwin();
}
void Input()
{
	keypad(stdscr,TRUE);
	halfdelay(1);

	int c = getch();

	switch(c)
	{
		case KEY_LEFT:
			dir = LEFT;
			break;
		case KEY_RIGHT:
			dir = RIGHT;
			break;
		case KEY_UP:
			dir = UP;
			break;
		case KEY_DOWN:
			dir = DOWN;
			break;
		case 113:      			//ASCII value for q
			gameOver = true;
			break;
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for(int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch(dir)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	if(x > width || x < 1 || y > height || y < 1)
	gameOver = true;
	
	if(x == fruitX && y == fruitY)
	{
		score ++;
		fruitX = (rand()%width) + 1;
		fruitY = (rand()%height) + 1;
		nTail ++;
	}
	for(int i = 0; i < nTail; i++)
	{
		if(tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
}

int main()
{
	Setup();
	//Draw();
	
	while(!gameOver){
		Draw();
		Input();
		Logic();
	}
	getch();
	endwin();
	return 0;
}