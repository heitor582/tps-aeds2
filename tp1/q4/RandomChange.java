import java.util.Random;

public class RandomChange{
    private static String randomChange(String s, char a, char b){
        String result = "";
        for(int i = 0; i < s.length(); i++){
            if(s.charAt(i) == a){
                result += b;
            } else {
                result += s.charAt(i);
            }
        }
        return result;
    }
    public static void main(String[] args){
        Random generator = new Random();
        generator.setSeed(4);

        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            char a = (char) ('a' + (Math.abs(generator.nextInt()) % 26)); // get the random char started on a
            char b = (char) ('a' + (Math.abs(generator.nextInt()) % 26)); // get the random char started on a
            MyIO.println(randomChange(text,a,b));
            text=MyIO.readLine();
        }
    }
}