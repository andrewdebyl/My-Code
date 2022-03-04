import java.util.*;
import java.io.*;

/*-------------------------------------*/
/* Andrew Debyl - Poetry	           */
/*-------------------------------------*/

public class poetry {

	public static String findType (String s)
	{
		char[] vowel = new char[]{'a', 'e', 'i', 'o', 'u'};
		String value = "";
		
		for (int i = s.length()-1; i >= 0; i--)
		{
			boolean isVow = false;
			for (int j = 0; j < vowel.length; j++)
			{
				if (vowel[j] == s.charAt(i))
				{
					isVow = true;
					break;
				}
			}
			value += s.charAt(i);
			
			if (isVow)
			{
				return new StringBuilder(value).reverse().toString();
			}
		}
		return new StringBuilder(value).reverse().toString();
	}
	
	public static void main(String[] args) throws Exception{
		BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
		
		int num = Integer.parseInt(r.readLine());
		
		for (int i = 0; i < num; i++)
		{
			String[] syl = new String[4];
			
			for (int j = 0; j < 4; j++)
			{
				String[] words = r.readLine().toLowerCase().split(" ");
				String syllable = findType(words[words.length-1]);
				syl[j] = syllable;
			}

			if (syl[0].equals(syl[1]) && syl[1].equals(syl[2]) && syl[2].equals(syl[3]))
			{
				System.out.println("perfect");
			}
			else if (syl[0].equals(syl[1]) && syl[2].equals(syl[3]))
			{
				System.out.println("even");
			}
			else if (syl[0].equals(syl[2]) && syl[1].equals(syl[3]))
			{
				System.out.println("cross");
			}
			else if (syl[0].equals(syl[3]) && syl[1].equals(syl[2]))
			{
				System.out.println("shell");
			}
			else
			{
				System.out.println("free");
			}
		}
	}
}
