import java.util.Scanner;
import java.lang.Math;

/*-------------------------------------*/
/* Andrew Debyl - Shifty Sum           */
/*-------------------------------------*/

public class shiftySum {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int num = sc.nextInt();
		int times = sc.nextInt();
		
		double total = 0;
		
		for (int i = 0; i < times + 1; i++)
		{
			total = (num*(Math.pow(10,i))) + total;
		}
		
		System.out.println((int)total);
	}
}
