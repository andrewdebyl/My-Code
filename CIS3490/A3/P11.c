/************************
 * Name: Andrew Debyl
 * ID: 1096633
 * Assignment #: 3
 * ********************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>


/*This function counts the frequency of each digit from 0-9 
 * and compares the two */
int anagram (char* a, char* b, int size)
{
	char* x =a;
	char* y =b;

	int i,j;
	int count1[10], count2[10];

	for (i=0;i<10;i++)
	{
		count1[i] = 0;
		count2[i]=0;
	}

	for (j=0; j < 10; j++)
	{
		for (i=0; i < size; i++)
		{
			if (x[i] == j+48)
			{
				count1[j]++;
			}
		}
	}

	for (j=0; j < 10; j++)
	{
		for (i=0; i < size; i++)
		{
			if (y[i] == j+48)
			{
				count2[j]++;
			}
		}
	}
	
	for (i=0; i<10; i++)
	{
		if (count1[i] != count2[i])
		{
			return 0;
		}
	}

	return 1;
}

/*function that reads in a file */
char* readFile (char* filename)
{
	FILE* fp = fopen(filename, "r");

	if (fp == NULL)
	{
		return NULL;
	}

	unsigned long filesize = 0;

	rewind(fp);
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	rewind(fp);

	char* fileCont = calloc(filesize+5, sizeof(char));
	int i;

	for (i=0; i<filesize; i++)
	{
		fileCont[i] = fgetc(fp);
	}
	
	fclose(fp);

	return fileCont;
}

/*function that splits up each string in the file*/
char** split (char* words, char* delim)
{
	int memSize=1;
	char** array = calloc(memSize,sizeof(char*));
	char* token = strtok(words, delim);

	while(token!=NULL)
	{
		array[memSize-1] = calloc(strlen(token)+1, sizeof(char));

		strcpy(array[memSize-1], token);
		
		memSize++;

		array = realloc(array, memSize*sizeof(char*));

		token = strtok(NULL,delim);
	}
	array[memSize] = NULL;

	return array;
}

int main (int argc, char* argv[])
{
	char* word = calloc(20,sizeof(char));
	int size, i, jj=0, num;

	char* words = readFile(argv[1]);
		
	printf("Enter a string: ");
	fgets(word, 20, stdin);	
	
	word[strlen(word)-1] = '\0';
	
	size = strlen(word);

	char** numbers = split(words, "\n \t");
	
	struct timeb before, after;

	ftime(&before);

	for (i = 0; numbers[i]!=NULL; i++)
	{
		if (strlen(numbers[i])==size)
		{
			num = anagram(numbers[i], word, size);

			if (num==1 && strcmp(word,numbers[i])!=0)
			{
				if (jj == 0)
				{
					printf("Anagrams:\n");
				}
				printf("%s\n",numbers[i]);
				jj++;
			}
		}
	}

	ftime(&after);
	float t = (after.time - before.time)*100 + (after.millitm - before.millitm);

	printf("Counts =  %d\n",jj);
	printf("Run time: %.2lf ms\n",t);

	free(word);
	free(words);
	free(numbers);
}
