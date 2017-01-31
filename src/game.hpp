#ifndef GAME_HPP
#define GAME_HPP

#include "pb.hpp"

class Game {
	public:
		Game();
		void start();
		int bidding_round();
		int play_card();

		Gamestate gs;
		PB pb;
};

#endif
