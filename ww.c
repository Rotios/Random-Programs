// This program reports duplicate adjacent words in text. 
// A word is a string of alphabetic characters, delimited 
// by non-alphabetic characters of file boundaries. 
// This program returns 1 if a pair is found.
// (c) 2015 Jose Rivas-Garcia

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Settings for the buffer to hold the next word
static size_t curpos = 0;
static size_t curSize = 10;

// The current line number for a given file (name) and
// the current character in that file being read
static size_t lineNum;
static char *name;
static char c;

// To be returned by the main method. Is 1 only if a pair is found.
static char pairFound = 0;

void Usage()
{
  printf("Cannot open file \"%s\". The program will not exit.\n", name);
  printf("Usage:\tww [File1 File2 ... FileN]\n");
  printf("Any number of files can be used. Please check for correct extensions.\n");
  printf("If no file is specified, stdin is used instead.\n");
  exit(1);
}

// Get the next word
char *getNextWord(FILE *fp)
{
  // Allocate memory for the word
  char *currWord = (char *) malloc(curSize * sizeof(char *));

  // if we have reached a new line, add 1 to lineNum
  if(c == '\n') lineNum++;
  
  // Loop through the beginning to get rid of any non alpha characters
  while(((c = fgetc(fp)) != EOF) && !isalpha(c))  
    // if we have reached a new line, add 1 to lineNum
    if(c == '\n') lineNum++;
    else;
  
  // If the current character is a letter
  while(isalpha(c)){

    // Reallocate memory for the word when necessary
    if ((curpos+1) >= curSize) {
      curSize *= 2;
      currWord = (char *) realloc (currWord, curSize * sizeof(char));
    }
    
    // add the current character to curWord and get the next character
    currWord[curpos++] = c;
    c = fgetc(fp);
  }

  // Set the end of currWord and reset curpos for later use
  currWord[curpos] = 0;
  curpos = 0;
  
  return currWord;
  
}

// Parse each file one at a time
void ParseFile(FILE *fp)
{
  // Get the first word
  char *prevWord = (char *) getNextWord(fp);
  char *currWord;
  
  // Saves the line of the current word
  size_t prevLine = lineNum;

  // So long as c has not reached the end of the file
  // Go through the loop again by fetching the next word
  while( c != EOF ){
    currWord = getNextWord(fp);
    
    // If the words match, then set pairFound = 1 and print out the pair
    if(!strcasecmp(currWord,prevWord)) {
      printf("%s:%zu:%s\n",name,prevLine,prevWord);
      pairFound = 1;
    }
    
    // Saves the line of the current word 
    prevLine = lineNum;
    // Reset the loop with the current word becoming the previous word
    prevWord = currWord;
  }

  // Close the file when done
  fclose(fp);
}

// Opens each file one at a time to parse in helper method below
void ParseAllFiles(int argc, char **argv)
{
  int i;

  // While there are still files to parse
  // remember the file name, open the file and parse through it
  for(i = 1; i < argc; i++){
    lineNum = 1;
    name = argv[i];
    FILE *file = fopen(argv[i],"r");
    
    if (file == NULL) Usage();

    ParseFile(file);
  }
}


int main (int argc, char **argv)
{
  // If we have more than 1 arguments (more than just the name in argv),
  // Then assume that we have files to parse through. Otherwise, parse
  // From standard input (stdin).
  if (argc > 1) ParseAllFiles(argc, argv);
  else{
      name = "stdin";
      ParseFile(stdin);
  }
  return pairFound;
}
