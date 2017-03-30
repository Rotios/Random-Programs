public class Pangram {

    /**
     * Check if a string is a pangram
     */
    public static void main(String[] args) {
      String s = "";  
      for (int i = 0; i < args.length; i++)
	      	s += args[i];
		
		// Initiate state to check if all letters used
        int[] checkArray = new int[26];
        int count = 0;
		
		// Traverse the string
        for(int i = 0; i < s.length(); i++){
		
			// Take the current character, subtract the char value 'A' to center all letters at value 0.
			// Then mod 32 to get rid of the six characters between 'Z' and 'a'
			char curLetter =  (char) ((int) (s.charAt(i) - 'A') % 32);
		
			// Make sure it is a letter and check to see if it has been seen yet.
			if(curLetter >= 0 && curLetter <= 25){
              if(checkArray[curLetter] == 0) count++;
              checkArray[curLetter]++;
            }
        }
		
		// Check if a pangram. If count is 26, then all letters have been seen. Otherwise, there is at least
		// one letter that has not been seen.
        if(count == 26) {
            System.out.println("pangram");
		}
        else {
            System.out.println("not pangram");
		}
	}

}
