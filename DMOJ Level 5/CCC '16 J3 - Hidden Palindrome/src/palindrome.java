import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Hidden Palindrome    */
/*-------------------------------------*/

public class palindrome {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		String word = sc.next();
		int length = word.length();
		int counter = 0, temp = 0;
		
		if (word.length() == 1)
		{
			System.out.println("1");
			System.exit(0);
		}
		
		for (int i = 0; i < length/2; i++)
		{
			if (word.charAt(i) == word.charAt(length-i-1))
			{
				counter++;
			}
		}
		
		if (counter==length/2)
		{
			System.out.println(length);
		}
		
		for (int k = 0; k < length; k++)
		{
			for (int j = 0; j < k; j++)
			{
				
			}
			if (counter > temp)
			{
				temp = counter;
			}
		}
		
	}
}
