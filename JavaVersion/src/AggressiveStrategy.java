public class AggressiveStrategy implements BettingStrategy {
    @Override
    public int calculateBet(int currentBet, int stack) {
        return Math.min(currentBet * 2, stack);
    }
}