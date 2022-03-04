import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Comparing Words      */
/*-------------------------------------*/

public class comparingWordsSatellies {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int num = sc.nextInt();
		String[] newWords = new String[num];
		
		for (int i = 0; i < num; i++)
		{
			String word1 = sc.next();
			String word2 = sc.next();
			String word3 = sc.next();
			
			if (word3.equals(word1))
			{
				newWords[i] = word3;
			}
			else if (word3.equals(word2))
			{
				newWords[i] = word3;
			}
			else if (word1.equals(word2))
			{
				newWords[i] = word1;
			}
			else if (word3.equals(word2) && (word3.equals(word1)))
			{
				newWords[i] = word3;
			}
			else
			{
				newWords[i] = "???";
			}
		}
		
		for (int i = 0; i < num; i++)
		{
			System.out.println(newWords[i]);
		}
		
	}

}
