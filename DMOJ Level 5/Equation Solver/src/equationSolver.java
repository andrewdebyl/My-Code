import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Equation Solver      */
/*-------------------------------------*/

public class equationSolver {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		String sign = new String();
		int num = 0, total;
		
		total = sc.nextInt();
		
		while (!sign.equals("="))
		{
			sign = sc.next();
			if (sign.equals("="))
			{
				System.out.println(total);
				System.exit(0);
			}
			num = sc.nextInt();
			
			if (sign.equals("P"))
			{
				total = total + num;
			}
			else if (sign.equals("M"))
			{
				total = total - num;
			}
		}
	}

}
