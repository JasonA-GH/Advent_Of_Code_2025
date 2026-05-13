#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long sum = 0;

typedef struct group_struct
{
  unsigned long long lowest;
  unsigned long long highest;
}Group;

typedef struct combined_struct
{
  int a;
  int b;
}Combined;

Group groups[180];
int group_index = 0;


void check_range(unsigned long long a, unsigned long long b)
{
  
  
  int found = 0;
  for(int i=0; i < group_index; i++)
    {
      if((a <= groups[i].lowest && b >= groups[i].lowest) ||
	 (a <= groups[i].highest && b >= groups[i].highest))
	{
	  //printf("%llu %llu is an extension of group %d (%llu %llu)\n", a, b, i, groups[i].lowest, groups[i].highest);
	  if(a <= groups[i].lowest)
	    {
	      groups[i].lowest = a;
	    }
	  if(b >= groups[i].highest)
	    groups[i].highest = b;
	  found = 1;
	  break;
	}
    }
  if(!found)
    {
      groups[group_index].lowest = a;
      groups[group_index].highest = b;
      group_index++;
    }
  
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

void split_file(char* file, unsigned long long size)
{
  char id_range[64] = {0};
  unsigned long long index = 0;
  for(unsigned long long i=0; i < size; i++)
    {
      if(file[i] != '\n')
	{
	  id_range[index] = file[i];
	  index++;
	}
      else
	{
	  //printf("Searching... %s %d\n", id_range, strlen(id_range));
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
  
  //fresh_numbers = malloc(sizeof(unsigned long long)*1000);

  for(int i=0; i < 180; i++)
    {
      groups[i].lowest = -1;
      groups[i].highest = 0;
    }
  
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

  split_file(file, index);

  printf("Total Groups: %d\n", group_index);

  int found = 1;
  while(found)
    {
      found = 0;
      for(int i=0; i < group_index; i++)
	{
	  for(int j=0; j < group_index; j++)
	    {
	      if(i == j || groups[j].lowest == 0 || groups[j].highest == 0)
		continue;
	      if((groups[j].lowest <= groups[i].lowest && groups[j].highest >= groups[i].lowest) ||
		 (groups[j].lowest <= groups[i].highest && groups[j].highest >= groups[i].highest))
		{
		  //printf("%llu %llu is an extension of group %d (%llu %llu)\n", a, b, i, groups[i].lowest, groups[i].highest);
		  printf("(Group %d) %llu %llu combined with (Group %d) %llu %llu\n", i, groups[i].lowest, groups[i].highest, j, groups[j].lowest, groups[j].highest);
		  if(groups[j].lowest < groups[i].lowest)
		    {
		      groups[i].lowest = groups[j].lowest;
		    }
		  if(groups[j].highest > groups[i].highest)
		    groups[i].highest = groups[j].highest;
		  found = 1;
		  groups[j].lowest = 0;
		  groups[j].highest = 0;
		}
	    }
	}
    }
 
  for(int i=0; i < group_index; i++)
    {
      if(groups[i].lowest != 0)
	{
	  printf("Group: %d %llu %llu\n", i, groups[i].lowest, groups[i].highest);
	  sum += (groups[i].highest - groups[i].lowest)+1;
	}
    }
  
  //printf("%llu %llu\n", lowest, highest);
  
  //parse_ids(file, index);
  printf("%llu\n", sum);
    
  
  return 0;
}
