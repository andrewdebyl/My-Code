import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Fraction Action      */
/*-------------------------------------*/

public class fractionAction {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		int[] num = new int[2];
		int front, top, bottom;
		
		System.out.println("Enter numerator and denominator: ");
		
		num[0] = sc.nextInt();
		num[1] = sc.nextInt();
		
		if (num[0] == 0)
		{
			System.out.println("0");
		}
		else if (num[0] % num[1] == 0)
		{
			System.out.println(num[0] / num[1]);
		}
		else
		{
			front = num[0] / num[1];
			top = num[0] % num[1];
			bottom = num[1];
		
			for (int j = 1; j<9; j++)
			{
				if ((top % j == 0) && (bottom % j==0))
				{
					top = top/j;
					bottom = bottom/j;
				}
			}
			
			if (front == 0)
			{
				System.out.println(top + "/" + bottom);
			}
			else
			{
				System.out.println(front + " " + top + "/" + bottom);
			}
		}
	}
}
