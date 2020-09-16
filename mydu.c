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
int depthfirstapply(char *path, int pathfun(char *path, char *options),char *options, int *fileCount);
int sizepathfun(char *path, char *options);
char *get_dir(char *dir,char *path);

//=========== MAIN ============

int main(int argc, char **argv){
	int options;
	char *selected_directory;
	char selected_options[10] = "";
	
	int *fileCount;
	fileCount = malloc(sizeof(int));    //allocating memory to pointer fileCount
	*fileCount = 0;

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
	char path[MAX_SIZE];
	selected_directory = get_dir(argv[optind], path);
	printf("Options selected: %s \n", selected_options);
	printf("Directory to be scanned: %s \n\n", selected_directory);
	
	depthfirstapply(selected_directory, sizepathfun, selected_options, fileCount);
	
	printf("Regular files:%d\n\n", *fileCount);
	
	
	free(fileCount);			
	return(0);
}
	
int depthfirstapply(char *path, int pathfun(char *pathl,char *options),char* options, int *fileCount) {
	 
	char buf[MAX_SIZE];
	struct stat statbuf; 
	struct dirent *direntp; // direntory entry pointer
	DIR *dir = opendir(path);
	int sum = 0;
			

	if (dir == NULL) {
		perror("ERROR: Failed to open directory\n");
		return -1;
	}
		
	while ((direntp = readdir(dir)) != NULL){
		// check if directory is current or previous
		if ( strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0 ) {
			strcat(strcat(strcpy(buf, path), "/"), direntp->d_name); // add directory to buffer
			//checks file status
			if (lstat(buf, &statbuf) == -1) {
				perror("ERROR: File status not found.\n");
				fprintf(stderr, "\t%s %s\n", path, direntp->d_name);
				return -1;
			}
			//Checks if the entry is a regular file
			if (S_ISREG(statbuf.st_mode)){
	                        *fileCount = *fileCount + 1;
	                }
                        if ((S_ISREG(statbuf.st_mode) && (strstr(options, "a") != NULL))) {
                                //sum += sizepathfun(buf, options);
                                printf("%-10d %s/%s\n", sizepathfun(buf, options), path, direntp->d_name);
                        }

			// checks if the entry is a directory
			if (S_ISDIR(statbuf.st_mode)) {
				sum += sizepathfun(buf, options);	
				sum += depthfirstapply(buf, sizepathfun, options, fileCount);
			}
			else
				sum += sizepathfun(buf, options);	
		}

	}
	
	closedir(dir);	
	
	printf("%-10d %s\n", sum, path);

	return sum;	
}

// returns total size in bytes
int sizepathfun(char *path, char *options) {
	struct stat statbuf;
	//checks file status
	if (lstat(path, &statbuf) == -1) {
		perror("ERROR: File status not found.\n");
		fprintf(stderr, "\t%s\n", path);
		return -1;
	}
	if((strstr(options, "b") != NULL) || (strstr(options, "B") != NULL) || (strstr(options, "m") != NULL)){
			return statbuf.st_size;
		}
	else
			return (statbuf.st_blocks/2);
		
	//return statbuf.st_size;
}
		

//returns a starting directory is given, if not given, current dir will be default
char *get_dir(char * dir,char *path){
	//char cwd[2] = ".";
	getcwd(path, MAX_SIZE);
	if(dir == NULL){
		return path;
	}
	else {
		return dir;
	}
}

