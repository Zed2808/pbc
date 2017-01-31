#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "deck.hpp"

class Gamestate {
	public:
		Gamestate();
		int next_player();

		int num_players;
		int dealer;
		int active_player;
		int min_bid;
		int bid;
		int bidder;
		int round;
		Deck deck = Deck(true);
		Deck hand0 = Deck(false);
		Deck hand1 = Deck(false);
};

#endif
