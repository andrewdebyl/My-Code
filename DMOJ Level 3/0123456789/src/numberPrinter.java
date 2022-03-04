import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - 0123456789           */
/*-------------------------------------*/

public class numberPrinter {

	//The four horizontal sections that create every number
	public static void section1 ()
	{
		System.out.println(" * * *");
	}
	
	public static void section2 ()
	{
		System.out.println("*\n*\n*");
	}
	
	public static void section3 ()
	{
		for (int i = 0; i < 3; i++)
		{
			System.out.println("*     *");
		}
	}
	
	public static void section4 ()
	{
		for (int i = 0; i < 3; i++)
		{
			System.out.println("      *");
		}
	}
	
	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		//Getting number from user
		System.out.print("Enter number you would like displayed: ");
		int number = sc.nextInt();
		
		if (number != 1 && number != 4)
		{
			section1();
		}
		if (number == 0 || number == 4 || number == 8 || number == 9)
		{
			section3();
		}
		if (number == 1 || number == 2 || number == 3 || number == 7)
		{
			section4();
		}
		if (number == 5 || number == 6)
		{
			section2();
		}
		if (number != 0 && number != 1 && number != 7)
		{
			section1();
		}
		if (number == 0 || number == 6 || number == 8)
		{
			section3();
		}
		if (number == 1 || number == 3 || number == 4 || number == 5 || number == 7 || number == 9)
		{
			section4();
		}
		if (number == 2)
		{
			section2();
		}
		if (number != 1 && number != 4 && number != 7)
		{
			section1();
		}
		

	}

}
