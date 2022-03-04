import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Cell Phone           */
/*-------------------------------------*/

public class magicSquares {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int num [][] = new int [4][4];
		int total = 0, temp = 0, temp1 = 0;
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				num[i][j] = sc.nextInt();
			}
		}

		for (int k =0; k<4; k++)
		{
			total = total + num[0][k];
		}
		
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				temp = temp + num[i][j];
				temp1 = temp1 + num[j][i];
			}
			
			if (total != temp || total != temp1)
			{
				System.out.println("not magic");
				System.exit(0);
			}
			temp = 0;
			temp1 = 0;
		}
		
		System.out.println("magic");
		
	}

}
