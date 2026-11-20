#include "bot_player.hpp"
#include <iostream>
#include "poker_exceptions.hpp"

BotPlayer::BotPlayer(std::string_view name, int stack, std::string_view strategy)
	:BasePlayer{ name,stack }
	,m_strategyName{ strategy }
	
{
	std::cout << "[BotPlayer ctor] " << GetName() << "\n";
}

//конструткор копирования
BotPlayer::BotPlayer(const BotPlayer & other)
	:BasePlayer{ other }
	, m_strategyName{ other.m_strategyName }

{
	std::cout << "[BotPlayer copy ctor]\n";
}

BotPlayer& BotPlayer::operator=(const BotPlayer& other)
{
	if (this == &other)
	{
		return *this;
	}

	BasePlayer::operator=(other);
	m_strategyName = other.m_strategyName;

	return *this;
}

std::string BotPlayer::Describe() const 
{
	return std::string(GetName())+" [" +std::to_string(GetStack()) +"] " + "[Strategy:" + m_strategyName + "]"+"(Bot)";
}

std::string BotPlayer::DecideAction() const 
{
	if (m_strategy) 
	{
		int bet = m_strategy->CalculateBet(50, GetStack());
		return "bet " + std::to_string(bet);
	}
	return "fold";
}

std::unique_ptr<BasePlayer> BotPlayer::Clone() const 
{
	return std::make_unique<BotPlayer>(*this);
}

void BotPlayer::MakeBet(int amount)
{
	if (amount > GetStack()) {
		
		throw InsufficientFundsException(amount, GetStack());
	}
	
	std::cout << "[" << GetName() << "] (Bot) ставит " << amount << " фишек.\n";
}

void BotPlayer::Fold()
{
	std::cout << "[" << GetName() << "] (Bot) пасует.\n";
}

BotPlayer::~BotPlayer()
{
	std::cout << "[BotPlayer dtor] " << GetName() << "\n";
}