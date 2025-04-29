import java.util.Scanner;
public class InvertString{
    private static String invert(String s){
        String result = "";
        for(int i = s.length()-1; i >=0; i--){
            result += s.charAt(i);
        }
        return result;
    }
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in, "UTF-8");
        String text = sc.nextLine();
        while(!text.equals("FIM")) {
            System.out.println(invert(text));
            text=sc.nextLine();
        }
        sc.close();
    }
}