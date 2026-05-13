#include <stdio.h>
#include <stdlib.h>
#include <string.h>



unsigned long long sum = 0;

unsigned long long fresh_numbers[1000] = {0};
unsigned long long fresh_size = 10;
unsigned long long ind = 0;

int done[1000] = {-1};
//int count = 0;

//15-22
//16
//17

void check_range(unsigned long long a, unsigned long long b)
{
  //fresh_size += b-a;
  //printf("%llu %llu | ", a, b);
  //count++;
  for(int i=0; i < 1000; i++)
    {
      int skip = 0;
      //count = 0;
      for(int j=0; j < 1000; j++)
	{
	  if(done[j] == -1)
	    break;
	  if(done[j] == i)
	    {
	      skip = 1;
	      break;
	    }
	}
      if(skip)
	{
	  //printf("skipping %llu\n", i);
	  continue;
	}
      if(fresh_numbers[i] >= a && fresh_numbers[i] <= b)
	{
	  printf("%llu %llu | %llu %d %d\n", a, b, fresh_numbers[i], i, ind);
	  done[ind] = i;
	  ind++;
	  sum++;
	  //break;
	}
    }
  //printf("%d\n", ind);
  //for(int j=0; j < 1000; j++)
  //printf("%llu\n", done[j]);
  //printf("%d\n", count);
  
  //fresh_numbers = realloc(fresh_numbers, sizeof(unsigned long long)*fresh_size);

  //printf("%llu %llu %llu\n", a, b, sizeof(unsigned long long)*fresh_size);
  
  /*for(unsigned long long i=a; i <= b; i++)
    {
      printf("%llu\n", ind);
      fresh_numbers[ind] = i;
      ind++;
      }*/


  //Get numbers then check if number falls in range instead of saving array
}

void test_food(char num[], unsigned long long size)
{
  unsigned long long f = atoll(num);
  printf("%llu\n", f);

  for(unsigned long long i=0; i < fresh_size; i++)
    {
      if(fresh_numbers[i] == f)
	sum++;
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
  int range_mode = 0;
  for(unsigned long long i=0; i < size; i++)
    {
      //printf("%c\n", file[i]);
      if(file[i] == '@')
	{
	  range_mode = 1;
	  index = 0;
	  ind = 0;
	  i++;
	  continue;
	}
      if(range_mode)
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
      else
	{
	  if(file[i] != '\n')
	    {
	      id_range[index] = file[i];
	      index++;
	    }
	  else
	    {
	      //printf("Got %s %d\n", id_range, ind);
	      fresh_numbers[ind] = atoll(id_range);
	      ind++;
	      //test_food(id_range, index);
	      memset(id_range, 0, sizeof(char)*64);
	      index = 0;
	    }
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

  for(int j=0; j < 1000; j++)
    {
      done[j] = -1;
    }
  
  //fresh_numbers = malloc(sizeof(unsigned long long)*1000);
  
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
  
  //parse_ids(file, index);
  printf("%llu\n", sum);
    
  
  return 0;
}
