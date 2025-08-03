#include "Scenes.h"
#include "Map.h"
#include "Player.h"
#include "Ui.h"
#include <conio.h>
#include <iostream>
#include <windows.h>


void Ui::PrintLevel(Level& LevelObj, Scenes level, Player& player)
{
	//if the player is in combat- skip frame print
	if (player.InCombat) return;
	
	system("cls"); 

	// Draw the whole map once at start
	MapDraw(LevelObj.GetMap());
	std::cout << std::endl;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Colors::DARK_CYAN); // DarkCyan
	std::cout << "-= Game Status =-" << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE); // White

	std::cout << "Current Level: ";
	SetConsoleTextAttribute(hConsole, Colors::DARK_YELLOW); // DarkYellow
	std::cout << static_cast<int>(level) << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	// TODO:
	//---------------Replace with player party units status using their display 
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
	//SetCur

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

void Ui::Tutorials()
{
	system("cls");

	std::cout << "Elementia\n"
		<< "Created by - Pe'er Malul & Thai Lazover Besher\n\n"
		<< "Welcome to our game! Enjoy and... try not to die too fast (the others didn't have much luck..)\n";

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*SetConsoleTextAttribute(hConsole, 4 | (7 << 4)); // DarkRed on Gray
	std::cout << "-=IMPORTANT!=-\n"
		<< "Please maximize the window to fill the screen for the game to work properly.\n"
		<< "Thank you for understanding. (press ENTER to continue)\n";*/
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

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


void Ui::PrintOpeningScreen()
{
	system("cls");

	std::cout << "Elementia\n"
		<< "Created by - Pe'er Malul & Thai Lazover Besher\n\n"
		<< "Welcome to our game! Enjoy and... try not to die too fast (the others didn't have much luck..)\n";

	std::string input;
	do
	{
		input = "";
		std::cout << "Press S to start, or T to see tutorials:\n";
		std::cin >> input;

		if (input == "T" || input == "t")
		{
			Tutorials();
			return;
		}
		else if (input == "S" || input == "s")
		{

			return; // Start the game
		}
		else
		{
			std::cout << "Invalid input. Please try again.\n";
		}
	} while (input != "S" && input != "s" && input != "T" && input != "t");
}


void Ui::PrintCombatVisual()
{
	system("cls");
	std::cout << "message" << std::endl;
	std::cout << "Press Enter to continue..." << std::endl;
	RequireEnterPressToProgress();
}


void Ui::PrintWinScreen()
{
	system("cls");
	std::cout << "message" << std::endl;
	std::cout << "Press Enter to continue..." << std::endl;
	RequireEnterPressToProgress();
}


void Ui::PrintLoseScreen()
{
	system("cls");
	std::cout << "message" << std::endl;
	std::cout << "Press Enter to continue..." << std::endl;
	RequireEnterPressToProgress();
}


void Ui::PrintLevelTransition()
{
	system("cls");
	for(int i = 0; i < 20; ++i)
	{
		std::cout << "Loading next level...\n";
		Sleep(200);
		std::cout << "###############################################" << std::endl;
	}
}


void Ui::PrintNotification(const Items Item)
{
	switch (Item)
	{
		case Items::HP_POTION:
		std::cout << "You have acquired a Health Potion! Use it wisely.";
		break;

		case Items::NORMAL_ATTACK_POTION:
			std::cout << "You have acquired a Normal Attack Potion! Use it wisely.";
			break;

		case Items::ELEMENTAL_ATTACK_POTION:
			std::cout << "You have acquired an Elemental Attack Potion! Use it wisely.";
			break;

		case Items::LEVEL_KEY:
			std::cout << "You have acquired a Key! Use it to unlock the exit.";
			break;

		case Items::SMOKE_BOMB:
			std::cout << "You have acquired a Smoke Bomb! Use it to escape from combat.";
			break;

		default:
			break;
	}
	Sleep(2500);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { 0, NOTIFICATION_LINE_INDEX });
	std::cout << "                                                                                                                  "; // Clear the notification line
}