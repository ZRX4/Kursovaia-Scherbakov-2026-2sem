public class Card implements Comparable<Card> {
    private final Suit suit;    // final = нельзя переназначить после конструктора
    private final Rank rank;
    private boolean isOpen;

    public Card(Suit suit, Rank rank) {
        this.suit = suit;
        this.rank = rank;
        this.isOpen = false;
        System.out.println("[Card ctor] " + this);   // this.toString() вызовется сама
    }

    public Suit getSuit() { return suit; }
    public Rank getRank() { return rank; }
    public boolean isOpen() { return isOpen; }

    public void open() {
        if (isOpen) {
            System.out.println("[Card] " + this + " уже открыта");
            return;
        }
        isOpen = true;
    }

    @Override
    public String toString() {
        return rank.getShortName() + suit.getShortName();
    }

    @Override
    public int compareTo(Card other) {
        int rankCompare = Integer.compare(this.rank.getValue(), other.rank.getValue());
        if (rankCompare != 0) {
            return rankCompare;
        }
        return this.suit.compareTo(other.suit);
    }
}