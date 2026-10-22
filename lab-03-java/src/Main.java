import java.lang.ref.WeakReference;

public class Main {
    public static void main(String[] args) {
        demoComposition();
        demoAggregation();
        demoRuleCheck();
        demoReferencesAndCopies();
        demoAutoCloseable();
        demoGarbageCollector();
    }

    private static void demoComposition() {
        System.out.println("========= 1. Композиция: Deck создаёт Card =========");
        Deck deck = new Deck(5);
        deck.printAll();
        deck.shuffle();
        Card dealt = deck.dealOne();
        System.out.println("Выдана карта: " + dealt);
        System.out.println("(Колода и её карты будут уничтожены GC когда-нибудь)");
    }

    private static void demoAggregation() {
        System.out.println("\n========= 2. Агрегация: Game использует внешний Deck =========");
        Deck sharedDeck = new Deck(10);

        {
            Game game = new Game("Sport Hold'em", sharedDeck, 5);
            game.printStatus();
            game.startNewHand();
            game.endRound();
        }
        // game вышла из области видимости, но колода жива

        System.out.println("\n--- После выхода из блока game колода всё ещё работает: ---");
        sharedDeck.printAll();
        System.out.println("Осталось карт: " + sharedDeck.getRemaining());
    }

    private static void demoRuleCheck() {
        System.out.println("\n========= 3. Проверка правила =========");
        Deck badDeck = new Deck(999);
        System.out.println("Итоговый размер: " + badDeck.getCardCount());
    }

    private static void demoReferencesAndCopies() {
        System.out.println("\n========= 4. Ссылки и копии =========");

        Card cardA = new Card(Suit.HEARTS, Rank.ACE);
        Card cardB = cardA;   // ← это НЕ копия, это ВТОРАЯ ССЫЛКА

        System.out.println("cardA == cardB: " + (cardA == cardB)
                + "  (это ОДИН объект)");
        System.out.println("cardA.isOpen(): " + cardA.isOpen());

        cardB.open();   // меняем «через cardB»

        System.out.println("cardA.isOpen() после cardB.open(): " + cardA.isOpen()
                + "  ← cardA \"тоже изменился\" — это тот же объект");

        Card cardC = new Card(Suit.HEARTS, Rank.ACE);   // явно НОВЫЙ объект
        System.out.println("cardA == cardC: " + (cardA == cardC)
                + "  (это РАЗНЫЕ объекты)");
        System.out.println("cardA.equals(cardC): " + cardA.equals(cardC)
                + "  (equals по умолчанию сравнивает ссылки)");
    }

    private static void demoAutoCloseable() {
        System.out.println("\n========= 5. AutoCloseable / try-with-resources =========");
        IssueLog newlog;
        try (IssueLog log = new IssueLog("Раздача #1")) {
            newlog=log;
            log.write("Игроки сделали ставки");
            log.write("Открыт флоп");
            log.write("Раунд завершён");
            System.out.println("    Внутри блока try — журнал ещё открыт");
        }
        // здесь Java автоматически вызвала log.close()

        System.out.println("После блока try — журнал закрыт (close() вызван автоматически)");
        newlog.write("Запись не должна пройти");
    }

    private static void demoGarbageCollector() {
        System.out.println("\n========= 6. Сборщик мусора =========");

        WeakReference<Card> watcher = createTemporaryCard();

        System.out.println("После выхода из createTemporaryCard: объект жив? "
                + (watcher.get() != null));
        System.out.println("(Локальная переменная temp уже вне области видимости,");
        System.out.println(" но GC её ещё не собрал — момент неизвестен)");

        // Просим GC собрать. Это ПРОСЬБА, не команда.
        for (int i = 0; i < 3; i++) {
            System.gc();
            try {
                Thread.sleep(50);
            } catch (InterruptedException ignored) {
            }
        }

        boolean alive = watcher.get() != null;
        System.out.println("После System.gc(): объект жив? " + alive);
        if (alive) {
            System.out.println("(GC не собрал )");
        } else {
            System.out.println("(GC собрал объект)");
        }
    }

    private static WeakReference<Card> createTemporaryCard() {
        Card temp = new Card(Suit.SPADES, Rank.KING);
        System.out.println("Создана временная карта: " + temp);
        return new WeakReference<>(temp);
    }
}