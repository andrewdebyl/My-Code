import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Mjehuric             */
/*-------------------------------------*/

public class mjehuric {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);

		int [] num = new int[5];
		int temp = 0;
		
		for (int i = 0; i < 5; i++)
		{
			num[i] = sc.nextInt();
		}
		
		for (int l = 0; l < 4; l++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (num[j] > num[j+1])
				{
					temp = num[j];
					num[j] = num[j+1];
					num[j+1] = temp;
					
					for (int k = 0; k < 5; k++)
					{
						System.out.print(num[k] +" ");
					}
					System.out.println();
				}
			}
		}
		
	}

}
