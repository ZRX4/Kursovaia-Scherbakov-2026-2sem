#pragma once

#include "card.hpp"
#include <cstddef>
#include <vector>

namespace poker {

	class Deck {
	public:

		static constexpr std::size_t STANDARD_DECK_SIZE = 52;
		static constexpr std::size_t DEMO_DECK_SIZE = 52;

	private:
		std::vector<Card> m_cards; //Композиция
		std::size_t m_nextToDeal{ 0 };

		static bool IsValidSize(std::size_t size);


	public:

		explicit Deck(std::size_t size = DEMO_DECK_SIZE);
		~Deck();

		Deck(const Deck&)			  = delete;
		Deck(Deck&&)				  = delete;
		Deck& operator=(const Deck&)  = delete;
		Deck& operator=(Deck&&)		  = delete;

		[[nodiscard]] std::size_t GetCardCount() const { return m_cards.size(); }
		[[nodiscard]] std::size_t GetRemaining() const { return m_cards.size() - m_nextToDeal; }

		// Содержательный метод перемешать
		void Shuffle();

		// Содержательный метод 2: раздать одну карту
		// Возвращает копию карты; если колода пуста вернет пустую карту.
		[[nodiscard]] Card DealOne();

		// Содержательный метод 3: сброс
		void Reset();

		//Для демонстрации
		void PrintAll() const;

	};

}


