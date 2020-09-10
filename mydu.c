//AUTHOR: Jesse McCarville-Schueths
//COURSE: CS 4760
//DATE: SEPT 7 2020
//FILENAME: mydu.c
//
//DESCRIPTION:
//
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>


#define MAX_ARGS 10


//======== PROTOTYPES =========
int depthfirstapply(char *path, int pathfun(char *path),char *opts);
int sizepathfun(char *path);
char *get_dir(char *dir);

//=========== MAIN ============

int main(int argc, char **argv){
	int options;
	char selected_directory[4096];
	char selected_options[MAX_ARGS];
	while((options = getopt(argc, argv, "haB:bmcd:HLs")) != -1){
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
				strcat(selected_options, "a");
				break;
			case 'B':
				strcat(selected_options, "B");
				break;
			case 'b':
				strcat(selected_options, "b");
				break;
			case 'm':
				strcat(selected_options, "m");
				break;
			case 'c':
				strcat(selected_options, "c");
				break;
			case 'd':
				strcat(selected_options, "d");
				break;
			case 'N':
				strcat(selected_options, "N");	
				break;
			case 'H':
				strcat(selected_options, "H");
				break;
			case 'L':
				strcat(selected_options, "L");
				break;
			case 's':
				strcat(selected_options, "s");
				break;
		}
	}
	selected_directory = get_dir(argv[optind]);
	printf("Options selected: %s \n",selected_options);
	printf("Directory to be scanned: %s \n", selected_directory);

	//int total = depthfirstapply(char *path, int pathfun(char *path), char *opts);

	return(0);
}

int depthfirstapply(char* path, int pathfun(char *path), char *opts){
	DIR *directory;
	return 0;	
}

int sizepathfun(char *path){
	return(0);
}

//returns a starting directory is given, if not given, current dir will be default
char *get_dir(char * dir){
	char cur_directory[2] = ".";
	if(dir == NULL){
		return cur_directory;
	}
	else {
		return dir;
	}
}
