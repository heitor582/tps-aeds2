import java.util.Scanner;

public class PasswordValidation {
    private static boolean validate(String x){
        if(x.length() < 8){
            return false;
        }

        boolean min = false;
        boolean mai = false;
        boolean special = false;
        boolean number = false;
        
        for(int i = 0; i< x.length(); i++){
            int asciiCode = (int)x.charAt(i);
            if(asciiCode > 96 && asciiCode <= 122 && !min){
                min = true;
            } else if(asciiCode > 64 && asciiCode <= 90 && !mai){
                mai = true;
            } else if(asciiCode > 47 && asciiCode <= 57 && !number){
                number = true;
            }else if(((asciiCode > 32 && asciiCode <= 47) 
            || (asciiCode > 57 && asciiCode <= 64)
            || (asciiCode > 90 && asciiCode <= 96)
            || (asciiCode > 122 && asciiCode <= 126)) && !special){
                special = true;
            }
        }

        return min && mai && special && number;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in, "UTF-8");
        String text = sc.nextLine();
        while(!text.equals("FIM")) {
            MyIO.println(validate(text) ? "SIM" : "NÃO");
            text=sc.nextLine();
        }
        sc.close();
    } 
}
