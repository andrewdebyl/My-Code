import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - ISBN			       */
/*-------------------------------------*/

public class isbn {

	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		int i = 0, isbnNum;
		int[] num = new int[13];
		
		System.out.println("Enter the 13 digits: ");
		
		do
		{
			num[i] = sc.nextInt();
			i++;
		}while(i<13);

		isbnNum = num[0] + (num[1] * 3) + num[2] + (num[3] * 3) + num[4] + (num[5] * 3) + num[6] + (num[7] * 3) + num[8] + (num[9] * 3) + num[10] + (num[11] * 3) + num[12];
		
		System.out.println("The 1-3 sum is " + isbnNum);
		
	}

}
