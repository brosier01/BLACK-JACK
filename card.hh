#include <string>

class Card{
public:
	Card(int c);
	std::string get_value();
	std::string get_card_value();
private:
	std::string _figure;
	std::string _value;
};