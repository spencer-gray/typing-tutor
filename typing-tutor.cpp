#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

const std::string letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int missedCount = 0;
int scoreCount = 0;
char headWord[10];
int xValues[10];
int yValues[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

const int height = 20;
const int width = 60;

// check to see if x position is already assigned
bool isInNum(int x, int arrVal[])
{
	bool result;
	int count = 0;

	for (int i = 0; i < 10; i++)
	{
		if (x == arrVal[i])
		{
			count++;
			if (count >= 2)
			{
				result = true;
				break;
			}
			else
			{
				result = false;
			}
		}
		else
		{
			result = false;
		}
	}
	return result;
}

// check to see if char entered is in array of chars
bool isInChar(char c, char arrChar[])
{
	bool result;
	for (int i = 0; i < 10; i++)
	{
		if (c == arrChar[i])
		{
			result = true;
			break;
		}
		else
		{
			result = false;
		}
	}
	return result;
}

// randomizes a character from the english alphabet
char randomChar()
{
	char result;
	for (int i = 0; i < 1; i++)
	{
		result = letter[rand()%52];
		if (isInChar(result, headWord))
		{
			i--;
		}
	}
	return result;
}

// finds position the char is sitting in array
int findPositionChar(char c, char arrChar[])
{
	int result;
	for (int i = 0; i < 10; i++)
	{
		if (c == arrChar[i])
		{
			result = i;
		}
	}
	return result;
}

int main(){

	srand (time(NULL));

	//initialize window
	initscr();

	int ch;
	nodelay(stdscr, TRUE);		//will not wait for user input

	bool check;

	//fill headWord array with random chars and x-values for those chars
	for (int i = 0; i < 10; i++)
	{
		headWord[i] = randomChar(); 	
		xValues[i] = (rand()%58)+1; 

		//will generate new x-values until unique
		if(isInNum(xValues[i], xValues) == true)
		{
			i--;
		}

	}


	while(check == false)
	{			
			mvwprintw(stdscr, height, 1, "Current score is %d. Enter ESC to exit", scoreCount);

			for (int i = 0; i <= height-1; i++)
			{
				if (i == 0)
				{
					for (int j = 0; j < 10; j++)
					{
						if (yValues[j] == 1)
						{
							mvaddch(yValues[j], xValues[j], headWord[j]);
							yValues[j] = yValues[j] + 1;
						}
					}
					mvwprintw(stdscr, height, 1, "Current score is %d. Enter ESC to exit", scoreCount);
					refresh();
				}
				else if (i == height-1)
				{
					for (int j = 0; j < 10; j++)
					{
						if (yValues[j] == height-1)
						{
							mvaddch(yValues[j]-1, xValues[j], ' ');
							missedCount++;
							yValues[j] = 1;	
							xValues[j] = (rand()%58)+1;		
							headWord[j] = randomChar();
						}

					}
					refresh();
				}
				else
				{
					for (int j = 0; j < 10; j++)
					{
						mvaddch(yValues[j]-1, xValues[j], ' ');
						mvaddch(yValues[j], xValues[j], headWord[j]);
						yValues[j] = yValues[j]+1; 
						if (yValues[j] == height-1)
						{
							mvaddch(yValues[j]-1, xValues[j], ' ');
							missedCount++;
							yValues[j] = 1;		
							xValues[j] = (rand()%58)+1;		
							headWord[j] = randomChar();		
						}
					}
					mvwprintw(stdscr, height, 1, "Current score is %d. Enter ESC to exit", scoreCount);
					refresh();
				}
				char c = getch();	
				if(isInChar(c, headWord)==true)
				{
					mvaddch(yValues[findPositionChar(c, headWord)]-1, xValues[findPositionChar(c, headWord)], ' ');
					headWord[findPositionChar(c, headWord)] = randomChar();

					//sending back to first row
					yValues[findPositionChar(c, headWord)] = 1;
					xValues[findPositionChar(c, headWord)] = (rand()%58)+1;

					scoreCount++;
				}
				else if(c == 27)
				{
					check = true;
					break;
				}

				napms(200);
					
				refresh();
		
			}
		refresh();
	}

	endwin();

	// Final score output
	std::cout << "Total score: " << scoreCount << std::endl;
	std::cout << "Total missed: " << missedCount << std::endl;

	return 0;
}