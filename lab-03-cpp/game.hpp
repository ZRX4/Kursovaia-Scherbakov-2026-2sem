#pragma once

#include "deck.hpp"
#include <memory>
#include <string>
#include <string_view>

namespace poker {

    class Game {
    public:
        static constexpr int MAX_PLAYERS = 5;

    private:
        std::string         m_name;
        std::weak_ptr<Deck> m_deck;   // агрегаци€: наблюдатель, не владелец
        int                 m_playerCount{ 0 };
        int                 m_roundNumber{ 0 };

    public:
        //  принимаем const shared_ptr& Ч не увеличиваем счЄтчик
        Game(std::string_view name,
            const std::shared_ptr<Deck>& deck,
            int playerCount);
        ~Game();

        Game(const Game&) = delete;
        Game(Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(Game&&) = delete;

        [[nodiscard]] const std::string& GetName()        const { return m_name; }
        [[nodiscard]] int                GetPlayerCount() const { return m_playerCount; }
        [[nodiscard]] int                GetRoundNumber() const { return m_roundNumber; }

        void StartNewHand();
        void EndRound();
        void PrintStatus() const;

        [[nodiscard]] bool HasDeck() const;
    };

} // namespace poker