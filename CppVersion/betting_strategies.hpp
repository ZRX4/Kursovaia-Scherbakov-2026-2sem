#pragma once
#include "i_betting_strategy.hpp"
#include <algorithm>

class AggressiveStrategy : public IBettingStrategy
{
public:
	int CalculateBet(int currentBet, int stack) const override
	{
		return std::min(currentBet * 2, stack); // удваивает или вабанк
	}

};

class PassiveStrategy : public IBettingStrategy
{
public:
	int CalculateBet(int currentBet, int stack) const override
	{
		return currentBet; // ѕросто коллирует
	}
};