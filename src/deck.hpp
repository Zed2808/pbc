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

std::string value_to_char(int value);

class Card {
	private:
		Suit suit;
		int value;

	public:
		Card();
		Card(Suit suit, int value);

		Suit get_suit();
		int get_value();
		std::string to_string();
};

class Deck {
	private:
		std::vector<Card> deck;
		int cards_left = 0;

	public:
		Deck(bool filled);
		Card operator [](int i) { return deck[i]; }
		void fill_deck();
		void shuffle();
		Card draw();
		void add_card(Card card);
		void remove_card(int index);
		int get_cards_left();
		int size();
		std::string to_string();
};

#endif
