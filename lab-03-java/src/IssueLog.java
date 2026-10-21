public class IssueLog implements AutoCloseable {
    private final String title;

    public IssueLog(String title) {
        this.title = title;
        System.out.println("[+] Журнал открыт: " + title);
    }

    public void write(String line) {
        System.out.println("    " + line);
    }

    @Override
    public void close() {
        System.out.println("[-] Журнал закрыт: " + title);
    }
}