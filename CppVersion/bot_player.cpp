#include "bot_player.hpp"
#include <iostream>

BotPlayer::BotPlayer(std::string_view name, int stack, std::string_view strategy)
	:BasePlayer{ name,stack }
	,m_strategy{strategy}
	
{
	std::cout << "[BotPlayer ctor] " << GetName() << "\n";
}

//конструткор копирования
BotPlayer::BotPlayer(const BotPlayer & other)
	:BasePlayer{ other }
	, m_strategy{ other.m_strategy }

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
	m_strategy = other.m_strategy;

	return *this;
}

std::string BotPlayer::Describe() const 
{
	return std::string(GetName())+" [" +std::to_string(GetStack()) +"] " + "[Strategy:" + m_strategy + "]"+"(Bot)";
}

std::string BotPlayer::DecideAction() const 
{
	return "fold";
}

std::unique_ptr<BasePlayer> BotPlayer::Clone() const 
{
	return std::make_unique<BotPlayer>(*this);
}

BotPlayer::~BotPlayer()
{
	std::cout << "[BotPlayer dtor] " << GetName() << "\n";
}