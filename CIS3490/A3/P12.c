/*********************
 * Name: Andrew Debyl
 * ID: 1096633
 * Assignment #: 3
 *********************/

#include <string.h>
#include <stdio.h>
#include <sys/timeb.h>
#include <stdlib.h>

/*function that sorts the strings from the lowest number to highest*/
char* sort (char* a, int size)
{
	int i,j;
	char temp;
	char* b=a;
	
	for (i=0; i<size-1; i++)
	{
		for (j=i+1; j<size; j++)
		{
			if (b[i] > b[j])
			{
				temp = b[i];
				b[i] = b[j];
				b[j] = temp;
			}
		}
	}
	
	return b;
}

/*function to read in a file*/
char* readFile (char* filename)
{
	FILE* fp = fopen(filename, "r");

	if (fp==NULL)
	{
		return NULL;
	}

	unsigned long fileSize = 0;

	rewind(fp);
	fseek(fp,0,SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);

	char* fileCont = calloc(fileSize+5, sizeof(char));
	int i;

	for (i=0; i<fileSize; i++)
	{
		fileCont[i] = fgetc(fp);
	}
	fclose(fp);

	return fileCont;
}

/*function to split up the strings*/
char** split (char* words, char* delim)
{
	int memsize=1;
	char** array = calloc(memsize, sizeof(char*));
	char* token = strtok(words, delim);

	while(token!=NULL)
	{
		array[memsize-1] = calloc(strlen(token)+1, sizeof(char));
		strcpy(array[memsize-1], token);
		memsize++;
		array = realloc(array, memsize*sizeof(char*));
		token = strtok(NULL,delim);
	}
	array[memsize]=NULL;

	return array;
}			

int main (int argc, char* argv[])
{		
	char* word = calloc(20,sizeof(char));
	int size, i, def=0, anaCount=0;
	char* temp = calloc(20,sizeof(char));
	char* thing = calloc(20,sizeof(char));
	char* thing2 = calloc(20,sizeof(char));

	char* words = readFile(argv[1]);

	printf("Enter a string: ");
	fgets(word, 20, stdin);
	
	word[strlen(word)-1] = '\0';
	size = strlen(word);
	
	strcpy(thing2,word);
	word = sort(word, size);

	char** numbers = split(words, "\n \t");

	struct timeb before, after;

	ftime(&before);

	for (i=0; numbers[i]!=NULL; i++)
	{
		if (size == strlen(numbers[i]))
		{	
			strcpy(thing, numbers[i]);
			temp = sort(numbers[i],size);

			if (strcmp(word,temp)==0)
			{
				def = 1;
			}
			if (strcmp(thing2,thing)==0)
			{
				def=0;
			}

			if (def == 1)
			{
				if (anaCount == 0)
				{
					printf("Anagrams:\n");
				}
				anaCount++;
				printf("%s\n",thing);
			}
			def=0;
		}
	}

	ftime(&after);
	float t = (after.time - before.time)*1000 + (after.millitm - before.millitm);

	printf("Counts = %d\n",anaCount);
	printf("Run time: %.2lf ms\n",t);

	free(word);
	free(temp);
	free(thing);
	free(thing2);
}
