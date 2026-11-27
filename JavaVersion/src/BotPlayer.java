public class BotPlayer extends BasePlayer 
{
    private String strategyName;


    public BotPlayer(String name, int stack,String strategy) 
    {
        super(name,stack);
        this.strategyName=strategy;

        System.out.println("[BotPlayer ctor] " + getName());
    }

    @Override
    public String describe() {
        return getName() + " [" + getStack() + "] [Strategy:" + strategyName + "] (Bot)";
    }

    @Override
    public String decideAction()
    {
        if (getStrategy() != null) {
            int bet = getStrategy().calculateBet(50, getStack());
            return "bet " + bet;
        }
        return "fold";
    }

    @Override
    public BasePlayer clone()
    {
        return new BotPlayer(getName(), getStack(), strategyName);
    }

}