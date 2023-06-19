# Name: Omkar Pathak
# TerpConnect login ID: omkarp07
# University ID number: 119272961
# Section Number: 0206

# The following MIPS assembly program is a translation of the C program in 
# prog2.s. The program prog2.s is an iterative program (e.g. relies on a 
# loop) that computes the number of digits in a number in a specified base.
# This program takes in two inputs (the number in decimal and its respective
# base) and outputs the number of digits of this number in the base. This 
# base must be positive (if it is not, -1 is outputted), though the number
# can be negative (if it is negative, it is negated to obtain its absolute
# value). This MIPS assembly program utilizes several MIPS system calls
# to take in user input and give output. It also uses the runtime stack 
# heavily to store the local variables and parameters of the function 
# numdigits. The data segment is used for the global variables number, base
# and result. Registers are also used to hold data and modify it using 
# branch instructions. Jump instructions are also used in order to jump
# unconditionally to certain parts of the program. MIPS integer instructions
# are also used to modify variables in registers. The algorithm this program
# is translating relies on iteratively dividing the number parameter by 
# the base until the number becomes small enough and is rounded to zero; 
# during this iteration, the local variable answer in numdigits is 
# incremented. 

# -*- mode: text -*-

.data
number: .word 0
base:   .word 0
result: .word 0
eoln:   .asciiz "\n"

.text
main:
    li      $sp,        0x7ffffffc                      # init $sp
    li      $v0,        5
    syscall 
    sw      $v0,        number
    sw      $v0,        ($sp)                           # push num. to stack
    sub     $sp,        $sp,                4           # updating $sp
    li      $v0,        5                               # taking input base
    syscall 
    sw      $v0,        base
    sw      $v0,        ($sp)                           # storing in stack
    sub     $sp,        $sp,                4           # updating $sp
    jal     numdigits                                   # jumping
    add     $sp,        $sp,                8           # popping args
    sw      $v0,        result                          # setting result
    lw      $a0,        result                          # printing result
    li      $v0,        1
    syscall 
    la      $a0,        eoln                            # printing out \n
    li      $v0,        4
    syscall 
    li      $v0,        10                              # exiting program
    syscall 


numdigits:                                              # prologue
    sub     $sp,        $sp,                12          # setting $sp
    sw      $ra,        12($sp)                         # save $ra
    sw      $fp,        8($sp)                          # save $fp
    add     $fp,        $sp,                12          # set new $fp
    li      $t0,        0                               # ans= 0
    sw      $t0,        4($sp)                          # pushing ans
    lw      $t0,        8($fp)                          # storing number $t0
    lw      $t1,        4($fp)                          # storing base $t1
    lw      $t2,        4($sp)                          # storing ans $t2

    blez    $t1,        nonpositivebase                 # jump if base < 0

    beqz    $t0,        zero
    bltz    $t0,        negativenumber

    beq     $t1,        1,                  baseone     # if base == 1 jump
    j       loop                                        # else, jump to loop

nonpositivebase:
    li      $t2,        -1
    sw      $t2,        4($sp)                          # ans= -1
    j       ret                                         # jump ret


zero:
    li      $t2,        1
    sw      $t2,        4($sp)                          # ans= 1
    j       ret                                         # jump to ret

negativenumber:
    neg     $t0,        $t0                             # n= -n
    beq     $t1,        1,                  baseone     # if (base == 1)
    bne     $t1,        1,                  loop        # else, go to loop

baseone:
    move    $t2,        $t0                             # ans= n
    sw      $t2,        4($sp)                          # pushing to stack
    j       ret                                         # jump to ret

loop:
    beq     $t0,        0,                  ret         # if n == 0, go ret
    add     $t2,        $t2,                1           # ans += 1
    sw      $t2,        4($sp)
    div     $t0,        $t0,                $t1         # n /= base
    sw      $t0,        8($fp)
    j       loop

ret:                                                    # epilogue
    move    $v0,        $t2                             # move ans to $v0
    lw      $ra,        12($sp)                         # restore $ra
    lw      $fp,        8($sp)                          # restore $fp
    add     $sp,        $sp,                12          # reset $sp
    jr      $ra                                         # go back to main
