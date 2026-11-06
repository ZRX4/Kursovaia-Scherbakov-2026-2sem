public class HumanPlayer extends BasePlayer 
{
  
    public HumanPlayer(String name, int stack) 
    {
        super(name,stack);
        System.out.println("[HumanPlayer ctor] " + getName());
    }

    public HumanPlayer(HumanPlayer other)
    {
        super(other);
        System.out.println("[BotPlayer copy ctor]");
    }

    @Override
    public String describe() {
        return super.describe() + " (Human)";
    }

    @Override
    public String decideAction() {
        return "call";
    }

    @Override
    public BasePlayer clone() {
        return new HumanPlayer(this);
    }

}