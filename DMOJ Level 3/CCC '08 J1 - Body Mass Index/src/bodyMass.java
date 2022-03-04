import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Multiple Choice      */
/*-------------------------------------*/

public class bodyMass {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int weight = sc.nextInt();
		double height = sc.nextDouble();
		
		double bmi = weight/(height*height);
		
		if (bmi > 25)
		{
			System.out.println("Overweight");
		}
		else if (bmi < 18.5)
		{
			System.out.println("Underweight");
		}
		else
		{
			System.out.println("Normal weight");
		}
	}

}
