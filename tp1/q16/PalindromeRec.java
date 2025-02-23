import java.util.Scanner;
public class PalindromeRec{
    private static boolean isPalindrome(String s, int i, int j){
        if(i >= j){
            return true;
        }
        if(s.charAt(i) != s.charAt(j)){
            return false;
        }

        return isPalindrome(s, i + 1, j-1);
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in, "UTF-8");
        String text = sc.nextLine();
        while(!text.equals("FIM")) {
            boolean isP = isPalindrome(text, 0, text.length() - 1);
            if(isP) System.out.println("SIM");
            else System.out.println("NAO");
            text=sc.nextLine();
        }
        sc.close();
    }

}