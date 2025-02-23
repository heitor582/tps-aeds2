public class IsRec {
    private static boolean isOnlyConsonant(String s, int i) {
        if (i == s.length()) {
            return true;
        }
        char c = Character.toLowerCase(s.charAt(i));
        if (c < 'a' || c > 'z' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            return false;
        }
        return isOnlyConsonant(s, i + 1);
    }

    private static boolean isOnlyVowels(String s, int i) {
        if (i == s.length()) {
            return true;
        }
        char c = Character.toLowerCase(s.charAt(i));
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
            return false;
        }
        return isOnlyVowels(s, i + 1);
    }

    private static boolean isIntegerNumber(String s, int i) {
        if (i == s.length()) {
            return true;
        }
        char c = s.charAt(i);
        if (c < '0' || c > '9') {
            return false;
        }
        return isIntegerNumber(s, i + 1);
    }

    private static boolean isDoubleNumber(String s, int i, boolean hasSeparator) {
        if (i == s.length()) {
            return hasSeparator;
        }
        char c = s.charAt(i);
        boolean isSeparator = (c == '.' || c == ',');
        if ((c < '0' || c > '9') && !isSeparator) {
            return false;
        }
        if (isSeparator) {
            if (hasSeparator) {
                return false;
            } else {
                hasSeparator = true;
            }
        }
        return isDoubleNumber(s, i + 1, hasSeparator);
    }

    private static void printOut(boolean result) {
        MyIO.print(result ? "SIM" : "NAO");
    }

    public static void main(String[] args) {
        String text = MyIO.readLine();
        while (!text.equals("FIM")) {
            printOut(isOnlyVowels(text, 0));
            MyIO.print(" ");
            printOut(isOnlyConsonant(text, 0));
            MyIO.print(" ");
            printOut(isIntegerNumber(text, 0));
            MyIO.print(" ");
            printOut(isDoubleNumber(text, 0, false));
            MyIO.println("");
            text = MyIO.readLine();
        }
    }
}
