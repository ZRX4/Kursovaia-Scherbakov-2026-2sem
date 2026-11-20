#pragma once

#include <string_view>

class IPlayerAction
{

public:
	virtual ~IPlayerAction() = default;

	//игрок может сделать ставку и  спасовать

	virtual void MakeBet(int amount) = 0;
	virtual void Fold() = 0;

};