#pragma once
#include <stdexcept>
#include <string>

class InsufficientFundsException : public std::runtime_error
{
public:
	explicit InsufficientFundsException(int required, int available)
	: std::runtime_error("Недостаточно фишек! Требуется: " + std::to_string(required) +
		", доступно: " + std::to_string(available)) {}
};