import java.util.Scanner;
public class Palindrome{
    private static boolean isPalindrome(String s){
        for(int i = 0; i<s.length()/2; i++){
            if(s.charAt(i) != s.charAt(s.length() - i - 1)) return false;
        }
        return true;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in, "UTF-8");
        String text = sc.nextLine();
        while(!text.equals("FIM")) {
            boolean isP = isPalindrome(text);
            if(isP) System.out.println("SIM");
            else System.out.println("NAO");
            text=sc.nextLine();
        }
        sc.close();
    }

}