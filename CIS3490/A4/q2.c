/**********************
 * Name: Andrew Debyl
 * ID: 1096633
 * Assignment #: 4
 * *******************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>
#include <float.h>
#include <limits.h>

/*declare global arrays for c and r*/
int c[2045][2045];
int r[2045][2045];

/*node structre used for the tree*/
struct node
{
	int rootNum;
	int i;
	int j;
	double cost;
	char word[256];
	struct node* leftChild;
	struct node* rightChild;
}; typedef struct node Node;

/*define functions used*/
char* readFile (char* filename);
char** split (char* words, char* delim);
void bst (int p[], char** input, int n);
Node* newNode (double num, char* value);
Node* tree (int i, int j, char** words);
void searchWord (char* word, Node* node);

/*function to read in the file*/
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

	char* fileCont = calloc(filesize+5, sizeof(char));
	int i;

	for (i=0; i<filesize; i++)
	{
		fileCont[i] = fgetc(fp);
	}

	fclose(fp);

	return fileCont;
}

/*function to split up file into words*/
char** split (char* words, char* delim)
{
	int memSize=1;
	char** array = calloc(memSize, sizeof(char));
	char* token = strtok (words,delim);

	while(token!=NULL)
	{
		array[memSize-1] = calloc(strlen(token)+1, sizeof(char));

		strcpy(array[memSize-1], token);

		memSize++;

		array=realloc(array, memSize*sizeof(char*));

		token=strtok(NULL, delim);
	}
	array[memSize]=NULL;

	return array;
}

/*algorithum function for binary search trees*/
void bst (int p[], char** input, int n)
{
	int i,d,j,k,s, kmin = 0;

	double minval, sum=0;

	for (i = 1; i < n; i++)
	{
		c[i][i] = 0;
		c[i][i] = p[i];
		r[i][i] = i;
	}

	c[n+1][n] = 0;

	for (d = 1; d <= n; d++)
	{
		for (i = 1; i <= n - d; i++)
		{
			j = i + d;
			minval = INT_MAX;

			for (k = i; k <= j; k++)
			{
				if (c[i][k-1] + c[k+1][j] < minval)
				{
					minval = c[i][k-1] + c[k+1][j];
					kmin = k;
				}
			}

			r[i][j] = kmin;
			sum = p[i];

			for (s = i + 1; s <= j; s++)
			{
				sum += p[s];
			}

			c[i][j] = minval + sum;
		}
	}
}

/*function to initialzie a node*/
Node* newNode (double num, char* value)
{
	Node* node = calloc(1,sizeof(Node));

	strcpy(node->word,value);

	node->cost = num;

	node->leftChild=NULL;
	node->rightChild=NULL;

	return node;
}

/*function to create the tree*/
Node* tree (int i, int j, char** words)
{
	Node* node;

	if (i > j)
	{
		node = NULL;
	}
	else
	{
		node = newNode(c[i][j], words[r[i][j]]);
		node->leftChild = tree(i, r[i][j]-1, words);
		node->rightChild = tree(r[i][j]+1, j, words);
	}

	return node;
}

/*function to search  and print the word*/
void searchWord (char* word, Node* node)
{
	if (node==NULL)
	{
		printf("not found\n");
		return;
	}

	int num;

	num = strcmp(word, node->word);

	if (num == 0)
	{
		printf("Compared with %s (%.3f), found.\n", node->word, node->cost/2045);
		return;
	}
	
	else if (num < 0)
	{
		printf("Compared with %s (%.3f), go left subtree.\n", node->word, node->cost/2045);
		searchWord(word, node->leftChild);
	}
	else
	{
		printf("Compared with %s (%.3f), go right subtree.\n", node->word, node->cost/2045);
		searchWord(word, node->rightChild);
	}
}

int main (int argc, char* argv[])
{
	char* word = calloc(20, sizeof(char));
	char temp[50];
	int i,j,p=0, counter=0;
	int freq[600];

	char* words = readFile(argv[1]);

	char** numbers = split(words, "\n \t");
	
	/*sort words*/
	for (i=0; i<2045-1; i++)
	{
		for (j=i+1; j<2045; j++)
		{
			if (strcmp(numbers[i], numbers[j]) > 0)
			{
				strcpy(temp,numbers[j]);
				strcpy(numbers[j],numbers[i]);
				strcpy(numbers[i],temp);
			}
		}
	}

	/*Initialize freq array to 0*/
	for (i=0;i<600;i++)
	{
		freq[i]=1;
	}

	/*remove duplicates*/
	for (i=0; i<2045-1; i++)
	{		
		if (strcmp(numbers[i],numbers[i+1]) !=0)
		{
			strcpy(numbers[p], numbers[i]);
			p++;
			counter++;
		}
		else
		{
			freq[counter]++;
		}
	}
	strcpy(numbers[p++], numbers[2044]);

	bst(freq, numbers, 600);
	Node* root = tree(1,599, numbers);

	printf("Enter a key: ");
	fgets(word, 20, stdin);
	word[strlen(word)-1] = '\0';

	searchWord(word, root);

	return 0;
}