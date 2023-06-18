/* Honor Pledge: I pledge on my honor that I have 
   not given or received any unauthorized assistance
   on this examination or assignment. 
   
   Name: Omkar Pathak
   TerpConnect login ID: omkarp07
   University ID number: 119272961
   Discussion Section Number: 0206
   
   The purpose of this program is to output the
   line numbers in a file that have length greater
   than 80. This program takes in input from 
   the program lengthwarning.c, which tracks
   which lines in its input have length 
   greater than 80. If a particular line 
   has length greater than 80, its line 
   number is printed as output. This 
   program will be useful to test style 
   for future projects in conjunction 
   with lengthwarning.c.
 */

#include <stdio.h> 

/* Main function--only function in this program*/
int main(void) {

  /* Declaring (and instantiating one) variables */
  char ch;
  int count = 0;

  /* Scanning first part of line before loop */
  scanf("%c", &ch); 

  /* Looping until end of input */
  while (!feof(stdin)) {

    /* If the line starts with a blank space
       the line is skipped and the end of the 
       line is scanned */
    if (ch == ' ') {
      
      /* Scanning until the end of 
	 the line that does not 
	 go over 80 characters */
      while (ch != '\n') {
	scanf("%c", &ch);
      }
     
      /* If the line does go over 
	 80 characters, a blank space is 
	 printed if it is not the first line 
	 to go over 80 characters in order 
	 to print its number next to the 
	 previous number */ 
    } else {
      if (count >= 1) {
	printf(" ");
      }
 
      /* Incrementing count to signify another
	 line over 80 characters has been found */
      count++;

      /* Scanning next character in line to 
	   reach its number */
      scanf("%c", &ch); 
  
      /* Looping until line number is reached */
      while (ch == ' ') {
	scanf("%c", &ch); 
      }
      
      /* After loop is exited, the number of the 
	 line is printed */
      printf("%c", ch);
      
      /* Looping until the end of the line after its
	 number has been printed */
      while (ch != '\n') {
	scanf("%c", &ch);
      }
    }

    /* Scanning next character */
    scanf("%c", &ch);
  }
  
  /* Printing blank line at the end of program */
  printf("\n");

  return 0;
}