#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char dir_input[2000];
    printf("Which directory do you want to search for its content?  input directory name or '.' for current directory \n");
    scanf("%s", &dir_input);
    read_sub (dir_input);
}
void read_sub (char* sub_dir)

{
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
       // printf("temp %s\n",temp);
       // printf("temp3 %s\n",temp3);
        if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
        {
            char* temp_sub = temp3 ;
            temp_sub = strcat(temp3,temp);

            char* temp_full_path = malloc(sizeof(char)*2000);
            temp_full_path = strcpy(temp_full_path,sub_dir);
           // printf("temp_sub  %s\n", temp_sub);
            strcat(temp_full_path,temp_sub);
            printf("%s \n",temp_full_path);
            DIR* subsubdp = opendir(temp_full_path);
            if(subsubdp!=NULL)
            {
                
                closedir(subsubdp);
                read_sub(temp_full_path);
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

