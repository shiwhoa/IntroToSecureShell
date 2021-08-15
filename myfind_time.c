#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main()
{
    char dir_input[2000];
    float time_diff_input;
    printf("Which directory do you want to search for its content?  input directory name or '.' for current directory \n");
    scanf("%s", &dir_input);
    printf("What file time within do you want to find \n");
    scanf("%f", &time_diff_input);
    printf("time_diff_search0 = %f\n", time_diff_input);
    read_sub (dir_input, time_diff_input);
}
void read_sub (char* sub_dir, double time_diff_search)

{
    printf("time_diff_search1 = %f\n", time_diff_search);

    if(*sub_dir == '.')
    {
       sub_dir = getcwd(NULL,0);
    }

DIR* sub_dp = opendir(sub_dir);

struct dirent* sub_dirp;

struct stat buf;

char temp1[]=".";

char temp2[]="..";

char temp3[]="/";

char* path = getcwd(NULL,0);

if(sub_dp!=NULL)
{


    while((sub_dirp=readdir(sub_dp))!=NULL)
    {
        char* temp =sub_dirp->d_name;
        char temp3[]="/";
        time_t now1;
        time(&now1);
        if(strcmp(temp,temp1)!=0 && strcmp(temp,temp2)!=0)
        {
            char* temp_sub = temp3 ;
            temp_sub = strcat(temp3,temp);

            char* temp_full_path = malloc(sizeof(char)*2000);
            temp_full_path = strcpy(temp_full_path,sub_dir);
            strcat(temp_full_path,temp_sub);
           
            if(stat(temp, &buf) == 0)//0 means successful
            {
               ctime(&buf.st_mtime);
               printf("time diff is %ld\n", (now1 -  buf.st_mtime)/60);
               printf("time_diff_search = %f\n", time_diff_search);
                if((now1 - buf.st_mtime)/60 <= time_diff_search )
                {
                    printf("%s \n",temp_full_path);
                }
            }
            else
            {
               // printf("it is subdir\n");
            }
            DIR* subsubdp = opendir(temp_full_path);
            if(subsubdp!=NULL)
            {
                closedir(subsubdp);
               // printf("imhere\n");  
                read_sub(temp_full_path, time_diff_search);
            }
        }
    }
closedir(sub_dp);
}
else
{
    printf("cannot open directory\n");
    exit(2);
}
}
