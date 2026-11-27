#include "human_player.hpp"
#include "bot_player.hpp"
#include "betting_strategies.hpp"
#include "poker_exceptions.hpp"
#include <iostream>
#include <vector>
#include <memory>

// Функция работает через интерфейс 
void ProcessTurn(IPlayerAction& player, int currentBet) {
    std::cout << "  [Дилер] Просит сделать ставку " << currentBet << "...\n";
    player.MakeBet(currentBet);
}

int main() {
    std::cout << "=== ЛР5: Полиморфизм, Стратегии и Исключения ===\n\n";

    std::vector<std::unique_ptr<BasePlayer>> players;

    // Создаем человека
    players.push_back(std::make_unique<HumanPlayer>("Ivan", 500));

    // Создаем бота и даем ему стратегию 
    auto bot = std::make_unique<BotPlayer>("Alpha", 1000, "Tight");
    bot->SetStrategy(std::make_unique<AggressiveStrategy>());
    players.push_back(std::move(bot));

    for (const auto& p : players) {
        std::cout << "\n--- Ход игрока ---\n";

        // Раннее связывание 
        std::cout << "Имя (раннее): " << p->GetName() << "\n";

        //  Позднее связывание 
        std::cout << "Описание (позднее): " << p->Describe() << "\n";

        //  Демонстрация работы стратегии
        std::cout << "Решение (Стратегия): " << p->DecideAction() << "\n";

        //  dynamic_cast
        //берем BasePlayer и проверяем, реализует ли он IPlayerAction
        if (auto* actionable = dynamic_cast<IPlayerAction*>(p.get())) {
            try {
                // Пункт 7: Успешное действие
                ProcessTurn(*actionable, 100);

                // нарушение правила (нехватка фишек)
                std::cout << "  [Провокация] Пытаемся поставить 10000 фишек...\n";
                ProcessTurn(*actionable, 10000);

            }
            catch (const InsufficientFundsException& e) {
                // частное исключение по const&
                std::cerr << "  [ПЕРЕХВАЧЕНО ИСКЛЮЧЕНИЕ] " << e.what() << "\n";
            }
            catch (const std::exception& e) {
                // Общее исключение идет вторым
                std::cerr << "  [НЕИЗВЕСТНАЯ ОШИБКА] " << e.what() << "\n";
            }
        }
        else {
            std::cout << "  -> Этот объект не умеет делать ставки.\n";
        }
    }

    std::cout << "\n=== Конец программы (смотрим деструкторы) ===\n";
    return 0;
}
