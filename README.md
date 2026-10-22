# Лабораторная работа 3. Часть 2 — C++ с умными указателями

Перевод проекта из ЛР 2 на умные указатели: `std::unique_ptr`,
`std::shared_ptr`, `std::weak_ptr`. В проекте не осталось ни одного
`new` и ни одного `delete`.

## Структура

- `card.hpp`, `card.cpp` — класс `Card` (без изменений из ЛР 2)
- `deck.hpp`, `deck.cpp` — класс `Deck` (композиция `Card` по значению — не трогаем)
- `game.hpp`, `game.cpp` — класс `Game` (поле `weak_ptr<Deck>` — агрегация)
- `main.cpp` — демонстрации

## Таблица владения

| Где был указатель | Владелец | Заменяется на |
|---|---|---|
| `Game::m_deck` | Внешний код | `std::weak_ptr<Deck>` |
| `main: Deck* sharedDeck` | `main` | `std::shared_ptr<Deck>` |
| `main: Deck* heapDeck` | `main` | `std::unique_ptr<Deck>` |
| `main: Card* cardArray` | `main` | `std::unique_ptr<Card[]>` |
| `main: Card** cardPtrArray` | `main` | `std::unique_ptr<Card> shelf[2]` |

## Сборка и запуск

```bash
g++ -std=c++17 *.cpp -o lab03cpp
./lab03cpp