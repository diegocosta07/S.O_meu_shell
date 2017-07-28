#include <fcntl.h> /* Definition of AT_* constants */
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


int
main()
{
    struct dirent **namelist;
    int n;
    struct stat sb;
    char* dir = get_current_dir_name();
    stat(dir, &sb);
        printf("%d\n", sb.st_ino);
    printf("%d\n",mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH));
  

    free(dir);
    
}
