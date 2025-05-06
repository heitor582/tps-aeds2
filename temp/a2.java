import java.util.*;
public class a2{
	public static void process(Queue<Integer> q) {
		int passadas = 0;
		int count = 0;
		while(q.size()!=0) {
			int cur = q.remove();
			if(cur - passadas == 0) count++;
			passadas+=30;
		}
		System.out.println(count);
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int horaAbertura = 7;
		while(sc.hasNext()) {
			int number = sc.nextInt();
			Queue<Integer> q = new LinkedList<>();
			for(int i = 0; i<number; i++) {
				int hora = sc.nextInt();
				int min = sc.nextInt();
				int tempo = sc.nextInt();

				q.add((hora - horaAbertura)*60 + min + tempo);
			}
			process(q);
		}
		sc.close();
	}
}