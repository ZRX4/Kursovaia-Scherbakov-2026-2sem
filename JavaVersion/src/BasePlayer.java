import java.util.Objects;

public abstract class BasePlayer implements PlayerAction {
    private static int s_lastId = 0;

    private final int id;
    private final String name;
    private  int stack;

    
    private BettingStrategy strategy; 

    protected BasePlayer (String name, int stack)
    {
        this.id = ++s_lastId;
        this.name = name;
        this.stack = stack;
        
    }

    public String getName() { return name; }
    public int getStack() { return stack; }


    public final int getId() { return id; } 
    
    public void setStrategy(BettingStrategy strategy) {
        this.strategy = strategy;
    }
    
    protected BettingStrategy getStrategy() {
        return strategy;
    }
    
    public abstract String decideAction(); 
    public abstract String describe();
    public abstract BasePlayer clone();
    

    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (o==null || getClass() != o.getClass()) return false;
         
        BasePlayer that = (BasePlayer) o;
        return id == that.id;

    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }

    @Override
    public void makeBet(int amount) {
        if (amount > stack) {
            // Если фишек не хватает - исключение
            throw new InsufficientFundsException(amount, stack);
        }
        stack -= amount;
        System.out.println("[" + name + "] делает ставку: " + amount + " фишек");
    }

    @Override
    public void fold() {
        System.out.println("[" + name + "] пасует");
    }



}