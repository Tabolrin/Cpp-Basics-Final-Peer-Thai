#include "Scenes.h"
#include "Map.h"
#include "Player.h"
#include "Ui.h"
#include "Score.h"
#include "FileIO.h"
#include "Game.h"
#include <conio.h>
#include <iostream>
#include <windows.h>


COORD Ui::notificationLineIndex = { 0, 0 };
int   Ui::lastNotificationLength = 0;
static bool s_mapDrawnOnce = false;


void Ui::PrintLevel(Level& LevelObj, Scenes level, Player& player, bool fullRedraw)
{
	//if the player is in combat- skip frame print
	if (player.InCombat) return;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (fullRedraw)
	{
		system("cls");

		// Draw the whole map 
		MapDraw(LevelObj.GetMap());
		std::cout << std::endl;
	}

	// move cursor to start of HUD area (just below the map)
	COORD hudPos = { 0, static_cast<SHORT>(LevelObj.GetMap().GetHeight() + 1) };
	SetConsoleCursorPosition(hConsole, hudPos);

	SetConsoleTextAttribute(hConsole, Colors::DARK_CYAN);
	std::cout << "-= Game Status =-" << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	std::cout << "Current Level: ";
	SetConsoleTextAttribute(hConsole, Colors::DARK_YELLOW); // DarkYellow
	std::cout << static_cast<int>(level) << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	std::cout << "Player coordinates: ";
	SetConsoleTextAttribute(hConsole, Colors::DARK_BLUE); // DarkBlue
	std::cout << player.GetPosition().x << " , " << player.GetPosition().y << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

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

	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE); // Red

	std::cout << "Party status:\n";
	player.GetParty()->PrintParty();

	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	std::cout << "Notifications:" << std::endl;

	// getting and setting the console cursor position for notifications
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
		notificationLineIndex = csbi.dwCursorPosition;
}


void Ui::MapDraw(Map& map) 
{
	for (int x = 0; x < map.GetHeight(); ++x)
	{
		for (int y = 0; y < map.GetWidth(); ++y)
		{
			Vector2 pos = Vector2(static_cast<int>(x), static_cast<int>(y));
			char ch = map.GetMapMatrix()[x][y];
			map.UpdatePosition(pos, ch);
		}
	}
}


void Ui::PrintPlayerPartyInfo(Player& player)
{
	PlayerParty party =  *player.GetParty();
	std::cout << "Player Party Info:\n";

	party.PrintParty();
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

	FileIO::PrintLines(FileIO::LoadFileLines("OpeningScreen.txt"));

	std::string input;

	do
	{
		input = "";
		std::cin >> input;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Clear the input buffer

		if (input == "S" || input == "s")
		{
			return Scenes::LEVEL_1; 
		}
		else
		{
			std::cout << "Invalid input. Please try again.\n";
			Sleep(3000);
		}
	} while (input != "S" && input != "s" );
}


void Ui::PrintCombatVisual(Elements enemyElement)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (enemyElement)
	{
		case Elements::FIRE:
			SetConsoleTextAttribute(hConsole, Colors::LIGHT_RED);
			FileIO::PrintLines(FileIO::LoadFileLines("FireElemental.txt"));
			break;

		case Elements::WATER:
			SetConsoleTextAttribute(hConsole, Colors::LIGHT_BLUE);

			FileIO::PrintLines(FileIO::LoadFileLines("WaterElemental.txt"));
			break;

		case Elements::GRASS:
			SetConsoleTextAttribute(hConsole, Colors::LIGHT_GREEN);
			FileIO::PrintLines(FileIO::LoadFileLines("GrassElemental.txt"));
			break;

		default:
			break;
	}
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

}


void Ui::PrintWinScreen()
{
	system("cls");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Colors::LIGHT_GREEN);
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "--==Final Score: " << Score::Get() << "==--" << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	FileIO::PrintLines(FileIO::LoadFileLines("WinScreen.txt"));
}


void Ui::PrintLoseScreen()
{
	system("cls");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, Colors::LIGHT_GREEN);
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "--==Final Score: " << Score::Get() << "==--" << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	FileIO::PrintLines(FileIO::LoadFileLines("LoseScreen.txt"));
}


void Ui::PrintLevelTransition()
{
	system("cls");
	std::cout << "Loading next level...\n";

	for(int i = 0; i < 20; ++i)
	{
		Sleep(100);
		std::cout << "################################################" << std::endl;
	}
	system("cls");
}


void Ui::PrintNotification(const Items Item)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, {0 , notificationLineIndex.Y });
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	std::string text;
	switch (Item)
	{
	case Items::HP_POTION:  
		text = "You have acquired a Health Potion! Use it wisely.";
		break;

	case Items::NORMAL_ATTACK_POTION: 
		text = "You have acquired a Normal Attack Potion! Use it wisely."; 
		break;

	case Items::ELEMENTAL_ATTACK_POTION:
		text = "You have acquired an Elemental Attack Potion! Use it wisely.";
		break;

	case Items::LEVEL_KEY:  
		text = "You have acquired a Key! Use it to unlock the exit."; 
		break;

	case Items::SMOKE_BOMB:    
		text = "You have acquired a Smoke Bomb! Use it to escape from combat.";
		break;

	default:   
		text = "";
		break;
	}

	std::cout << text;
	lastNotificationLength = static_cast<int>(text.size());  

	Sleep(2500);

	SetConsoleCursorPosition(hConsole, { 0 , notificationLineIndex.Y });
	std::cout << '\r' << std::string(lastNotificationLength, ' ') << '\r';
}

void Ui::PrintNotification(const std::string message)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, { 0 , notificationLineIndex.Y });
	SetConsoleTextAttribute(hConsole, Colors::BRIGHT_WHITE);

	std::cout << message;
	lastNotificationLength = static_cast<int>(message.size());

	Sleep(2500);

	SetConsoleCursorPosition(hConsole, { 0 , notificationLineIndex.Y });
	std::cout << '\r' << std::string(lastNotificationLength, ' ') << '\r';
}