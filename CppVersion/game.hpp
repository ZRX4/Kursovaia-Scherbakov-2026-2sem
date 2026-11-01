#pragma once

#include "deck.hpp"
#include <cstdint>
#include <string>

namespace poker {

    class Game {
    public:
        static constexpr int MAX_PLAYERS = 5;

    private:
        std::string m_name;
        Deck* m_deck{ nullptr };   // ? АГРЕГАЦИЯ: не владеет колодой
        int         m_playerCount{ 0 };
        int         m_roundNumber{ 0 };

    public:
        // ПРОВЕРКА ПРАВИЛА: game принимает только валидные параметры
        Game(std::string_view name, Deck* deck, int playerCount);

        ~Game();

        Game(const Game&) = delete;
        Game(Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(Game&&) = delete;

        [[nodiscard]] const std::string& GetName() const { return m_name; }
        [[nodiscard]] int GetPlayerCount() const { return m_playerCount; }
        [[nodiscard]] int GetRoundNumber() const { return m_roundNumber; }

        // Содержательный метод 1: начать новую раздачу
        void StartNewHand();

        // Содержательный метод 2: завершить раунд торговли
        void EndRound();

        // Содержательный метод 3: показать состояние игры
        void PrintStatus() const;

        // Демонстрация того, что мы НЕ владеем колодой
        [[nodiscard]] bool HasDeck() const { return m_deck != nullptr; }
    };

} // namespace poker