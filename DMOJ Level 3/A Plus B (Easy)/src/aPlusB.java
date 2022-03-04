import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Snakes And Ladders   */
/*-------------------------------------*/

public class aPlusB {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		int times = sc.nextInt();
		
		for (int i = 0; i < times; i++)
		{
			int a = sc.nextInt();
			int b = sc.nextInt();
			System.out.println(a+b);
		}
		
	}
}