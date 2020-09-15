#include <iostream>
#include "Problem1.h"
#include "Problem2.h"
#include "Problem3.h"
using namespace std;

int main()
{
    int choice;
    while (true)
    {
      printf("1-  Problem 1\n");
      printf("2-  Problem 2\n");
      printf("3-  Problem 3\n");
      printf("4-  Exit\n");
      printf("Please enter the respective number:");
      scanf("%d" , &choice);
      printf("---------------------------------------------------------\n");
      switch(choice)
      {
          case(1) : Part1();break;
          case(2) : Part2();break;
          case(3) : Part3();break;
          case(4) : exit(1);
          default : printf("Please enter a number from 1 to 4...\n");
      }
      printf("---------------------------------------------------------\n");
    }
    return 0;
}
