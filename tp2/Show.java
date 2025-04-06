import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;

public class Show{
    static SimpleDateFormat ddf = new SimpleDateFormat("dd-MM-yyyy");

    public static final String FILE_PATH = "/tmp/disneyplus.csv";
    public static ArrayList<Show> shows = new ArrayList<Show>();

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

    public Show clone() {return new Show(this.show_id, this.type, this.title, this.director, this.cast, this.country, this.date_added, this.release_year, this.range, this.duration, this.listed_in);}
    public Show() {}
    public Show(final String show_id, final String type, final String title, final String director, final String[] cast, final String country, final Date date_added, final int release_year, final String range, final String duration, final String[] listed_in) {this.show_id = show_id;this.type = type;this.title = title;this.director = director;this.cast = cast;this.country = country;this.date_added = date_added;this.release_year = release_year;this.range = range;this.duration = duration;this.listed_in = listed_in;}
    public String getShow_id() {return show_id;}
    public String getType() {return type;}
    public String getTitle() {return title;}
    public String getDirector() {return director;}
    public String[] getCast() {return cast;}
    public String getCountry() {return country;}
    public Date getDate_added() {return date_added;}
    public int getRelease_year() {return release_year;}
    public String getRange() {return range;}
    public String getDuration() {return duration;}
    public String[] getListed_in() {return listed_in;}
    public Show setShow_id(String show_id) {this.show_id = show_id;return this;}
    public Show setType(String type) {this.type = type;return this;}
    public Show setTitle(String title) {this.title = title;return this;}
    public Show setDirector(String director) {this.director = director;return this;}
    public Show setCast(String[] cast) {this.cast = cast;return this;}
    public Show setCountry(String country) {this.country = country;return this;}
    public Show setDate_added(Date date_added) {this.date_added = date_added;return this;}
    public Show setRelease_year(int release_year) {this.release_year = release_year;return this;}
    public Show setRange(String range) {this.range = range;return this;}
    public Show setDuration(String duration) {this.duration = duration;return this;}
    public Show setListed_in(String[] listed_in) {this.listed_in = listed_in;return this;}

    public static Show searchById(String id, ArrayList<Show> shows) {
        for(int i = 0; i < shows.size(); i++) {

            if(shows.get(i).getShow_id().equals(id)) return shows.get(i);
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
                    ? parts.get(4).split(",\\s*")
                    : new String[]{"NaN"};

            this.country = !parts.get(5).isEmpty() ? parts.get(5) : "NaN";

            if (!parts.get(6).isEmpty()) {
                try {
                    this.date_added = new SimpleDateFormat("MMMM d, yyyy", Locale.ENGLISH).parse(parts.get(6));
                } catch (ParseException e) {
                    this.date_added = null;
                }
            } else {
                this.date_added = null;
            }

            this.release_year = !parts.get(7).isEmpty()
                    ? Integer.parseInt(parts.get(7))
                    : -1;

            this.range = !parts.get(8).isEmpty() ? parts.get(8) : "NaN";
            this.duration = !parts.get(9).isEmpty() ? parts.get(9) : "NaN";

            this.listed_in = !parts.get(10).isEmpty()
                    ? parts.get(10).split(",\\s*")
                    : new String[]{"NaN"};

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void print() {
        System.out.print("=> " + show_id + " ## " + type + " ## " + title + " ## " + director + " ## [");
        System.out.print(String.join(", ", cast));
        System.out.print("] ## " + country + " ## ");

        System.out.print(date_added != null ? ddf.format(date_added) : "NaN");
        System.out.print(" ## " + release_year + " ## " + range + " ## " + duration + " ## [");
        System.out.print(String.join(", ", listed_in));
        System.out.println("]");
    }


    public static void startShows() {
        try {
            FileInputStream fstream = new FileInputStream(FILE_PATH);
            BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
            String line = br.readLine();

            while((line = br.readLine()) != null) {
                Show show = new Show();

                show.read(line);
                shows.add(show);
            }

            fstream.close();
        }
        catch(IOException e) { e.printStackTrace(); }
    }

    public static void main(String[] args) {
        startShows();
       Scanner inScanner = new Scanner(System.in);

       Show show = new Show();
       String line = inScanner.nextLine();

       while(!line.equals("FIM")) {

           show = searchById(line, shows);

           if(show != null) show.print();
           else System.out.println("x Show not found!");

           line = inScanner.nextLine();
       }

       inScanner.close();
    }

}