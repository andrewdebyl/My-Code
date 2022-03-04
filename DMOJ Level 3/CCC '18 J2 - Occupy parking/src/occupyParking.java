import java.util.*;

/*-------------------------------------*/
/* Andrew Debyl - Occupy Parking       */
/*-------------------------------------*/

public class occupyParking {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int num = sc.nextInt();
		int count = 0;
		char[] first = sc.next().toCharArray();
		char[] second = sc.next().toCharArray();
		
		for (int i = 0; i < num; i++)
		{
			if (first[i] == 'C' && second[i] == 'C')
			{
				count++;
			}
		}
		
		System.out.println(count);
		
	}

}
