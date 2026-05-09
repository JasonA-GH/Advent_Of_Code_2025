#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long sum = 0;
int total_count = 0;

void check_range(unsigned long long a, unsigned long long b)
{
  printf("Check range of %llu and %llu ", a, b);
  int count = 0;
  for(unsigned long long i=a; i <= b; i++)
    {
      char buffer[64] = {0};
      char half[32] = {0};
      int eject = 0;
      sprintf(buffer, "%llu", i);
      unsigned long long length = strlen(buffer);
      if(length%2 != 0)
	continue;
      strncpy(half, buffer, length/2);
      //printf("%s %s\n", half, buffer);
      for(unsigned long long j=0; j < length/2; j++)
	{
	  if(half[j] != buffer[j+length/2])
	    {
	      eject = 1;
	      break;
	    }
	}
      if(eject)
	{
	  continue;
	}
      sum += i;
      //printf("%llu\n", sum);
      //printf("INVALID ID: %d\n", i);
      count++;
      total_count++;
    }
  printf("| %d\n", count);
}

void search_id_range(char range[], unsigned long long size)
{
  //get first number
  //get second number
  //pass to check_range

  //printf("Searching range %s size: %d\n", range, size);
  
  char num1[64] = {0};
  char num2[64] = {0};
  unsigned long long index = 0;
  int numO = 1;
  for(unsigned long long i=0; i < size; i++)
    {
      //printf("%d\n", i);
      if(range[i] == '-')
	{
	  //printf("Done first number, moving onto second one\n");
	  numO = 2;
	  index = 0;
	}
      else
	{
	  if(numO == 1)
	    {
	      num1[index] = range[i];
	    }
	  else
	    num2[index] = range[i];
	  index++;
	}
    }

  //printf("Got ranges %s %s as %llu %llu | ", num1, num2, atoll(num1), atoll(num2));
  check_range(atoll(num1), atoll(num2));
}

void parse_ids(char* file, unsigned long long size)
{
  char id_range[64] = {0};
  unsigned long long index = 0;
  for(unsigned long long i=0; i < size; i++)
    {
      //printf("%c\n", file[i]);
      if(file[i] != ',' && file[i] != '\n')
	{
	  id_range[index] = file[i];
	  index++;
	}
      else
	{
	  search_id_range(id_range, index);
	  memset(id_range, 0, sizeof(char)*64);
	  index = 0;
	}
    }
}


int main(int argc, char* argv[])
{
  int size = 256;
  char* file = malloc(sizeof(char)*size);
  
  FILE* f = fopen("input.txt", "r");
  char ch;
  int count = 0;
  unsigned long long index = 0;
  while((ch = fgetc(f)) != EOF)
    {
      file[index] = ch;
      index++;
      if(count == 255)
	{
	  size += 256;
	  file = realloc(file, sizeof(char)*size);
	  count = 0;
	}
      else
	count++;
    }

  file[index] = '\0';

  parse_ids(file, index);

  printf("%llu %d\n", sum, total_count);
    
  
  return 0;
}
