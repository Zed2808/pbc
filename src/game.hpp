#ifndef GAME_HPP
#define GAME_HPP

#include "pb.hpp"

class Game {
	public:
		void start();
		int bidding_round();
		int do_round();
		void score_hands();

		Gamestate gs;
		PB pb;
};

#endif
