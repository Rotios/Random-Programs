// This program analyzes the length of lines inputted
// by the user. The -r switch can be used to allow
// the user to check the min and max width.
// (c) 2015 Jose D. Rivas-Garcia

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Lets the user know how to use width correctly.
void Usage(){
  printf("Usage: width -r\n");
  printf("\t -r \t prints both min and max\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  int c;
  size_t min = 0, current = 0, max = 0;
  char rSwitch = 0;

  // Check to see that the switch for r is thrown in the first argument.
  if (argc > 1 && !strcmp(argv[1], "-r")) rSwitch = 1;
  else if (argc > 1) Usage();
  
  // Get each character one by one and count how many in each line.
  // '\t' causes the line to round to the nearest 8 and needs its own calculation.
  while (EOF != (c = fgetc(stdin))) {
    if (c == '\t') current = ((8 - (current % 8)) + current);
    else if(c != '\n') current++;

    // Once a line is finished, reset the max and minimum values as necessary.
    else{
      if (current > max) max = current;
      if (!min || current < min) min = current;
      current = 0;
    }
  }

  // We print max at all times, but min is only printed if the correct argument is given.
  if(rSwitch) printf("%zu %zu\n", min, max);
  else printf("%zu\n",max);

  return 0;
}

