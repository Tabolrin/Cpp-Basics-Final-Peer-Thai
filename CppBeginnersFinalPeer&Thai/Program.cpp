#include "Game.h"

int main()
{
	//Game game;
	//game.RunGameLoop();

    try {
        // PlayerParty party;   // ← temporarily disable
        std::cout << "Got past party construction\n";
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Allocation failed: " << e.what() << "\n";
    }


	return 0;
}