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
//#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <stdbool.h>

#define MAX_ARGS 10
#define MAX_SIZE 4096

//======== PROTOTYPES =========
int depthfirstapply(char *path, int pathfun(char *path, char *options, int scale),char *options, int counts[],int scale,int depth);
int sizepathfun(char *path, char *options, int scale);
char *get_dir(char *dir,char *path);
char *human_read(double size, char *buf);
bool option_check(char *options);
//=========== MAIN ============

unsigned int global_depth = -1;


int main(int argc, char **argv){
	unsigned int options;
	char *selected_directory;
	char selected_options[10] = "";
	unsigned int total; // total size
	char path[MAX_SIZE];
	char buffer[MAX_SIZE];
	unsigned int counts[3] = {0,1}; // counter for files and directories and symlinks
	unsigned int scale = 1048576; // default for scale
	unsigned int depth;
	

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
				scale = atoi(optarg); // argument replaces default
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
				depth = atoi(optarg);
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

	// checks for incompatible options
	if(option_check(selected_options)){ return EXIT_FAILURE;}
	
	//printf("Options selected: %s \n", selected_options);
	
	// loops through directories
	while(argv[optind] != '\0'){
		// get selected directory
		selected_directory = get_dir(argv[optind], path);

		// runs the search and print through the directory and files
		total = depthfirstapply(selected_directory, sizepathfun, selected_options, counts, scale, depth);

        	if((strstr(selected_options, "c") != NULL) || (strstr(selected_options, "s") != NULL)){
                	if(strstr(selected_options, "s") != NULL){
				printf("Directory: %s -> ", selected_directory);
			}
			if (strstr(selected_options, "H") != NULL){
                        	printf("Total: %s\n", human_read((double) total, buffer));
                	}
                	else {
                        	printf("Total: %d\n", total);
                	}
        	}
		// increase index to next directory
		optind++;
	}

	printf("\nDirectories: %d\n", counts[1]);
	printf("Regular files:%d\n", counts[0]);
	if(strstr(selected_options, "L") != NULL){
		printf("Symbolic links: %d\n", counts[2]);
	}
		
	printf("\n");			
	return(0);
}
	
int depthfirstapply(char *path, int pathfun(char *pathl,char *options, int scale),char* options, int counts[], int scale, int depth) {
	 
	char buf[MAX_SIZE]; //buffer for path
	char altbuf[MAX_SIZE]; //alternative buffer for converting to human readable
	struct stat statbuf; 
	struct dirent *direntp; // direntory entry pointer
	DIR *dir = opendir(path);
	unsigned int sum = 0; //size sum
	global_depth++;		
	
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
	                        counts[0] = counts[0] + 1; // adds to count of files
	                }
                        // if regular file and a selection then print stats on files too
			if ((S_ISREG(statbuf.st_mode) && (strstr(options, "a") != NULL))) {
                                //prints files
                                unsigned int size = sizepathfun(buf, options, scale);
                                if(!(strstr(options, "s") != NULL)){

					if(strstr(options, "H") != NULL){
	                			printf("%-10s %s/%s\n", human_read((double)size, altbuf), path, direntp->d_name);
        				}
        				else {
						printf("%-10d %s/%s\n", size, path, direntp->d_name);
                        		}
				}
			}
			
			// checks if entry is symbolic link
			if ((S_ISLNK(statbuf.st_mode) && (strstr(options, "L") != NULL))) {
			unsigned int size = sizepathfun(buf, options, scale);
			counts[2] = counts[2] + 1; // add to count of symlinks
                                if(!(strstr(options, "s") != NULL)){
                                        if(strstr(options, "H") != NULL){
                                                printf("%-10s %s/%s\n", human_read((double)size, altbuf), path, direntp->d_name);
                                        }
                                        else {
                                                printf("%-10d %s/%s\n", size, path, direntp->d_name);
                                        }
                                }
			}
			
			// checks if the entry is a directory
			if (S_ISDIR(statbuf.st_mode)) {
				// checks for depth of directory
				if((strstr(options, "d") != NULL) && (global_depth >= depth)) {break;}
				counts[1] = counts [1] + 1; //adds to count of directories
				sum += sizepathfun(buf, options, scale);
				sum += depthfirstapply(buf, sizepathfun, options, counts, scale, depth);
			}
			else
				sum += sizepathfun(buf, options, scale);	
		}

	}
	
	closedir(dir);
	
	if(!(strstr(options, "s") != NULL)){
		//prints the size and path of directory
		if(strstr(options, "H") != NULL){ // human readable
			printf("%-10s %s\n", human_read((double) sum,altbuf), path);
		}
		else {printf("%-10d %s\n", sum, path);}
	}
	global_depth--;
	return sum;	
}

// returns total size in bytes
int sizepathfun(char *path, char *options, int scale) {
	struct stat statbuf;
	//checks file status
	if (lstat(path, &statbuf) == -1) {
		perror("ERROR: File status not found.\n");
		fprintf(stderr, "\t%s\n", path);
		return -1;
	}
	if((strstr(options, "b") != NULL)){
			return statbuf.st_size;	
	}
	else if((strstr(options, "B") != NULL) || (strstr(options, "m") != NULL)){
                int size = statbuf.st_size/scale;
		if (size > 1){ return size;}
		else { return 1;}
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


char* human_read(double size/*in bytes*/, char *buf) {
	unsigned int index = 0;
	const char* suffix_units[] = {"B", "kB", "MB", "GB", "TB"};
	while (size > 1024) {
		size /= 1024;
		index++;
    }
    sprintf(buf, "%.*f %s", index, size, suffix_units[index]);
    return buf;
}

bool option_check(char * options){
	if((strstr(options, "B") != NULL) && (strstr(options, "m") != NULL)){
                printf("ERROR: cannot have options 'B' and 'm' together\n");
		printf("Usage: mydu [-a] [-B M | -b | -m] [-c] [-d N] [-H] [-L] [-s] <dir1> <dir2> ...\n");
		return true;
                }
        if((strstr(options, "B") != NULL) && (strstr(options, "b") != NULL)){
                printf("ERROR: cannot have options 'B' and 'b' together\n");
		printf("Usage: mydu [-a] [-B M | -b | -m] [-c] [-d N] [-H] [-L] [-s] <dir1> <dir2> ...\n");
		return true;
                }
        if((strstr(options, "b") != NULL) && (strstr(options, "m") != NULL)){
                printf("ERROR: cannot have options 'b' and 'm' together\n");
		printf("Usage: mydu [-a] [-B M | -b | -m] [-c] [-d N] [-H] [-L] [-s] <dir1> <dir2> ...\n");
		return true;
                }
	else
		return false;

}

