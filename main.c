/*
  *
  *
  *
  * Name: Satwik Shresth
  * Date: 4/3/2022
  * 
  * The code use recursion to play the game hot&cold and count the number of time it repeats itself and returns the value for the same
  * 
  * 
  * 
  *
  *
  *
  *
  */
  
  
  
#include <stdio.h>
#include <stdlib.h>

enum Debug{On,Off};

/*This function is modified version of Binary Search algorithms thats plays the game hot & cold to return the number of guesses*/
int hotCold(int start,int end,int magic,int guess,int lastGuess,enum Debug details);

//code for the abs() function in stdlib
int absolute(int number);

//computes the average of the number of step in a range from a to b.
void average(int steps);

int nextGuess(int start,int stop,int prevguess);

int main( int argc, char **argv )
{
  if( argc == 4 ) 
	{
    if(atoi(argv[1])>atoi(argv[2]))
    {
      printf( "Invalid inputs.\n" ) ; //prints an error
      return 0;
    }
    else if (atoi(argv[3]) < atoi(argv[1]) || atoi(argv[1]) > atoi(argv[2]))
    {
      printf( "Invalid inputs.\n" ) ; //prints an error
      return 0;
    }
    printf("Simulating Gussing Number from %d to %d.\n",atoi(argv[1]),atoi(argv[2]));
    printf("Secret Number is %d.\n",atoi(argv[3]));
    printf("Number of Questions Asked: %d\n",hotCold(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),atoi(argv[1]),atoi(argv[1]),On));
    
	}
  else if( argc == 2 ) 
	{
    printf("Start,Stop,Average\n");
    average(atoi(argv[1]));
	}
  else
  {
    printf( "Invalid number of inputs.\n" ) ; //prints error
		return 0;
  }
}


void average(int steps)
{
  int power = 2;
  int powerValue;
  while ( power <= steps )
  {
    powerValue = 1 << power; // powerValue = 1 * (2^power)
    int total = 0;                   
    for (int range = 1;range <= powerValue;range++)
    {
      total += hotCold(1,powerValue,range,1,1,Off);
    }
    power++;
    printf("%d,%d,%d\n",1,powerValue,total/(powerValue+1));
  }
}

//returns x if above 0, else return -1(x)
int absolute(int number)
{
  if ( number >= 0 ) return number;
  else return ( -1 * number );
}

int nextGuess (int start,int stop,int prevGuess)
{
  
}

//use recusion to print each step and pivot the search
//if c=p (i.e only the first guess) it guesses the last term
//if c = magicNumber then it return the count
//count is increased in each search
//if 
int hotCold(int start,int end,int magic,int guess,int lastGuess,enum Debug details)
{
  int middle = start + ((end-start)/2);
  int nextGuess;

  if (guess == lastGuess)
  {
    if (details == On)printf("Guess of %d\n",guess);
    if(start == end)
    {
      if (details == On)printf("Answer: yes\n");
      return 1;
    }
    if (details == On)printf("Answer: cold\n");
    return 1 + hotCold(start,end,magic,end,start,details);
  }
  if (guess == magic)
  {
    if (details == On)printf("Guess of %d\n",guess);
    if (details == On)printf("Answer: yes\n");
    return 0;
  }
  else if (start == end-1)
  {
    
    if (guess == start)
    {
      if (details == On)printf("Guess of %d\n",guess);
      if (details == On)printf("Answer: hot\n");
      nextGuess = guess+1;
    }
    else
    {
      nextGuess = start;
    }
    return 1 + hotCold(start,end,magic,nextGuess,guess,details);
  }

    
  else if(absolute( magic-guess ) >= absolute( magic-lastGuess )) //cold
  {
    if (details == On)printf("Guess of %d\n",guess);
    if (details == On)printf("Answer: cold\n");
    if (guess > lastGuess) //[start,middle]
    {
      nextGuess = (start + middle) - guess ; // a+b-p
      return 1 + hotCold(start,middle,magic,nextGuess,guess,details);
    }
    else if (guess <= lastGuess) //[middle,end]
    {
      nextGuess = (middle + end) - guess ;
      return 1 + hotCold(middle,end,magic,nextGuess,guess,details);
    }
  }
  
  else if ( absolute(magic-guess) < absolute(magic-lastGuess))
  {
    if (details == On)printf("Guess of %d\n",guess);
    if (details == On)printf("Answer: hot\n"); 
    if (guess > lastGuess) //[middle,end]
    {
      nextGuess = (end + middle) - guess ;
      return 1 + hotCold(middle,end,magic,nextGuess,guess,details);
    }
    else if (guess <= lastGuess) //[start,middle]
    {
      nextGuess = (middle + start) - guess ;
      return 1 + hotCold(start,middle,magic,nextGuess,guess,details);
    }
  }
}