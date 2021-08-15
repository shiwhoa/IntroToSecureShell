#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char dir_input[2000];
    char inod_input[2000];
    printf("Which directory do you want to search for its content?  input directory name or '.' for current directory \n");
    scanf("%s", &dir_input);
    printf("What file inod do you want to find \n");
    scanf("%s", &inod_input);
    read_sub (dir_input, inod_input);
}
void read_sub (char* sub_dir, char* inod_search)

{
    if(*sub_dir == '.')
    {
       sub_dir = getcwd(NULL,0);
    }
//char nam_input[2000];
//printf("What file name do you want to find \n");
//scanf("%s", &nam_input);
//printf("%s",nam_input);


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
        char inode[2000];
        //printf("sub_dirp->d_name %s\n",sub_dirp->d_name);
       // printf("temp3 %s\n",temp3);
        if(strcmp(temp,temp1)!=0 && strcmp(temp,temp2)!=0)
        {
            char* temp_sub = temp3 ;
            temp_sub = strcat(temp3,temp);

            char* temp_full_path = malloc(sizeof(char)*2000);
            temp_full_path = strcpy(temp_full_path,sub_dir);
           // printf("temp_sub  %s\n", temp_sub);
            strcat(temp_full_path,temp_sub);
            //printf("temp  %s\n", *temp);
            //printf("nam_input  %s\n", nam_input);
            // printf("buf1");
            if(stat(temp, &buf) == 0)
            {
                snprintf(inode,sizeof(inode),"%d",(int)buf.st_ino);
               // printf("*inode   %s \n", inode);
               // printf("*inode_search   %s \n",inod_search);
                if(strcmp(inode, inod_search)==0)
                {
                    printf("%s \n",temp_full_path);
                }
            }
            DIR* subsubdp = opendir(temp_full_path);
            if(subsubdp!=NULL)
            {

                closedir(subsubdp);
                read_sub(temp_full_path, inod_search);
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

