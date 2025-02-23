import java.util.HashMap;
import java.util.Map;
public class Anagram {
    private static boolean anagram(String x, String y) {
        if(x.length() != y.length()){
            return false;
        }
        Map<Character, Integer> map = new HashMap<Character, Integer>();

        for(int i = 0; i<x.length(); i++){ //O(x)
            map.put(x.charAt(i), map.get(x.charAt(i))+1);
        }

        for(int i = 0; i<y.length(); i++){ //O(y)
            map.put(y.charAt(i), map.get(y.charAt(i))-1);
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
        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            MyIO.println(anagram(text, text));
            text=MyIO.readLine();
        }
    } 
}
