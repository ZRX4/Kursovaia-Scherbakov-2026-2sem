#pragma once

class IBettingStrategy
{
public:

	virtual ~IBettingStrategy() = default;
	virtual int CalculateBet(int currentBet, int stack) const = 0;
};