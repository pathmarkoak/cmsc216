/* Honor Pledge: I pledge on my honor that I have not given
   or received any unauthorized assitance on this examination
   or assginment. 

   Name: Omkar Pathak
   TerpConnect login ID: omkarp07
   University ID number: 119272961
   Discussion Section Number: 0106
   
   The purpose of this program is to check whether or not 
   any lines in its input have length greater than 80 characters. 
   This program takes in a file containing no more than 99999 
   lines that each have no more than 999 characters. 
   This program utilizes an array to store individual
   characters in lines and, after each line is read, 
   prints out the characters in the line. If the line contains
   more than 80 characters, a secondary line is printed with 
   carets under every character after the 80th character.
   This program will be useful to test style for 
   future projects, and contains only one main 
   function.
 */

#include <stdio.h> 

/* Main function--only function in this program*/
int main(void) {

  /* Declaring (and instantiating some) variables */
  char ch;
  char arr[1001];
  int length = 0;
  int size = 0;
  int number = 0;

  /* Integer variables to be used in for loops */
  int i; 
  int j; 
  int k;

  /* Scanning first part of line before loop */
  scanf("%c", &ch);

  /* Looping until end of input*/
  while (!feof(stdin)) {

    /* Line number */
    number++;

    /* Inner loop until end of line is reached */
    while (ch != '\n') {

      /* Special case for tab characters */
      if (ch == '\t') {
	/* Modifying length with tab character length */
	length = length + (8 - (length % 8));

      /* If character is not a tab, length incremented normally */
      } else {
	length++;
      }

      /* Assigning line character to array and incrementing size */
      arr[size] = ch;
      size++;

      /* Scanning next character in line */
      scanf("%c", &ch);
    }

    /* Assigning newilne character to last new array in an array */
    arr[size] = '\n';
    
    /* Handling case where line length is less than 80 */
    if (length <= 80) {
	printf(" "); 
      } else {
      /* If length is greater than 80, a * is printed */
	printf("*");  
      }
      /* Printing line number and colon */
      printf("%5d", number); 
      printf(": ");

      /* Printing out every character in array */
      for (i = 0; i < size; i++) {
	printf("%c", arr[i]);
      }

    /* If the length is greater than 80, the new line with carets is printed */
    if (length > 80) {
      printf("\n");
      for (j = 1; j <= 88; j++) {
        printf(" "); 
      }
      /* Printing out carets under chracters past 80 */
      for (k = 1; k <= length-80; k++) {
	printf("^");
      }
    }
    
    /* Printing new line, and resetting length and size variables */
    printf("\n");
    length = 0;
    size = 0;

    /* Scanning next character */
    scanf("%c", &ch);
  } 
  return 0;
}

