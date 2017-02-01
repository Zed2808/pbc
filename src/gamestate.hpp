#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "deck.hpp"

class Gamestate {
	public:
		Gamestate();
		int next_player();

		int num_players;
		int hand_size;
		int dealer;
		int active_player;
		int min_bid;
		int bid;
		int bidder;
		int round;
		int turn;
		int taker;
		Card top_card;
		Suit trump;
		Suit lead_suit;
		Deck deck = Deck(true);
		Deck middle = Deck(false);
		std::vector<Deck> hands;
		std::vector<Deck> tricks;
		std::vector<int> scores;
};

#endif
