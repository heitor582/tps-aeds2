import java.util.HashMap;
import java.util.Map;

public class Substring {
    private static String longerSubstring(String x){
        if(x.length() < 2){
            return x;
        }

        String result = "";
        Map<Character, Integer> map = new HashMap<Character, Integer>(); // can use contains on string but i prefer to change O(n) for O(1) with O(n) of space
        int j = 0;
        int i = 0;
        String history = "";
        while(i<j) {
            while(map.get(x.charAt(i)) > 1){
                i++;
                map.put(x.charAt(i), map.get(x.charAt(i))-1);
                history = history.substring(i);  // create a new string from index i to string.length(), is better than use contains()
            }
            map.put(x.charAt(i), map.get(x.charAt(i))+1);
            if(j-i > result.length()){
                result = history; // or use history.substring(i,j);
            }
            j++;
            history += x.charAt(i);
        }

        return result;
    }

    public static void main(String[] args) {
        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            MyIO.println(longerSubstring(text));
            text=MyIO.readLine();
        }
    } 
}
