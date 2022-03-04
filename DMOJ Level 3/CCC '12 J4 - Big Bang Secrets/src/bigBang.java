import java.util.Scanner;

public class bigBang {

	public static void main(String[] args) {
		Scanner sc = new Scanner (System.in);
		
		int num = sc.nextInt();
		char[] word = sc.next().toCharArray();
		char[] newWord =  new char[word.length];
		int value = 0, shift = 0;
		
		for (int i = 0; i < word.length ; i++)
		{
			shift = ((i+1)*3) + num;
			value = (int)word[i] - shift;
			
			if (value < 65)
			{
				value = value + 26;
			}
			
			newWord[i] = (char)value;
			shift = 0;
			value = 0;	
			System.out.print(newWord[i]);
		}

	}

}
