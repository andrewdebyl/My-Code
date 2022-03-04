import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Cell Phone           */
/*-------------------------------------*/

public class cellPhone {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		String []words = new String[100];
		String input;
		int i = -1, time = 0;
		char []second = {'b', 'e', 'h', 'k', 'n', 'q', 'u', 'x'};
		char []third = {'c', 'f', 'i', 'l', 'o', 'r', 'v', 'y'};
		
		do
		{
			i++;
			input = sc.next();
			words[i] = input;
		}while (!words[i].equals("halt"));
		
		for (int k = 0; k < i; k++)
		{
			for (int j = 0; j < words[k].length(); j++)
			{
				time = time + 1;
				
				if (j != words[k].length()-1)
				{
					if ((words[k].charAt(j) - words[k].charAt(j+1))<=0 && (words[k].charAt(j) - words[k].charAt(j+1))>=-2)
					{
						time = time + 2;
					}
				}
				
				for (int r = 0; r < second.length; r++)
				{
					if (words[k].charAt(j) == second[r])
					{
						time = time + 1;
					}
				}	
				
				for (int l = 0; l < third.length; l++)
				{
					if (words[k].charAt(j) == third[l])
					{
						time = time + 2;
					}
				}	
				
				if (words[k].charAt(j) == 's' || words[k].charAt(j) == 'z')
				{
					time = time + 3;
				}
				
			}
			System.out.println(time);
			time = 0;
		}
	}
}
