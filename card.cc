#include "card.hh"
#include <iostream>

Card::Card(int c){
	int value=(c/4)+1;

	if(value==1){
		_value="A";
	}
	else if(value==11){
		_value="J";
	}
	else if(value==12){
		_value="Q";
	}
	else if(value==13){
		_value="K";
	}
	else{
		_value=std::to_string(value);
	}
	
	if(c%4==0){
		_figure="♠︎ ";
	}
	else if(c%4==1){
		_figure="♣ ";
	}
	else if(c%4==2){
		_figure="♦︎ ";
	}
	else{
		_figure="♥ ";
	}
}

std::string Card::get_card_value(){
	std::string s;

	if(_figure=="♦︎ " || _figure=="♥ "){
		s+="\033[0;31m\033[47m";
		s+=_value;
		s+=_figure;
		s+="\033[0m";
	}else{
		s+="\033[0;30m\033[47m";
		s+=_value;
		s+=_figure;
		s+="\033[0m";
	}
	
	return s;
}

std::string Card::get_value(){
	return _value;
}