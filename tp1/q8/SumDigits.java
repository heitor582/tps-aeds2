public class SumDigits {
    private static int sumDigits(int number) {
        if(number <= 9){
            return number;
        }
        int sum = number % 10 + sumDigits(number/10);
        
        return sum;
    }
    public static void main(String[] args) {
        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            MyIO.println(sumDigits(Integer.parseInt(text)));
            text=MyIO.readLine();
        }
    }    
}
