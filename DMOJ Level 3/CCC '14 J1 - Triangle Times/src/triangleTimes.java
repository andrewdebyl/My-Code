import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Triangle Times       */
/*-------------------------------------*/

public class triangleTimes {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int one = sc.nextInt();
		int two = sc.nextInt();
		int three = sc.nextInt();
		
		if (one + two + three == 180)
		{
			if (one == 60 && two == 60 && three == 60)
			{
				System.out.println("Equilateral");
			}
			else if (one != two && one != three && two != three)
			{
				System.out.println("Scalene");
			}
			else
			{
				System.out.println("Isosceles");
			}
		}
		else
		{
			System.out.println("Error");
		}
		
	}

}
