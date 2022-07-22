#pragma once

#include "card.hh"
#include <vector>

class Player{
public:
	void add_card(Card& card);
	std::string get_card();
	std::vector<Card> get_card_vector();
private:
	std::vector<Card> _card;
};