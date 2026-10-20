import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class Deck {
    public static final int STANDARD_DECK_SIZE = 52;
    public static final int DEMO_DECK_SIZE = 5;

    private static final Rank[] ALL_RANKS = {
        Rank.TWO, Rank.THREE, Rank.FOUR, Rank.FIVE, Rank.SIX, Rank.SEVEN,
        Rank.EIGHT, Rank.NINE, Rank.TEN, Rank.JACK, Rank.QUEEN, Rank.KING, Rank.ACE
    };

    private static final Suit[] ALL_SUITS = {
        Suit.HEARTS, Suit.DIAMONDS, Suit.CLUBS, Suit.SPADES
    };

    private final List<Card> cards;   // ← карты «внутри» колоды
    private int nextToDeal;

    public Deck(int size) {
        if (!isValidSize(size)) {
            System.err.println("[Deck] Неверный размер колоды: " + size
                    + ". Использую " + STANDARD_DECK_SIZE);
            size = STANDARD_DECK_SIZE;
        }
        System.out.println("[Deck ctor] Создаю колоду на " + size + " карт");

        this.cards = new ArrayList<>();
        this.nextToDeal = 0;

        for (int i = 0; i < size; i++) {
            Suit suit = ALL_SUITS[(i / ALL_RANKS.length) % ALL_SUITS.length];
            Rank rank = ALL_RANKS[i % ALL_RANKS.length];
            cards.add(new Card(suit, rank));   // ← СОЗДАЁМ карты ВНУТРИ колоды
        }
    }

    public Deck() {
        this(DEMO_DECK_SIZE);
    }

    private static boolean isValidSize(int size) {
        return size > 0 && size <= STANDARD_DECK_SIZE;
    }

    public void shuffle() {
        Collections.shuffle(cards, new Random());
        nextToDeal = 0;
        System.out.println("[Deck] Перемешано");
    }

    public Card dealOne() {
        if (nextToDeal >= cards.size()) {
            System.err.println("[Deck] Колода пуста! Возвращаю пустую карту");
            return new Card(Suit.UNKNOWN, Rank.UNKNOWN);
        }
        Card original = cards.get(nextToDeal++);
        return new Card(original.getSuit(), original.getRank());   // копия
    }

    public void reset() {
        nextToDeal = 0;
        shuffle();
    }

    public int getCardCount() { return cards.size(); }
    public int getRemaining() { return cards.size() - nextToDeal; }

    public void printAll() {
        System.out.print("[Deck] Содержимое: ");
        for (Card c : cards) {
            System.out.print(c + " ");
        }
        System.out.println();
    }
}