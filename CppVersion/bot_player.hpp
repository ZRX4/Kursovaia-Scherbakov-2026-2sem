#pragma once 
#include "base_player.hpp"
#include <string>
#include <memory>

class BotPlayer final : public BasePlayer {

private:
	std::string m_strategy;

public:
	BotPlayer(std::string_view name, int stack, std::string_view strategy);
	~BotPlayer() override;

	std::string Describe() const override;
	std::string DecideAction() const override;
	std::unique_ptr<BasePlayer> Clone() const override;

};