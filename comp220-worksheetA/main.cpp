#include "main.h"
#include <iostream>

//Entry point for the program
int main(int argc, char ** argsv) 
{
	//Create new game class
	Game game = Game();

	//Initialise and set up
	game.Init();
	game.Setup();

	//Run the game loop and clean up afterwards
	game.GameLoop();
	game.Cleanup();

	return 0;
}