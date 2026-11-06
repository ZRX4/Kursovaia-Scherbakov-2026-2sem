public class Main
{
    public static void main(String[] args)
    {
        demoPolymorphism();
        demoClone();
        demoShallowCopy();
        demoDeepCopy();
        demoEqualsAndHashCode();
        demoThis();
    }

    private static void demoPolymorphism()
    {
        System.out.println("\n=== 1. Полиморфный массив ===");
        BasePlayer[] players = new BasePlayer[3];
        players[0] = new HumanPlayer("Alex", 1000);
        players[1] = new BotPlayer("Alpha", 1000, "Tight");
        players[2] = new BotPlayer("Beta", 800, "Loose");

        for (BasePlayer p : players) {
            System.out.println(p.describe() + " -> " + p.decideAction());
        }
    }

    private static void demoClone()
    {
        System.out.println("\n=== 2. Клонирование (Clone) ===");

        HumanPlayer orig = new HumanPlayer("Alex", 1000);
        BasePlayer clon = orig.clone();

        System.out.println("Оригинал: " + orig.describe());
        System.out.println("Копия:    " + clon.describe());
        System.out.println("Разные объекты в памяти? " + (orig != clon));
    }

    private static void demoShallowCopy() 
    {
        System.out.println("\n=== 3. Поверхностная копия (Shallow Copy) ===");

        ShallowDemo original= new ShallowDemo("Bob");
        ShallowDemo no_original = new ShallowDemo(original);
        
        System.out.println("Оригинал до:   " + original.nickname);
        no_original.nickname.append("no original ");
        System.out.println("Оригинал после:  "+original.nickname);
        System.out.println("Rjgbz после:  "+no_original.nickname);
    }

    private static void demoDeepCopy()
    {
        System.out.println("\n=== 4. Глубокая копия (Deep Copy) ===");

        HumanPlayer orig = new HumanPlayer("Alex", 1000);
        HumanPlayer copy = new HumanPlayer(orig);

        System.out.println("Оригинал до:   " + orig.getNickname());

        copy.getNickname().append("(no orig) ");
        System.out.println("Оригинал после "+orig.getNickname());
        System.out.println("Rjgbz после "+copy.getNickname());
    }

    private static void demoThis()
    {
        System.out.println("\n=== 6. Использование this ===");
        HumanPlayer p1 = new HumanPlayer("Mark",1234);
        BotPlayer p2 = new BotPlayer("Oleg",1234,"Loose");
        //возврат this
        BasePlayer p1_copy = p1.sitDown(p2);
        p1_copy.sitDown(p2); 

    }

    private static void demoEqualsAndHashCode()
    {
        System.out.println("\n=== 5. Сравнение equals и hashCode ===");
        HumanPlayer p1 = new HumanPlayer("Test", 100);
        HumanPlayer p2 = new HumanPlayer("Test", 100);
        HumanPlayer p3 = p1; // Ссылка на тот же объект

        System.out.println("p1.equals(p2): " + p1.equals(p2) + " (разные ID)");
        System.out.println("p1.equals(p3): " + p1.equals(p3) + " (один и тот же объект)");
        System.out.println("p1.hashCode() == p2.hashCode(): " + (p1.hashCode() == p2.hashCode()));
        System.out.println("p1.hashCode() == p3.hashCode(): " + (p1.hashCode() == p3.hashCode()));
    }


}
