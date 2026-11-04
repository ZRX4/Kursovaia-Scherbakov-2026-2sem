#include "human_player.hpp"
#include "bot_player.hpp"
#include <iostream>

int main() {
    std::cout << "=== Тест иерархии ===\n";

    HumanPlayer human{ "Ivan", 500 };
    BotPlayer bot{ "Alpha", 1000, "Tight-Aggressive" };

    std::cout << "\n=== Описания ===\n";
    std::cout << human.Describe() << "\n";
    std::cout << bot.Describe() << "\n";

    std::cout << "\n=== Решения ===\n";
    std::cout << human.GetName() << " -> " << human.DecideAction() << "\n";
    std::cout << bot.GetName() << " -> " << bot.DecideAction() << "\n";

    std::cout << "\n=== Конец программы (смотрим деструкторы) ===\n";
    return 0;
}