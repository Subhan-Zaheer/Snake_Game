#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void initial_setup(); // all initial setups of game 
void snake_and_board_drawing();	// includes drawing of every element in the game
void movement_of_snake();		// movement control of snake
void logic_of_game();	  // all rules and logic of game

const int height = 20; // vertical length of board
const int width = 20; // horizontal length of board

int x_coordinate, y_coordinate, food_x, food_y, score = 0; // snake and food variables
int snake_tail_x_coordinate[50], snake_tail_y_coordinate[50]; // snake tail variables
int snake_tail_length = 0; // tail length controller variable

bool game_over = true; // gameover variable

enum direction_of_snake { STOP = 0, UP, DOWN, LEFT, RIGHT } snake_direction; // snake direction variables

int main()

{

	initial_setup(); // calling of initial function 

	while (game_over) // condition satisfaction of gameover

	{

		snake_and_board_drawing(); // calling of drawing function
		movement_of_snake(); // calling of snake movement function
		logic_of_game(); // calling of logical rules of game

	}

}

void initial_setup() // coordinates setup of elements

{

	snake_direction = STOP;   // initial direction

	// coordinates of snake position

	x_coordinate = width / 2;
	y_coordinate = height / 2;

	// coordinates of food position

	food_x = rand() % width;
	food_y = rand() % height;

}

void snake_and_board_drawing() // drawing of everyting appearing on board including board

{

	system("cls");

	for (int i = 0; i < width + 2; i++) // board upper boundary
		cout << "_";

	cout << endl;

	for (int i = 0; i < height; i++) // middle board

	{

		for (int j = 0; j < width; j++)

		{

			if (j == 0)
				cout << "|";     // right boundary

		// functions between left and right boundary

			if (i == y_coordinate && j == x_coordinate) // initial snake head
				cout << "0";

			else if (food_x == j && food_y == i) // initial food position
				cout << "o";

			else

			{

				bool print_tail = true; // variable to tell if the tail was printed or not

				for (int k = 0; k < snake_tail_length; k++) // loop to print tail segments
					if (snake_tail_x_coordinate[k] == i && snake_tail_y_coordinate[k] == j) // condition to print tail segment within boundary 

					{

						cout << "o";
						print_tail = false; // if tail is printed the space will not print so in logic a space will be subtracted for each tail segment

					}

				if (print_tail) // if no tail was printed
					cout << " "; // spaces between the left and right boundary

			}

			if (j == width - 1)    // left boundary
				cout << "|";

			if (i == 10 && j == 19) // condition to print the score at coordinates

				cout << "\t\t\t\tSCORE : " << score; // printion score

		}

		cout << endl;

	}

	for (int i = 0; i < width + 2; i++) // board bottom boundary
		cout << "*";

}

void movement_of_snake() // all movements of snake in any direction

{

	if (kbhit()) // variable to know if there is a keyboard key presssed or not

	{

		switch (getch()) // switching to keyboard key that was pressed

		{

		case 'a': // when key 'a' is pressed

			snake_direction = LEFT; // snake direction will face towards left
			break;

		case 's': // when key 's' is pressed

			snake_direction = DOWN; // snake direction will face downwards
			break;

		case 'd': // when key 'd' is pressed

			snake_direction = RIGHT; // snake direction will face right
			break;

		case 'w':  // when key 'w' is pressed

			snake_direction = UP; // snake direction will face upwards
			break;

		default: // when any other key is pressed

			break;

		}

	}

}

void logic_of_game() // all the logics and rules of game

{

	// variables to remember last position of head

	int previous_tail_x_coordinate = snake_tail_x_coordinate[0]; // 1st head x-coordinate copied
	int previous_tail_y_coordinate = snake_tail_y_coordinate[0]; // 1st head y-coordinate copied


	int previous_copy_tail_x_coordinate, previous_copy_tail_y_coordinate; // 2nd tail variable to follow the one before


	// tail before head to follow the path of head

	snake_tail_y_coordinate[0] = x_coordinate; // y-coordinate of tail to follow y-coordinate of head
	snake_tail_x_coordinate[0] = y_coordinate; // x-coordinate of head to follow x-coordinate of head

	for (int i = 1; i < snake_tail_length; i++)

	{

		// make copy of 2nd segment after first
		previous_copy_tail_x_coordinate = snake_tail_x_coordinate[i]; // copy of x-coordinate 2nd segment of 1st tail segment
		previous_copy_tail_y_coordinate = snake_tail_y_coordinate[i]; // copy of y-coordinate 2nd segment of 1st tail segment

		// giving coordinates of previous tail segment
		snake_tail_x_coordinate[i] = previous_tail_x_coordinate; // x-coordinate
		snake_tail_y_coordinate[i] = previous_tail_y_coordinate; // y-coordinate

		// storing new tail coordinates of previous segment to follow the previous segment 
		previous_tail_x_coordinate = previous_copy_tail_x_coordinate; // x-coordinate of segment
		previous_tail_y_coordinate = previous_copy_tail_y_coordinate; // y-coordinate of segment

	}

	switch (snake_direction) // switch to what is stored in snake_direction variable

	{

	case UP: // if 'w' (UP) was pressed

		--y_coordinate; // height will start increasing
		break;

	case DOWN: // if 's' (DOWN) was pressed

		++y_coordinate; // height will start decreasing
		break;

	case RIGHT: // if 'd' (RIGHT) was pressed 

		++x_coordinate; // width will start increasing
		break;

	case LEFT: // if 'a' (LEFT) was pressed

		--x_coordinate; // width will start decreasing
		break;

	}

	// conditions for if the snake head hits the boundary wall


	// right or left wall

	if (x_coordinate < 0) // if head hits left boundary wall
		x_coordinate = width - 1; // head will move towards the right boundary wall

	else if (x_coordinate >= width) //if head hits right boundary wall
		x_coordinate = 0; // head will move to left boundary wall

		// top or bottom wall

	if (y_coordinate < 0) // if head hits top boundary wall 
		y_coordinate = height - 1; // head will move toward bottom boundary wall 

	else if (y_coordinate >= height) // if head hits bottom boundary wall
		y_coordinate = 0; // head will move toward top boundary wall 

	for (int i = 0; i < snake_tail_length; i++) // loop for tail segments
		if (snake_tail_x_coordinate[i] == y_coordinate && snake_tail_y_coordinate[i] == x_coordinate)  // condition for if the head gets in touch with a tail segment
			game_over = false;

	if (x_coordinate == food_x && y_coordinate == food_y) // condition for if head hits the food

	{

		// will move the food to another location inside the boundary
		food_x = rand() % width;
		food_y = rand() % height;

		// score will increase to 5 points
		score += 5;

		//tail length will increase +1
		++snake_tail_length;

	}

}