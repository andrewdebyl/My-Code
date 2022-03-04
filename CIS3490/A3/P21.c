/*********************
 * Name: Andrew Debyl
 * ID: 1096633
 * Assignment #: 3
 * ******************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/timeb.h>

/*function to read in a file*/
char* readFile (char* filename)
{
	FILE* fp = fopen(filename, "r");

	if (fp==NULL)
	{
		return NULL;
	}

	unsigned long filesize = 0;

	rewind(fp);
	fseek(fp,0,SEEK_END);
	filesize=ftell(fp);
	rewind(fp);

	char* filecont = calloc(filesize+5, sizeof(char));
	int i;

	for(i=0; i<filesize; i++)
	{
		filecont[i] = fgetc(fp);
	}

	fclose(fp);

	return filecont;
}

/*function to split up the strings*/
char** split (char* words, char* delim)
{
	int memsize=1;
	char** array = calloc(memsize,sizeof(char*));
	char* token = strtok(words,delim);

	while(token!=NULL)
	{
		array[memsize-1]=calloc(strlen(token)+1, sizeof(char));
		strcpy(array[memsize-1], token);
		memsize++;
		array=realloc(array, memsize*sizeof(char*));
		token=strtok(NULL,delim);
	}
	array[memsize]=NULL;

	return array;
}

/*brute force function to search for the inputted string*/
int bfSearch (char* input, char* word)
{
	int inputLength = strlen(input);
	int wordLength = strlen(word);
	int i, counter=0;

	for (i=0; i <= wordLength - inputLength; i++)
	{
		int j;
		
		for (j=0; j<inputLength; j++)
		{
			if (word[i+j] != input[j])
			{
				break;
			}
		}

		if (j == inputLength)
		{
			counter++;
		}
	}
	
	return counter;
}

int main (int argc, char* argv[])
{
	int i;
	char* term = calloc(20,sizeof(char));

	char* words = readFile(argv[1]);

	printf("Enter a pattern: ");
	fgets(term, 20, stdin);
		
	term[strlen(term)-1]='\0';

	char** numbers = split(words, "\n \t");

	int num=0;

	struct timeb before, after;

	ftime(&before);

	for (i=0; numbers[i]!=NULL; i++)
	{
		num += bfSearch(term, numbers[i]);
	}

	ftime(&after);
	float t = (after.time - before.time)*1000 + (after.millitm - before.millitm);

	printf("Counts: %d\n",num);
	printf("Run time: %.2lf ms\n", t);

	free(term);
	free(words);
	free(numbers);
}
