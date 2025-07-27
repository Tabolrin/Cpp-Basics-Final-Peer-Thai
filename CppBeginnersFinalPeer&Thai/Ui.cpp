#include "Levels.h"
#include "Map.h"
#include "Player.h"
#include "Ui.h"
#include <conio.h>
#include <iostream>
#include <windows.h>


void Ui::PrintFrame(Level& LevelObj, Levels level, Player& player)
{
	system("cls"); 

	// Draw the whole map once at start
	MapDraw(LevelObj.GetMap());
	std::cout << std::endl;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 3); // DarkCyan
	std::cout << "-= Game Status =-" << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE); // White

	std::cout << "Current Level: ";
	SetConsoleTextAttribute(hConsole, 6); // DarkYellow
	std::cout << static_cast<int>(level) << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	//---------------Replace with player part units statatus using their display 
	//std::cout << "Attack Power: ";
	//SetConsoleTextAttribute(hConsole, 5); // Magenta
	//std::cout << player.GetDamageOutput() << std::endl;
	//SetConsoleTextAttribute(hConsole, 7);

	std::cout << "Player coordinates: ";
	SetConsoleTextAttribute(hConsole, Colors::DARK_BLUE); // DarkBlue
	std::cout << player.GetPosition().x << " , " << player.GetPosition().y << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "Key On Player: ";
	if (player.IsKeyAcquired())//if player has key
	{
		SetConsoleTextAttribute(hConsole, Colors::LIGHT_GREEN); // Green
		std::cout << "V" << std::endl;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, Colors::LIGHT_RED); // Red
		std::cout << "X" << std::endl;
	}
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);
}

void Ui::MapDraw(Map map) 
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
	std::cout << "Elementum Prime\n"
		<< "Created by - Pe'er Malul & Thai L azover Besher\n\n"
		<< "Welcome to our game! Enjoy and... try not to die too fast (the others didn't have much luck..)\n";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*SetConsoleTextAttribute(hConsole, 4 | (7 << 4)); // DarkRed on Gray
	std::cout << "-=IMPORTANT!=-\n"
		<< "Please maximize the window to fill the screen for the game to work properly.\n"
		<< "Thank you for understanding. (press ENTER to continue)\n";*/
	SetConsoleTextAttribute(hConsole, 7);

	RequireEnterPressToProgress();

	std::cout << "Tutorials:\n"
		<< "Movement: W,A,S,D/arrow keys.\n"
		<< "To interact with an object just stand right next to it from the right, left, top or beneath.\n"
		<< "Sign legend:\n"
		<< Symbols::PLAYER << " = Your avatar.\n"
		<< Symbols::ENEMY << " = Enemy.\n"
		<< Symbols::WALL << " = Wall (you can't walk through it).\n"
		<< Symbols::KEY << " = Key - you must take the key in order for the passage to the next level to work!\n"
		<< Symbols::EXIT << " = Exit point - if you have the key it will send you to the next level.\n"
		<< Symbols::FULL_CHEST << " = Full Chest - will let you choose a reward.\n"
		<< Symbols::EMPTY_CHEST << " = Empty chest - a chest that was already used - useless to you now.\n"
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

const WORD Ui::GetColorForChar(char ch)
{
	// Pick color based on char
	switch (ch)
	{
		case ENEMY:
			return Colors::DARK_RED;
			break;

		case PLAYER:
			return Colors::DARK_CYAN;
			break;

		case FULL_CHEST:
			return Colors::LIGHT_YELLOW;
			break;

		case EMPTY_CHEST:
			return Colors::GRAY;
			break;

		case EXIT:
			return Colors::DARK_BLUE;
			break;

		case KEY:
			return Colors::MAGENTA;
			break;

		default:
			return Colors::BRIGHT_WHITE ;
			break;
	}
}