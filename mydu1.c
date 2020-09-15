#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/stat.h>  
#include <glob.h>  
#include <string.h>  
  
#define PATHMAX 4096  
  
static int  
is_loop(const char *path)  
{  
    char *pos;  
  
    pos = strrchr(path, '/');  
    if (pos==NULL) {  
        return 0;  
    }  
    if (strcmp(pos+1, "..")==0) {  
        return 1;  
    }  
    if (strcmp(pos+1, ".")==0) {  
        return 1;  
    }  
    return 0;  
}  
  
static int  
mydu(const char *path)  
{  
    int ret, sum=0, i;  
    struct stat stat_res;  
    static char complpath[PATHMAX];  
    glob_t glob_res;  
  
    ret = lstat(path, &stat_res);  
    if (ret==-1) {  
        return -1;  
    }  
    if (!S_ISDIR(stat_res.st_mode)) {  
        return stat_res.st_blocks;  
    }  
    if (is_loop(path)) {  
        return 0;  
    }  
/**********************************/  
    sum += stat_res.st_blocks;  
  
    snprintf(complpath, PATHMAX, "%s/*", path);  
    ret = glob(complpath, GLOB_NOSORT, NULL, &glob_res);  
    if (ret!=0) {  
        return -1;  
    }  
    snprintf(complpath, PATHMAX, "%s/.*", path);  
    ret = glob(complpath, GLOB_NOSORT|GLOB_APPEND, NULL, &glob_res);  
    if (ret!=0) {  
        return -1;  
    }  
    for (i=0;i<glob_res.gl_pathc;++i) {  
        ret = mydu(glob_res.gl_pathv[i]);  
        if (ret==-1) {  
            perror("mydu()");  
            continue;  
        }  
        sum += ret;  
    }  
    globfree(&glob_res);  
    return sum;  
}  
  
int  
main(int argc, char **argv)  
{  
    int ret;  
  
    if (argc<2) {  
        fprintf(stderr, "Usage:...\n");  
        exit(1);  
    }  
  
    ret = mydu(argv[1]);  
    if (ret==-1) {  
        perror("mydu()");  
        exit(1);  
    }  
  
    printf("%d blocks total.\n", ret);  
  
    exit(0);  
}  
