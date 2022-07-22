#include "game.hh"

int main(int argc, char** argv){
	/* Creating a party */
	Game my_game;
	
	/* Lauching the party */
	my_game.init_game();
	my_game.play();

	return 0;
}