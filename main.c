// Learning C. Just testing file I/O.

#include <stdio.h>
#include <stdlib.h>

const unsigned int PORT_NUM = 50000; /* random port number, we need something */

int main(int argc, char const *argv[])
{
  // all names must be shorter than 10 characters
  char fam[10], person[10];
  int arrTime, duration;
  FILE *file = fopen("input.txt", "r+");

  if(file == NULL)
  {
    printf("No file provided.\n");
    return -1;
  }

  while(!feof(file)) 
  {
    fscanf(file, "%s %s %d %d", fam, person, &arrTime, &duration);
    printf("%s %s %d %d\n", fam, person, arrTime, duration);
  }

  printf("end.\n");
    //  break;

  fclose(file); 
 
  return 0;
}