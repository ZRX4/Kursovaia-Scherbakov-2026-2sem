#include "game.hpp"
#include <iostream>

namespace poker {

    Game::Game(std::string_view name, Deck* deck, int playerCount)
        : m_name{ name }
        , m_deck{ deck }
        , m_playerCount{ playerCount }
    {
        if (m_deck == nullptr) {
            std::cerr << "[Game] Ошибка: колода не передана!\n";
            m_playerCount = 0;
            return;
        }

        // ПРОВЕРКА ПРАВИЛА предметной области: за столом от 2 до 5 игроков
        if (m_playerCount < 2 || m_playerCount > MAX_PLAYERS) {
            std::cerr << "[Game] Неверное число игроков: " << m_playerCount
                << ". Допустимо 2.." << MAX_PLAYERS << "\n";
            m_playerCount = 0;
            return;
        }

        std::cout << "[Game ctor] Игра \"" << m_name
            << "\" создана, игроков: " << m_playerCount << "\n";
    }

    Game::~Game() {
        std::cout << "[Game dtor] Игра \"" << m_name << "\" завершена. "
            << "Колода НЕ уничтожается (агрегация)\n";
        // m_deck НЕ удаляем — мы им не владеем!
    }

    void Game::StartNewHand() {
        if (!HasDeck()) {
            std::cerr << "[Game] Нет колоды — раздача невозможна\n";
            return;
        }
        if (m_deck->GetRemaining() < static_cast<std::size_t>(m_playerCount) * 2) {
            std::cerr << "[Game] Недостаточно карт для раздачи. Сбрасываю колоду.\n";
            m_deck->Reset();
        }
        ++m_roundNumber;
        std::cout << "[Game] Раздача #" << m_roundNumber << " начата\n";
    }

    void Game::EndRound() {
        std::cout << "[Game] Раунд торговли завершён\n";
    }

    void Game::PrintStatus() const {
        std::cout << "=== Игра: " << m_name
            << " | Игроков: " << m_playerCount
            << " | Раздача: " << m_roundNumber << " ===\n";
        if (m_deck) {
            std::cout << "Карт в колоде: " << m_deck->GetCardCount()
                << " | Осталось: " << m_deck->GetRemaining() << "\n";
        }
    }

} // namespace poker