/*********************
 * Name: Andrew Debyl
 * ID: 1096633
 * Assignment #: 3
 * *******************/

#include <string.h>
#include <stdio.h>
#include <limits.h> 
#include <stdlib.h>
#include <sys/timeb.h>

#define MAX 256 

/*function to read in file*/
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

/*function to initialize and find last character*/
void algorithm(int length, char *str, int temp[MAX]) 
{ 
    int i,j; 
  
  	/*initialize*/
    for (i = 0; i < MAX; i++) 
    {
         temp[i] = 0; 
    }
 
    for (j = 0; j < length; j++) 
    {
         temp[(unsigned char) str[j]] = j; 
    }
}

/*function to implement algorithm and to search*/
int search(char *words, char *input) 
{ 
    int x = strlen(words); 
    int y = strlen(input); 
  
    int temp[MAX]; 
  	int counter=0;
    
    algorithm(x, words, temp); 
  
    int z = 0, v;   
                
    while(z <= y - x) 
    { 
        v = x - 1; 
  
        while((v >= 0) && (words[v] == input[z + v])) 
        {
            v--; 
        }
        
        if (v < 0) 
        { 
            counter++; 
            
            if (z+x < y)
            {
            	z = z + x-temp[(unsigned char)input[z+x]];
            }
            else
            {
            	z = z + 1;
            }
        }
        else
        {
            if (1 > v - temp[(unsigned char)input[z+v]]) 
            {
            	z = z + 1;
            }
            else
            {
            	z = z + (v - temp[(unsigned char)input[z+v]]);
            }
        }
    } 

    return counter;
} 

int main (int argc, char* argv[])
{
	
	char* term = calloc(20,sizeof(char));
	char* words = readFile(argv[1]);

	printf("Enter a pattern: ");
	fgets(term,30,stdin);

	term[strlen(term)-1]='\0';

	char** allWords = split(words, "\n \t");
	
	int i, num=0,counter=0;

	struct timeb before, after;
	ftime(&before);

	for (i=0; allWords[i]!=NULL; i++)
	{
		num= search(term, allWords[i]);
		
		if (num==1)
		{
			counter++;
		}
	}

	ftime(&after);
	float t = (after.time - before.time)*1000 - (after.millitm - before.millitm);

	printf("Counts: %d\n",counter);
	printf("Run time: %.2lf ms\n", t);
}
