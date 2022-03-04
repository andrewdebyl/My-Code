import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Iron Scaling          */
/*-------------------------------------*/

public class ironScaling {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		System.out.print("Enter number to scale icon: ");
		int num = sc.nextInt();
		
		for (int j = 0; j < num; j++)
		{
			for (int i = 0; i < num; i++)
			{
				System.out.print("*");
			}
			for (int i = 0; i < num; i++)
			{
				System.out.print("x");
			}
			for (int i = 0; i < num; i++)
			{
				System.out.print("*");
			}
			System.out.println();
		}
		
		for (int j = 0; j < num; j++)
		{
			for (int i = 0; i < num; i++)
			{
				System.out.print(" ");
			}
			for (int i = 0; i < num*2; i++)
			{
				System.out.print("x");
			}
			System.out.println();
		}
		
		for (int j = 0; j < num; j++)
		{
			for (int i = 0; i < num; i++)
			{
				System.out.print("*");
			}
			for (int i = 0; i < num; i++)
			{
				System.out.print(" ");
			}
			for (int i = 0; i < num; i++)
			{
				System.out.print("*");
			}
			System.out.println();
		}
	}

}
