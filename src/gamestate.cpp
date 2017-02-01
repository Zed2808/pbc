#include "gamestate.hpp"

Gamestate::Gamestate() {
	num_players = 2;            // Total number of players
	hand_size = 6;              // Size of each players' hand/number of rounds
	dealer = 0;                 // Set dealer to first player
	active_player = dealer;
	next_player();              // Set player after dealer to active
	min_bid = 2;                // Minimum bid is 2
	bid = 0;                    // Set initial bid to 0
	bidder = -1;                // No initial bidder
	round = -1;                 // Bidding round = -1

	// Create player hands/trick piles/scores
	for(int i = 0; i < num_players; i++) {
		hands.push_back(Deck(false));
		tricks.push_back(Deck(false));
		scores.push_back(0);
	}
}

// Change active_player to next player & return player number
int Gamestate::next_player() {
	active_player++;
	if(active_player >= num_players) {
		active_player = 0;
	}
	return active_player;
}
