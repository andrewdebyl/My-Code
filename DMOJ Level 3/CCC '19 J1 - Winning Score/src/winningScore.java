import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Winning Score        */
/*-------------------------------------*/

public class winningScore {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int[] app = new int[3];
		int[] ban = new int[3];
		int aTot = 0, bTot = 0;
		
		for (int i = 0; i < 3; i++)
		{
			app[i] = sc.nextInt();
		}
		
		for (int j = 0; j < 3; j++)
		{
			ban[j] = sc.nextInt();
		}

		aTot = (app[0]*3) + (app[1]*2) + (app[2]);
		bTot = (ban[0]*3) + (ban[1]*2) + (ban[2]);
		
		if (aTot > bTot)
		{
			System.out.println("A");
		}
		else if (aTot < bTot)
		{
			System.out.println("B");
		}
		else
		{
			System.out.println("T");
		}
		
	}

}
