public class PassiveStrategy implements BettingStrategy {
    @Override
    public int calculateBet(int currentBet, int stack) {
        return currentBet; // Просто колл
    }
}