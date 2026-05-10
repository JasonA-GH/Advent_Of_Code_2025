#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 137
#define COLS 137 // need to include \0

int sum = 0;

char lines[ROWS][COLS] = {0};

int get_neighbour_count(int i, int j)
{
  //Search row(p->x-1) at columns p->y +-1, +0, +1
  //then same on row p->x
  //then again on row p->x+1
  //make sure p->x +1 and -1 exist same with p->y +1 and -1

  int count = 0;
  int start_y = i-1;
  int end_y = i+1;
  int start_x = j-1;
  int end_x = j+1;
  if(i == 0)
    start_y = 0;
  else if(i == ROWS-1)
    {
      end_y = ROWS-1;
    }

  if(j == 0)
    start_x = 0;
  else if(j == COLS-1)
    end_x = COLS-1;
  
  for(int y=start_y; y <= end_y; y++)
    {
      for(int x = start_x; x <= end_x; x++)
	{
	  if(x == j && y == i)
	    continue;

	  //printf("%d %d %d %d\n", i, j, x ,y);

	  if(lines[y][x] == '@')
	    {
	      count++;
	    }
	}
    }
  return count;

}

void sum_neighbours()
{
  for(int i=0; i < ROWS; i++)
    {
      for(int j=0; j < COLS; j++)
	{
	  //printf("%d\n", strlen(lines[i]));
	  if(lines[i][j] == '@')
	    {
	      if(get_neighbour_count(i, j) < 4)
		{
		  //printf("%d %d %s\n", i, j, lines[i]);
		  sum++;
		}
	    }
	}
    }
}

int main(int argc, char* argv[])
{
  char line[512] = {0};

  int y = 0;
  while(fgets(line, sizeof(line), stdin) != NULL)
    {
      //printf("READ LINE: %s %d", line, strlen(line));
      line[strlen(line)-1] = '\0';//line includes '\n' so replace with terminator. Also first lines didn't have terminator
      //printf("%s %d\n", line, strlen(line));
      //printf("%d\n", line[COLS]);
      strncpy(lines[y], line, COLS+5);
      //printf("%s %s\n", lines[y], line);
      y++;
      
      //paper_size += strlen(line);
      //all_paper = realloc(all_paper, sizeof(*all_paper)*paper_size);
      //save_paper(line, strlen(line), y);
      //y++;
    }

  //printf("||||%s %d\n", lines[0], strlen(lines[0]));

  sum_neighbours();

  printf("%d\n", sum);
  
  //printf("%d %d %d\n", ind, all_paper[ind-1].x, all_paper[ind-1].y);

  
  return 0;
}
