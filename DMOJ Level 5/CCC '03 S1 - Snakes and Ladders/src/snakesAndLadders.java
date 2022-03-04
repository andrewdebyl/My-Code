import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Snakes And Ladders   */
/*-------------------------------------*/

public class snakesAndLadders {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		int num = 1, input;
		
		do
		{
			input = sc.nextInt();
			
			if (input == 0)
			{
				System.out.println("You Quit!");
				System.exit(0);
			}
			
			if (num+input<=100)
			{
				num = num + input;
			}
			
			if (num == 100)
			{
				System.out.println("You are now on square " + num);
				System.out.println("You Win!");
				System.exit(0);
			}
			else if (num == 54)
			{
				num = 19;
			}
			else if (num == 90)
			{
				num = 48;
			}
			else if (num == 99)
			{
				num = 77;
			}
			else if (num == 9)
			{
				num = 34;
			}
			else if (num == 40)
			{
				num = 64;
			}
			else if (num == 67)
			{
				num = 86;
			}
			
			System.out.println("You are now on square " + num);
			
		}while(num!=1000);
	}

}
