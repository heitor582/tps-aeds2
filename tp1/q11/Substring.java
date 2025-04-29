import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Substring {
    private static int longerSubstring(String x){
        if(x.length() < 2){
            return x.length();
        }

        Map<Character, Integer> map = new HashMap<Character, Integer>(); // can use contains on string but i prefer to change O(n) for O(1) with O(n) of space
        int j = 0;
        int i = 0;
        int result = 0;
        while(j<x.length()) {
            while(map.getOrDefault(x.charAt(j), 0) > 0){
                map.put(x.charAt(i), map.get(x.charAt(i))-1);
                i++;
            }
            map.put(x.charAt(j), map.getOrDefault(x.charAt(j), 0)+1);
            j++;
            if((j-i) > result){
                result = j-i;
            }
        }

        return result;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in, "ISO-8859-1");
        String text = sc.nextLine();
        while(!text.equals("FIM")) {
            System.out.println(longerSubstring(text));
            text = sc.nextLine();
        }
        sc.close();
    } 
}
