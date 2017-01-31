#include <algorithm>
#include "deck.hpp"

std::string suit_to_string(Suit suit) {
	switch(suit) {
		case Suit::SPADES:
			return "SPADES";
			break;
		case Suit::HEARTS:
			return "HEARTS";
			break;
		case Suit::DIAMONDS:
			return "DIAMONDS";
			break;
		case Suit::CLUBS:
			return "CLUBS";
			break;
		default:
			return "SPADES";
	}
}

std::string suit_to_char(Suit suit) {
	switch(suit) {
		case Suit::SPADES:
			return "\u2660";
			break;
		case Suit::HEARTS:
			return "\u2661";
			break;
		case Suit::DIAMONDS:
			return "\u2662";
			break;
		case Suit::CLUBS:
			return "\u2663";
			break;
		default:
			return "\u2660";
	}
}

char value_to_char(int value) {
	switch(value) {
		case 10:
			return 'T';
			break;
		case 11:
			return 'J';
			break;
		case 12:
			return 'Q';
			break;
		case 13:
			return 'K';
			break;
		case 14:
			return 'A';
			break;
		default:
			return value;
	}
}

Card::Card() {
	suit = Suit::SPADES;
	value = 14;
}

Card::Card(Suit suit, int value) {
	this->suit = suit;
	this->value = value;
}

Suit Card::get_suit() {
	return suit;
}

int Card::get_value() {
	return value;
}

Deck::Deck(bool filled) {
	if(filled) fill_deck();
}

void Deck::fill_deck() {
	for(int value = 2; value <= 14; value++) {
		deck.push_back(Card(Suit::SPADES, value));
		deck.push_back(Card(Suit::HEARTS, value));
		deck.push_back(Card(Suit::DIAMONDS, value));
		deck.push_back(Card(Suit::CLUBS, value));
	}

	shuffle();

	cards_left = 52;
}

void Deck::shuffle() {
	std::random_shuffle(deck.begin(), deck.end());
}

Card Deck::draw() {
	cards_left--;
	Card card = deck.back();
	deck.pop_back();
	return card;
}

void Deck::add_card(Card card) {
	deck.push_back(card);
}

int Deck::get_cards_left() {
	return cards_left;
}
