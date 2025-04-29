import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class SplitIntoWord {
    private static List<String> split(char splitChar, String s){
        if(s.length() < 1){
            return new ArrayList<>();
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
        Scanner sc = new Scanner(System.in, "UTF-8");
        String text = sc.nextLine();
        while(!text.equals("FIM")) {
            System.out.println(split(' ', text).size() + 1);
            text=sc.nextLine();
        }
        sc.close();
    }
}
