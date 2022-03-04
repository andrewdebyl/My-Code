import java.util.Scanner;

/*-------------------------------------*/
/* Andrew Debyl - American to Canadian */
/*-------------------------------------*/

public class americanToCanadian {
	
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		
		//declaring variables needed
		String[] words1 = new String[100];
		String input;
		int i = -1;
		
		System.out.println ("Enter words to translate: ");
		
		//Putting the words into an array
		do 
		{
			i++;
			input = sc.next();
			words1[i] = input;
		} while (!words1[i].equals("quit!"));
		sc.close();
		
		//Putting into new array now that I have the size
		String[] words2 = new String[i+1];
		
		for (int j = 0; j < i; j++)
		{
			words2[j] = words1[j];
		}
		
		System.out.println("\nCanadian words:");
		
		for (int k = 0; k < words2.length-1 ; k++)
		{
			int wordLength = words2[k].length();
			
			if (wordLength >= 4)
			{
				if (((words2[k].charAt(wordLength-2)) == 'o') && ((words2[k].charAt(wordLength-1)) == 'r') && (((words2[k].charAt(wordLength-3)) != 'a') && ((words2[k].charAt(wordLength-3)) != 'e') && ((words2[k].charAt(wordLength-3)) != 'i') && ((words2[k].charAt(wordLength-3)) != 'o') && ((words2[k].charAt(wordLength-3)) != 'u') && ((words2[k].charAt(wordLength-3)) != 'y') ))
				{
					//inserts the letter 'u' in between the 'o' and 'r' at the end of the word
					StringBuffer str = new StringBuffer(words2[k]);
					str.insert(wordLength - 1, 'u');
					
					//prints the new word
					System.out.println(str);
				}
				else
				{
					//prints if the suffix is a vowel
					System.out.println(words2[k]);
				}
			}
			else
			{
				//prints if the word is less than 4 letters
				System.out.println(words2[k]);
			}
		}
	}

}
