// Tells you the phases of the moon given a date formatted month day year.
// The -a switch tells you the phase as a digit, instead of as its western description.
// (c) 2015 Jose D. Rivas-Garcia

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char day = 0;
char month = 0;
short year = 0;
char f = 0; 

char *phasemap[] = {"new","new","waxing crescent","waxing crescent","waxing crescent",
		   "waxing crescent","waxing crescent","first quarter","first quarter",
		   "waxing gibbous","waxing gibbous","waxing gibbous","waxing gibbous",
		   "waxing gibbous","full","full","full","waning gibbous","waning gibbous",
		   "waning gibbous","waning gibbous","waning gibbous","third quarter",
		   "third quarter","waning crescent","waning crescent","waning crescent",
		   "waning crescent","waning crescent","new"};

//If the user gives improper input, tell them how to use the program
void Usage(){
  printf("phoon (-a) month(int) day(int) year(int)\n");
  printf("month\tint between 1 and 12 inclusive\n");
  printf("day\tint between 1 and 31 inclusive\n");
  printf("year\tint between 1900 and 2099 inclusive\n");
  exit(1);
}

void ParseDate(int argc, char **argv){
  int i = 0;
  int g = 0;

  // If we do not have at least 4 arguments (name, day, month, year), then we cannot parse
  // the date correctly
  if (argc < 4) Usage();
  // If we have more than 4 arguments, we assume the first is -a, or else we quit the program
  if (argc > 4){
    if((f == 0) && !strcmp(argv[++i],"-a")) f = 1;
    else Usage();
  }

  // Go through each argument one by one and set the date
  if((g = atoi(argv[++i])) && (g>0 && g<13)) month = g;
  else Usage();
  if((g = atoi(argv[++i])) && (g>0 && g<31)) day = g;
  else Usage();
  if((g = atoi(argv[++i])) && (g>=1900 && g<2100)) year = g;
  else Usage();
} 

int main(int argc, char **argv)
{
  
  //Set the date
  ParseDate(argc,argv); 
  
  // Begin the initial calculations of s
  int s = day + month + 30;
  s -= (year >= 2000) ? 8 : 4;
  
  //Make year = yy (the last two digits of the year
  year -= (year >= 2000) ? 2000 : 1900;

  // Calculate the distance d to the closest multiple of 19 (m) as d = yy - m
  int m = ((year%19)>9) ? (year/19) + 1 : year/19;
  int d = year - m * 19;

  // Prepend a tens digit to d. % will give me a neg if d is neg so this will work
  // for both positive or negative numbers
  d = 10*(d % 3) + d;

  // s will always be greater than d, so this will always be a proper mod
  s = (d + s) % 30;

  // Print out either the phase name if no -a switch was used, or s if a -a switch was used
  if (!f) printf("%s\n", phasemap[s]);
  else printf("%d\n", s);

  return 0;
}
