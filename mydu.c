//Jesse McCarville-Schueths
//CS 4760
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
//#include <unistd.h>


//======== PROTOTYPES =========
int depthfirstapply(char *path, int pathfun(char *path1));
int sizepathfun(char *path);

//=========== MAIN ============

int main(int argc, char **argv){
	int options;
	while((options = getopt(argc, argv, "haB:bmcdNHLs")) != -1){
		switch(options){
			case 'h':  
				printf("Usage: mydu [-a] [-B M | -b | -m] [-c] [-d N] [-H] [-L] [-s] <dir1> <dir2> ...\n");
				printf("\t-a Write count for all files, not just directories.\n");
				printf("\t -B M Scale sizes by M before printing; for example, -BM prints size in units of 1,048,576 bytes.\n");
				printf("\t-b Print size in bytes.\n");
				printf("\t-c Print a grand total.\n");
				printf("\t-d N Print the total for a directory only if it is N or fewer levels below the command line argument.\n");
				printf("\t-h Print a help message or usage, and exit\n");
				printf("\t-H Human readable; print size in human readable format, for example, 1K, 234M, 2G\n");
				printf("\t-L Dereference all symbolic links. By default, you will not dereference symbolic links.\n");
				printf("\t-m Same as -B 1048576.\n");
				printf("\t-s Display only a total for each argument\n");
				return EXIT_SUCCESS;
			case 'a':
				break;
			case 'B':
				break;
			case 'b':
				break;
			case 'm':
				break;  
			case 'c':
				break;
			case 'd':
				break;
			case 'N':
				break;
			case 'H':
				break;
			case 'L':
				break;
			case 's':
				break;
        }  
    }  
    
int depthfirstapply(char *path, int pathfun(char *path1));

    return(0);
}


int depthfirstapply(char *path, int pathfun(char *path1)){

    return (0);
}

int sizepathfun(char *path){
    return(0);
}
