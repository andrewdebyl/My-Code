import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Speed Fines          */
/*-------------------------------------*/

public class speedFines {

	public static void main(String[] args) {
		Scanner sc  = new Scanner (System.in);
		
		int limit = sc.nextInt();
		int speed = sc.nextInt();
		int over = speed - limit;
		int fine = 0;
	
		if (over >= 1 && over <= 20)
		{
			fine = 100;
		}
		else if (over >= 21 && over <= 30)
		{
			fine = 270;
		}
		else if (over >=31)
		{
			fine = 500;
		}
		else
		{
			System.out.println("Congratulations, you are within the speed limit!");
			System.exit(0);
		}
		System.out.println("You are speeding and your fine is $" + fine +".");  
	}

}
