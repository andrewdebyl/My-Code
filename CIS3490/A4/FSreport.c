#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
int main(int argc, char** argv) {
    struct dirent *direntry;
    char path[200];
    char name[200];
    FILE *fp;
    DIR *dir = opendir("/proc/");
    while ((direntry = readdir(dir)) != NULL) {
        strcpy(path, "/proc/");
        strcat(path, direntry->d_name);
        strcat(path, "/comm");
        fp = fopen(path, "r");
        if (fp != NULL) {
            fscanf(fp, "%s", name);
            printf("%s-%s\n\r", direntry->d_name, name);
            fflush(NULL);
            fclose(fp);
        }
    }
    closedir(dir);
    return (EXIT_SUCCESS);
}