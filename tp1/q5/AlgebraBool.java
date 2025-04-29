import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

public class AlgebraBool {
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
	private static String parse(String cmd) {
		List<Integer> arguments = new ArrayList<>();
		int i = getVariables(cmd, arguments);
		Stack<String> p = new Stack<>();
		for(int j = i; i<cmd.length(); i++) {
			char c = cmd.charAt(i);
			if(c == '(') {
				p.push(cmd.substring(j, i));
				j = i+1;//skip the (
			} else if(c >= 'A' && c <= 'Z') {
				p.push(boolToString(valueOfArgument(arguments, c)));
				j = i+1;//skip the option
			} else if(c == ')') {
				List<String> listOfArgs = new ArrayList<>();
				while(p.peek().charAt(0) == '0' || p.peek().charAt(0) == '1') {
					listOfArgs.add(p.pop());//get all the arguments of the function from stack
				}

				String operation = p.pop();
				boolean res;
				switch (operation) {
				case "not":
					res= not(boolArg(listOfArgs.get(0)));
					break;
				case "and":
					res=and(listOfArgs);
					break;
				default:
					res=or(listOfArgs);
					break;
				};
				p.push(boolToString(res)); // add the result to stack for the next operation

				j = i+1;//skip the )
			}

			while(j < cmd.length() && (cmd.charAt(j) == ' ' || cmd.charAt(j) == ',')) {
				j++;
			}// for skip useless information
		}
		return p.pop();
	}
	public static void main(String[] args) {
		String text = MyIO.readLine();
		while(!text.equals("0")) {
			MyIO.println(parse(text));
			text=MyIO.readLine();
		}
	}
}
