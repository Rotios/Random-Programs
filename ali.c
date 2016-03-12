// A program that filters positive integers 
// based on their aliquot sum and certain filters
// inputted by the user as argument switches.
// (c) 2015 Jose D. Rivas-Garcia

#include <stdio.h>
#include <stdlib.h>

// In case an improper argument is attempted, let the user 
// know how to use the program.
void Usage(){
  // I split the print statements to make it look neater than having
  // 1 single long print statement.
  printf("Usage: ali -dpa1 \n");
  printf("\t -d \t deficient numbers \n");
  printf("\t -p \t perfect numbers \n");
  printf("\t -a \t abundant numbers \n"); 
  printf("\t -1 \t prime numbers \n");
  exit(1);
}

int ParseArgs(int argc, char **argv){
  char f = 0;
  char *arg;
  int i, c;
   
  // Using the number of arguments, check each argument for
  // switches and change f appropriately using bitwise or.
  for (i = 0; i < argc; i++){
    arg = argv[i];
    // This allows the program to ignore inputs that are not switches
    if (arg[0] == '-') {
      arg++;
      while((c = *arg)) {
	switch(c) {
	case 'd':
	  f = f | 1;
	  break;
	case 'p':
	  f = f | 2;
	  break;
	case 'a':
	  f = f | 4;
	  break;
	case '1':
	  f = f | 8;
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

int main (int argc, char **argv)
{
  // My initial values for the current number being streamed,
  // the iteration to check for factors, and the current
  // argument being checked, respectively.
  int n, i; 

  // Boolean for the 4 switches using bitwise operations on f.
  char f = ParseArgs(argc, argv);
  
  // Take the stream, scan each member into an integer, and
  // finds it's aliquot sum.
  while( scanf("%d", &n) != EOF ){  
    int aliSum = 0;
    for ( i = 1; i < (n/2 + 1); i++ ) if (!(n % i)) aliSum += i;
    
    // Print the number if and only if the correct switch is on 
    // and it meets the appropriate requirements.
    if ((f & 1) && (aliSum < n)) printf("%d\n", n);
    else if ((f & 2) && (aliSum == n)) printf("%d\n", n);
    else if ((f & 4) && (aliSum > n)) printf("%d\n", n);
    else if ((f & 8) && (aliSum == 1)) printf("%d\n", n);
  }
  
  return 0;
}
