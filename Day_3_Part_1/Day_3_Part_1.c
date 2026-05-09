#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum = 0;

int get_num(char a, char b)
{
  char num[3] = {0};
  num[0] = a;
  num[1] = b;
  num[2] = '\0';

  return atoi(num);
}

int get_largest(char line[], int size)
{
  int ten = 0;
  int index = 0;
  //printf("%s ", line);
  for(int i=0; i < size; i++)
    {
      int num = line[i]-'0';
      //printf("%d\n", num);
      if(num > ten)
	{
	  ten = num;
	  index = i;
	}
    }
  return index;
}

int get_largest_from_to(char line[], int start, int end)
{
  int ten = 0;
  int index = 0;
  //printf("%s ", line);
  for(int i=start; i < end; i++)
    {
      int num = line[i]-'0';
      //printf("%d\n", num);
      if(num > ten)
	{
	  ten = num;
	  index = i;
	}
    }
  return index;
}

void read_line(char line[], int size)
{

  int num_index = get_largest(line, size);
  
  //printf("Before: %d %d\n", num_index, size);
  
  if(num_index == size-2)
    num_index = get_largest_from_to(line, 0, num_index);

  //printf("After: %d\n", num_index);
  
  int largest = 0;
  int second_index = 0;
  for(int i=num_index+1; i < size; i++)
    {
      int curr_num = get_num(line[num_index], line[i]);
      if(curr_num > largest)
	{
	  largest = curr_num;
	  second_index = i;
	}
    }

  //printf("%d Found at %d and %d\n", largest, num_index, second_index);
  if(num_index == second_index)
    printf("FAILED\n");
  sum += largest;
}

int main(int argc, char* argv[])
{

  char line[512];
  while(fgets(line, sizeof(line), stdin) != NULL)
    {
      read_line(line, strlen(line));
    }

  printf("%d\n", sum);
  
  return 0;
}
