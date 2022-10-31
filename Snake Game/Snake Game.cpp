#include <iostream>
#include <conio.h> //gives functions to input and output format in the console
#include <windows.h> //allows us to use Win21 API functions, also includes functions from stdio.h/stdlib.h

using namespace std;

//these are global
bool gameOver;
const int height = 20; //height and width of the board
const int width = 20;

//position of the head and the fruit
int x, y, fruitX, fruitY, score; //x,y is position of snake head, fruit x, y is position of fruit, score is score

int tailX[100], tailY[100], nTail;

//variables for the direction and input
enum eDirection {STOP = 0, UP, DOWN, LEFT, RIGHT}; //this is for WASD inputs 
eDirection dir; //declare eDirection variable named "dir" short for "direction"

//4 functions
void Setup() 
{
	gameOver = false; //game over us false because during setup we need game to go 
	//we want snake to start in the middle of the screen, so we put it in the setup function
	dir = STOP; //set direction to stop so that the snake stays still in the 
	x = width / 2; //divide by 2 so that it is in middle of screen (total screen length / 2 = half of screen length)
	y = height / 2;

	fruitX = rand() % width; //spawn fruit on random part of the map
	fruitY = rand() % height;
}
void Draw()  //draw the game board, need to use the global height and width functions
{
	//since the while function will print the board infinite times, we want this clear screen function
	system("CLS");


	for(int i = 0; i < width; i++) //1 //iterate through the width of the board. THIS IS THE TOP ROW
		{
		cout << '#'; 
		}
	cout << endl;

	//print the rest of the board here 
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "#";
			}

			else if (i == y && j == x)
			{
				cout << "O"; //prints the head of the snake
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "F"; //prints F for fruit 
			}
			else //this part prints the tail in the logic 
			{
				bool print = false;

				for (int k = 0; k < nTail; k++) //may need to be nTail - 1
				{
					if (i == tailY[k] && j == tailX[k])
					{
						cout << "o";
						print = true;
					}
				}
				if (!print) { cout << " "; }
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width; i++) //2 //iterate through the width of the board. THIS IS THE BOTTOM ROW
	{
		cout << '#';
	}
	cout << endl;
	cout << "Score: " << score << endl;
}


void Input() //for the input of the user
{
	if (_kbhit()) //if the keyboard is hit
	{
		switch(_getch()) //get the character that was hit. Use switch statement so that we can use cases of what was hit
		{ //IF CAPS LOCK IS ON, THIS WONT WORK, NEED TO HAVE SET FOR CAPSLOCK AS WELL
		case 'w':
			dir = UP;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'W':
			dir = UP;
			break;
		case 'A':
			dir = LEFT;
			break;
		case 'S':
			dir = DOWN;
			break;
		case 'D':
			dir = RIGHT;
			break;
		default: //default is just default 
			break;
		}
	}
}


void Logic() //going to use the Input directions from above in this logic board
{
	//this part is to keep track of the tail
	int prevX = tailX[0];
	int prevY = tailY[0];

	tailX[0] = x;
	tailY[0] = y;

	int prev2X, prev2Y;

	for (int i = 1; i < nTail; i++) //start at 1 since 0 is alr above ^^, nTail = length of tail
	{
		prev2X = tailX[i]; //keep track of tail
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case UP: //if the UP case is used, lower Y (since the board is printed upside down)
		y--;
		break;
	case DOWN: 
		y++;
		break;
	case LEFT: 
		x--;
		break;
	case RIGHT: 
		x++;
		break;
	default:
		break;
	}

	if (x < 0 || x > width || y < 0 || y > height) //THIS IS TO TERMINATE GAME IF GONE OUTSIDE THE MAP
	{
		gameOver == true;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			gameOver = true;
		}
	}


	if (x == fruitX && y == fruitY) //if the head of the snake goes in the same coord of the fruit, then it eats it, so + 10 score
	{
		score += 10;
		fruitX = rand() % width; //SINCE FRUIT GOT EATEN, WE NEED TO SPAWN ANOTHER ONE USING SAME CODE AS EARLIER
		fruitY = rand() % height;
		nTail++; //when we eat a fruit we want to increase the lenght of the tail by 1
	}
}



int main()
{
	
	Setup();
	while (!gameOver) //while game is not over, call draw, input and logic
	{
		Draw();
		Input();
		Logic();
		Sleep(45); //this is so that the screen doesnt blink that much
	}



	return 0;  //return 0 means successful, 1 is error
}

