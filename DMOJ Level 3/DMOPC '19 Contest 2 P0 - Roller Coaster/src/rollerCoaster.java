import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Deal or No Deal      */
/*-------------------------------------*/

public class rollerCoaster {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int total = sc.nextInt();
		int min = sc.nextInt();
		int max = sc.nextInt();
		int i = -1, counter = 0;
		int[] kids = new int[total];
		
		do 
		{
			i++;
			kids[i] = sc.nextInt();
		}while (i < total-1);
		
		for (int j = 0; j < total; j++)
		{
			if (kids[j] <= max && kids[j] >= min)
			{
				counter++;
			}
		}
		System.out.println(counter);
	}

}
