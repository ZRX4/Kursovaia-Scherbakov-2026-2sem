#include "deck.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>

namespace poker {

	bool Deck::IsValidSize(std::size_t size) {
		return size > 0 && size <= STANDARD_DECK_SIZE;
	}


	Deck::Deck(std::size_t size) {
		if (!IsValidSize(size)) {
			// ПРОВЕРКА ПРАВИЛА: сообщаем и откатываемся к безопасному размеру
			std::cerr << "[Deck] Неверный размер колоды: " << size
				<< ". Использую " << DEMO_DECK_SIZE << "\n";
			size = DEMO_DECK_SIZE;
		}


		std::cout << "[Deck ctor] Создаю колоду на " << size << " карт\n";
		m_cards.reserve(size);

		// Заполняем колоду первыми size картами (для демо — просто по одной масти)
		for (std::size_t i = 0; i < size; i++) {
			auto rank = static_cast<Card::Rank>((i % 13) + 2);
			auto suit = static_cast<Card::Suit>(i / 13);
			m_cards.emplace_back(suit, rank);
		}
	}

	Deck:: ~Deck() {
		std::cout << "[Deck dtor] Уничтожаю колоду (" << m_cards.size() << " карт)\n";
		// m_cards — вектор по значению; при уничтожении Deck
		// автоматически вызываются деструкторы всех Card (композиция)
	}

	void Deck::Shuffle() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(m_cards.begin(), m_cards.end(), gen);
		m_nextToDeal = 0;
		std::cout << "[Deck] Перемешано\n";
	}

	Card Deck::DealOne() {
		if (m_nextToDeal >= m_cards.size()) {
			std::cerr << "[Deck] Колода пуста! Возвращаю пустую карту\n";
			return Card{};
		}
		return m_cards[m_nextToDeal++];
	}

	void Deck::Reset() {
		m_nextToDeal = 0;
		Shuffle();
	}

	void Deck::PrintAll() const {
		std::cout << "[Deck] Содержимое: ";
		for (const auto& c : m_cards) {
			std::cout << c.ToString() << " ";
		}
		std::cout << "\n";
	}

}//namespace poker