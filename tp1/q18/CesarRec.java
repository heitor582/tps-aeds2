public class CesarRec{
    private static String cipher(String s, int at){
        if(at == s.length()) return "";
        String result = "";
        result += (char)(s.charAt(at)+3);
        return result + cipher(s, at+1);
    }
    public static void main(String[] args){
        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            MyIO.println(cipher(text, 0));
            text=MyIO.readLine();
        }
    }
}