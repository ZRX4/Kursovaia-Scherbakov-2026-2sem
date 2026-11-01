#include "game.hpp"
#include <iostream>

namespace poker {

    Game::Game(std::string_view name,
        const std::shared_ptr<Deck>& deck,
        int playerCount)
        : m_name{ name }
        , m_deck{ deck }
        , m_playerCount{ playerCount }
    {
        if (!deck) {
            std::cerr << "[Game] Ошибка: колода не передана!\n";
            m_playerCount = 0;
            return;
        }
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
            << "Колода НЕ уничтожается (агрегация через weak_ptr)\n";
    }

    bool Game::HasDeck() const {
        return !m_deck.expired();   // без lock() — легче, не меняет use_count
    }

    void Game::StartNewHand() {
        auto deck = m_deck.lock();  //  обязательно проверять
        if (!deck) {
            std::cerr << "[Game] Нет колоды — раздача невозможна\n";
            return;
        }
        if (deck->GetRemaining() < static_cast<std::size_t>(m_playerCount) * 2) {
            std::cerr << "[Game] Недостаточно карт для раздачи. Сбрасываю колоду.\n";
            deck->Reset();
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
        if (auto deck = m_deck.lock()) {          //  проверка
            std::cout << "Карт в колоде: " << deck->GetCardCount()
                << " | Осталось: " << deck->GetRemaining() << "\n";
        }
        else {
            std::cout << "(Колода уже уничтожена)\n";
        }
    }

} // namespace poker