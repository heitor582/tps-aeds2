import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;
import java.util.function.Consumer;

abstract class List<T> {
    int size = 0;

    abstract void inserirInicio(T t);

    abstract void inserir(T t, int posicao);

    abstract void inserirFim(T t);

    abstract T removerInicio();

    abstract T remover(int posicao);

    abstract T removerFim();

    abstract T get(int i);

    abstract void print();

    int size() {
        return size;
    }

    void addSize() {
        size++;
    }

    void minusSize() {
        size--;
    }
}

class SequencialList extends List<Show> {
    private int maxSize = 50;
    private Show[] list = new Show[maxSize];

    private void realoc() {
        maxSize *= 2;
        Show[] newList = new Show[maxSize];
        for (int i = 0; i < size; i++) {
            newList[i] = list[i];
        }
        list = newList;
    }

    @Override
    void print() {
        for (int i = 0; i < size(); i++) {
            get(i).print();
        }
    }

    @Override
    public Show get(int i) {
        return list[i];
    }

    @Override
    public void inserirInicio(Show show) {
        if (size == maxSize) {
            realoc();
        }
        for (int i = size - 1; i >= 0; i--) {
            list[i + 1] = list[i];
        }
        list[0] = show;
        this.addSize();
    }

    @Override
    public void inserir(Show show, int posicao) {
        if (posicao < 0 || posicao > size)
            return;
        if (size == maxSize)
            realoc();
        for (int i = size - 1; i >= posicao; i--) {
            list[i + 1] = list[i];
        }
        list[posicao] = show;
        addSize();
    }

    @Override
    public void inserirFim(Show show) {
        if (size == maxSize) {
            realoc();
        }
        list[size] = show;
        this.addSize();
    }

    @Override
    public Show removerInicio() {
        if (size == 0)
            return null;
        Show temp = list[0];
        for (int i = 1; i < size; i++) {
            list[i - 1] = list[i];
        }
        this.minusSize();
        list[size] = null;
        return temp;
    }

    @Override
    public Show remover(int posicao) {
        if (posicao < 0 || posicao >= size)
            return null;
        Show removed = list[posicao];
        for (int i = posicao + 1; i < size; i++) {
            list[i - 1] = list[i];
        }
        minusSize();
        list[size] = null;
        return removed;
    }

    @Override
    public Show removerFim() {
        if (size == 0)
            return null;
        this.minusSize();
        Show temp = list[size];
        list[size] = null;
        return temp;
    }
}

class Node<T> {
    Node<T> next, previous;
    T val;

    public Node(T val) {
        next = previous = null;
        this.val = val;
    }
}

class LinkedList extends List<Show> {
    Node<Show> head, tail = null;

    public LinkedList() {
    }

    @Override
    void inserirInicio(Show t) {
        Node<Show> newNode = new Node<Show>(t);
        if (this.head == null && this.tail == null) {
            this.tail = this.head = newNode;
        } else {
            this.head.previous = newNode;
            newNode.next = this.head;
            this.head = newNode;
        }
    }

    @Override
    void inserir(Show t, int position) {
        if (position == 0) {
            inserirInicio(t);
            return;
        }
        if (position == this.size) {
            inserirFim(t);
            return;
        }
        Node<Show> cur = this.head;
        for (int i = 0; cur != null && i < position; cur = cur.next, i++)
            ;
        Node<Show> newNode = new Node<Show>(t);
        newNode.next = cur;
        newNode.previous = cur.previous;
        cur.previous.next = newNode;
        cur.previous = newNode;
        this.size++;
    }

    @Override
    void inserirFim(Show t) {
        if (this.head == null && this.tail == null) {
            inserirInicio(t);
            return;
        }
        Node<Show> newNode = new Node<Show>(t);
        newNode.previous = this.tail;
        this.tail.next = newNode;
        this.tail = newNode;
        this.size++;
    }

    @Override
    Show removerInicio() {
        if (this.head == null && this.tail == null)
            return null;

        Node<Show> tempNode = this.head;
        Show temp = tempNode.val;

        if (this.head == this.tail) {
            this.head = null;
            this.tail = null;
        } else {
            this.head = this.head.next;
            this.head.previous = null;
        }

        this.size--;

        return temp;
    }

    @Override
    Show remover(int position) {
        if (position == 0)
            return removerInicio();
        if (position == this.size)
            return removerFim();

        Node<Show> cur = this.head;
        for (int i = 0; cur != null && i < position; cur = cur.next, i++)
            ;
        cur.previous.next = cur.next;
        cur.next.previous = cur.previous;
        Show temp = cur.val;
        cur.next = null;
        cur.previous = null;
        this.size--;
        return temp;
    }

    @Override
    Show removerFim() {
        if (this.head == null && this.tail == null || this.head == this.tail)
            return removerInicio();
        Node<Show> tempNode = this.tail;
        Show temp = tempNode.val;

        this.tail = this.tail.previous;
        this.tail.next = null;
        this.size--;
        return temp;
    }

    @Override
    Show get(int i) {
        Node<Show> cur = this.head;
        for (int j = 0; cur != null && j < i; cur = cur.next)
            ;
        return cur.val;
    }

    @Override
    void print() {
        for (Node<Show> cur = this.head; cur != null; cur = cur.next) {
            cur.val.print();
        }
    }

    void printInverse() {
        int i = size;
        for (Node<Show> cur = this.tail; cur != null; cur = cur.previous, i--) {
            System.out.print("[" + i + "] ");
            cur.val.print();
        }
    }

}

public class Show {
    static SimpleDateFormat ddf = new SimpleDateFormat("MMMM dd, yyyy");
    static SimpleDateFormat ddf2 = new SimpleDateFormat("MMMM d, yyyy");
    public static final String FILE_PATH = "/tmp/disneyplus.csv";
    public static ArrayList<Show> shows = new ArrayList<Show>();
    static int comp = 0;
    static int mov = 0;
    private String show_id;
    private String type;
    private String title;
    private String director;
    private String[] cast;
    private String country;
    private Date date_added;
    private int release_year;
    private String range;
    private String duration;
    private String[] listed_in;

    public Show clone() {
        return new Show(this.show_id, this.type, this.title, this.director, this.cast, this.country, this.date_added,
                this.release_year, this.range, this.duration, this.listed_in);
    }

    public Show() {
    }

    public Show(final String show_id, final String type, final String title, final String director, final String[] cast,
            final String country, final Date date_added, final int release_year, final String range,
            final String duration, final String[] listed_in) {
        this.show_id = show_id;
        this.type = type;
        this.title = title;
        this.director = director;
        this.cast = cast;
        this.country = country;
        this.date_added = date_added;
        this.release_year = release_year;
        this.range = range;
        this.duration = duration;
        this.listed_in = listed_in;
    }

    public String getShow_id() {
        return show_id;
    }

    public String getType() {
        return type;
    }

    public String getTitle() {
        return title;
    }

    public String getDirector() {
        return director;
    }

    public String[] getCast() {
        return cast;
    }

    public String getCountry() {
        return country;
    }

    public Date getDate_added() {
        return date_added;
    }

    public int getRelease_year() {
        return release_year;
    }

    public String getRange() {
        return range;
    }

    public String getDuration() {
        return duration;
    }

    public String[] getListed_in() {
        return listed_in;
    }

    public Show setShow_id(String show_id) {
        this.show_id = show_id;
        return this;
    }

    public Show setType(String type) {
        this.type = type;
        return this;
    }

    public Show setTitle(String title) {
        this.title = title;
        return this;
    }

    public Show setDirector(String director) {
        this.director = director;
        return this;
    }

    public Show setCast(String[] cast) {
        this.cast = cast;
        return this;
    }

    public Show setCountry(String country) {
        this.country = country;
        return this;
    }

    public Show setDate_added(Date date_added) {
        this.date_added = date_added;
        return this;
    }

    public Show setRelease_year(int release_year) {
        this.release_year = release_year;
        return this;
    }

    public Show setRange(String range) {
        this.range = range;
        return this;
    }

    public Show setDuration(String duration) {
        this.duration = duration;
        return this;
    }

    public Show setListed_in(String[] listed_in) {
        this.listed_in = listed_in;
        return this;
    }

    public void heapSort(String[] v) {
        for (int i = 1; i < v.length; i++) {
            for (int j = i; j > 0 && v[j].trim().compareTo(v[(j - 1) / 2].trim()) > 0; j = (j - 1) / 2) {
                String temp = v[j];
                v[j] = v[(j - 1) / 2];
                v[(j - 1) / 2] = temp;
            }
        }
        for (int i = v.length - 1; i >= 0;) {
            String temp = v[i];
            v[i] = v[0];
            v[0] = temp;
            i--;
            int j = 0;
            while (j < i) {
                if (j * 2 + 1 <= i || j * 2 + 2 <= i) {
                    int ji = j * 2 + 2 <= i && v[j * 2 + 2].trim().compareTo(v[j * 2 + 1].trim()) > 0 ? j * 2 + 2
                            : j * 2 + 1;
                    if (v[j].trim().compareTo(v[ji].trim()) < 0) {
                        String temp2 = v[j];
                        v[j] = v[ji];
                        v[ji] = temp2;
                        j = ji;
                    } else {
                        j = i;
                    }
                } else {
                    j = i;
                }
            }
        }
    }

    public static Show searchById(String id, ArrayList<Show> shows) {
        for (int i = 0; i < shows.size(); i++) {
            if (shows.get(i).getShow_id().equals(id))
                return shows.get(i);
        }
        return null;
    }

    public void read(String line) {
        try {
            ArrayList<String> parts = new ArrayList<>();
            boolean inQuotes = false;
            StringBuilder sb = new StringBuilder();

            for (char c : line.toCharArray()) {
                if (c == '"') {
                    inQuotes = !inQuotes;
                } else if (c == ',' && !inQuotes) {
                    parts.add(sb.toString().trim());
                    sb = new StringBuilder();
                } else {
                    sb.append(c);
                }
            }
            parts.add(sb.toString().trim());
            this.show_id = !parts.get(0).isEmpty() ? parts.get(0) : "NaN";
            this.type = !parts.get(1).isEmpty() ? parts.get(1) : "NaN";
            this.title = !parts.get(2).isEmpty() ? parts.get(2) : "NaN";
            this.director = !parts.get(3).isEmpty() ? parts.get(3) : "NaN";

            this.cast = !parts.get(4).isEmpty()
                    ? parts.get(4).split(",\s*")
                    : new String[] { "NaN" };
            this.heapSort(this.cast);

            this.country = !parts.get(5).isEmpty() ? parts.get(5) : "NaN";

            if (parts.get(6) != null && !parts.get(6).isEmpty()) {
                try {
                    this.date_added = ddf.parse(parts.get(6));
                } catch (ParseException e) {
                    this.date_added = null;
                }
            } else {
                this.date_added = ddf.parse("March 1, 1900");
            }

            this.release_year = !parts.get(7).isEmpty()
                    ? Integer.parseInt(parts.get(7))
                    : -1;

            this.range = !parts.get(8).isEmpty() ? parts.get(8) : "NaN";
            this.duration = !parts.get(9).isEmpty() ? parts.get(9) : "NaN";

            this.listed_in = !parts.get(10).isEmpty()
                    ? parts.get(10).split(",\s*")
                    : new String[] { "NaN" };
            this.heapSort(this.listed_in);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void print() {
        System.out.print("=> " + show_id + " ## " + title + " ## " + type + " ## " + director + " ## [");
        System.out.print(String.join(", ", cast));
        System.out.print("] ## " + country + " ## ");

        System.out.print(date_added != null ? ddf2.format(date_added) : "NaN");
        System.out.print(" ## " + release_year + " ## " + range + " ## " + duration + " ## [");
        System.out.print(String.join(", ", listed_in));
        System.out.println("] ##");
    }

    public static void startShows() {
        try {
            FileInputStream fstream = new FileInputStream(FILE_PATH);
            BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
            String line = br.readLine();

            while ((line = br.readLine()) != null) {
                Show show = new Show();

                show.read(line);
                shows.add(show);
            }

            fstream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void process(String command, SequencialList showsList) {
        if (command.startsWith("R")) {
            Show removed = null;
            if (command.startsWith("RI"))
                removed = showsList.removerInicio();
            else if (command.startsWith("RF"))
                removed = showsList.removerFim();
            else if (command.startsWith("R*"))
                removed = showsList.remover(Integer.parseInt(command.split(" ")[1]));
            System.out.println("(R) " + removed.title);
        } else if (command.startsWith("I")) {
            String id = command.startsWith("I*") ? command.split(" ")[2] : command.split(" ")[1];
            Show show = searchById(id, shows);
            if (command.startsWith("II"))
                showsList.inserirInicio(show);
            else if (command.startsWith("IF"))
                showsList.inserirFim(show);
            else if (command.startsWith("I*"))
                showsList.inserir(show, (Integer.parseInt(command.split(" ")[1])));
        }
    }

    public static void process(String command, LinkedList showsList) {
        if (command.startsWith("R")) {
            Show removed = showsList.removerFim();
            System.out.println("(R) " + removed.title);
        } else if (command.startsWith("I")) {
            String id = command.split(" ")[1];
            Show show = searchById(id, shows);
            showsList.inserirFim(show);
        }
    }

    public static int compare(String a, String b) {
        comp++;
        return a.trim().compareToIgnoreCase(b.trim());
    }

    public static int compareDateAddedAndTitle(Show a, Show b) {
        if (a.date_added == null || b.date_added == null) {
            return compare(a.title, b.title);
        }
        comp++;
        int compDate = a.date_added.compareTo(b.date_added);
        if (compDate != 0) {
            return compDate;
        }

        return compare(a.title, b.title);
    }

    static void swap(Node<Show> a, Node<Show> b) {
        Show temp = a.val;
        a.val = b.val;
        b.val = temp;
        mov += 3;
    }

    static Node<Show> partition(Node<Show> low, Node<Show> high) {
        Node<Show> pivot = high;
        Node<Show> i = low.previous;

        for (Node<Show> j = low; j != high; j = j.next) {
            if (compareDateAddedAndTitle(j.val, pivot.val) < 0) {
                i = (i == null) ? low : i.next;
                swap(i, j);
            }
        }
        i = (i == null) ? low : i.next;
        swap(i, high);

        return i;
    }

    static void quickSort(Node<Show> low, Node<Show> high) {
        if (low != null && high != null &&
                low != high && low != high.next) {

            Node<Show> pivot = partition(low, high);
            quickSort(low, pivot.previous);
            quickSort(pivot.next, high);
        }
    }

    public static void verdeSort(List<Show> list, String filename, Consumer<List<Show>> sort,
            Consumer<List<Show>> print) throws FileNotFoundException {
        long inicio = System.currentTimeMillis();
        sort.accept(list);
        long fimTempo = System.currentTimeMillis();
        print.accept(list);

        PrintWriter log = new PrintWriter("867936_" + filename + ".txt");
        log.println("867936\t" + comp + "\t" + mov + "\t" + (fimTempo - inicio));
        log.close();
    }

    public static void main(String[] args) throws FileNotFoundException {
        startShows();
        Scanner sc = new Scanner(System.in);

        List<Show> list = new LinkedList();
        String line = sc.nextLine();

        while (!line.equals("FIM")) {
            Show show = searchById(line, shows);

            if (show != null)
                list.inserirFim(show);
            else
                System.out.println("x Show not found!");

            line = sc.nextLine();
        }
        // int size = sc.nextInt();
        // sc.nextLine();
        // for (int i = 0; i < size; i++) {
        // line = sc.nextLine();
        // process(line, (LinkedList) list);
        // }
        // ((LinkedList) list).printInverse();
        verdeSort(list, "quicksort", lista -> {
            quickSort(((LinkedList) list).head, ((LinkedList) list).tail);
        }, lista -> {
            lista.print();
        });

        sc.close();
    }

}