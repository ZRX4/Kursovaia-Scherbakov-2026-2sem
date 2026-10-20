public enum Suit {
    HEARTS, DIAMONDS, CLUBS, SPADES, UNKNOWN;

    public String getShortName() {
        switch (this) {
            case HEARTS:   return "H";
            case DIAMONDS: return "D";
            case CLUBS:    return "C";
            case SPADES:   return "S";
            default:       return "?";
        }
    }
}