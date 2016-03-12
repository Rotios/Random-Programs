// This program reverses characters and/or lines
// depending on which switch is thrown.
// (c) 2015 Jose D. Rivas-Garcia

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In case an improper argument is attempted, let the user 
// know how to use the program.
void Usage(){
  // I split the print statements to make it look neater than having
  // 1 single long print statement.
  printf("Usage: verse -cl \n");
  printf("\t -c \t reverse the characters \n");
  printf("\t -l \t reverse the lines \n");
  exit(1);
}

int ParseArgs(int argc, char **argv){
  char f = 0;
  char *arg;
  int i, c;
  
  //This automatically sets the program to reverse char, if no args are set
  if(argc < 2) f = f | 1;

  // Using the number of arguments, check each argument for
  // switches and change f appropriately using bitwise or.
  else for (i = 0; i < argc; i++){
    arg = argv[i];
    // This allows the program to ignore inputs that are not switches
    if (arg[0] == '-') {
      arg++;
      while((c = *arg)) {
	switch(c) {
	case 'c':
	  f = f | 1;
	  break;
	case 'l':
	  f = f | 2;
	  break;
	default:
	  Usage();
	}
	arg++;
      }
    }
  }
  return f;
}

// Exactly like revLn, but for characters in each line. A typical swap routine.
char *revChar (char *buff)
{
  char temp;
  int len = strlen(buff);

  char *left = buff;
  char *right = buff + len - 1;

  while (left < right){
    temp = left[0];
    left++[0] = right[0];
    right--[0] = temp;
  }
  return buff;
}

int main (int argc, char **argv)
{
  // Whether we should switch chars, lines, or both
  char f = ParseArgs(argc,argv);

  // Setting the temporary buffer for each separate line
  size_t pos = 0;
  size_t buffsize = 10;
  char *buff = (char *) malloc (buffsize * sizeof(char));

  // Setting the 2d buffer to hold all of the lines
  size_t curpos = 0;
  size_t curSize = 10;
  char **curr = (char **) malloc(curSize * sizeof(char *));  

  // Go through the input 1 char at a time
  char c;
  while ((c = fgetc(stdin)) != EOF){
    
    // change the size of buffer if the line is too long
    if((pos+1) >= buffsize) {
      buffsize *= 2;
      buff = (char *) realloc (buff, buffsize * sizeof(char));
    }

    if (c != '\n') buff[pos++] = c;
    else{
      // Mark the end of the buffer array
      buff[pos] = 0;

      // Change the size of the current array of lines if needed
      if ((curpos+1) >= curSize) {
	curSize *= 2;
	curr = (char **) realloc (curr, curSize * sizeof(char *));
      }
     
      // Either reverse the line, or keep it the same
      if (f & 1) curr[curpos++] = revChar(strdup(buff));
      else curr[curpos++] = strdup(buff);
      
      // Restart the buffer position
      pos = 0;
    }
  }
  
  // Add the end of array char to be sure we know where the end is
  // and free the buffer
  curr[curpos] = 0;
  free(buff);

  // If we need to, print the lines in reverse order
  if (f & 2) 
    while(curpos) 
      printf("%s\n", curr[--curpos]);
  // Print out the lines in regular order
  else 
    for(pos = 0; pos < curpos; pos++)
      printf("%s\n", curr[pos]);
  
  free(curr);
  return 0;
}
