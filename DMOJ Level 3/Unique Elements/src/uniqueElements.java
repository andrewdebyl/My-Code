import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Unique Elements      */
/*-------------------------------------*/

public class uniqueElements {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int num = sc.nextInt();
		int[] list = new int[num];
		int count = 0;
		
		for (int i = 0; i < num; i++)
		{
			list[i] = sc.nextInt();
		}
		
		for (int j=0; j < list.length; j++)
		{
			int k;
			
			for (k=0; k < j; k++)
			{
				if (list[j] == list[k])
				{
					break;
				}
			}
			
			if (j == k)
			{
				count++;
			}
		}

		System.out.println(count);
		
	}

}
