#include <iostream>
#include "game.hpp"
#include "deck.hpp"

void Game::start() {
	std::cout << "Player " << std::to_string(gs.dealer + 1) << " is the dealer." << std::endl;

	// Deal players' hands
	for(int player = 0; player < gs.num_players; player++) {
		for(int card = 0; card < gs.hand_size; card++) {
			gs.hands[player].add_card(gs.deck.draw());
		}
	}

	// Print player's hand
	std::cout << "Your hand: " << gs.hands[0].to_string() << std::endl;

	// Do bidding round and return winner
	gs.active_player = bidding_round();

	std::cout << "Player " << gs.active_player + 1 << " won the bidding round with a bid of " << gs.bid << "." << std::endl;

	// Do actual game rounds
	for(gs.round = 0; gs.round < gs.hand_size; gs.round++) {
		do_round();
	}
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

int Game::do_round() {
	std::cout << "Player " << gs.active_player + 1 << " is leading out." << std::endl;

	// Give each player a turn to play a card
	for(gs.turn = 0; gs.turn < gs.num_players; gs.turn++) {
		int choice;
		Card played_card;

		// Active player human/bot?
		if(gs.active_player == 0) {
			// Print player's hand
			std::cout << "Your hand:" << std::endl;
			std::cout << gs.hands[gs.active_player].to_string() << "\n";
			for(int i = 1; i <= gs.hands[gs.active_player].size(); i++) {
				std::cout << i << ". ";
			}

			// Let player choose card
			std::cout << std::endl << "Enter a number to play a card: ";
			while(true) {
				std::cin >> choice;
				// Choice out of bounds
				if(choice < 1 || choice > gs.hands[gs.active_player].size()) {
					std::cout << "Invalid card: ";
				} else {
					break;
				}
			}
		} else {
			choice = pb.play_card(gs);
		}

		// Get played card from hands
		played_card = gs.hands[gs.active_player][choice - 1];

		std::cout << "Player " << gs.active_player + 1 << " plays " << played_card.to_string() << "." << std::endl;

		// If leading the hand
		if(gs.turn == 0) {
			gs.lead_suit = played_card.get_suit();
			gs.taker = gs.active_player;
			gs.top_card = played_card;

			// Set trump if first round
			if(gs.round == 0) {
				gs.trump = played_card.get_suit();
				std::cout << "Trump is now " << suit_to_string(gs.trump) << "." << std::endl;
			}
		// Check if new card beats previous top
		} else {
			// Current top card is trump
			if(gs.top_card.get_suit() == gs.trump) {
				// Played card is trump
				if(played_card.get_suit() == gs.trump) {
					// Our trump beats their trump
					if(played_card.get_value() > gs.top_card.get_value()) {
						gs.taker = gs.active_player;
						gs.top_card = played_card;
					}
				}
			// Current top card has to be lead out suit
			} else {
				// Played card is trump
				if(played_card.get_suit() == gs.trump) {
					gs.taker = gs.active_player;
					gs.top_card = played_card;
				// Played card is lead out suit
				} else if(played_card.get_suit() == gs.lead_suit) {
					// Played card value beats top card
					if(played_card.get_value() > gs.top_card.get_value()) {
						gs.taker = gs.active_player;
						gs.top_card = played_card;
					}
				}
			}
		}

		// Move card from hand to middle
		gs.middle.add_card(played_card);
		gs.hands[gs.active_player].remove_card(choice - 1);

		gs.next_player();
	}

	std::cout << "Player " << gs.taker + 1 << " takes the trick." << std::endl;

	// Take trick
	for(int card = 0; card < gs.num_players; card++) {
		gs.tricks[gs.taker].add_card(gs.middle[card]);
	}

	// Clear middle
	gs.middle = Deck(false);

	// Set lead out player to trick taker
	gs.active_player = gs.taker;
}
