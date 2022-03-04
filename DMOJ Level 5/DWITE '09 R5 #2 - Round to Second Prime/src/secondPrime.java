import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Second Prime         */
/*-------------------------------------*/

public class secondPrime {

	public static int prime (int numb)
	{
		boolean flag = false;
		
		for (int i = 2; i <= numb/2; i++)
		{
			if (numb % i == 0)
			{
				flag = true;
				break;
			}
		}
		
		if (!flag)
		{
			return 1;
		}
		else 
		{
			return 0;
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);

		int[] num = new int [5];
		int count, k, j, i;
		
		for (i = 0; i < 5; i++)
		{
			num[i] = sc.nextInt();
		}
		
		for (i = 0; i < 5; i++)
		{
			j = num[i];
			k = num[i];
			
			count = 0;
			
			do
			{
				j--;
				
				if (prime(j) == 1)
				{
					count++;
				}
			}
			while (count != 2);
			
			count = 0;
			
			do
			{
				k++;
				
				if (prime(k) == 1)
				{
					count++;
				}
			} 
			while (count != 2);
			
            if ((k-num[i]) < (num[i]-j))
            {
            	System.out.println(k);
            }
            else if ((k-num[i]) > (num[i]-j))
            {
                System.out.println(j);
            }
            else
            {
                System.out.println(k);
            }
		
		}	
	}
}
