import java.util.Scanner;
import java.util.*;

/*-------------------------------------*/
/* Andrew Debyl - Boolean              */
/*-------------------------------------*/

public class booleanProj {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		List<String> list = new ArrayList<String>();
		int i = -1;
		boolean temp = false;
		
		do
		{
			i++;
			list.add(sc.next());
		}while(!list.get(i).equals("True") && !list.get(i).equals("False"));

		int size = list.size();
		
		if (list.get(size-1).equals("True"))
		{
			temp = true;
		}
		else if (list.get(size-1).equals("False"))
		{
			temp = false;
		}
		
		for (int j = 0; j < size-1; j++)
		{
			if (temp == true)
			{
				temp = false;
			}
			else if (temp == false)
			{
				temp = true;
			}
		}
		
		if (temp == true)
		{
			System.out.println("True");
		}
		else if (temp == false)
		{
			System.out.println("False");
		}		
	}

}
