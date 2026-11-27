public class HumanPlayer extends BasePlayer 
{
  
    public HumanPlayer(String name, int stack) 
    {
        super(name,stack);
        System.out.println("[HumanPlayer ctor] " + getName());
    }

   
    @Override
    public String describe() {
       return getName() + " [" + getStack() + "] (Human)";
    }

    public String decideAction() {
        if (getStrategy() != null) {
            int bet = getStrategy().calculateBet(50, getStack());
            return "bet " + bet;
        }
        return "call";
    }

    @Override
    public BasePlayer clone() {
        return new HumanPlayer(getName(), getStack()); 
    }

}