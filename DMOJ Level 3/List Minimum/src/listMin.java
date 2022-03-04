import java.util.Scanner;
import java.util.*;

/*-------------------------------------*/
/* Andrew Debyl - Multiple Choice      */
/*-------------------------------------*/

public class listMin {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		List<Integer> list = new ArrayList<Integer>();
		
		int size = sc.nextInt();
		int temp = 1001, j = 0, store = 0;
		
		for (int i = 0; i < size; i++)
		{
			list.add(sc.nextInt());
		}
		
		int thing = list.size();
		
		for (int k = 0; k < thing-1; k++)
		{
			for (j = 0; j < list.size(); j++)
			{
				if (list.get(j) < temp)
				{
					temp = list.get(j);
					store = j;
				}
			}
			System.out.println(list.get(store));
			list.remove(store);
			
			store = 0;
			temp = 1001;
		}
		System.out.println(list.get(0));
	}
}
