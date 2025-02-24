import java.util.Scanner;

public class SumDigits {
    private static int sumDigits(int number) {
        if(number <= 9){
            return number;
        }
        int sum = number % 10 + sumDigits(number/10);
        
        return sum;
    }
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in, "UTF-8");
        String text = sc.nextLine();
        while(!text.equals("FIM")) {
            System.out.println(sumDigits(Integer.parseInt(text)));
            text=sc.nextLine();
        }
        sc.close();
    }
}
