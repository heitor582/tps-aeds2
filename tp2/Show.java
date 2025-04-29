import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.Scanner;
import java.util.function.Consumer;

public class Show{
    static SimpleDateFormat ddf = new SimpleDateFormat("MMMM dd, yyyy");
    static SimpleDateFormat ddf2 = new SimpleDateFormat("MMMM d, yyyy");

    public static final String FILE_PATH = "/tmp/disneyplus.csv";
    public static ArrayList<Show> shows = new ArrayList<Show>();
    private static int mov = 0;
    private static int comp = 0;

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
    
    public void heapSort(String[] v){
        for(int i = 1; i < v.length; i++){
            for(int j = i; j > 0 && v[j].trim().compareTo(v[(j-1)/2].trim()) > 0; j = (j-1)/2){
                String temp = v[j];
                v[j] = v[(j-1)/2];
                v[(j-1)/2] = temp;
            }
        }
        for(int i = v.length-1; i>=0;){
            String temp = v[i];
            v[i] = v[0];
            v[0] = temp;
            i--;
            int j = 0;
            while(j < i){
                if(j*2+1 <= i || j*2+2 <= i){
                    int ji = j*2+2 <= i && v[j*2+2].trim().compareTo(v[j*2+1].trim()) > 0?  j*2+2 : j*2+1;
                    if(v[j].trim().compareTo(v[ji].trim()) < 0) {
                        String temp2 = v[j];
                        v[j] = v[ji];
                        v[ji] = temp2;
                        j=ji;
                    } else {j=i;}
                } else {
                    j=i;
                }
            }
        }
    }
    public static void heapSort(List<Show> v){
        for(int i = 1; i < v.size(); i++){
            for(int j = i; j > 0 && 
            (compare(v.get(j).director, v.get((j-1)/2).director) > 0 
            || (compare(v.get(j).director, v.get((j-1)/2).director) == 0 
                && compare(v.get(j).title, v.get((j-1)/2).title) > 0)); j = (j-1)/2){
                swap(v, j, (j-1)/2);
            }
        }
        for(int i = v.size()-1; i>=0;i--){
            swap(v, 0, i);
            int j = 0;
            while(j < i){
                if(j*2+1 < i || j*2+2 < i){
                    int ji = j*2+2 < i && 
                    (compare(v.get(j*2+2).director, v.get(j*2+1).director) > 0 || 
                    compare(v.get(j*2+2).director, v.get(j*2+1).director) == 0 && 
                    compare(v.get(j*2+2).title, v.get(j*2+1).title) > 0) ?  j*2+2 : j*2+1;
                    int result = compare(v.get(j).director,v.get(ji).director);
                    if(result < 0 || (result==0 && compare(v.get(j).title,v.get(ji).title) < 0)) {
                        swap(v, j, ji);
                        j=ji;
                    } else {j=i;}
                } else {
                    j=i;
                }
            }
        }
    }
    public static void merge(List<Show> arr, int left, int mid, int right){
        int nLength = mid+1-left;
        int nRight = right-mid;
        List<Show> L = new ArrayList<>(), R = new ArrayList<>();
        for(int i = 0; i < nLength; i++){
            L.add(arr.get(left+i));
        }
        for(int i = 0; i < nRight; i++){
            R.add(arr.get(mid+1+i));
        }
        for(int i = left, r = 0, l=0; i<=right; i++){
            Show show = null;
            if (l >= L.size()) {
                show = R.get(r++);
            } else if (r >= R.size()) {
                show = L.get(l++);
            } else {
                int result = compareWithCase(L.get(l).duration, R.get(r).duration);
                if(result < 0) {
                    show = L.get(l);
                    l++;
                } else if(result == 0) {
                    if(compare(L.get(l).title, R.get(r).title) < 0){
                        show = L.get(l);
                        l++;
                    } else {
                        show = R.get(r);
                        r++;
                    }
                } else {
                    show = R.get(r);
                    r++;
                }
            }
            mov++;
            arr.set(i, show);
        }
    }
    public static void mergeSort(List<Show> arr, int left, int right) {
        if(left>=right){
            return;
        }
        int mid = left+(right-left)/2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);
        merge(arr,left,mid,right);
    }
    public static void selectionSortPartial(List<Show> shows, int right){
        if(shows.size() < right){
            right = shows.size();
        }
        for(int i = 0; i<right; i++){
            int min = i;
            for(int j = i+1; j<shows.size(); j++){
                comp++;
                if(compare(shows.get(min).getTitle(), shows.get(j).getTitle()) > 0){
                    min = j;
                }
            }
            swap(shows, i, min);
        }
    }
    public static void selectionSort(List<Show> shows){
        for(int i = 0; i<shows.size()-1; i++){
            int min = i;
            for(int j = i+1; j<shows.size(); j++){
                comp++;
                if(compare(shows.get(min).getTitle(), shows.get(j).getTitle()) > 0){
                    min = j;
                }
            }
            swap(shows, i, min);
        }
    }
    public static void insertionSort(List<Show> arr) {
        for (int i = 1; i < arr.size(); i++) {
            Show current = arr.get(i);
            int j = i - 1;
            
            while (j >= 0 && (compare(arr.get(j).type, current.type) > 0 || 
                              (compare(arr.get(j).type, current.type) == 0 && compare(arr.get(j).title, current.title) > 0))) {
                arr.set(j + 1, arr.get(j));
                j--;
            }
    
            arr.set(j + 1, current);
        }
    }
    public static void verdeSort(List<Show> list, String filename, Consumer<List<Show>> sort) throws FileNotFoundException{
        long inicio = System.currentTimeMillis();
        sort.accept(list);
        long fimTempo = System.currentTimeMillis();
        for(Show item : list){
             item.print();
        }

        PrintWriter log = new PrintWriter("867936_"+filename+".txt");
        log.println("867936\t" + comp + "\t" + mov + "\t" + (fimTempo - inicio));
        log.close();
    }
    public static void verdeSort(List<Show> list, String filename, Consumer<List<Show>> sort, Consumer<List<Show>> print) throws FileNotFoundException{
        long inicio = System.currentTimeMillis();
        sort.accept(list);
        long fimTempo = System.currentTimeMillis();
        print.accept(list);

        PrintWriter log = new PrintWriter("867936_"+filename+".txt");
        log.println("867936\t" + comp + "\t" + mov + "\t" + (fimTempo - inicio));
        log.close();
    }
    public static Show searchById(String id, ArrayList<Show> shows) {
        for(int i = 0; i < shows.size(); i++) {
            if(shows.get(i).getShow_id().equals(id)) return shows.get(i);
        }
        return null;
    }
    public static Show searchByTitle(String title, ArrayList<Show> shows) {
        for(int i = 0; i < shows.size(); i++) {
            comp++;
            if(shows.get(i).getTitle().equals(title)) {
                return shows.get(i);
            };
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
                    : new String[]{"NaN"};
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
                    : new String[]{"NaN"};
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
    public static void swap(List<Show> shows, int i, int j){
        Show show = shows.get(i);
        shows.set(i, shows.get(j));
        shows.set(j, show);
        mov+=3;
    }
    public static int compare(String a, String b){
        comp++;
        return a.trim().compareToIgnoreCase(b.trim());
    }
    public static int compareDateAddedAndTitle(Show a, Show b){
        if(a.date_added == null || b.date_added == null){
            return compare(a.title, b.title);
        }
        comp++;
        int compDate = a.date_added.compareTo(b.date_added);
        if(compDate != 0){
            return compDate;
        }

        return compare(a.title, b.title);
    }
    public static int compareWithCase(String a, String b){
        comp++;
        return a.trim().compareTo(b.trim());
    }
    public static int compare(int a, int b){
        comp++;
        int result = 0;
        if(a == b){
            result = 0;
        } else if(a > b){
            result = 1;
        } else {
            result = -1;
        }
        return result;
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
    public static void quicksortRec(List<Show> array, int esq, int dir, int k) {
        int i = esq, j = dir;
        Show pivo = array.get((dir+esq)/2);
    
        while (i <= j) {
            while (compareDateAddedAndTitle(array.get(i), pivo) < 0) {
                i++;
            }
            while (compareDateAddedAndTitle(array.get(j), pivo) > 0) {
                j--;
            }
    
            if (i <= j) {
                swap(array, i, j);
                i++;
                j--;
            }
        }
        if (esq < j) quicksortRec(array, esq, j, k);
        if (i < k && i < dir) quicksortRec(array, i, dir, k);
    }
    
    public static void quicksort(List<Show> array, int n) {
        quicksortRec(array, 0, n-1, 10);
    }
    public static int getMaior(List<Show> array, int tam){
        int maior = array.get(0).getRelease_year();
        for(int i = 1; i < tam; i++){
            if(array.get(i).getRelease_year() > maior){
                maior = array.get(i).getRelease_year();
            }
        }
        return maior;
    }
    
    public static int getMaxString(List<Show> array, int tam){
        int max = 0;
    
        for (int i = 0; i < tam; i++) {
            int len = array.get(i).getTitle().length();
            if (len > max) {
                max = len;
            }
        }
        return max;
    }
    public static void countingSort(List<Show> array){
        int tam = array.size();
        int maior = getMaior(array, tam);
        int x = 0, p = 0, ano;
        Show[] ordenado = new Show[tam];
        int[]  count = new int[maior+1];
        
        for(int i = 0; i < maior+1; i++){
            count[i] = 0;
        }
        for(int i = 0; i < tam; i++){
            count[array.get(i).getRelease_year()]++;
        }
        for(int i = 1; i < count.length; i++){
            count[i] += count[i-1];
        }
        for(int i = tam-1; i >= 0; i--){
            ordenado[count[array.get(i).getRelease_year()]-1] = array.get(i);
            count[array.get(i).getRelease_year()]--;
        }
        for(int i = 0; i < tam; i++){
            array.set(i, ordenado[i]);
        }
        while (x != tam) {
            ano = array.get(x).getRelease_year();
    
            while (x < tam && array.get(x).getRelease_year() == ano) {
                x++;
            }
    
            int listaTam = x - p;
            List<Show> lista = new ArrayList<>(Collections.nCopies(listaTam, (Show) null));
            for (int i = 0; i < listaTam; i++) {
                lista.set(i, array.get(p+i));
            }
    
            int max = getMaxString(lista, listaTam);
            for (int pos = max - 1; pos >= 0; pos--) {
                countingsortString(lista, listaTam, pos);
            }
    
            for (int i = 0; i < listaTam; i++) {
                array.set(p+i, lista.get(i));
            }
            p = x;
        }
    }
    
    public static void countingsortString(List<Show> array, int n, int esp){
        Show[] ordenado = new Show[n];
        int[]  count = new int[256];
        
        for (int i = 0; i < 256; i++) {
            count[i] = 0;
        }
        for(int i = 0; i < n; i++){
            int digit = (array.get(i).getTitle().length() > esp) ? Character.toLowerCase(array.get(i).getTitle().charAt(esp)) : 0;
            digit = (digit >= 0 && digit < 256) ? digit : 0;
            comp++;
            count[digit]++;
        }
        for(int i = 1; i < 256; i++){
            count[i] += count[i-1];
        }
        for(int i = n-1; i >= 0; i--){
            int digit = (array.get(i).getTitle().length() > esp) ? Character.toLowerCase(array.get(i).getTitle().charAt(esp)) : 0;
            digit = (digit >= 0 && digit < 256) ? digit : 0;
            comp++;
            ordenado[count[digit]-1] = array.get(i);
            count[digit]--;
            mov++;
        }
        for(int i = 0; i < n; i++){
            array.set(i, ordenado[i]);
            mov++;
        }
    }
    public static void main(String[] args) throws FileNotFoundException {
       startShows();
       Scanner sc = new Scanner(System.in);

       ArrayList<Show> list = new ArrayList<>();
       String line = sc.nextLine();

       while(!line.equals("FIM")) {
         Show show = searchById(line, shows);

           if(show != null) list.add(show);
           else System.out.println("x Show not found!");

           line = sc.nextLine();
       }

    //    line = sc.nextLine();
       
    //    while(!line.equals("FIM")){
    //     Show show = searchByTitle(line, list);
    //     if(show != null) System.out.println("SIM");
    //        else System.out.println("NAO");

    //        line = sc.nextLine();
    //    }

       sc.close();
       //verdeSort(list, "selecao", lista -> selectionSort(lista));
       //verdeSort(list, "heapsort", lista -> heapSort(lista));
    //    verdeSort(list, "selecaoparcial", lista -> {
    //     selectionSortPartial(list, 10);;
    //    }, lista -> {
    //     for(int i = 0; i<10; i++){
    //         lista.get(i).print();
    //     }
    //    });
    verdeSort(list, "quickparcial", lista -> {
        quicksort(list, list.size());
       }, lista -> {
        for(int i = 0; i<10; i++){
            lista.get(i).print();
        }
       });
    //    log.println("867936\t" + (fimTempo - inicio) + "\t" + comp); //sequencial
    //verdeSort(list, "countingsort", lista -> countingSort(lista));
    }

}