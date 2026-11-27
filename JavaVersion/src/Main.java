import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== ЛР5 (Java): Полиморфизм и Исключения ===\n");

        // 1. Полиморфный массив
        List<BasePlayer> players = new ArrayList<>();
        players.add(new HumanPlayer("Ivan", 500));
        
        BotPlayer bot = new BotPlayer("Alpha", 1000, "Tight");
        bot.setStrategy(new AggressiveStrategy()); // Конфигурирование
        players.add(bot);

        // 2. Работа через интерфейс и instanceof
        System.out.println("--- Демонстрация интерфейса и instanceof ---");
        for (BasePlayer player : players) {
            System.out.println("\nИгрок: " + player.getName());
            System.out.println("ID (раннее связывание, final): " + player.getId()); 
            System.out.println("Описание (позднее): " + player.describe());
            System.out.println("Решение: " + player.decideAction());
            
            // Аналог dynamic_cast -> instanceof 
            if (player instanceof PlayerAction actionPlayer) {
                try {
                    actionPlayer.makeBet(100); // Успешное действие
                    
                    System.out.println("  [Провокация] Пытаемся поставить 10000 фишек...");
                    actionPlayer.makeBet(10000); // Выбросит InsufficientFundsException
                    
                } catch (InsufficientFundsException e) {
                    // частное исключение (по ссылке)
                    System.err.println("  [ОШИБКА] " + e.getMessage());
                } catch (Exception e) {
                    // Общее исключение (идет вторым)
                    System.err.println("  [НЕИЗВЕСТНАЯ ОШИБКА] " + e.getMessage());
                }
            }
        }

        // 3. Смена стратегии  (Динамическое конфигурирование)
        System.out.println("\n--- Смена стратегии (Динамическое конфигурирование) ---");
        bot.setStrategy(new PassiveStrategy());
        System.out.println("Бот Alpha сменил стратегию. Новое решение: " + bot.decideAction());

        // 4. Comparable и try-with-resources
        System.out.println("\n--- Comparable и try-with-resources ---");
        // Используем твой IssueLog, который реализует AutoCloseable
        try (IssueLog log = new IssueLog("Лог Сортировки")) {
            List<Card> deck = new ArrayList<>();
            deck.add(new Card(Suit.HEARTS, Rank.ACE));
            deck.add(new Card(Suit.SPADES, Rank.TWO));
            deck.add(new Card(Suit.CLUBS, Rank.KING));
            
            Collections.sort(deck); // Сортировка работает через Comparable
            log.write("Карты отсортированы: " + deck);
            
        } // log.close() вызовется автоматически!
    }
}