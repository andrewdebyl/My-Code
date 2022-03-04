import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - American to Canadian */
/*-------------------------------------*/

public class trident {

	//function that prints a number of spaces
	public static void spaces (int number)
	{
		for (int y = 0; y < number; y++)
		{
			System.out.print(" ");
		}
		System.out.print("*");
	}
	
	public static void main(String[] args) {
		Scanner sc=new Scanner(System.in);
		
		int height, space, handle;
		
		//Getting input from user
		System.out.print("Enter height of tines: ");
		height=sc.nextInt();
		
		System.out.print("Enter space between tines: ");
		space=sc.nextInt();
		
		System.out.print("Enter length of handle: ");
		handle=sc.nextInt();
		
		//Printing the three tines 
		for (int j = 0; j < height; j++)
		{
			System.out.print("*");
			for (int i = 0; i < 2; i++)
			{
				spaces(space);
			}
			System.out.println();
		}
		
		//Printing the line 
		for (int b = 0; b < space*2 + 3; b++)
		{
			System.out.print("*");
		}
		
		//Printing the handle 
		System.out.println();
		for (int c = 0; c < handle; c++)
		{
			spaces((space*2+3)/2);
			System.out.println();
		}	
	}
}
