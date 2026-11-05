#pragma once
#include "base_player.hpp"
#include <memory>

class HumanPlayer : public BasePlayer 
{
public:
	HumanPlayer(std::string_view name, int stack);
	HumanPlayer(const HumanPlayer& other);
	HumanPlayer& operator=(const HumanPlayer& other);

	~HumanPlayer() override;

	std::string Describe() const override;
	std::string DecideAction() const override;
	std::unique_ptr<BasePlayer> Clone() const override;

};