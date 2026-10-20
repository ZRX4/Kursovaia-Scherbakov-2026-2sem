public class Game {
    public static final int MAX_PLAYERS = 5;

    private final String name;
    private final Deck deck;   // ← ссылка на ВНЕШНЮЮ колоду
    private final int playerCount;
    private int roundNumber;

    public Game(String name, Deck deck, int playerCount) {
        this.name = name;
        this.deck = deck;
        this.roundNumber = 0;

        if (deck == null) {
            System.err.println("[Game] Ошибка: колода не передана!");
            this.playerCount = 0;
        } else if (playerCount < 2 || playerCount > MAX_PLAYERS) {
            System.err.println("[Game] Неверное число игроков: " + playerCount
                    + ". Допустимо 2.." + MAX_PLAYERS);
            this.playerCount = 0;
        } else {
            this.playerCount = playerCount;
            System.out.println("[Game ctor] Игра \"" + name
                    + "\" создана, игроков: " + playerCount);
        }
    }

    public boolean hasDeck() {
        return deck != null;
    }

    public void startNewHand() {
        if (!hasDeck()) {
            System.err.println("[Game] Нет колоды — раздача невозможна");
            return;
        }
        if (deck.getRemaining() < playerCount * 2) {
            System.err.println("[Game] Недостаточно карт для раздачи. Сбрасываю колоду.");
            deck.reset();
        }
        roundNumber++;
        System.out.println("[Game] Раздача #" + roundNumber + " начата");
    }

    public void endRound() {
        System.out.println("[Game] Раунд торговли завершён");
    }

    public void printStatus() {
        System.out.println("=== Игра: " + name
                + " | Игроков: " + playerCount
                + " | Раздача: " + roundNumber + " ===");
        if (deck != null) {
            System.out.println("Карт в колоде: " + deck.getCardCount()
                    + " | Осталось: " + deck.getRemaining());
        }
    }

    public String getName() { return name; }
    public int getPlayerCount() { return playerCount; }
    public int getRoundNumber() { return roundNumber; }
}