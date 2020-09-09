//Jesse McCarville-Schueths
//CS 4760
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
//#include <unistd.h>

int depthfirstapply(char *path, int pathfun(char *path1));

int sizepathfun(char *path);

int main(int argc, char **argv){
     while((options = getopt(argc, argv, “:haBMbmcdNHLs”)) != -1)  
    {  
        switch(options)  
        {  
            case ‘h’:  
                printf("Usage:\n
                    mydu [-a] [-B M | -b | -m] [-c] [-d N] [-H] [-L] [-s] <dir1> <dir2> ...\n
                    -a Write count for all files, not just directories.\n
                    -B M Scale sizes by M before printing; for example, -BM prints size in units of 1,048,576 bytes.\n
                    -b Print size in bytes.\n
                    -c Print a grand total.\n
                    -d N Print the total for a directory only if it is N or fewer levels below the command line argument.\n
                    -h Print a help message or usage, and exit\n
                    -H Human readable; print size in human readable format, for example, 1K, 234M, 2G\n
                    -L Dereference all symbolic links. By default, you will not dereference symbolic links.\n
                    -m Same as -B 1048576.\n
                    -s Display only a total for each argument\n");
                    break;
            case ‘a’:  
            case ‘r’:  
                printf(“option: %c\n”, opt);  
                break;  
            case ‘f’:  
                printf(“filename: %s\n”, optarg);  
                break;  
            case ‘:’:  
                printf(“option needs a value\n”);  
                break;  
            case ‘?’:  
                printf(“unknown option: %c\n”, optopt); 
                break;  
        }  
    }  
    
    depthfirstapply(char *path, int pathfun(char *path1));

    return(0);
}


int depthfirstapply(char *path, int pathfun(char *path1)){

    return (0);
}

int sizepathfun(char *path){
    return(0);
}