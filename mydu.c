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
#define MAX_SIZE 4096

//======== PROTOTYPES =========
//int depthfirstapply(char *path, int pathfun(char *path),char *opts);
int depthfirstapply(char *sel_path, int indent);
//int sizepathfun(char *path);
char *get_dir(char *dir);


//int traverse(char *dir);


//=========== MAIN ============

int main(int argc, char **argv){
	int options;
	char *selected_directory;
	char selected_options[10] = "";
	while((options = getopt(argc, argv, "haB:bmcd:HLs")) != -1){
		switch(options){
			case 'h':  
				printf("Usage: mydu [-a] [-B M | -b | -m] [-c] [-d N] [-H] [-L] [-s] <dir1> <dir2> ...\n");
				printf("\t-a Write count for all files, not just directories.\n");
				printf("\t-B M Scale sizes by M before printing; for example, -BM prints size in units of 1,048,576 bytes.\n");
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
			case 'M':
                                strcat(selected_options, "M");
                                break;
			case 'c':
				strcat(selected_options, "c");
				break;
			case 'd':
				strcat(selected_options, "d");
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
			default:
				printf("ERROR: use option -h for help.\n");
				return EXIT_FAILURE;
		}
	}
	selected_directory = get_dir(argv[optind]);
	printf("Options selected: %s \n", selected_options);
	printf("Directory to be scanned: %s \n", selected_directory);
	
	depthfirstapply(selected_directory, 0);
	//int total = depthfirstapply(char *path, int pathfun(char *path), char *opts);

	return(0);
}






int depthfirstapply(char* sel_path, int indent){
	
	unsigned long size;	
	struct stat st;
	
	struct dirent *entry;
	char *name = entry->d_name; //file name	

	DIR *dir = opendir(sel_path);

	
	//struct stat info;
	//char *name = entry->d_name;
	//char pathname[4096];
	//sprintf(pathname, "%s/%s", sel_path, name);
	
	while((entry = readdir(dir)) != NULL){
		if(entry->d_type == DT_DIR){ //DT_DIR menas a directory
			char path[1024];
			if(strcmp(entry->d_name,".") != 0 || strcmp(entry->d_name, "..") != 0)
				continue;
			snprintf(path, sizeof(path),"%s/%s", sel_path, entry->d_name);
			printf("%*s[%s]\n", indent, "", entry->d_name);
			depthfirstapply(sel_path, indent + 2);
		}
		else{
			printf("%*s- %s\n",indent, "", entry->d_name);
		}
			//strcpy(path, sel_path);
			//strcat(path, "/");
			//strcat(path, entry->d_name);
		}
	closedir(dir);
}	

		

//returns a starting directory is given, if not given, current dir will be default
char *get_dir(char * dir){
	//char cwd[2] = ".";
	char cwd[MAX_SIZE];
	getcwd(cwd, sizeof(cwd));
	if(dir == NULL){
		return cwd;
	}
	else {
		return dir;
	}
}
