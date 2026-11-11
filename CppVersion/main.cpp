#include "human_player.hpp"
#include "bot_player.hpp"
#include <iostream>
#include <vector>
#include <memory>


struct ShallowDemo 
{
    std::shared_ptr<std::string> nickname;
};


int main() 
{
    std::cout << "=== Тест иерархии ===\n";

    HumanPlayer human{ "Ivan", 500 };
    BotPlayer bot{ "Alpha", 1000, "Tight-Aggressive" };

    std::cout << "\n=== Описания ===\n";
    std::cout << human.Describe() << "\n";
    std::cout << bot.Describe() << "\n";

    std::cout << "\n=== Решения ===\n";
    std::cout << human.GetName() << " -> " << human.DecideAction() << "\n";
    std::cout << bot.GetName() << " -> " << bot.DecideAction() << "\n";

    std::cout << "=== 1. Создание полиморфного массива ===\n";
    std::vector<std::unique_ptr<BasePlayer>> players;

    players.push_back(std::make_unique<HumanPlayer>("Alex", 1000));
    players.push_back(std::make_unique<BotPlayer>("Alpha", 1000,"Tight"));
    players.push_back(std::make_unique<BotPlayer>("Beta", 1000,"Loose"));

    //вызов методов через базовый указатель (полиморфизм)
    for (const auto& p : players) 
    {
        std::cout << p->Describe() << " -> " << p->DecideAction() << "\n";
    }


    std::cout << "\n=== 2. Демонстрация Clone() ===\n";

    std::unique_ptr<BasePlayer> clone = players[0]->Clone();
    std::cout << "Оригинал: " << players[0]->Describe() << "\n";
    std::cout << "Копия:    " << clone->Describe() << "\n";

    //проверка на то что это разные объекты
    if (players[0].get() != clone.get()) 
    {
        std::cout << "это два разных объекта в памяти\n";
    }

    std::cout << "\n=== 4. Поверхностная копия ===\n";
    ShallowDemo originalShallow;

    originalShallow.nickname = std::make_shared<std::string>("Bob");
    ShallowDemo copyShallow = originalShallow;


    std::cout << "Оригинал до: " << *originalShallow.nickname << "\n";
    *copyShallow.nickname += "_SHALLOW"; // Меняем через копию
    std::cout << "Оригинал после: " << *originalShallow.nickname << "\n"; 
    std::cout << "Копия после:    " << *copyShallow.nickname << "\n";



    std::cout << "\n=== 5. Глубокая копия (Deep Copy) ===\n";
    HumanPlayer deepOriginal{ "Bob2.0", 1000 };
    HumanPlayer deepCopy = deepOriginal; // Вызывается созданны конструктор копирования

    std::cout << "Оригинал до: " << *deepOriginal.GetNickname() << "\n";
    std::cout << "Копия до:    " << *deepCopy.GetNickname() << "\n";
    
    *deepCopy.GetNickname() += " (NoOriginlBob2.0)";

    std::cout << "Оригинал после: " << *deepOriginal.GetNickname() << "\n"; 
    std::cout << "Копия после:    " << *deepCopy.GetNickname() << "\n";    


    std::cout << "\n=== 5. Работа со строками (find, substr, сравнение) ===\n";
    std::string botName = "Bot_Alpha";
    std::cout << "Имя бота: " << botName << "\n";

    size_t pos = botName.find("_");
    if (pos != std::string::npos) 
    {
        std::cout << "Символ '_' найден на позиции: " << pos << "\n";
        std::string prefix = botName.substr(0, pos); // Выделяем подстроку
        std::cout << "Подстрока до '_': " << prefix << "\n";

        if (prefix == "Bot") 
        { // Сравниваем
            std::cout << "Сравнение прошо успешно\n";
        }

    }

    std::cout << "\n=== 6. Использование this для передачи объекта ===\n";
    HumanPlayer p1{ "Ivan", 500 };
    BotPlayer p2{ "Beta", 500, "Loose" };
    p1.SitDown(p2); // Передаем объект p1 в метод p2

    std::cout << "\n=== Конец программы (смотрим деструкторы) ===\n";
    return 0;
}