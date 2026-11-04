#pragma once
#include "base_player.hpp"

class HumanPlayer : public BasePlayer {

public:
	HumanPlayer(std::string_view name, int stack);
	~HumanPlayer() override;
	std::string Describe() const override;
	std::string DecideAction() const override;
	std::unique_ptr<BasePlayer> Clone() const override;

};