import java.util.*;

/*-------------------------------------*/
/* Andrew Debyl - Invitations          */
/*-------------------------------------*/

public class invitations {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int num = sc.nextInt();
		char[] letter = sc.next().toCharArray();
		char[] newletter = new char[num];
		List<String> name = new ArrayList<String>();
		int count = 0, l = 0;
		
		for (int i = 0; i < num; i++)
		{
			name.add(sc.next());
		}
		
		for (int k = 0; k < letter.length; k++)
		{
			if (letter[k] == 'X' )
			{
					count++;
					continue;
			}
			
			if (count > 0)
			{
				newletter[l - count] = letter[k];
				count = 0;
			}
			else
			{
				newletter[l++] = letter[k];
			}
		}
		
		for (int j = 0; j < num; j++)
		{
			if (newletter[j] == 'A')
			{
				System.out.println("Dear " + name.get(j) + ", beloved artist, I would love to have you at my party. Come to my crib on April 20th.");
			}
			else if (newletter[j] == 'O')
			{
				System.out.println("Dear " + name.get(j) + ", beloved occasion enthusiast, come to my crib to celebrate this very special day.");
			}
			else if (newletter[j] == 'R')
			{
				System.out.println("Dear " + name.get(j) + ", April 20th is happening again this year. Don't miss out.");
			}
		}
		
	}

}
