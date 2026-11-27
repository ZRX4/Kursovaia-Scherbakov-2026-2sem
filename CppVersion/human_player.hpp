#pragma once
#include "base_player.hpp"
#include <memory>
#include "i_player_action.hpp"

class HumanPlayer : public BasePlayer, public IPlayerAction
{
public:
	HumanPlayer(std::string_view name, int stack);
	HumanPlayer(const HumanPlayer& other);
	HumanPlayer& operator=(const HumanPlayer& other);

	~HumanPlayer() noexcept override;

	std::string Describe() const override;
	std::string DecideAction() const override;
	std::unique_ptr<BasePlayer> Clone() const override;

	void MakeBet(int amount) override;
	void Fold() override;

};