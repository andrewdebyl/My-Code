import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Note			       */
/*-------------------------------------*/

public class note {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int [] num = new int[8];
		int temp1 = 0, temp2=0;
		
		for (int i =0; i < 8; i++)
		{
			num[i] = sc.nextInt();
		}
		
		for (int j = 0; j < 7; j++)
		{
			if (num[j]<num[j+1])
			{
				temp1++;
			}
			else if (num[j]>num[j+1])
			{
				temp2++;
			}
		}
		
		if (temp1==7)
		{
			System.out.println("ascending");
		}
		else if (temp2==7)
		{
			System.out.println("descending");
		}
		else
		{
			System.out.println("mixed");
		}
	}

}
