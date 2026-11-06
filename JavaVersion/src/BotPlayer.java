public class BotPlayer extends BasePlayer 
{
    private String strategy;


    public BotPlayer(String name, int stack,String strategy) 
    {
        super(name,stack);
        this.strategy=strategy;

        System.out.println("[BotPlayer ctor] " + getName());
    }

    public BotPlayer(BotPlayer other)
    {
        super(other);
        this.strategy = other.strategy;
        System.out.println("[BotPlayer copy ctor]");
    }

    @Override
    public String decideAction()
    {
        return "fold";
    }

    @Override
    public BasePlayer clone()
    {
        return new BotPlayer(this);
    }

}