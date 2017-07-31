#include <fcntl.h> /* Definition of AT_* constants */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int
main()
{
    /*
    int n;
    struct stat sb;
    char* dir = get_current_dir_name();
    stat(dir, &sb);
    printf("%d\n", sb.st_ino);
    strcat(dir,"/01");
    printf("%d\n",mkdirat(sb.st_ino, dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH));
    perror("mkdirat");
    free(dir);
   */

    /*struct dirent **namelist;
    int n;
    char* dir = get_current_dir_name();
    struct stat sb;
    stat(dir, &sb);
    n = scandirat(sb.st_ino, dir, &namelist, NULL, alphasort);
    perror("scandirat");
    while (n--) {
        printf("%s\n", namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);
         */

   
    /*char* str = "/home/diego/Documents/meu_shell/01";
    chdir(str);
    perror("chdir");
    struct dirent **namelist;
    int n;
    char* dir = get_current_dir_name();
    struct stat sb;
    stat(dir, &sb);
    n = scandirat(sb.st_ino, dir, &namelist, NULL, alphasort);
    perror("scandirat");
    while (n--) {
        printf("%s\n", namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);*/

}
