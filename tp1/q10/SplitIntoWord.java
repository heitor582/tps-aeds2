package resp.q10;

import java.util.ArrayList;
import java.util.List;

public class SplitIntoWord {
    private static List<String> split(char splitChar, String s){
        if(s.length() < 1){
            return List.of();
        }

        List<String> resultList = new ArrayList<>();
        String word = "";
        for(int i = 0; i<s.length(); i++){
            if(s.charAt(i) != splitChar){
                word+=s.charAt(i);
            } else if(word.length() > 0) {
                resultList.add(word.toString());
                word = "";
            }
        }

        return resultList;
    }
    public static void main(String[] args){
        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            MyIO.println(split(' ', text));
            text=MyIO.readLine();
        }
    }
}
