#include "Scenes.h"
#include "Map.h"
#include "Player.h"
#include "Ui.h"
#include "FileIO.h"
#include "Game.h"
#include <conio.h>
#include <iostream>
#include <windows.h>

//todo: remaining missions: add patrol point, ADD SCORE SYSTEM


void Ui::PrintLevel(Level& LevelObj, Scenes level, Player& player)
{
	//if the player is in combat- skip frame print
	if (player.InCombat) return;

	system("cls");

	// Draw the whole map once at start
	MapDraw(LevelObj.GetMap());
	std::cout << std::endl;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Colors::DARK_CYAN);
	std::cout << "-= Game Status =-" << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	std::cout << "Current Level: ";
	SetConsoleTextAttribute(hConsole, Colors::DARK_YELLOW); // DarkYellow
	std::cout << static_cast<int>(level) << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	std::cout << "Player coordinates: ";
	SetConsoleTextAttribute(hConsole, Colors::DARK_BLUE);
	std::cout << player.GetPosition().x << " , " << player.GetPosition().y << std::endl;
	SetConsoleTextAttribute(hConsole, 7);

	std::cout << "Key On Player: ";
	if (player.IsKeyAcquired())
	{
		SetConsoleTextAttribute(hConsole, Colors::LIGHT_GREEN);
		std::cout << "V" << std::endl;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, Colors::LIGHT_RED);
		std::cout << "X" << std::endl;
	}

	PlayerParty party = *player.GetParty();
	std::cout << "Player Party Info:\n";
	party.PrintParty();

	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	std::cout << "Notifications:" << std::endl;

	// getting and setting the console cursor position for notifications
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
		notificationLineIndex = csbi.dwCursorPosition;

}


void Ui::MapDraw(Map& map) 
{
	FileIO::PrintLines(map.GetMapMatrix());
}


void Ui::PrintPlayerPartyInfo(Player& player)
{
	PlayerParty party =  *player.GetParty();
	std::cout << "Player Party Info:\n";

	party.PrintParty();
}


void Ui::Tutorials()
{
	system("cls");

	std::cout << "Elementia \n"
		<< "Created by - Pe'er Malul & Thai Lazover Besher\n\n"
		<< "Welcome to our game! Enjoy and... try not to die too fast (the others didn't have much luck..)\n";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	RequireEnterPressToProgress();

	std::cout << "Tutorials:\n"
		<< "Move: W/A/S/D or arrow keys.\n"
		<< "Interact: step onto objects (chests, keys, exit).\n\n"
		<< "Combat:\n"
		<< "  On your turn choose: 1=Attack, 2=Use Item, 3=Switch Unit\n"
		<< "  For Attack: 1=Normal or 2=Elemental (strong/weak vs. enemy element)\n\n"
		<< "Legend:\n"
		<< "  " << Symbols::PLAYER << " = Your character\n"
		<< "  " << Symbols::ENEMY << " = Enemy (enter battle range to fight)\n"
		<< "  " << Symbols::WALL << " = Wall (impassable)\n"
		<< "  " << Symbols::FULL_CHEST << " = Full Chest (move on it for a random reward)\n"
		<< "  " << Symbols::EMPTY_CHEST << " = Empty Chest (already looted)\n"
		<< "  " << Symbols::KEY << " = Key (must pick up to open exit)\n"
		<< "  " << Symbols::EXIT << " = Exit (leaves level if you have a key)\n\n"
		<< "Goal: Survive all 3 levels. Good luck!\n";

		Sleep(1500);
		std::cout << "....Oh, almost forgot! - press Enter to return to the opening screen.";

	RequireEnterPressToProgress();

	PrintOpeningScreen();
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


Scenes Ui::PrintOpeningScreen()
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
			return Scenes::TUTORIAL; 
		}
		else if (input == "S" || input == "s")
		{
			return Scenes::LEVEL_1; 
		}
		else
		{
			std::cout << "Invalid input. Please try again.\n";
		}
	} while (input != "S" && input != "s" && input != "T" && input != "t");
}


void Ui::PrintCombatVisual(Elements enemyElement)
{
	switch (enemyElement)
	{
		case Elements::FIRE:
			FileIO::PrintLines(FileIO::LoadFileLines("FireElemental.txt"));
			break;

		case Elements::WATER:
			FileIO::PrintLines(FileIO::LoadFileLines("WaterElemental.txt"));
			break;

		case Elements::GRASS:
			FileIO::PrintLines(FileIO::LoadFileLines("GrassElemental.txt"));
			break;

		default:
			break;
	}
}


void Ui::PrintWinScreen()
{
	system("cls");
	FileIO::PrintLines(FileIO::LoadFileLines("WinScreen.txt"));
	RequireEnterPressToProgress();
}


void Ui::PrintLoseScreen()
{
	system("cls");
	FileIO::PrintLines(FileIO::LoadFileLines("LoseScreen.txt"));
	RequireEnterPressToProgress();
}


void Ui::PrintLevelTransition()
{
	system("cls");
	for(int i = 0; i < 60; ++i)
	{
		std::cout << "Loading next level...\n";
		Sleep(200);
		std::cout << "##########################################################################" << std::endl;
	}
}


void Ui::PrintNotification(const Items Item)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, {0 , notificationLineIndex.Y });

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

	SetConsoleCursorPosition(hConsole, { 0 , notificationLineIndex.Y });
	std::cout << '\r' << std::string(lastNotificationLength, ' ') << '\r'; // Clear the notification line

	lastNotificationLength = 80;
}

void Ui::PrintNotification(const std::string message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { 0 , notificationLineIndex.Y });

	std::cout << message;

	Sleep(2500);

	SetConsoleCursorPosition(hConsole, { 0 , notificationLineIndex.Y });
	std::cout << '\r'	<< std::string(lastNotificationLength, ' ') << '\r'; // Clear the notification line

	lastNotificationLength = message.size();
}