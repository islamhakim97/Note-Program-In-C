#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

void fatal(char*);//fatal error func declaration
void *chk_malloc(unsigned int); // fuc declare for reserve space in memory
// usage func of [our Note]
void usage(char *progname,char *filename)
{
 printf("[USAGE]:[ %s Data Added to %s] \n",progname,filename);
printf("[Author]: Islam Hakim --> islamabdlhakim10@gmail.com\n");
 exit(0);
}

int main (int argc,char *argv[])
{
 int fd;//filedescriptor
 char *buffer,*datafile ;//for sring notes and path of file created 
 buffer=(char*)chk_malloc(100);
 datafile= (char*)chk_malloc(20);
 strcpy(datafile,"Documents/Note");
 //if prgram arguments less than 2 show usage then exit
 if (argc<2)
 { 
  usage(argv[0],datafile);
  exit(0);
  }
 strcpy(buffer,argv[1]);
 printf("[DEBUG:]Address Of Buffer@%p Content:%s\n ",buffer,buffer);
 printf("[DEBUG:]Address Of FilePath@%p \tContent:%s\n ",datafile,datafile);
 strncat(buffer,"\n",1);
//Openning File
fd=open(datafile,O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
if (fd==-1)
  fatal("in main() while openning file");
printf("[DEBUG:] File descriptor is %d \n ");
//writing Data To file
if(write(fd,buffer,strlen(buffer))== -1)
  fatal("In main() while writtinig Buffer to file");
//closing file
if (close(fd)==-1)
                 fatal("in main() while closing file");
printf("Note has been saved .\n");
//free Heap  [buffer&datafile]
free(buffer);
free(datafile);
}
//Fatal Error function implementation   
void fatal(char *message)
{
char err_msg[20];
strcpy(err_msg,"[!!]Fatal Error:");
strncat(err_msg,message,84);
perror(err_msg);
exit(-1);
}
// an error check malloc() wrapper function
void *chk_malloc(unsigned int size)
{
void *ptr =malloc(size);
if (ptr==NULL)
 fatal("on chk malloc on memory allocation ");
return ptr;
}


