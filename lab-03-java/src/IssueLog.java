public class IssueLog implements AutoCloseable {
    private final String title;
    private boolean open;

    public IssueLog(String title) {
        this.title = title;
        this.open = true;
        System.out.println("[+] Журнал открыт: " + title);
    }

    public void write(String line) {
        if (!open){
            System.out.println("Журнал уже закрыт.");
            return;
        }
        System.out.println("    " + line);
        
    }

    @Override
    public void close() {
        if(!open){
            return;
        }
        System.out.println("[-] Журнал закрыт: " + title);
        open=false;
    }
}