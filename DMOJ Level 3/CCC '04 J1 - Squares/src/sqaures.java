import java.util.Scanner;
import java.lang.Math; 

/*-------------------------------------*/
/* Andrew Debyl - Squares              */
/*-------------------------------------*/

public class sqaures {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int length = 0;
		int num = sc.nextInt();

		length = (int)Math.sqrt(num);
		
		System.out.println("The largest square has side length " + length + ".");
	}

}
