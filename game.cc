#include "game.hh"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>

void Game::init_deck(){
	for(int i=0;i<6;i++){
		for(int j=0;j<52;j++){
			Card new_card(j);
			_deck.push_back(new_card);
		}
	}

	for(int i=0;i<312;i++){
		_draw[i]=false;
	}
}

void Game::init_game(){
	init_bank();
	ask_for_bet();
	init_deck();
	init_player();
}

void Game::init_player(){
	srand(time(NULL));

	int index=(rand())%312;
	
	Player new_player;
	Player dealer;

	_draw[index]=true;
	dealer.add_card(_deck[index]);
	_deck.erase(_deck.begin()+index);
	_player.push_back(dealer);

	index=(rand())%312;

	_draw[index]=true;
	new_player.add_card(_deck[index]);

	index=(rand())%312;

	_draw[index]=true;
	new_player.add_card(_deck[index]);

	_player.push_back(new_player);

}


void Game::play(){ 
	show_game();
	int player_score,dealer_score;

	player_score=evaluate_cards(1);
	if(player_score>21){
		defeat();
		update_bank(-(_bet));
		return;
	}
	else if(player_score==21){
		black_jack();
		return;
	}

	bool ans=ask_for_play();

	if(ans){
		draw_card(1);
		play();
	}
	else{
		
		player_score=evaluate_cards(1);
		std::cout<<std::to_string(player_score)<<std::endl;
		dealer_play();
		show_game();
		dealer_score=evaluate_cards(0);

		if(dealer_score>21 || player_score>dealer_score){
			win();
			update_bank(_bet);
		}
		else if(player_score==dealer_score){
			equality();
			update_bank(0);
		}
		else{
			defeat();
			update_bank(-(_bet));
		}
		
	}
}

int Game::evaluate_cards(int no_player){
	int value=0;
	std::vector<Card> player_cards=_player[no_player].get_card_vector();;
	bool ace_flag=false;

	for(int i=0;i<player_cards.size();i++){
		if(player_cards[i].get_value()=="A"){
			ace_flag=true;
			value+=1;
		}
		else if(player_cards[i].get_value()=="J" || player_cards[i].get_value()=="K" || player_cards[i].get_value()=="Q"){
			value+=10;
		}
		else{
			value+=std::stoi(player_cards[i].get_value());
		}
	}

	/* The ace can be 1 or 11 */
	if(ace_flag && value<=10){
		value+=10;
	}

	return value;
}

void Game::draw_card(int no_player){
	int index;

	/* Check if the card had already been drawn */
	while(1){
		index=(rand())%312;
		if(!_draw[index]){
			break;
		}
	}
	
	_draw[index]=true;

	_player[no_player].add_card(_deck[index]);
}

bool Game::ask_for_play(){
	std::string answer;
	std::cout<<"DRAW ? YES/NO : ";
	std::cin >> answer;
	if(answer=="YES"){
		return true;
	}
	else if(answer=="NO"){
		return false;
	}
	else{
		/* Ask again if the entry is wrong */
		ask_for_play();
	}
	return false;
}


void Game::show_game(){
	system("clear");

	std::cout<<"\033[1;32m ___________________________________________ \033[0m"<<std::endl;
	std::cout<<std::endl;

	std::cout<<"\033[1;36m Dealer : \033[0m"<<_player[0].get_card();
	
	std::cout<<std::endl;
	std::cout<<std::endl;

	std::cout<<"\033[1;36m Player : \033[0m"<<_player[1].get_card();

	std::cout<<std::endl;
	std::cout<<std::endl;

	std::cout<<"\033[1;36m BANK : "<<_bank<<"\033[0m"<<std::endl;

	std::cout<<"\033[1;32m ___________________________________________ \033[0m"<<std::endl;
	std::cout<<std::endl;

}

void Game::dealer_play(){
	/* Dealer draws cards until he egts 17 or more */
	draw_card(0);
	int score=evaluate_cards(0);
	if(score<17){
		dealer_play();
	}
}


void Game::win(){
	std::cout<<"\033[1;32m You won "<<_bet<<" !\033[0m"<<std::endl<<std::endl;
}


void Game::defeat(){
	std::cout<<"\033[1;31m You lost... "<<_bet<<" !\033[0m"<<std::endl<<std::endl;
}

void Game::black_jack(){
	float bj_gain=_bet*1.5;
	std::cout<<"\033[1;35m BLACK JACK !"<<" You won "<<bj_gain<<"\033[0m"<<std::endl<<std::endl;
	update_bank(bj_gain);
}

void Game::init_bank(){
	std::ifstream bank_file("bank.txt");
	std::string bank;
	
	bank_file>>bank;
	_bank=std::stof(bank);

	bank_file.close();
}

void Game::ask_for_bet(){
	system("clear");
	std::string bet;

	std::cout<<"What bet do you want to play ? : ";
	std::cin>>bet;

	try{
		_bet=std::stof(bet);
		std::cout<<"Bet : "<<std::to_string(_bet)<<std::endl;
	}
	catch(std::exception& e){
		ask_for_bet();
	}
}

void Game::update_bank(float amount){
	float refresh_amount=_bank + amount;
	std::ofstream bank_file;
	
	bank_file.open("bank.txt", std::ofstream::out | std::ofstream::trunc);
	bank_file<<std::to_string(refresh_amount);
}

void Game::equality(){
	std::cout<<"\033[1;35m Equality, no one wins\033[0m"<<std::endl<<std::endl;
}