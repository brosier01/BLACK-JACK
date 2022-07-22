#include "player.hh"

void Player::add_card(Card& card){
	_card.push_back(card);
}

std::vector<Card> Player::get_card_vector(){
	return _card;
}

std::string Player::get_card(){
	std::string s;
	for(int i=0;i<_card.size();i++){
		s= s + "" + _card[i].get_card_value();
	}

	return s;
}