import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - Calorie Counting     */
/*-------------------------------------*/

public class calorieCounting {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		int op1 = sc.nextInt();
		int op2 = sc.nextInt();
		int op3 = sc.nextInt();
		int op4 = sc.nextInt();
		
		int burger[] = {461,431,420,0};
		int side[] = {100,57,70,0};
		int drink[] = {130,160,118,0};
		int dessert[] = {167,266,75,0}; 
		
		int total = burger[op1-1] + side[op2-1] + drink[op3-1] + dessert[op4-1];
		
		System.out.println("Your total Calorie count is " + total + ".");
		
	}

}
