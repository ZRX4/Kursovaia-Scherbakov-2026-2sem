#pragma once

#include <cstdint>
#include <string>
#include <string_view>

namespace poker {


	class Card {
	public:
		enum class Suit : std::unit8_t {
			eHearts=0, eDiamonds, eCluds, eSpades, eUnknown
		};

		enum class Rank : std::unit8_t {
			eTwo = 2, eThree, eFour, eFive, eSix, eSeven, eEight,
			eNine, eTen, eJack, eQueen, eKing, eAce, eUnknown
		};

	private:
		Suit m_suit{ Suit::eUnknown };
		Rank m_rank{ Rank::eUnknown };
		bool m_isOpen{ false };

	public:
		Card() = default;
		Card(Suit suit, Rank rank);

		~Card();

		[[nodiscard]] Suit GetSuit() const { return m_suit; }
		[[nodiscard]] Rank GetRank() const { return m_rank; }
		[[nodiscard]] Suit IsOpen() const { return m_isOpen; }

		// Содержательный метод 1: открыть карту
		void Open();

		// Содержательный метод 2: строковое представление
		[[nodiscard]] std::string ToString() const;

	};

}// namespace poker