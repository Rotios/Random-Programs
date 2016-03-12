// An interpreter for a small language called Brainfuse.
// (c) 2015 Jose Rivas-Garcia

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Settings for the buffer to hold the instructions and data
static size_t pos = 0;
static size_t buffSize = 10;

static char c;

static size_t datSize = 30000;
static size_t datPos = 0;

// If something is wrong with how the program is used, then exit here
void Usage()
{
  printf("Usage:\tbfz char*[brainfuze program]\n");
  printf("\t This program interprets any brainfuze program given to it as a string parameter.\n");
  exit(1);
}

// Go through each instruction step by step.
void interpretInstructions(char *inst)
{
  size_t temp;

  // While we have not reached the fuze, read the character and perform the appropriate action
  while(inst[pos])
    {  
      switch(inst[pos])
	{
	  // for ',', read in a character, and if not EOF then place it in data
	case (','):
	  if( (c = fgetc(stdin)) != EOF ) inst[datPos] = c;
	  break;
	  
	  // for '.', print out whatever character is in data at the current data counter
	case ('.'):
	  printf("%c",inst[datPos]);
	  break;
	  
	  // move the data counter right by 1 (add 1 to it)
	case('>'):
	  datPos++;
	  if((datPos + 1)  > buffSize)
	    {
	      buffSize *=2;
	      inst = realloc(inst,buffSize * sizeof(char));
	    }
	  break;
	  
	  // move the data counter left by 1 (subtract 1 from it)
	case('<'):
	  datPos--;
	  break;
	  
	  // add 1 to the data at the current data position
	case('+'):
	  inst[datPos] = inst[datPos] + 1;
	  break;
	  
	  // subtract 1 from the data at the current data position
	case('-'):
	  inst[datPos] = inst[datPos] - 1;
	  break;
	  

	  // If the current data is 0, then find the appropriate ']' later in the code
	case('['):

	  // how many '[' have been seen, counting this one
	  temp = 1;
	  
	  if (!(inst[datPos]))
	    {
	      pos++;
 
	      // Each time we see a '[' add 1, but subtract 1 if we see a ']'.
	      // By doing this, when temp = 0, then we have found the appropriate
	      // ']' to pair with the '[' we are current on in the instruction.
	      // Howevever, if we hit the fuze, then we know no such ']' exists.
	      while(temp)
		{
		  if(inst[pos] == '[') temp++;
		  else if(inst[pos] == ']') temp--;
		  else if (inst[pos] == 0)
		    {
		      printf("No matching \"]\" found.\n");
		      Usage();
		    }
		  pos++;
		}
	    }
	  break;
	  
	  // This code is similar to the one above, but it traverses backwards if
	  // the current data is not a 0 to look for the matching '['.
	case(']'):
	  temp = 1;
	  if (inst[datPos])
	    {
	      pos--;
	      while(temp)
		{	
		  if(inst[pos] == ']') temp++;
		  else if(inst[pos] == '[') temp--;
		  else if(pos == 0)
		    {
		      printf("No matching \"]\" found.");
		      Usage();
		    }
		  pos--;
		}
	    }
	  break;
	}
      // at all times we add 1 to the instruction position counter
      pos++;
    }
}

// Place the instructions in an array with enough space for data 
char *getInstructions(char *inst)
{
  // The fuze will be at the end (the length) of the instruction array
  size_t len = strlen(inst);

  // create a buffer with enough space to hold 30,000 bytes of data
  buffSize = len + datSize;
  char *buff = (char *) calloc (buffSize, sizeof(char));

  // copy the instructions into the buffer
  strcpy(buff, inst);
  
  // the position of the data pointer is one ahead of the fuze
  datPos = len + 1;

  return buff;
}

// This simply takes the instructions, finds where the fuze is
// and then traverses through the intstructions to interpret them.
// If no brainfuze program is given, then exit through Usage().
int main(int argc, char **argv)
{
  if(argc > 1)
    {
      char *inst = getInstructions(argv[1]);
      interpretInstructions(inst);
    }
  else Usage();
  return 0;
}
