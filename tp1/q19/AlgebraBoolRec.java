import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Stack;

public class AlgebraBoolRec {
	private static boolean boolArg(String arg) {
		return arg.equals("1");
	}
	private static String boolToString(boolean arg) {
		return arg ? "1" : "0";
	}
	private static int charToInt(char c) {
		return c - '0';
	}
	private static boolean or(List<String> args) {
		boolean resp = false;
		for(String arg : args) {
			if(boolArg(arg)) {
				return true;
			}
			resp = resp || boolArg(arg);
		}
		return resp;
	}
	private static boolean and(List<String> args) {
		boolean resp = true;
		for(String arg : args) {
			if(!boolArg(arg)) {
				return false;
			}
			resp = resp && boolArg(arg);
		}
		return resp;
	}
	private static boolean not(boolean arg) {
		return !arg;
	}
	private static boolean valueOfArgument(List<Integer> arguments, char letter) {
		return arguments.get(Character.toLowerCase(letter) - 'a') == 1; // get the argument position by the letter
	}
	private static int getClosedIndex(String cmd, int i) {
		int open = 0;
		for(; i<cmd.length(); i++) {
			char c = cmd.charAt(i);
			if(c=='(') {
				open++;
			} else if(c == ')') {
				open--;
			}
			if(open == 0) {
				return i;
			}
		}

		return i;
	}
	private static int getVariables(String cmd, List<Integer> arguments) {
		int i = 0;
		int qtd = 0;
		for(i = 0; cmd.charAt(i) != ' '; i++) {
			qtd = (qtd * 10) + charToInt(cmd.charAt(i));
		}
		i++;//get out of the space index
		for(int j = 0; j<qtd; i+=2,j++) {
			arguments.add(charToInt(cmd.charAt(i)));
		}

		return i;
	}
	private static void doOperations(Stack<String> p) {
		List<String> listOfArgs = new ArrayList<>();
		while(p.peek().charAt(0) == '0' || p.peek().charAt(0) == '1') {
			listOfArgs.add(p.pop());//get all the arguments of the function from stack
		}


		String operation = p.pop();
		boolean res = switch (operation) {
		case "not" -> not(boolArg(listOfArgs.get(0)));
		case "and" -> and(listOfArgs);
			default-> or(listOfArgs);
		};
		p.push(boolToString(res));
	}
	private static String methods(String cmd) {
		if(cmd.equals("or")) {
			return "or";
		} else if(cmd.equals("nd")) {
			return "and";
		}
		return "not";
	}
	private static void parse(String cmd, List<Integer> arguments, Stack<String> p, int i) {
		if(i >= cmd.length()) {
			return;
		}

		char c = cmd.charAt(i);
		int icpy = i+1;
		if(c == '(') {
			int j = getClosedIndex(cmd, i);
			p.push(methods(cmd.substring(i-2, i)));
			parse(cmd.substring(i+1, j), arguments, p, 0);
			doOperations(p);
			icpy = j;
		} else if(c >= 'A' && c <= 'Z') {
			p.push(boolToString(valueOfArgument(arguments, c)));
		}

		parse(cmd, arguments, p, icpy);
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String text = sc.nextLine();
		while(!text.equals("0")) {
			Stack<String> p = new Stack<>();
			List<Integer> arguments = new ArrayList<>();
			int i = getVariables(text, arguments);
			parse(text, arguments, p, i);
			System.out.println(p.pop());
			text=sc.nextLine();
		}
		sc.close();
	}
}