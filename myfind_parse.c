#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


void find1(char* sub_dir)
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
                find1(temp_full_path);
            }
	}
    }

closedir(sub_dp);//close the steam
}
else
{
    printf("cannot open directory\n");
    exit(2);
}
        //printf("find1 %s %s %s\n", where);
}


//
//
//


void find2(char* sub_dir, char* nam_search, int e, int d, char* new_nam)
{
        /* Test arguments parsed. */

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
           // printf("temp  %s\n", *temp);
           // printf("nam_search  %s\n",*nam_search);
            if(strcmp(temp, nam_search)==0)// 0 means successful
            {
                printf("%s \n",temp_full_path);
	    	    
            	if(d==1)
            	{
               		int ret;
		 	ret = remove(temp_full_path);
		 	if(ret == 0)
		 	{
				 printf("%s is deleted \n",temp_full_path);
		 	}
			 else
		 	{
				printf("file could not be deleted");
		 	}
	    	}
	    
                if(e==1)
                {
                        
			char ch;
			FILE *fp = fopen(temp_full_path, "r");
			while((ch = fgetc(fp)) != EOF)
     			printf("%c", ch);

		        fclose(fp);
                }
                if(e==2)
                {
                        int ret;
                        ret = remove(temp_full_path);
                        if(ret == 0)
                        {
                                 printf("%s is deleted \n",temp_full_path);
                        }
                         else
                        {
                                printf("file could not be deleted");
                        }
                }
                if(e==3)
                {
                        rename(temp, new_nam);
                }

	    }
           
	    	DIR* subsubdp = opendir(temp_full_path);
            	if(subsubdp!=NULL)
            	{

                	closedir(subsubdp);
                	find2(temp_full_path, nam_search, e, d, new_nam);
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



//
//
//




void find3(char* sub_dir, char* inod_search, int d)

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
            if(stat(temp, &buf) == 0)//0 means successful
            {
                snprintf(inode,sizeof(inode),"%d",(int)buf.st_ino);
               // printf("*inode   %s \n", inode);
               // printf("*inode_search   %s \n",inod_search);
                if(strcmp(inode, inod_search)==0)// 0 means successful
                {
                       printf("%s \n",temp_full_path);
 	               if(d==1)
        	        {
                	        int ret;
                       		ret = remove(temp_full_path);
                       		if(ret == 0)
                       		{
                                	 printf("%s is deleted \n",temp_full_path);
                       		}
                   	        else
                       		{
                               		 printf("file could not be deleted");
                       		}
               		}

                }
            }
            DIR* subsubdp = opendir(temp_full_path);
            if(subsubdp!=NULL)
            {

                closedir(subsubdp);
                find3(temp_full_path, inod_search, d);
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


//
//
//


void find4(char* sub_dir, char* sym,  double time_diff_search, int d)

{
   // printf("time_diff_search1 = %f\n", time_diff_search);
//	printf("symhere = %c\n", *sym);
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
	char temp1[]=".";
	char temp2[]="..";
        char temp3[]="/";
	char* temp4="-";
	char* temp5="+";
        time_t now1;
        time(&now1);
        if(strcmp(temp,temp1)!=0 && strcmp(temp,temp2)!=0)
        {
            char* temp_sub = temp3 ;
            temp_sub = strcat(temp3,temp);

            char* temp_full_path = malloc(sizeof(char)*2000);
            temp_full_path = strcpy(temp_full_path,sub_dir);
            strcat(temp_full_path,temp_sub);
//		printf("temp is %s\n", temp);

	    if(stat(temp_full_path, &buf) == 0)//0 means successful
            {
               ctime(&buf.st_mtime);
	      // printf("(inside stat(temp,&buff) transfer successful ; file name open: %s \n", temp);
              // printf("time diff between now and file touched  %ld\n", (now1 -  buf.st_mtime)/60);
              // printf("my time constraint = %f\n", time_diff_search);
	      //printf("sym is %c \n", *sym);
	        //if((now1 - buf.st_mtime)/60 <= time_diff_search)
		//{
		//    printf("imhere\n");
		//}
                if(sym[0]=='-'  &&  (now1 - buf.st_mtime)/60 <= time_diff_search )
                {
                    printf("%s \n",temp_full_path);
	                if(d==1)
	                {
	                        int ret;
	                        ret = remove(temp_full_path);
	                        if(ret == 0)
	                        {
	                                 printf("%s is deleted \n",temp_full_path);
	                        }
	                         else
	                        {
	                                printf("file could not be deleted");
	                        }
	                }

                }
                else if(sym[0]=='+'  &&  (now1 - buf.st_mtime)/60 > time_diff_search )
                {
                    printf("%s \n",temp_full_path);
                        if(d==1)
                        {
                                int ret;
                                ret = remove(temp_full_path);
                                if(ret == 0)
                                {
                                         printf("%s is deleted \n",temp_full_path);
                                }
                                 else
                                {
                                        printf("file could not be deleted");
                                }
                        }

                }
                else if(sym[0]=='0'  &&  (now1 - buf.st_mtime)/60 == time_diff_search )
                {
                    printf("%s \n",temp_full_path);
                        if(d==1)
                        {
                                int ret;
                                ret = remove(temp_full_path);
                                if(ret == 0)
                                {
                                         printf("%s is deleted \n",temp_full_path);
                                }
                                 else
                                {
                                        printf("file could not be deleted");
                                }
                        }

                }

            }
            else
            {
                printf("it is subdir, cannot transfer to buffer to extract time\n");
            }
            DIR* subsubdp = opendir(temp_full_path);
            if(subsubdp!=NULL)
            {
                closedir(subsubdp);
               // printf("imhere\n");
                find4(temp_full_path, sym, time_diff_search, d);
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





//
//
//









int main(int argc, char **argv)
{
        int w=0;
	int n=0;
	int m=0;
	int i=0;
	int d=0;
        int e=0;

        char *where, *name, *mmin, *inum, *exec;
        char* optargsign;
        float moff;

                        char str1[] = "cat";
                        char str2[] = "rm";
                        char str3[] = "mv";

        while (1)
        {
            char c;
            c = getopt(argc, argv, "w:n:m:i:e:d");   /* A colon (‘:’) means there HAS to be an argument accompanying the -option*/
                if (c == -1)
                {
                        /* We have finished processing all the arguments. */
                        break;
                }
                switch (c)
                {
                case 'w':
                        w = 1;
                        where = optarg;// argument along with -w is captured in where
                       // printf("where: %s\n", where);
                        break;
                case 'n':
                        n = 1;
                        name = optarg;// argument along with -n is captured in name
                       // printf("name: %s\n", optarg);
                        break;
                case 'm':
                        m = 1;
			//printf("mmin 1st char : %c \n", optarg[0]);
                        if(optarg[0]=='-' || optarg[0]=='+')
			{
			       // printf("imhereeeeee\n");
				optargsign = &(optarg[0]);
			//	printf("optargsign  %c\n", optargsign);
				optarg = optarg + 1;
				moff = atof(optarg);
				break;
			}

                        else
                        {
                                char z[1];
				z[0] = '0';
                                optargsign = &(z[0]);
			//	printf("optargsign  %c\n", optargsign);
				moff = atof(optarg);
				break;
			}

			//mmin = optarg;// argument along with -m is captured in mmin
                        //printf("mmin: %s\n", optarg);
                        break;
                case 'i':
                        i = 1;
                        inum = optarg;
                        printf("inum: %s\n", optarg);// argument along with -i is captured in inum
                        break;
                case 'e':
			if(strcmp(optarg, "cat")==0)
			{
				e=1;
			//	printf("im in 1 \n");
			}
                        if(strcmp(optarg, "rm")==0)
                        {
                                e=2;
			//	printf("im in 2 \n");
                        }
                        if(optarg[0]== 'm' && optarg[1]== 'v')
                        {
                                e=3;
				optarg = optarg + 3;
				//printf("im in 3 \n");
                        }

			exec = optarg;// argument along with -e is captured in action
                        //printf("exec: %s\n", optarg);
                        break;
		case 'd':
			d = 1;
			break;
                case '?':
                default:
                        printf("An invalid option detected.\n");
                }
        }

        /* The following codes are optional, but better to study it. */
        if (w == 1 && n==0 && m==0 && i==0 && e==0)
        {
            find1(where);
        }
        if (w == 1 && n==1 && m==0 && i==0 && e==0)
        {
            find2(where, name, e, d, exec);
	}        
        if (w == 1 && n==0 && m==0 && i==1 && e==0)
        {
            find3(where, inum, d);
        }
        if (w == 1 && n==0 && m==1 && i==0 && e==0)
        {
	     find4(where, optargsign, moff, d);
        }
        if (w == 1 && n==1 && m==0 && i==0 && e!=0)
        {
             find2(where, name, e, d, exec);
        }






























        /*
         * Now set the values of "argc" and "argv" to the values after the
         * options have been processed above.
         */
       // argc -= optind;
        //argv += optind;

        /*
         * Now do something with the remaining command-line arguments, if
         * necessary.
         */
       // if (argc > 0) {
       //         printf("There are %d command-line arguments left to process:\n", argc);
       //         for (i = 0; i < argc; i++) {
       //                 printf("Argument %d: '%s'\n", i + 1, argv[i]);
       //         }
       // }
        return 0;
}

