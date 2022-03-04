import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Its Cold Here        */
/*-------------------------------------*/

public class coldHere {
	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int temp = 0, last = 0, max = 0;
		String city = new String();
		String coldest = new String();
		
		while (!city.equals("Waterloo"))
		{
			city = sc.next();
			temp = sc.nextInt();
			
			if (temp < max)
			{
				max = temp;
				coldest = city;
			}
		}
		
		System.out.println(coldest);
		
	}
}
