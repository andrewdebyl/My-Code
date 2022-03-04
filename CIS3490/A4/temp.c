/**********************
 * Name: Andrew Debyl
 * ID: 1096633
 * Assignment #: 4
 * *******************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <string.h>
#include <limits.h>

int c[2045][2045];
int r[2045][2045];

struct node
{
	int rootNum;
	int i;
	int j;
	char word[256];
	struct node* leftChild;
	struct node* rightChild;
}; typedef struct node Node;

struct stack
{
	Node** nodes;
	int length;
}; typedef struct stack Stack;

char* readFile (char* filename);
char** split (char* words, char* delim);
void bst (int p[], char** input, int n);
void push (Stack* stack, Node* node);
Node* pop (Stack* stack);
Node* newNode (char* value, int rNum, int i, int j);
Stack* newStack (int size);
Node* tree (int i, int j, char** keys);

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

void bst (int p[], char** input, int n)
{
	int i,d,j,k,s, kmin = 0, sum = 0;

	for (i = 0; i < n; i++)
	{
		c[i][i] = 0;
		r[i][i] = 0;
		c[i][i+1] = p[i];
		r[i][i+1] = i+1;
	}

	c[n][n] = 0;

	for (d = 2; d <= n; d++)
	{
		for (i = 0; i <= n - d; i++)
		{
			j = i + d;
			int minval = INT_MAX;

			for (k = i; k < j; k++)
			{
				if (c[i][k] + c[k+1][j] < minval)
				{
					minval = c[i][k] + c[k+1][j];
					kmin = k;
				}
			}

			r[i][j] = kmin+1;
			sum = p[i];

			for (s = i + 1; s < j; s++)
			{
				sum += p[s];
			}

			c[i][j] = minval + sum;
		}
	}
}

void push (Stack* stack, Node* node)
{
	stack->nodes[stack->length] = node;

	stack->length++;
}

Node* pop(Stack* stack)
{
	if (stack->length==0)
	{
		return NULL;
	} 
	else
	{
		stack->length--;
		return stack->nodes[stack->length];
	}
}

Stack* newStack(int size)
{
	Stack* stack = calloc(1,sizeof(Stack));
	stack->nodes = calloc(size,sizeof(Node*));

	stack->length=0;

	return stack;
}

Node* newNode (char* value, int rNum, int i, int j)
{
	Node* node = calloc(1,sizeof(Node));
	node->rootNum = rNum;

	strcpy(node->word,value);
	node->i=i;
	node->j=j;

	node->leftChild=NULL;
	node->rightChild=NULL;

	return node;
}

Node* tree (int i, int j, char** keys)
{/*
	int index = r[i][j] - 1;
	int rootNum = r[i][j];
	char* key = keys[index];

	Node* root = newNode(key, rootNum, i,j);
	Stack* stack = newStack(j);

	push(stack, root);

	while(stack->length > 0)
	{
		Node* u = pop(stack);

		int x = u->i;
		int y = u->j;

		if (x < u->rootNum-1)
		{
			rootNum = r[0][root->rootNum-1];
			index = rootNum-1;

			key = keys[index];

			Node* leftChild = newNode(key, rootNum, x, rootNum-1);
			root->leftChild = leftChild;
			
			push(stack, leftChild);
		}

		if (y > u->rootNum)
		{
			rootNum = r[root->rootNum][y];

			index = rootNum-1;
			key = keys[index];

			Node* rightChild = newNode(key, rootNum, root->rootNum, y);
			root->rightChild=rightChild;

			push(stack, rightChild);
		}
	}*/

	Node* node;

	if (i > j)
	{
		node = NULL;
	}
	else
	{
		node = newNode()
	}

	return root;
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
	for (i=0; i</*2045-1*/9-1; i++)
	{
		for (j=i+1; j</*2045*/9; j++)
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
	for (i=0;i</*600*/5;i++)
	{
		freq[i]=1;
	}

	/*remove duplicates*/
	for (i=0; i</*2045-1*/9-1; i++)
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
	strcpy(numbers[p++], numbers[/*2044*/8]);

	bst(freq, numbers, /*600*/5);

	printf("Enter a key: ");
	fgets(word, 20, stdin);

	word[strlen(word)-1] = '\0';

	//size = strlen(word);

	
	for (i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		{
			printf("%d ",r[i][j]);
		}
		printf("\n");
	}

	Node* root = tree(0,5, numbers);




	return 0;
}
