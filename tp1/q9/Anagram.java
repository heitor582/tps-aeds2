import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
public class Anagram {
    private static boolean anagram(String x, String y) {
        if(x.length() != y.length()){
            return false;
        }
        Map<Character, Integer> map = new HashMap<Character, Integer>();

        for(int i = 0; i<x.length(); i++){ //O(x)
            char c = Character.toLowerCase(x.charAt(i));
            map.put(c, map.getOrDefault(c, 0)+1);
        }

        for(int i = 0; i<y.length(); i++){ //O(y)
            char c = Character.toLowerCase(y.charAt(i));
            map.put(c, map.getOrDefault(c, 0)-1);
        }

        for(Character key:map.keySet()){ //O(m)
            Integer value = map.get(key);
            if(value != 0){
                return false;
            }
        }

        return true;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in, "UTF-8");
        String text = sc.nextLine();
        while(!text.equals("FIM")) {
            int j = 0;
            for(int i = 0; i<text.length(); i++){
                if(text.charAt(i) == '-'){
                    j=i-1;
                    i = text.length();
                }
            }
            boolean is = anagram(text.substring(0, j), text.substring(j+3, text.length()));
            MyIO.println(is ? "SIM" : "NÃO");
            text=sc.nextLine();
        }
        sc.close();
    } 
}
