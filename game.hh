#pragma once

#include <iostream>
#include "player.hh"

class Game{
public:
	void play();
	void init_deck();
	void init_player();
	void init_bank();
	void ask_for_bet();
	void init_game();
	
private:
	std::vector<Card> _deck;
	std::vector<Player> _player;
	void show_game();
	void draw_card(int no_player);
	int evaluate_cards(int no_player);
	bool ask_for_play();
	void dealer_play();
	void win();
	void defeat();
	void black_jack();
	void update_bank(float amount);
	void equality();
	float _bank;
	float _bet;
	bool _draw[312];
};