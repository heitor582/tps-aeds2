import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
class Main{
    interface SortAlgorithm {
        void sort(int[] array);
    }
    private static long comp = 0;
    private static long mov = 0;
    private static void reset() {
        comp = 0;
        mov=0;
    }
    private static boolean isSmaller(int a, int b){
        comp += 1;
        return a < b;
    }
    private static void swap(int array[], int i, int j) {
        mov+=3;
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    private static int[] generateRandomArray(int n) {
        Random random = new Random();
        int[] array = new int[n];
        for (int i = 0; i < n; i++) {
            array[i] = random.nextInt(100);
        }
        return array;
    }
    private static void selectionSort(int array[]){
        for(int i = 0; i<array.length-1; i++){
            int min = i;
            for(int j = i+1; j<array.length; j++){
                if(isSmaller(array[j], array[min])){
                    min = j;
                }
            }
            swap(array, min, i);
        }
    }
    private static void bubbleSort(int array[]){
        boolean swaped = true;
        for(int i = 0; i<array.length-1 && swaped; i++){
            swaped = false;
            for(int j = 0; j<array.length-1-i; j++){
                if(isSmaller(array[j+1], array[j])){
                    swap(array, j, j+1);
                    swaped=true;
                }
            }
        }
    }
    private static void insertionSort(int array[]){
        for (int i = 1; i < array.length; i++) {
            int key = array[i];
            mov++;
            int j = i - 1;
            while (j >= 0 && isSmaller(key, array[j])) {
                array[j + 1] = array[j];
                mov++;
                j--;
            }
            array[j + 1] = key;
            mov++;
        }
    }
    private static void quickSort(int array[], int left, int right){
        int middle = left+(right-left)/2;
        int i = left, j = right;
        while(i <= j){
            while (isSmaller(array[i], array[middle]))  i++;
            while (isSmaller(array[middle], array[j])) j--;
            if(i <= j){
                swap(array, i, j);
                i++;j--;
            }
        }
        if(left < j) quickSort(array, left, j);
        if(i < right) quickSort(array, i, right);
    }
    private static void quickSort(int array[]){
        quickSort(array, 0, array.length-1);
    }

    public static void main(String[] args) {
        int[] sizes = {100, 1_000, 10_000, 100_000};

        SortAlgorithm[] sorts = {Main::selectionSort, Main::insertionSort, Main::bubbleSort, Main::quickSort};
        String[] names = {
            "SelectionSort",
            "InsertionSort",
            "BubbleSort",
            "QuickSort"
        };

        int runs = 30;

        int totalSize = sizes.length * runs * sorts.length;
        long[] compMem = new long[totalSize];
        long[] movMem = new long[totalSize];
        long[] timeMem = new long[totalSize];

        StringBuilder results = new StringBuilder();
        results.append("Algoritmo(Tamanho(Run));Mov;Comp;Tempo(ms)\n");     
        int index = 0;
        for (int i = 0; i<sizes.length; i++) {
            int[] original = generateRandomArray(sizes[i]);
            for (int s = 0; s < sorts.length; s++) {
                for (int j = 0; j < runs; j++) {
                    int[] array = original.clone();
                    reset();
                    long init = System.nanoTime();
                    sorts[s].sort(array);
                    long end = System.nanoTime();
                    compMem[index] = comp;
                    movMem[index] = mov; 
                    timeMem[index] = (end-init) / 1_000_000; 

                    results.append(String.format("%s(%d)(%d);%d;%d;%d\n",
                            names[s], sizes[i], j + 1, mov, comp, timeMem[index]));
                    index++;
                }
            }
        }

        results.append("Algoritmo;Tamanho;Comparações Média;Movimentações Média;Tempo Médio(ms)\n");  
        System.out.println("Algoritmo\t\tTamanho\t\tExecuções\t\tComp Média\t\tMov Média\t\tTempo Médio (ms)");
        System.out.println("---------------------------------------------------------------------------------------------------");

        index = 0;
        for (int i = 0; i<sizes.length; i++) {
            for (int s = 0; s < sorts.length; s++) {
                long totalComp = 0, totalMov = 0, totalTime = 0;
                for (int j = 0; j < runs; j++) {
                    totalComp += compMem[index];
                    totalMov += movMem[index];
                    totalTime += timeMem[index];

                    index++;
                }
                results.append(String.format("%s;%d;%d;%d;%d\n", names[s], sizes[i], totalComp / runs, totalMov / runs, totalTime / runs));
                System.out.printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d ms\n",
                        names[s], sizes[i], runs, totalComp / runs, totalMov / runs, totalTime / runs);
            }
        }

        try (FileWriter writer = new FileWriter("sort_results.csv")) {
            writer.write(results.toString());
            System.out.println("Resultados gravados no arquivo 'sort_results.csv'");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}