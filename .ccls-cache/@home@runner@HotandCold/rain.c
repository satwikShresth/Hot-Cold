#include <stdio.h>
#include <stdlib.h>



int func(int br)
{
  int *ptr = 5;
  printf("%d",*ptr);
  
}

int main()
{
  int *ptr;
  *ptr = 5;
  func(0);
}