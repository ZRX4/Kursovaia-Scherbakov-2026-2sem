public class InsufficientFundsException extends RuntimeException {
    public InsufficientFundsException(int required, int available) {
        super("Недостаточно фишек! Требуется: " + required + ", доступно: " + available);
    }
}