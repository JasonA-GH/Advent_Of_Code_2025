#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SIZE 12

unsigned long long sum = 0;

int to_int(char a)
{
  return a-'0';
}

unsigned long long get_num(char* nums)
{
  return atoll(nums);
}

void to_chars(int* inds, char line[], char* nums)
{
  //char* nums = malloc(sizeof(*nums)*NUM_SIZE);
  for(int i=0; i < NUM_SIZE; i++)
    {
      nums[i] = line[inds[i]];
    }
}

int get_largest_from_dist(char line[], int size, int start, int dist_from_end)
{
  int ten = 0;
  int index = 0;
  //printf("%d %d %d\n", start, (size-2)-dist_from_end, dist_from_end);
  //printf("%d %d ", (size-2)-dist_from_end, start);
  for(int i=(size-2)-dist_from_end; i >= start; i--)
    {
      int num = line[i]-'0';
      //printf("%d %d\n", num, i);
      if(num >= ten) //>= to ensure the furthest number from the end. Otherwise it would take the first instance of the highest number, blocking it off from the rest
	{
	  ten = num;
	  index = i;
	}
    }
  //printf("%c %d\n", line[index], index);
  return index;
}

void print_inds(int* inds)
{
  for(int i=0; i < NUM_SIZE; i++)
    {
      printf("%d ", inds[i]);
    }
  printf("\n");
}

void get_inds(char line[], int size, int* inds)
{

  //search for largest num atleast 11 from the end
  //then next largest at least 10 from the end and so on...

  int index = 1;
  int dist = 10;

  inds[0] = get_largest_from_dist(line, size, 0, 11);
  
  while(index < 12)
    {
      //print_inds(inds);
      //printf("%d %d %d\n", size, inds[index-1]+1, dist);
      inds[index] = get_largest_from_dist(line, size, inds[index-1]+1, dist);
      index++;
      dist--;
    }
  //print_inds(inds);
}

int main(int argc, char* argv[])
{

  char line[512];
  int* inds = malloc(sizeof(int)*NUM_SIZE);
  char* nums = malloc(sizeof(char)*NUM_SIZE+1);
  while(fgets(line, sizeof(line), stdin) != NULL)
    {
      //read_line(line, strlen(line));
      for(int i=0; i < NUM_SIZE; i++)
	{
	  inds[i] = -1;
	}
      memset(nums, '\0', sizeof(char)*NUM_SIZE+1);
      
      get_inds(line, strlen(line), inds);
      to_chars(inds, line, nums);
      
      printf("Nums(post_chars) : %s\n", nums);
      
      unsigned long long num = get_num(nums);
      
      printf("Num(post_get_num): %llu\n", num);
      
      sum += num;
    }

  printf("Sum: %llu\n", sum);
  
  return 0;
}
