/*********************
 * Name: Andrew Debyl
 * ID: 1096633
 * Assignment #: 3
 * ******************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

/*function to read in a file*/
char* readFile (char* filename)
{
	FILE* fp = fopen(filename, "r");

	if(fp==NULL)
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

	return filecont;
}

/*function to split up strings in file*/
char** split (char* words, char* delim)
{
	int memsize=1;
	char** array=calloc(memsize, sizeof(char*));
	char* token=strtok(words,delim);

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

/*function to set up the shift table and implement the horspools algorithm*/
int algorithm (char word[], char w[])
{
	int x, y, z;
	int table[256];

	z = strlen(w);

	for (x = 0; x < 256 ; x++)
	{
		table[x] = z;
	}
	
	for (y = 0; y < z-1; y++)
	{
		table[(unsigned char)w[y]] = z - 1 - y;
	}

	int wordLength, wLength;

	wordLength = strlen(word);
	wLength = strlen(w);

	x = wLength - 1;

	while(x < wordLength)
	{
		y = 0;

		while((y < wLength) && (w[wLength - 1 - y] == word[x - y]))
		{
			y++;
		}

		if (y == wLength)
		{
			return (x - wLength + 1);
		}
		else
		{
			x += table[(unsigned char)word[x]];
		}
	}

	return -1;
}

int main (int argc, char* argv[])
{
	int i, counter=0;
	char term[30];
	char* words = readFile(argv[1]);

	printf("Enter a pattern: ");
	fgets(term,30,stdin);

	term[strlen(term)-1]='\0';

	char** allWords = split(words, "\n \t");

	struct timeb before, after;
	ftime(&before);

	for (i=0; allWords[i]!=NULL; i++)
	{	
		int set = algorithm(allWords[i], term);

		if (set >= 0)
		{
			counter++;
		}
	}

	ftime(&after);
	float t = (after.time - before.time)*1000 + (after.millitm - before.millitm);

	printf("Counts: %d\n", counter);
	printf("Run time: %.2lf ms\n", t);
}
