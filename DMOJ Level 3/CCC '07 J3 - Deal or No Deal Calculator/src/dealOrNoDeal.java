import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Deal or No Deal      */
/*-------------------------------------*/

public class dealOrNoDeal {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int i = 0, offer, avg = 0;
		int[] numbers = new int[10];
		int[] values = {100,500,1000,5000,10000,25000,50000,100000,500000,1000000};
		
		int num = sc.nextInt();
		
		while (i < num)
		{
			numbers[i] = sc.nextInt();
			i++;
		}
		
		offer = sc.nextInt();
		
		//Assigning values of cases opened to 0
		for (int j = 0; j < i; j++)
		{
			int temp = numbers[j];
			values[temp-1] = 0;
		}
		
		// Finding the average of remaining cases
		for (int k = 0; k < 10; k++)
		{
			avg = avg + values[k];
		}
		avg = avg/(10-i);
		
		//Outputting deal or no deal
		if (offer > avg){
			System.out.println("deal");
		}
		else{
			System.out.println("no deal");
		}
	}

}
