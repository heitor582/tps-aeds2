public class InvertString{
    private static String invert(String s){
        String result = "";
        for(int i = s.length()-1; i >=0; i--){
            result += s.charAt(i);
        }
        return result;
    }
    public static void main(String[] args){
        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            MyIO.println(invert(text));
            text=MyIO.readLine();
        }
    }
}