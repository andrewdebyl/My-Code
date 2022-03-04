import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Tournament Selection */
/*-------------------------------------*/

public class tournament {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		String games[] = new String[6];
		int count=0;
		
		for (int i = 0; i < 6; i++)
		{
			games[i] = sc.next();
			
			if (games[i].equals("W"))
			{
				count++;
			}
		}
		
		if (count == 1 || count == 2)
		{
			System.out.println("3");
		}
		else if (count == 3 || count == 4)
		{
			System.out.println("2");
		}
		else if (count == 5 || count == 6)
		{
			System.out.println("1");
		}
		else
		{
			System.out.println("-1");
		}
	}

}
