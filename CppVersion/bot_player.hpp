#pragma once 
#include "base_player.hpp"
#include <string>
#include <memory>
#include "i_player_action.hpp"

class BotPlayer final : public BasePlayer , public IPlayerAction
{
private:
	std::string m_strategyName;

public:
	BotPlayer(std::string_view name, int stack, std::string_view strategy);
	//конструктор копирования
	BotPlayer(const BotPlayer& other);
	BotPlayer& operator=(const BotPlayer& other);

	~BotPlayer() noexcept override;

	std::string Describe() const override;
	std::string DecideAction() const override;
	std::unique_ptr<BasePlayer> Clone() const override;

	void MakeBet(int amount) override;
	void Fold() override;

};