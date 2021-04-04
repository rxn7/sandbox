#include "Game.h"

int main() {
	Game game;

	if (!game.Start()) {
		return -1;
	}
	
	return 0;
}