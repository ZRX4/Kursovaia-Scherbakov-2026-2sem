#include "human_player.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(std::string_view name, int stack)
	:BasePlayer{ name,stack }
{
	std::cout << "[HumanPlayer ctor] " << GetName() << "\n";
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

HumanPlayer::~HumanPlayer() {
	std::cout << "[HumanPlayer dtor] " << GetName() << "\n";
}