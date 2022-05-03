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
// Determines if we should print or not
enum Debug{On,Off};

// Play hot and cold from start to stop

int hotCold(int start,int end,int target,enum Debug details);

//code for the abs() function in stdlib
int absolute(int number);

//computes the average of the number of step in a range from a to b.
void average(int steps);

//guesses the next word
int nextGuess(int start,int end,int lastGuess);

//find the middle of the range
int middle(int start, int end);

//prints out the guess
void printGuess(int guess, enum Debug details);

//prints out the answer
void printAnswer(char* answer, enum Debug details);


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
    printf("Number of Questions Asked: %d\n",hotCold(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]),On));
    
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

//takes an integer n to compute the average number of question needed to ask from 1 to to 2^n,
//prints start,stop,average
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
      total += hotCold(1,powerValue,range,Off);
    }
    power++;
    printf("%d,%d,%d\n",1,powerValue,total/(powerValue+1));
  }
}

//takes an interger x and returns x if above 0, else return -1*(x)
int absolute(int number)
{
  if ( number >= 0 ) return number;
  else return ( -1 * number );
}

//accepts 3 integers, namely start, end and lastGuess, to guess the next word using a mathematical function, returns the next guess for the game
int nextGuess(int start,int end,int lastGuess)
{
  return start+end-lastGuess;
}

//accepts 2 interger, basically the start and the end of the range to return the middle of the range
int middle(int start, int end)
{
  return start + ((end-start)/2);
}

//accepts an integer and an enum to check if printing is on, returns nothing but prints the number guessed if detail is on
void printGuess(int guess, enum Debug details)
{
  if (details == On)printf("Guess of %d\n",guess);
}

//accepts a pointer to an array and an enum to check if printing is on, returns nothing but prints the answer if detail is on
void printAnswer(char* answer, enum Debug details)
{
  if (details == On)printf("Answer: %s\n",answer);
}

//takes 3 integer namely start stop and target and an enum to determine priniting of values 
//if current guess=previous guess (i.e only the first guess) it guesses the last term
//if c = targetNumber then it returns the count
//count is increased in each loop
int hotCold(int start,int end,int target,enum Debug details)
{
  int count = 0;
  for(int guess = start, lastGuess = start;; )
  {
    if (guess == lastGuess) // special condition for first iteration
    {
      printGuess(guess, details);
      printAnswer("cold",details);
      if(start == end) // if the first guess is already the end and hits bullseye
      {
        printAnswer("yes",details);
        return 1;
      }
      if (guess == target ) //if the first guess hits the bullseye
      {
        printAnswer("yes",details);
        return 1;
      }
      lastGuess = guess;
      guess = nextGuess(start,end,lastGuess);
      count++;
    }
    else if (guess == target) // special condtion for when guess ==target
    {
      printGuess(guess, details);// prints guess
      printAnswer("yes",details);// prints answer
      return count;
    }
    else if (start == end-1) // special condtion when range has only 2 numbers
    {
      lastGuess = guess; //lastGuess changed to currentGuess
      if (guess == start) // if guess == start not until it is deliberately changed in this very same fucntion
      {
        printAnswer("hot",details); // prints the answer
        guess = guess+1; //guess changed to guess+1 for next loop
      }
      else
      {
        guess = start;
        printGuess(guess, details);//prints the guess
      }
      count++; // count increased by 1
    }

    
    else if(absolute( target-guess ) >= absolute( target-lastGuess )) //condition for cold
    {
      printGuess(guess, details); //prints the guess
      printAnswer("cold",details); //prints the answer
      if (guess > lastGuess) // condition for range to become [start,middle]
      {
        end = middle(start,end);//end is changed for next loop
      }
      else if (guess <= lastGuess) //condition for range to become [middle,end]
      {
        start = middle(start,end);//start is changed for next loop
      }
      lastGuess = guess;//lastGuess changed to currentGuess
      guess = nextGuess(start,end,lastGuess);// currentGuess changed to lastGuess
      count++;// count increased by 1
    }
  
    else if ( absolute(target-guess) < absolute(target-lastGuess)) // condition for hot
    {
      printGuess(guess, details);
      printAnswer("hot",details); 
      if (guess > lastGuess) //condition for range to become [middle,end]
      {
        start = middle(start,end); //start is changed for next loop
      }
      else if (guess <= lastGuess) //condition for range to become [start,middle]
      {
        end = middle(start,end); //end is changed for next loop
      }
      lastGuess = guess; //lastGuess changed to currentGuess
      guess = nextGuess(start,end,lastGuess); // currentGuess changed to lastGuess
      count++; // count increased by 1
    }
  }
  return count;
}