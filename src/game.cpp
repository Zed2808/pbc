#include <iostream>
#include "game.hpp"
#include "deck.hpp"

Game::Game() {

}

void Game::start() {
	// Create new filled deck
	gs.deck = Deck(true);

	// Create players' hands
	gs.hand0 = Deck(false);
	gs.hand1 = Deck(false);

	std::cout << "Player " << std::to_string(gs.dealer + 1) << " is the dealer." << std::endl;

	// Deal players' hands
	for(int i = 0; i < 6; i++) {
		gs.hand0.add_card(gs.deck.draw());
		gs.hand1.add_card(gs.deck.draw());
	}

	// Print player's hand
	std::cout << "Your hand: " << gs.hand0.to_string() << std::endl;

	// Do bidding round and return winner
	gs.active_player = bidding_round();

	std::cout << "Player " << gs.active_player + 1 << " won the bidding round with a bid of " << gs.bid << "." << std::endl;
}

// Returns player number of winning bidder
int Game::bidding_round() {
	std::cout << "Player " << std::to_string(gs.active_player + 1) << " bids first." << std::endl;

	int bid = 0;

	// Bid until back to the dealer
	while(gs.active_player != gs.dealer) {
		// Active player human or bot?
		if(gs.active_player == 0) {
			std::cout << "Current bid is " << (bid) << std::endl;

			while(true) {
				// Get bid from player
				std::cout << "Your bid (0 to pass): ";
				std::cin >> bid;
				// If bid too small/large, get new bid from player
				if((bid < gs.min_bid || bid > 4) && bid != 0) {
					std::cout << "Bid must be between " << gs.min_bid << " and 4." << std::endl;
				// If valid bid
				} else {
					// Player passes
					if(bid == 0) {
						std::cout << "Player " << gs.active_player + 1 << " passes." << std::endl;
					// Player bids
					} else {
						gs.bid = bid;
						gs.min_bid = gs.bid + 1;
						gs.bidder = gs.active_player;
					}
					break;
				}
			}
		} else {
			// If bot passes
			bid = pb.bid(gs);
			if(bid == 0) {
				std::cout << "Player " << gs.active_player + 1 << " passes." << std::endl;
			} else {
				gs.bid = bid;
				gs.min_bid = gs.bid + 1;
				gs.bidder = gs.active_player;
				std::cout << "Player 2 bid " << gs.bid << "." << std::endl;
			}
		}

		gs.next_player();
	}

	// No bids, dealer's bid is forced
	if(gs.bid < 2) {
		std::cout << "Player " << gs.active_player + 1 << " is forced to bid " << gs.min_bid << "." << std::endl;
		gs.bid = gs.min_bid;
		gs.bidder = gs.active_player;

		return gs.bidder;
	}

	// Give dealer the chance to match/pass
	bid = 0;

	// Human/bot is active
	if(gs.active_player == 0) {
		std::cout << "As the dealer, you may match Player " << gs.bidder + 1 << "'s bid of " << gs.bid << " or pass (0): ";
		while(true) {
			std::cin >> bid;
			// Invalid bid (didn't match or pass)
			if(bid != 0 && bid != gs.bid) {
				std::cout << "Bid must be " << gs.bid << " or pass (0): ";
			} else {
				break;
			}
		}
	} else {
		// If bot passes
		bid = pb.bid(gs);
	}

	// Dealer passes
	if(bid == 0) {
		std::cout << "Player " << gs.active_player + 1 << " passes." << std::endl;
	// Dealer Matches
	} else {
		std::cout << "Player " << gs.active_player + 1 << " matches Player " << gs.bidder + 1 << "'s bid of "
		          << gs.bid << "." << std::endl;
		gs.bidder = gs.active_player;
	}

	return gs.bidder;
}

int Game::play_card() {

}
