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
int depthfirstapply(char *path, int pathfun(char *path),char *opts);
//int depthfirstapply(const char *sel_path);
int sizepathfun(char *path);
char *get_dir(char *dir,char *path);
void listdir(const char *name, int indent);
void listdir1(char *path, size_t size);
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
	char path[MAX_SIZE];
	selected_directory = get_dir(argv[optind], path);
	printf("Options selected: %s \n", selected_options);
	printf("Directory to be scanned: %s \n\n", selected_directory);
	//listdir1(selected_directory,0);
	depthfirstapply(selected_directory, sizepathfun, selected_options);
	//int total = depthfirstapply(char *path, int pathfun(char *path), char *opts);

	return(0);
}
	
int depthfirstapply(char *path, int pathfun(char *pathl),char* opts) {
	/* XXX will use a fixed sized buf here and not size check */ 
	char buf[1024];
	struct stat statbuf;
	struct dirent *direntp;
	DIR *dirp;
	int sum = 0;

	if ((dirp = opendir(path)) == NULL) {
		perror("Can't open directory");
		return -1;
	}

	while ((direntp = readdir(dirp)) != NULL) {

		if ( strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0 ) {
			strcat(strcat(strcpy(buf, path), "/"), direntp->d_name);

			if ( lstat(buf, &statbuf) == -1) {
				perror("Couldn't get file status");
				fprintf(stderr, "\t%s %s\n", path, direntp->d_name);
				return -1;
			}

			if ( S_ISDIR(statbuf.st_mode) ) {
				sum += pathfun(buf);	
				depthfirstapply(buf, pathfun, opts);
			}
			else
				sum += pathfun(buf);	
		}

	}

	while ((closedir(dirp) == -1) && (errno == EINTR)) {}

	/*stat(path, &statbuf);*/
	printf("%i %s\n", sum, path);

	return 1;	
}

int sizepathfun(char *path) {
	struct stat statbuf;

	if ( lstat(path, &statbuf) == -1) {
		perror("Couldn't get file status");
		fprintf(stderr, "\t%s\n", path);
		return -1;
	}
	/* printing off_t */
	/* printf("%li\t%s\n", (long)statbuf.st_size, path); */

	return statbuf.st_size;
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

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

void listdir1(char *path, size_t size) {
    DIR *dir;
    struct dirent *entry;
    size_t len = strlen(path);

    if (!(dir = opendir(path))) {
        fprintf(stderr, "path not found: %s: %s\n",
                path, strerror(errno));
        return;
    }

    puts(path);
    while ((entry = readdir(dir)) != NULL) {
        char *name = entry->d_name;
        if (entry->d_type == DT_DIR) {
            if (!strcmp(name, ".") || !strcmp(name, ".."))
                continue;
            if (len + strlen(name) + 2 > size) {
                fprintf(stderr, "path too long: %s/%s\n", path, name);
            } else {
                path[len] = '/';
                strcpy(path + len + 1, name);
                listdir1(path, size);
                path[len] = '\0';
            }
        } else {
            printf("%s/%s\n", path, name);
        }
    }
    closedir(dir);
}




