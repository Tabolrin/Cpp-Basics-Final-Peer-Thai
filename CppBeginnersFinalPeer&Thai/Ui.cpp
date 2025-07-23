#include "Ui.h"
#include "Map.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include "Player.h"
#include "Levels.h"


void Ui::PrintFrame(Level& LevelObj, Levels level, Player& player)
{
	system("cls"); 

	// Draw the whole map once at start
	InitialMapDraw(LevelObj.GetMap());
	std::cout << std::endl;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 3); // DarkCyan
	std::cout << "-= Game Status =-" << std::endl;
	SetConsoleTextAttribute(hConsole, 7); // White

	std::cout << "Current Level: ";
	SetConsoleTextAttribute(hConsole, 6); // DarkYellow
	std::cout << static_cast<int>(level) << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
	/*
	std::cout << "HP: ";
	SetConsoleTextAttribute(hConsole, 4); // DarkRed
	std::cout << player.GetCurrentHP() << " / " << player.GetMaxHP() << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "Attack Power: ";
	SetConsoleTextAttribute(hConsole, 5); // Magenta
	std::cout << player.GetDamageOutput() << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "Player coordinates: ";
	SetConsoleTextAttribute(hConsole, 1); // DarkBlue
	std::cout << player.getPosition().x << " , " << player.getPosition().y << std::endl;
	SetConsoleTextAttribute(hConsole, 7);*/

	std::cout << "Key On Player: ";
	/*
	if ()//if player has key
	{
		SetConsoleTextAttribute(hConsole, 2); // Green
		std::cout << "V" << std::endl;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 4); // Red
		std::cout << "X" << std::endl;
	}*/
	SetConsoleTextAttribute(hConsole, 7);
}

void Ui::InitialMapDraw(Map map) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//system("cls");

	for (int x = 0; x < map.GetHeight(); ++x)
	{
		for (int y = 0; y < map.GetWidth(); ++y)
		{
			char ch = map.GetMapMatrix()[x][y];
			SetConsoleTextAttribute(hConsole, Ui::GetColorForChar(ch));
			std::cout << ch;
		}
		std::cout << std::endl;
	}
}

void Ui::PrintOpeningAndTutorials()
{
	std::cout << "Dimensional Mayhem\n"
		<< "Created by - Pe'er Malul\n\n"
		<< "Welcome to my game! Enjoy and... try not to die too fast (the others didn't have much luck..)\n";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 4 | (7 << 4)); // DarkRed on Gray
	std::cout << "-=IMPORTANT!=-\n"
		<< "Please maximize the window to fill the screen for the game to work properly.\n"
		<< "Thank you for understanding. (press ENTER to continue)\n";
	SetConsoleTextAttribute(hConsole, 7);

	RequireEnterPressToProgress();

	std::cout << "Tutorials:\n"
		<< "Movement: W,A,S,D/arrow keys.\n"
		<< "To interact with an object just stand right next to it from the right, left, top or beneath.\n"
		<< "Sign legend:\n"
		<< "+ = Wall.\n"
		<< "X = Your avatar.\n"
		<< "W = Enemy.\n"
		<< "+ = Wall (you can't walk through it).\n"
		<< "K = Key - you must take the key in order for the passage to the next level to work!\n"
		<< "S = Spawn point.\n"
		<< "E = Exit point - if you have the key it will send you to the next level.\n"
		<< "O = Full Chest - will let you choose a reward.\n"
		<< "Ø = Empty chest - a chest that was already used - useless to you now.\n"
		<< "¤ = Trap - a trap that you have already stepped on. Will not reduce more of your HP on touch.\n\n"
		<< "Your goal is to survive all 10 levels. Good luck and choose carefully! (;\n\n"
		<< "Furthermore, I recommend not to make long presses for continuous movement. Too long of a press will result in a long lag.\n"
		<< "....Oh, almost forgot! - press Enter to start the game.";

	RequireEnterPressToProgress();
}

void Ui::RequireEnterPressToProgress()
{
	char input;
	do
	{
		input = _getch();
	} while (input != '\r');
}

const int Ui::GetColorForChar(char ch)
{
	// Pick color based on char
	switch (ch)
	{
	case ENEMY:
		return static_cast<int>(Colors::DARK_RED);
		break;

	case PLAYER:
		return static_cast<int>(Colors::DARK_CYAN);
		break;

	case FULL_CHEST:
		return static_cast<int>(Colors::LIGHT_YELLOW);
		break;

	case EMPTY_CHEST:
		return static_cast<int>(Colors::GRAY);
		break;

	case EXIT:
		return static_cast<int>(Colors::DARK_BLUE);
		break;

	case KEY:
		return static_cast<int>(Colors::MAGENTA);
		break;

	default:
		return static_cast<int>(Colors::BRIGHT_WHITE);
		break;
	}
}