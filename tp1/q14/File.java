import java.io.RandomAccessFile;

public class File {
    static void write(int n, String fileOut) throws Exception{
        RandomAccessFile file = new RandomAccessFile(fileOut, "rw");
        for(int i = 0; i < n; i++){
            file.writeDouble(MyIO.readDouble());
        }
        file.close();
       
    }
    static void read(int n, String fileOut) throws Exception{
        RandomAccessFile file = new RandomAccessFile(fileOut, "r");
        double value;
        for(int i = 8*(n-1); i >= 0; i-=8){
            file.seek(i);
            value = file.readDouble();
            MyIO.println(value == (int)value ? (int)value : value);
        }
        file.close();
    }
    public static void main(String[] args) {
        String fileOut = "saida.txt";
        int n = MyIO.readInt();
        try{
            write(n, fileOut);
            read(n, fileOut);
        }catch(Exception e){}
    }
}