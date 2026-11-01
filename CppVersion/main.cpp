#include "card.hpp"
#include "deck.hpp"
#include "game.hpp"

#include <iostream>

using namespace poker; // можно в .cpp, но не в .hpp

int main() {
    std::cout << "========= 1. Композиция: Deck владеет Card =========\n";
    {
        Deck deck{ 5 };            // создаём колоду на 5 карт
        deck.PrintAll();
        deck.Shuffle();
        Card c = deck.DealOne();   // карта копируется наружу
        std::cout << "Выдана карта: " << c.ToString() << "\n";
    } // <-- здесь деструктор Deck уничтожает все Card (композиция)

    std::cout << "\n========= 2. Агрегация: Game использует внешний Deck =========\n";
    Deck* sharedDeck = new Deck{ 10 };  // создана СНАРУЖИ

    {
        Game game{ "Sport Hold'em", sharedDeck, 5 };
        game.PrintStatus();
        game.StartNewHand();
        game.EndRound();
    } // <-- деструктор Game. Колода НЕ удаляется

    std::cout << "\n--- После уничтожения Game колода жива: ---\n";
    sharedDeck->PrintAll();              // доказательство: колода работает
    std::cout << "Осталось карт: " << sharedDeck->GetRemaining() << "\n";

    delete sharedDeck;                   // удаляем сами — теперь карты исчезнут

    std::cout << "\n========= 3. Проверка правила =========\n";
    Deck badDeck{ 999 };                 // правило нарушено — сообщение в stderr
    std::cout << "Итоговый размер: " << badDeck.GetCardCount() << "\n";

    std::cout << "\n========= 4. Стек, указатель, динамический массив =========\n";
    Deck stackDeck{ 3 };                 // статический объект
    Deck* heapDeck = new Deck{ 3 };      // динамический объект
    stackDeck.Shuffle();                 // по значению
    heapDeck->Shuffle();                 // по указателю
    Deck& ref = *heapDeck;               // ссылка на объект
    ref.PrintAll();

    // Динамический массив объектов класса
    Card* cardArray = new Card[2]{ {Card::Suit::eHearts, Card::Rank::eAce},
                                   {Card::Suit::eSpades, Card::Rank::eKing} };
    delete[] cardArray;

    // Массив динамических объектов класса
    Card** cardPtrArray = new Card * [2];
    cardPtrArray[0] = new Card{ Card::Suit::eClubs, Card::Rank::eTen };
    cardPtrArray[1] = new Card{ Card::Suit::eDiamonds, Card::Rank::eJack };
    for (int i = 0; i < 2; ++i) delete cardPtrArray[i];
    delete[] cardPtrArray;

    delete heapDeck;
    return 0;
}