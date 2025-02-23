public class Is {
    private static String isOnlyConsonant(String s) {
        for (int i = 0; i < s.length(); i++) {
            char c = Character.toLowerCase(s.charAt(i));  
            if ((c < 'a' || c > 'z') || (c != 'a' || c != 'e' || c != 'i' || c != 'o' || c != 'u')) {
                return "NAO";
            }
        }
    
        return "SIM";
    }
    private static String isOnlyVowels(String s) {
        for (int i = 0; i < s.length(); i++) {
            char c = Character.toLowerCase(s.charAt(i));
            if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
                return "NAO";
            }
        }
        return "SIM";
    }
    private static String isIntegerNumber(String s) {
        for (int i = 0; i < s.length(); i++) {
            char c = Character.toLowerCase(s.charAt(i));
            if (c < '0' || c > '9') {
                return "NAO";
            }
        }
        return "SIM";
    }
    private static String isDoubleNumber(String s) {
        boolean hasSeparator = false;
        for (int i = 0; i < s.length(); i++) {
            char c = Character.toLowerCase(s.charAt(i));
            boolean isSeparator = (c == '.' || c == ',');
            if ((c < '0' || c > '9') && !isSeparator) {
                return "NAO";
            }
            if(isSeparator){
                if(hasSeparator){
                    return "NAO";
                } else {
                    hasSeparator = true;
                }
            }
        }
        return hasSeparator ? "SIM" : "NAO";
    }
    public static void main(String[] args) {
        String text = MyIO.readLine();
        while(!text.equals("FIM")) {
            MyIO.println(isOnlyVowels(text) + " " + isOnlyConsonant(text) + " " + isIntegerNumber(text) + " " + isDoubleNumber(text));
            text=MyIO.readLine();
        }
    } 
}
