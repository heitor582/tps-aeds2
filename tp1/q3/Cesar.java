public class Cesar{
    private static String cipher(String s){
        String result = "";
        for(int i = 0; i < s.length(); i++){
            result += (char)(s.charAt(i)+3);
        }
        return result;
    }
    public static void main(String[] args){
        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            MyIO.println(cipher(text));
            text=MyIO.readLine();
        }
    }
}