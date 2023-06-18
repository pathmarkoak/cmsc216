/* Honor Pledge: I pledge on my honor that I have not given
   or received any unauthorized assitance on this examination
   or assginment.

   Name: Omkar Pathak
   TerpConnect login ID: omkarp07
   University ID number: 119272961
   Discussion Section Number: 0106

   The purpose of this program is to do some operations with the MAD Raisin
   CPU. This source file contains three functions that will be called during
   testing. In addition, this file contains an auxiliary function (as well
   as its prototype) that is used to abstract away certain repetitive parts
   of function. The three functions are used to print an instruction,
   load an instruction into the MAD Raisin, and disassemble an instruction
   based on a given set of instructions. These functions depend on the
   validity of the instruction and parameters passed in.
*/

#include "raisin.h"
#include <stdio.h>

/* Auxiliary function prototype */
static unsigned short instruction_valid(unsigned int instruction);

/* Auxiliary function instruction_valid takes an instruction as a parameter
    and is used to check whether the instruction passed in is a valid
    MAD raisin instruction or not. This function does not modify the
    instruction in any way and returns 1 if the instruction is valid and
    0 if it is not valid. */
static unsigned short instruction_valid(unsigned int instruction) {

    /* Variables representing the different parts of the instruction */
    int opcode_value, register_1, register_2, addr;

    /* Variable representing the return value of the function */
    int return_val = 0;

    /* Using bit manipulation and bit masking to extract the relevant parts
        of the instruction to */
    opcode_value = instruction >> 27;
    register_1 = (instruction >> 22) & ~(~(0 << 4) << 5);
    register_2 = (instruction >> 17) & ~(~(0 << 10) << 5);

    /* If opcode_value represents a branch, instruction is shifted by 17 bits
       bits to obtain addr */
    if (opcode_value == 21) {
        addr = (instruction & (0377777));
    } else {
        addr = (instruction & (0177777));
    }

    /* Checking the below checks are only executed if the opcode_value is
       below 21 */
    if (opcode_value <= 21) {

        /* Return value is initially set to 1 */
        return_val = 1;

        /* Checking register values are not invalid if the instruction */
        /* uses both registers; return_val modified accordingly */
        if ((opcode_value >= 2 && opcode_value <= 8) ||
            (opcode_value >= 11 && opcode_value <= 17)) {
            if (register_1 > 17 || register_2 > 17 || register_1 == 16 ||
                register_1 == 17) {
                return_val = 0;
            }
        }

        /* If the instruction doesn't use the second */
        if ((opcode_value >= 9 && opcode_value <= 10) ||
            (opcode_value >= 18 && opcode_value <= 20)) {
            if (register_1 > 17 || register_1 == 16 || register_1 == 17) {
                return_val = 0;
            }
        }

        /* Checking if address is valid (divisible by 4) */
        if (opcode_value == 18 || opcode_value == 19 || opcode_value == 21) {
            if ((addr % 4) != 0) {
                return_val = 0;
            }
        }
    }
    return return_val;
}

/* print_instruction takes an instruction as a parameter and returns
    whether or not the instruction was successfully able to be printed
    based on whether it was a valid instruction or not. This method does
    not modify the instruction argument in any way. */
unsigned short print_instruction(unsigned int instruction) {

    /* Variables representing the different parts of the instruction */
    int opcode_value, register_1, register_2, addr;

    /* Calling auxiliary function and setting it as the return value; if the
       instruction is invalid, the return value will be set to 0; otherwise,
       it will be set to 1 */
    unsigned short return_val = instruction_valid(instruction);

    /* Using bit manipulation and bit masking to extract the different
       parts of instruction */
    opcode_value = instruction >> 27;
    register_1 = (instruction >> 22) & ~(~(0 << 4) << 5);
    register_2 = (instruction >> 17) & ~(~(0 << 10) << 5);

    /* Using bit masking, depending on whether the opcode is li or not,
       the addr of the instruction is extracted */
    if (opcode_value == 20) {
        addr = (instruction & (0377777));
    } else {
        addr = (instruction & (0177777));
    }

    /* If return_val is valid, the relevant parts of the instruction based
       on whether or not the instruction uses the function are printed out.
       While it would be more efficient to do this with char* (e.g. an
       array with pointers to strings), strings were not covered in class */
    if (return_val == 1) {
        if (opcode_value == 0) {
            printf("halt");
            printf("\n");
            return_val = 1;
        } else if (opcode_value == 1) {
            printf("syscall");
            printf("\n");
            return_val = 1;

            /* If the opcode value is between 2 and 8, or between 11 and 17,
               both of its registers are like this. Note that we could use a
               switch case for the below code, but the differences in program
               length are marginal, and hence a series of else-if statements
               are used. */
        } else if ((opcode_value >= 2 && opcode_value <= 8) ||
                   (opcode_value >= 11 && opcode_value <= 17)) {
            if (opcode_value == 2) {
                printf("add ");
            } else if (opcode_value == 3) {
                printf("sub ");
            } else if (opcode_value == 4) {
                printf("mul ");
            } else if (opcode_value == 5) {
                printf("quot ");
            } else if (opcode_value == 6) {
                printf("mod ");
            } else if (opcode_value == 7) {
                printf("and ");
            } else if (opcode_value == 8) {
                printf("or ");
            } else if (opcode_value == 11) {
                printf("eql ");
            } else if (opcode_value == 12) {
                printf("neq ");
            } else if (opcode_value == 13) {
                printf("lt ");
            } else if (opcode_value == 14) {
                printf("le ");
            } else if (opcode_value == 15) {
                printf("gt ");
            } else if (opcode_value == 16) {
                printf("ge ");
            } else {
                printf("move ");
            }
            printf("R%d ", register_1);
            printf("R%d", register_2);
            printf("\n");

            /* If the opcode values are between 9 and 10, only the first
                   register is printed*/
        } else if (opcode_value == 9 || opcode_value == 10) {
            if (opcode_value == 9) {
                printf("neg ");
            } else {
                printf("not ");
            }
            printf("R%d", register_1);
            printf("\n");

            /* If the opcode values are between 18 and 20, their register_1
                   and address are printed */
        } else if (opcode_value >= 18 && opcode_value <= 20) {
            if (opcode_value == 18) {
                printf("lw ");
            } else if (opcode_value == 19) {
                printf("sw ");
            } else {
                printf("li ");
            }
            printf("R%d ", register_1);
            printf("%05d", addr);
            printf("\n");

            /* If opcode is 21, its address is printed */
        } else {
            printf("branch ");
            printf("%d", addr);
            printf("\n");
        }
    }
    return return_val;
}

/* load_program takes in several parameters used to load the program
    into the MAD Raisin memory at a certain address. The MAD Raisin
    memory is represented with the array memory[], the program to be
    loaded in is represented by program[], and the start address, size
    of the program, and size of the data segment, are represented by
    start_addr, pgm_size, and data_segment_size. This function returns
    an int based on whether the program was successfully loaded or not,
    and does not modify the program in any way. This function also
    uses the auxiliary program instruction_valid to check whether
    an instruction is valid or not before printing it; this was implemented
    after seeing commends in public11.c, and as I did not want to resubmit my
    code, I will not remove this. */
int load_program(unsigned int memory[], const unsigned int program[],
                 unsigned int start_addr, unsigned short pgm_size,
                 unsigned short data_segment_size) {

    /* Variables used to increment in for loops used to print the program
       if the program is valid */

    int i = (start_addr) / 4;
    int j, k = 0;

    /* Variable used to return the appropriate value based on whether the
       program was successfully loaded or not*/
    int return_val = 0;

    /* If the parameters are valid, the process of checking instruction
       validity for every instruction in the program starts */
    if (start_addr < (NUM_WORDS * 4) && (start_addr % 4 == 0) &&
        pgm_size <= NUM_WORDS && !(pgm_size == 0 && data_segment_size != 0) &&
        ((start_addr) / 4 + pgm_size <= NUM_WORDS)) {

        /* return_val is initially set to 1 so the first iteration of
           the while loop succeeds */
        return_val = 1;

        /* Iterating through entire program and checking whether the program
           is valid or not using instruction_valid auxiliary function */
        while (i < (start_addr) / 4 + pgm_size - data_segment_size &&
               return_val != 0) {
            return_val = instruction_valid(program[i]);
            i++;
        }

        /* If every program was checked to be valid (e.g. the while loop did
           exit with return_val = 1), the process of loading the program in
           starts */
        if (return_val != 0) {
            for (j = (start_addr) / 4, k = 0; j < (start_addr) / 4 + pgm_size;
                 j++, k++) {

                /* Loading program into MAD Raisin memory array */
                memory[j] = program[k];
            }
        }
    }
    return return_val;
}

/* dissassemble takes in several parameters uesd to disassemble a program
   loaded into the MAD Raisin processor. memory[] represents the memory
   of the processor, and start_addr, pgm_size, and data_segment size
   represent the start address of where the program should be dissassembled,
   from, the size of the program, and the size of the data segment in the
   program. This function does not modify its parameters in any way, and
   returns an int indicating whether or not the program was successfully
   disassembled or not. */
unsigned short disassemble(const unsigned int memory[],
                           unsigned int start_addr, unsigned int pgm_size,
                           unsigned int data_segment_size) {

    /* Variable used to indicate the return value of the function*/
    unsigned short return_val = 0;

    /* Array used to check program validity using load_program */
    unsigned int memory_temp[NUM_WORDS] = {0};

    /* Variables used in loops used to disassemble program (if the program
       does not contain any invalid instructions) */
    unsigned int i = (start_addr) / 4;
    unsigned int j;

    /* If all parameters are valid, the process of loading begins to ensure
     * that every instruction in the progarm is valid */
    if ((start_addr % 4) == 0 && (start_addr) / 4 < NUM_WORDS &&
        pgm_size <= NUM_WORDS && !(pgm_size == 0 && data_segment_size > 0) &&
        (start_addr) / 4 + pgm_size <= NUM_WORDS) {

        /* return_val is set to the value of load_program, e.g. it is 0 if
           the program was not successfully able to be loaded (meaning not
           all of its instructions were valid)*/
        return_val = load_program(memory_temp, memory, start_addr, pgm_size,
                                  data_segment_size);

        /* If return_val is not 0, all of the data in the program is printed
           out using print_instruction */
        if (return_val != 0) {
            while (i < ((start_addr) / 4 + pgm_size - data_segment_size)) {
                print_instruction(memory[i]);
                i++;
            }

            /* Afterwards, if there is any data in the program, it is
                printed out in hexadecimal with zeroes padded if it is less
                than 10000000 in hexadecimal */
            for (j = i; j < pgm_size; j++) {
                printf("%08x\n", memory[j]);
            }
        }
    }
    return return_val;
}
