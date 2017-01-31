#ifndef DECK_HPP
#define DECK_HPP

#include <string>
#include <vector>

enum class Suit {
	SPADES,
	HEARTS,
	DIAMONDS,
	CLUBS
};

std::string suit_to_string(Suit suit);
std::string suit_to_char(Suit suit);

char value_to_char(int value);

class Card {
	private:
		Suit suit;
		int value;

	public:
		Card();
		Card(Suit suit, int value);

		Suit get_suit();
		int get_value();
};

class Deck {
	private:
		std::vector<Card> deck;
		int cards_left = 0;

	public:
		Deck(bool filled);
		void fill_deck();
		void shuffle();
		Card draw();
		void add_card(Card card);
		int get_cards_left();
};

#endif
