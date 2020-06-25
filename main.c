/*
The make file creates the read_dir object file. To execute this program the syntax format is:
./read_dir -letter_for_function directory file_name

The syntax is different for different finctions
but the above given syntax is the general form.
The detail syntax for all the function are given below.
Here, 'demo' is a demo directory.

For finding the directory:
./read_dir -F demo

For finding file with directory and file name.
./read_dir -f demo bimal.c

For finding file with directory and minutes.
./read_dir -m 10

For finding file with directory and i_node number.
./read_dir -i 12344565

For finding file with removing file with directory and criterai.
./read_dir -r demo c_lang.c
./read_dir -r demo 10
./read_dir -r demo 123456

For finding file and implementing cat.
./read_dir -c demo bimal.c

For finding file with directory and removing file with file name.
./read_dir -d demo bimal.c

For finding file with directory and changing file name.
./read_dir -v demo bimal.c karki.c


*/



// including all the requuired libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
char * full_path;

//defining global variable for argc and argv.
// these variable are assigned a value from main function

int a_argc;
char * a_argv1;
char * a_argv2;
char * a_argv3;
char * a_argv4;
char * a_argv5;

//defining struct for linked list.
//all the directories are stored in linked list.
//the name, time of last modification and i-node number is stored in this linked list.

typedef struct node{
    char *name;
    int min;
    int i_node;
    struct node *next;
}node_t;

node_t *head=NULL;

//this is the add function which adds the values in linked list

node_t * add (char *name1,int minute, int i,node_t  *head){
     node_t *new_node;
     new_node = (node_t *) malloc(sizeof(node_t));
     new_node->name = name1;
     new_node->min = minute;
     new_node->i_node = i;
     new_node->next = head;
     head=new_node;
     return head;
}

// this function prints all the values stored in linked list.

void print(node_t *head) {
  printf("File directory, Last access time  and i_node number \n");
    node_t *current_node = head;
 while ( current_node != NULL) {
        printf("%s %d %d \n", current_node->name,(current_node->min/60),current_node->i_node);
        current_node = current_node->next;
    }
    printf("\n \n");
}

/*this functiion prints all the directories and sub directory related with the user
 specified keyword. For eg. if the key word is "Demo", this function returns all the
 directories and sub directory that has the key word "Demo". */

 void search_dir(node_t *head) {
     char *val1=(char*)malloc(100*sizeof(char));
     int x=0;
     node_t *current_node = head;
     char* p;
     while ( current_node != NULL) {
        val1=current_node->name;
       p=strstr(val1,a_argv3);
       if(p){
          printf("%s \n",current_node->name);
       }
       current_node = current_node->next;
       }
}

//this function prints all the files realted to user specified directory.

void search_file(node_t *head) {
     char *key1=(char*)malloc(100*sizeof(char));
     char *key2=(char*)malloc(100*sizeof(char));
     char *val1=(char*)malloc(100*sizeof(char));

     node_t *current_node = head;
     key1=a_argv3;
     key2=a_argv4;
     while ( current_node != NULL) {
      val1=current_node->name;
      if(strstr(val1,key1)){
       if(strstr(val1,key2)){
          printf("%s \n",current_node->name);
       }
      }
       current_node = current_node->next;
     }
    }
    //this function prints all the directory that is modified with in user specified minutes.
void search_time(node_t *head){
  int key=atoi(a_argv3);
  int val;
  time_t seconds;
  seconds = time(NULL);
  printf("Current time %ld\n", seconds);
  node_t *current_node = head;

  while ( current_node != NULL) {
       val=current_node->min;
       int diff=seconds-val;
       if(diff<=(key*60)){
          printf("%s \n",current_node->name);
       }
       current_node = current_node->next;
  }
}


 //this function prints all the directory for a user specified i-node number.
void search_inode(node_t *head) {
     int key=atoi(a_argv3);
     int val;
     node_t *current_node = head;
    // print(head);
     while ( current_node != NULL) {
        val=current_node->i_node;
       if(val==key){
          printf("%s \n",current_node->name);
       }
       current_node = current_node->next;
        }
}


// this function deletes the file according to user specified criterai and directory.

void search_dir_delete(node_t *head) {
     char *val1=(char*)malloc(100*sizeof(char));
     char *val2=(char*)malloc(100*sizeof(char));
     char *val3=(char*)malloc(100*sizeof(char));
     char *key2=(char*)malloc(100*sizeof(char));
     char *key1=(char*)malloc(100*sizeof(char));
     char *key=(char*)malloc(100*sizeof(char));
     char *val4=(char*)malloc(100*sizeof(char));

     int i;
int u=0;
      time_t seconds;
      seconds = time(NULL);

     key=a_argv3;
     key2=a_argv4;
     node_t *current_node = head;
     char* p;

     while ( current_node != NULL) {
        val1=current_node->name;
        int s_v2=current_node->min;
        int diff=seconds-s_v2;
        int s_v3=current_node->i_node;
        int u;

        sprintf(val2, "%d", (diff/60));
        sprintf(val3, "%d", s_v3);

      if(strstr(val1,key)){
       if(strstr(val1,a_argv4)||strstr(val2,a_argv4)||strstr(val3,a_argv4)){
          key1=val1;
       }
      }
      remove(key1);
      current_node = current_node->next;

       }

 }

 //this function opens the specified file and read content of the file.
//implements 'cat'

void cat_imp(){

  char d;
  chdir(a_argv3);
  FILE *fd;
  fd=fopen(a_argv4,"r");

  if(fd<0){
    printf("Error finding file....");
  }

  d = fgetc(fd);
    while (d != EOF)
      {
    printf ("%c", d);
        d = fgetc(fd);
    }

  fclose(fd);
}

//this function deletes the specified file from the current directory.
void delete(){
  char *key=(char*)malloc(100*sizeof(char));
  char *key2=(char*)malloc(100*sizeof(char));
  key=a_argv3;
  key2=a_argv4;
  char x='.';
  int i;

  chdir(key);

  remove(key2);
  exit(2);

}

//this function renames the file name.
void r_rename(){
   char *new_n=(char*)malloc(100*sizeof(char));
   new_n=a_argv5;
   char *old_n=(char*)malloc(100*sizeof(char));
   old_n=a_argv4;
   chdir(a_argv3);
   rename(old_n, new_n);

}

/*this is a search function which determines which function to call according to argument
passed to it.*/

void search(int i){
  if(i==1){
     search_dir(head);
  }else if(i==2){
     search_file(head);}
  else if (i==3){
     search_time(head);
  }else if (i==4){
     search_inode(head);
  }else if(i==5){
    search_dir_delete(head);
  }else if(i==6){
 cat_imp();
  }else if(i==7){
     delete();
  }else if(i==8){
     r_rename();
  }else {
 printf("Wrong option....");
  }
}

/*this function recurcively loop into the sub-directory to find all the directory and add them to linked list*/
void read_sub(char* sub_dir)
{
  DIR *sub_dp=opendir(sub_dir);
  struct dirent * sub_dirp;
   struct stat buf;
char *sub_dd;
  if(sub_dp!=NULL)
    {
       while((sub_dirp=readdir(sub_dp))!=NULL)
        {
         sub_dd=sub_dirp->d_name;
            if(stat(sub_dirp->d_name,&buf)==0);
                char * temp =sub_dirp->d_name;
       char temp1[]=".";
       char temp2[]="..";
  if(strcmp(temp,temp1)!=0&&strcmp(temp,temp2)!=0)
      {
      char temp3[]="/";
      char *temp_sub=temp3;
      temp_sub=strcat(temp_sub,temp);
      char * temp_full_path=malloc(sizeof(char)*2000);
       temp_full_path=strcpy(temp_full_path,sub_dir);
      strcat(temp_full_path,temp_sub);
      DIR * subsubdp=opendir(temp_full_path);
      head=add(temp_full_path,buf.st_mtime,buf.st_ino,head);
      if(subsubdp!=NULL){
      closedir(subsubdp);

      read_sub(temp_full_path);

      }
      }
      }
   }
   else
   {
       printf("cannot open directory\n");
 exit(2);
   }
  closedir(sub_dp);
  }

  //this is the main function.
  //All other function are called from here.
  //Global variables are assiogned here.
  int main(int argc, char **argv)
{

  //all global varibales are assigned here.
  a_argc=argc;
  a_argv1=argv[0];
  a_argv2=argv[1];
  a_argv3=argv[2];
  a_argv4=argv[3];
  a_argv5=argv[4];
    char * dir;
    if(argc <10)
    {
        dir=".";
    }
    else
    {
        dir=argv[1];
    }
 read_sub(dir);/*read_sub() is called with the current directory argument. this adds all the directory to linked list.*/
int c;

/*"Ffmircdv" is used to execute the program.
F calls the search_dir function.
f calls the search_file function.
m calls the search_time function.
i calls the search_inode function.
r calls the search_dir_delete function.
c calls the cat_imp function.
d calls the delete function.
v calls the r_rename function.
  */

//print(head);
while((c=getopt(argc,argv,"Ffmircdv"))!=-1){
  switch(c)
  {
    case 'F':
       search(1);
       break;
    case 'f':
       search(2);
       break;
    case 'm':
      search(3);
      break;
    case 'i':
      search(4);
      break;
    case 'r':
       search(5);
      break;
    case 'c':
      search(6);
      break;
    case 'd':
      search(7);
      break;
    case 'v':
     search(8);
      break;
    case '?':
      fprintf(stderr,"Unknown option -%c. \n",optopt);
      break;
    default:
      fprintf(stderr,"getopt");

  }
}
 exit(0);
}
