#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dial = 50;
int zero_count = 0;

void move_dial(char d[])
{
  int dir = 1;
  if(d[0] == 'L')
    dir = -1;

  char num[10];

  strncpy(num, d+1, 10);
  num[10] = '\0';

  int amount = atoi(num);

  int dial_start = dial;

  //printf("|%s| |%s| %d\n", d, num, amount);

  //printf("Start %d ", dial);
  int zero_change = 0;
  int zero_over = 0;
  
  dial += dir*amount;
  if(amount > 100)
    zero_over += abs(amount/100);
  //printf("%d\n", -1000/100);
  
  //printf("dir*amount %d ", dial);

  //int zero_over = abs(amount/100)-1;
  dial = dial%100;
  if(dial_start != 0)
    {
      if((amount%100)*dir+dial_start > 100 ||
	 (amount%100)*dir+dial_start < 0)
	zero_change++;
    }
  //if(dir == 1 && dial_start > dial)
  // zero_count++;
  //printf("dialmod100 %d\n", dial);
  if(dial < 0)
    {
      dial = abs(dial);
      dial = 100-dial;
    }

  //if(abs(dial+dial_start) > 100)
  //zero_change++;

  //printf("dial abs %d\n", dial);

  zero_count += zero_over + zero_change;

  //printf("PRE  %d %d %d\n", dial, amount, oldDial);

  //printf("DIAL %d %d\n", dial, dial%100);

  //if(dial >= 100 || dial < 0)
  //printf("OUT OF RANGE %d\n", dial);
  //else
  //printf("\n");
  
  if(dial == 0)
    zero_count++;

  /*if(zero_change > 0 && zero_over > 0)
    printf("---------------------");
  if(dial_start == 0 && (zero_change > 0))
    printf("0000000000000000000000000000000000000");
  if(dial == 0 && (zero_change > 0))
  printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");*/

  if(dial == 0)
  printf("dial_start: %d dial: %d amount: %d dir: %d zero_change: %d zero_over: %d zero_count: %d\n", dial_start, dial, amount, dir, zero_change, zero_over, zero_count);
  
  /*if(dial < 0)
    {
      int new_dial = (dial%100);
      //printf("%d %d %d\n", dial, new_dial, new_dial+100);
      if(new_dial != 0)
	dial = new_dial+100;
      else
	dial = 0;
      //printf("%d %d\n", dial, new_dial);
    }
  else if(dial > 99)
    {
      dial = dial%100;
    }
  else
    {
      zero_count++;
      }*/

  //printf("POST %d\n", dial);
}

int main(int argc, char* argv[])
{
  char line[512];
  while(fgets(line, sizeof(line), stdin) != NULL)
    {
      move_dial(line);
      if(dial >= 100 || dial < 0)
	printf("OUT OF RANGE %s %d\n", line, dial);
      //printf("%d\n", dial);
    }
  printf("%d\n", zero_count);
  
  return 0;
}
