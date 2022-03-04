import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Returning Home       */
/*-------------------------------------*/

public class returningHome 
{

	// Fuction to check if all the directions are the same
	public static boolean areSame(String words[], int num)
	{
		String first = words[0];
		for (int j = 1; j < words.length-num; j++)
		{
			if (!first.equals(words[j]))
			{
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		
		//Declaring variables
		String[] directions = new String[5];
		String[] directions2 = new String[5];
		String[] streets = new String[5];
		String temp;
		int i = -1, y = 0, last;
		
		System.out.println("Enter directions (min 2/max 5, all caps): ");
		
		//Getting input from user
		do 
		{
			i++;
			temp = sc.next();
			directions[i]=temp;
			temp = sc.next();
			streets[i] = temp;
		} while (!streets[i].equals("SCHOOL"));
		sc.close();
		
		i++;
		int num = i;

		if (!areSame(directions,5-i))
		{
			String[] newWords = new String[5];

			for (int r = 0; num > 0; r++)
			{
				num--;
				newWords[r] = directions[num];
			}
			
			for (int k = 0; k < i; k++)
			{
				if (newWords[k].equals("L"))
				{
					directions2[k] = "RIGHT";
				}
				else if (newWords[k].equals("R"))
				{
					directions2[k] = "LEFT";
				}
			}
		}
		else
		{
			for (int k = 0; k < i; k++)
			{
				if (directions[0].equals("L"))
				{
					directions2[k] = "RIGHT";
				}
				else if (directions[0].equals("R"))
				{
					directions2[k] = "LEFT";
				}
			}
		}

		i--;
		last = i;
		
		do 
		{
			i--;
			System.out.println("Turn " + directions2[y] + " onto " + streets[i] + " street.");
			y++;
		}while(i>0);
		
		System.out.println("Turn " + directions2[last] + " into your HOME.");
	}

}
