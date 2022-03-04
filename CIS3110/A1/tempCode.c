#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

char **cutInput(char *input);
char *parse(void);
int exitProg(char **args);
int andCheck(char** argv);
void freeArgs (char **one, char* two);

char *parse(void)
{
    //variables
    int counter = 0, character;
    char *word = malloc(4096);

    /*parsing input from user */
    for (;;)
    {
        character = getchar();

        if (character == EOF)
        {
            exit(0);
        }
        else if (character == '\n')
        {
            word[counter] = '\0';
            return word;
        }
        else
        {
            word[counter] = character;
        }
        counter = counter + 1;
    }
}

char **cutInput(char *input)
{
    //variables
    int count = 0;
    char **newInput = malloc(512 * 8);
    char *temp = strtok(input, " \t\r\n\a");

    /* cutting the input into different parts */
    while (temp != NULL)
    {
        newInput[count] = temp;

        temp = strtok(NULL, " \t\r\n\a");

        count = count + 1;
    }

    newInput[count] = NULL;

    return newInput;
}

int exitProg(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    /* if the user types exit */
    if (strcmp(args[0], "exit") == 0 && args[1] == NULL)
    {
        return 0;
    }
    else
    {
    }

    /* the cd case */
    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            printf("Error\n");
        }
        else if (chdir(args[1]) != 0)
        {
            printf("Error\n");
        }
        
        return 1;
    }

    int status;

    pid_t fork = fork();

    /*running the child and parent case*/
    if (fork >= 0)
    {
        switch(fork)
        {
            case 0:
                if (execvp(args[0], args) == -1)
                {
                    printf("Error\n");
                }
                exit(1);

            default:
                waitpid(fork, &status, WUNTRACED);
        }
    }
    return 1;
}

int andCheck (char** argv)
{
    /*checking if there is an '&' symbol*/
    int i;

    for (i=0; argv[i]!=NULL ; i++)
    {
        if (strcmp(argv[i],"&")==0)
        {
            return 1;
        }
    }
    return 0;
}

void freeArgs (char **one, char* two)
{
    /*freeing*/ 
    free(one);
    free(two);
}

int main(int argc, char **argv)
{
    /*variables*/
    int num;
    char **output;
    char *buf;

    do
    {
        printf("> ");
        
        buf = parse();

        if (buf == NULL)
        {
            printf("Error, null\n");
            exit(0);
        }

        output = cutInput(buf);

        if (output == NULL)
        {
            printf("Error, null\n");
            exit(0);
        }

        num = exitProg(output);

        freeArgs(output,buf);
        
    } while (num != 0);

    return 0;
}