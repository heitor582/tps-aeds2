import java.io.*;
import java.net.*;
import java.util.HashMap;

public class Html {
   private static String getHtml(String endereco){
        URL url;
        InputStream is = null;
        BufferedReader br;
        String resp = "", line;
        try {
            url = new URI(endereco).toURL();
            is = url.openStream();
            br = new BufferedReader(new InputStreamReader(is));

            while ((line = br.readLine()) != null) {
                resp += line + "\n";
            }
        } catch (MalformedURLException mue) {
            mue.printStackTrace();
        } catch (IOException ioe) {
            ioe.printStackTrace();
        } catch (URISyntaxException e) {
            e.printStackTrace();
        }finally{
        try {is.close();} catch (IOException ioe) {}
        }
        return resp;

   }
   
   private static Integer getIndex(char v){
        HashMap<Character, Integer> map = new HashMap<>();
        map.put('a', 0);
        map.put('e', 1);
        map.put('i',2);
        map.put('o', 3);
        map.put('u', 4);

        map.put('\u00E1', 5);//á
        map.put('\u00E9', 6);//é
        map.put('\u00ED', 7);//í
        map.put('\u00F3', 8);//ó
        map.put('\u00FA', 9);//ú

        map.put('\u00E0', 10);//à
        map.put('\u00E8', 11);//è
        map.put('\u00EC', 12);//ì
        map.put('\u00F2', 13);//ò
        map.put('\u00F9', 14);//ù

        map.put('\u00E2', 15);//â
        map.put('\u00EA', 16);//ê
        map.put('\u00EE', 17);//î
        map.put('\u00F4', 18);//ô
        map.put('\u00FB', 19);//û

        map.put('\u00E3', 20);//ã
        map.put('\u00F5', 21);//õ

        return map.get(v);
   }

  static boolean isVowel(char s){
   return (s == 'a' || s == 'A' || s == 'e' || s == 'E' || s == 'i' || s == 'I' || s == 'o' || s == 'O' || s == 'u' || s == 'U');
   }
   static boolean isConsonant(char s){
   return (!isVowel(s) && (s >= 'a' && s <= 'z' || s >= 'A' && s <= 'Z'));
   }
   static boolean isBr(String s){
      return s.equals("<br>");
   }
   static boolean isTable(String s){
      return s.equals("<table>");
   }
  static int[] contador(String s){
   int[] x = new int[26];
   String temp = "";
   for(int i = 0; i < s.length(); i++){
        char c = s.charAt(i);
        if(getIndex(c) != null){
            x[getIndex(c)]+=1;
        } else if(isConsonant(c)){
         x[22] +=1;
      }else if(c == '<'){
        temp = s.substring(i, i+4);
        if(isBr(temp)){
            x[23] +=1;
            temp = "";
            i+=3;
         } else {
            temp = s.substring(i, i+6);
            if(isTable(temp)){
                x[24] +=1;
                temp = "";
                i+=6;
             } 
         }
     }
   }
   return x;
  }

   public static void main(String[] args) {
      MyIO.setCharset("UTF-8");
      int[] x = new int[25];
      String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            String endereco = MyIO.readLine();
            String html = getHtml(endereco);
               x = contador(html);
              MyIO.print("a("+x[0]+") ");
              MyIO.print("e("+x[1]+") ");
              MyIO.print("i("+x[2]+") ");
              MyIO.print("o("+x[3]+") ");
              MyIO.print("u("+x[4]+") ");
              MyIO.print("\u00E1("+x[5]+") ");
              MyIO.print("\u00E9("+x[6]+") ");
              MyIO.print("\u00ED("+x[7]+") ");
              MyIO.print("\u00F3("+x[8]+") ");
              MyIO.print("\u00FA("+x[9]+") ");
              MyIO.print("\u00E0("+x[10]+") ");
              MyIO.print("\u00E8("+x[11]+") ");
              MyIO.print("\u00EC("+x[12]+") ");
              MyIO.print("\u00F2("+x[13]+") ");
              MyIO.print("\u00F9("+x[14]+") ");
              MyIO.print("\u00E3("+x[15]+") ");
              MyIO.print("\u00F5("+x[16]+") ");
              MyIO.print("\u00E2("+x[17]+") ");
              MyIO.print("\u00EA("+x[18]+") ");
              MyIO.print("\u00EE("+x[19]+") ");
              MyIO.print("\u00F4("+x[20]+") ");
              MyIO.print("\u00FB("+x[21]+") ");
              MyIO.print("consoante("+x[22]+") ");
              MyIO.print("<br>("+x[23]+") ");
              MyIO.print("<table>("+x[24]+") ");
              MyIO.println(text);
              text=MyIO.readLine();
        }
   }
}
