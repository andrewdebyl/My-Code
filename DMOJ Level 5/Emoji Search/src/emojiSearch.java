import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Emoji Search         */
/*-------------------------------------*/

public class emojiSearch {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		String[] words = new String[1000];
		int i = -1;
		
		while(sc.hasNextLine())
		{
			i++;
			words[i] = sc.nextLine();
		}
		
		System.out.println(words[0] + "" + words[1]);
		
	}

}
