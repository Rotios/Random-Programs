// A program to encrypt data by rotating the alphabet.
// (c) 2015 Jose D. Rivas-Garcia

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// If rot is used incorrectly, let the user know how to use it.
void Usage(){
  printf("Usage: rot [INT]\n");
  exit(1);
}

int main(int argc, char *argv[])
{
  int c;
  
  // This will make sure that some argument is passed to rot
  // but will not catch characters that are not ints. The default
  // is set to rotate 0 if a character (like a or b) is passed.
  if(argc != 2) Usage();
  int n = atoi(argv[1]);
  
  // Since % can return a negative integer, this finds 
  // the positive value congruent to n mod 26
  if (n < 0) n = (n % 26) + 26;
  
  // Grab the characters from the input and rotate them
  // appropriately, which depends on their case.
  while (EOF != (c = fgetc(stdin))) {
    if ( islower(c) ) {
      c = (((c - 'a') + n) % 26) + 'a';
    } 
    else if ( isupper(c) ) {
      c = (((c - 'A') + n) % 26) + 'A';
    } 
    
    // Output the rotated character.
    fputc(c,stdout);
  } 
  
  return 0;
}
