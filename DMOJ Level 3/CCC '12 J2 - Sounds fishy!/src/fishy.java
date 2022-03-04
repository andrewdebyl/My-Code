import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Sounds Fishy         */
/*-------------------------------------*/

public class fishy {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
	
		int fish[] = new int [4];
		int temp = 0, temp1 = 0;
		
		for (int i = 0; i < 4; i++)
		{
			fish[i] = sc.nextInt();
		}
	
		if (fish[0] == fish[1] && fish[1] == fish[2] && fish[2] == fish[3])
		{
			System.out.println("Fish At Constant Depth");
			System.exit(0);
		}
		
		for (int j = 0; j < 3; j++)
		{
			if (fish[j] < fish[j+1])
			{
				temp++;
			}
			
			if (fish[j] > fish[j+1])
			{
				temp1++;
			}
		}
		
		if (temp == 3)
		{
			System.out.println("Fish Rising");
		}
		else if (temp1 == 3)
		{
			System.out.println("Fish Diving");
		}
		else 
		{
			System.out.println("No Fish");
		}
	
	}
}
