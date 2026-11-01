#include "card.hpp"
#include "deck.hpp"
#include "game.hpp"

#include <iostream>
#include <memory>

using namespace poker;

int main() {
    // ===== 1. Композиция: Deck владеет Card по значению =====
    std::cout << "========= 1. Композиция: Deck владеет Card =========\n";
    {
        Deck deck{ 5 };
        deck.PrintAll();
        deck.Shuffle();
        Card c = deck.DealOne();
        std::cout << "Выдана карта: " << c.ToString() << "\n";
    }   // ~Deck → ~Card для всех карт

    // ===== 2. Агрегация: shared_ptr (владелец) + weak_ptr (наблюдатель) =====
    std::cout << "\n========= 2. Агрегация: shared_ptr + weak_ptr =========\n";
    {
        auto sharedDeck = std::make_shared<Deck>(10);
        std::cout << "use_count после создания: " << sharedDeck.use_count() << "\n";

        {
            Game game{ "Sport Hold'em", sharedDeck, 5 };
            std::cout << "use_count после передачи в Game: "
                << sharedDeck.use_count() << "\n";   // 1 — weak_ptr не владеет
            game.PrintStatus();
            game.StartNewHand();
            game.EndRound();
        }   // ~Game, колода жива

        std::cout << "\n--- После уничтожения Game колода жива: ---\n";
        sharedDeck->PrintAll();
        std::cout << "Осталось карт: " << sharedDeck->GetRemaining() << "\n";
    }   // ~Deck и ~Card для всех карт

    // ===== 3. Проверка правила =====
    std::cout << "\n========= 3. Проверка правила =========\n";
    {
        Deck badDeck{ 999 };
        std::cout << "Итоговый размер: " << badDeck.GetCardCount() << "\n";
    }

    // ===== 4. unique_ptr: один владелец, без delete =====
    std::cout << "\n========= 4. unique_ptr: один владелец =========\n";
    {
        auto heapDeck = std::make_unique<Deck>(3);
        heapDeck->Shuffle();
        heapDeck->PrintAll();
    }   // автоматический delete → ~Deck и ~Card

    // ===== 5. unique_ptr: передача владения через std::move =====
    std::cout << "\n========= 5. unique_ptr: передача владения =========\n";
    {
        auto original = std::make_unique<Deck>(3);
        std::cout << "original до move:  "
            << (original ? "владеет" : "пуст") << "\n";

        auto taken = std::move(original);
        std::cout << "original после move: "
            << (original ? "владеет" : "пуст") << "\n";   // по памятке 5.6
        std::cout << "taken: "
            << (taken ? "владеет" : "пуст") << "\n";
    }   // ~Deck и ~Card от taken

    // ===== 6. shared_ptr: use_count растёт и падает =====
    std::cout << "\n========= 6. shared_ptr: счётчик владельцев =========\n";
    {
        auto first = std::make_shared<Deck>(3);
        std::cout << "use_count: " << first.use_count() << "\n";   // 1
        {
            auto second = first;
            std::cout << "use_count после копии: "
                << first.use_count() << "\n";   // 2
        }
        std::cout << "use_count после уничтожения копии: "
            << first.use_count() << "\n";   // 1
    }   // ~Deck и ~Card

    // ===== 7. weak_ptr: lock() работает, пока жив, пустой после =====
    std::cout << "\n========= 7. weak_ptr: lock и проверка жизни =========\n";
    {
        auto owner = std::make_shared<Deck>(3);
        std::weak_ptr<Deck> watcher = owner;

        if (auto locked = watcher.lock()) {
            std::cout << "Пока жив: карт в колоде "
                << locked->GetCardCount() << "\n";
        }

        owner.reset();   // последний владелец отказался

        if (auto locked = watcher.lock()) {
            std::cout << "После reset: колода всё ещё жива?!\n";
        }
        else {
            std::cout << "После reset: колода уничтожена, "
                << "lock() вернул пустой указатель\n";
        }
    }

    // ===== 8. Массив объектов: unique_ptr<Card[]> =====
    std::cout << "\n========= 8. Массив объектов: unique_ptr<Card[]> =========\n";
    {
        auto cardArray = std::make_unique<Card[]>(2);
        cardArray[0] = Card{ Card::Suit::eHearts, Card::Rank::eAce };
        cardArray[1] = Card{ Card::Suit::eSpades, Card::Rank::eKing };
        std::cout << "Карты: " << cardArray[0].ToString()
            << ", " << cardArray[1].ToString() << "\n";
    }   // delete[] → ~Card для обоих

    // ===== 9. Массив указателей: unique_ptr<Card> shelf[2] (памятка 5.4) =====
    std::cout << "\n========= 9. Массив указателей: unique_ptr<Card> shelf[2] =========\n";
    {
        std::unique_ptr<Card> shelf[2];
        shelf[0] = std::make_unique<Card>(Card::Suit::eClubs, Card::Rank::eTen);
        shelf[1] = std::make_unique<Card>(Card::Suit::eDiamonds, Card::Rank::eJack);
        std::cout << "Карты: " << shelf[0]->ToString()
            << ", " << shelf[1]->ToString() << "\n";
    }   // каждый unique_ptr уничтожает свой Card

    return 0;
}