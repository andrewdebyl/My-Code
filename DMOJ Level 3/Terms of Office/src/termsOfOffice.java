import java.util.Scanner;
import java.util.*;

/*-------------------------------------*/
/* Andrew Debyl - Terms of Office      */
/*-------------------------------------*/

public class termsOfOffice {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int year1 = sc.nextInt();
		int year2 = sc.nextInt();
		int counter = 0, i = 2;
		
		while (i > 1)
		{
			if (year1 + counter <= year2)
			{
				System.out.println("All positions change in year " + (year1 + counter));
				counter = counter + 60;
			}
			else
			{
				System.exit(0);
			}
		}
	}
}
