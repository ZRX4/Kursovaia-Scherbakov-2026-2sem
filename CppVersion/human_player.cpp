#include "human_player.hpp"
#include <iostream>
#include "poker_exceptions.hpp"

HumanPlayer::HumanPlayer(std::string_view name, int stack)
	:BasePlayer{ name,stack }
{
	std::cout << "[HumanPlayer ctor] " << GetName() << "\n";
}

HumanPlayer::HumanPlayer(const HumanPlayer& other)
	: BasePlayer{ other }

{
	std::cout << "[HumanPlayer copy ctor]\n";
}

HumanPlayer& HumanPlayer::operator=(const HumanPlayer& other){
	if (this == &other) {
		return *this;
	}
	BasePlayer::operator=(other);


	return *this;
}


std::string HumanPlayer::Describe() const {
	return BasePlayer::Describe() + "(Human)";
}
std::string HumanPlayer::DecideAction() const {
	return "call";
}

std::unique_ptr<BasePlayer> HumanPlayer::Clone() const {
	return std::make_unique<HumanPlayer>(*this);
}

void HumanPlayer::MakeBet(int amount)
{
	if (amount > GetStack()) {
		throw InsufficientFundsException(amount, GetStack());
	}
	std::cout << "[" << GetName() << "] (Human) ставит " << amount << " фишек.\n";
}

void HumanPlayer::Fold()
{
	std::cout << "[" << GetName() << "] (Human) пасует.\n";
}

HumanPlayer::~HumanPlayer() {
	std::cout << "[HumanPlayer dtor] " << GetName() << "\n";
}