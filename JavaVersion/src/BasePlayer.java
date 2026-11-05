public abstract class BasePlayer {

    private static int lasTd=0;

    private final int id;
    private final String name;
    private final int stack;
    private final boolean isDealer;

    private String nickname;

    //конструктор

    protected basePlayer (String name, int stack)
    {
        this.id = nextId();
        this.name = name;
        this.stack = stack;
        this.isDealer = false;
        this.nickname = name;
    }

    //конструктор копирования
    protected basePlayer (BasePlayer other)
    {
        this.id = nextId();
        this.name = other.name;
        this.stack = other.stack;
        this.isDealer = other.isDealer;
        this.nickname = new String(other.nickname);
    }

    public static int nextId()
    {
        return ++lastId;
    }

    public String getName() { return name; }
    public int getStack() { return stack; }
    public int getId() { return id; }
    public boolean isDealer() { return isDealer; }
    public String getNickname() { return nickname; }

    protected String header()
    {
        return name + "["+stack+"]";
    }

    public String describe()
    {
        if (isDealer)
        {
            return header()+" dealer";
        }
        return header();
    }

    public abstract String decideAction();
    public abstract BasePlayer clone();


    public BasePlayer sitDown(BasePlayer other) 
    {
        System.out.println("  [this] " + this.getName() + " sits with " + other.getName());
        return this; // Возвращаем текущий объект
    }


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



}