#include "gamestate.hpp"

Gamestate::Gamestate() {
	num_players = 2;            // Total number of players
	dealer = 0;                 // Set dealer to first player
	active_player = dealer;
	next_player();              // Set player after dealer to active
	min_bid = 2;                // Minimum bid is 2
	bid = 0;                    // Set initial bid to 0
	bidder = -1;                // No initial bidder
	round = -1;                 // Bidding round = -1
}

int Gamestate::next_player() {
	active_player++;
	if(active_player >= num_players) {
		active_player = 0;
	}
	return active_player;
}
