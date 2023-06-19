# Name: Omkar Pathak
# TerpConnect login ID: omkarp07
# University ID number: 119272961
# Section Number: 0206

# The following MIPS assembly program is a translation of the C program in 
# prog3.s. The program prog3.c is similar to the one in prog2.c and has the 
# same functionality. However, the algorithm in prog3.c is a recursive one, 
# as opposed to the iterative one in prog2.c. The algorithm consists of 
# repeatedly jumping to numdigits and incrementing the local variable ans 
# by one plus the result of numdigits with the number divided by the base 
# and the original base passed in as parameters. This MIPS assembly program
# makes use of MIPS system calls, the registers $t0 through $t2 (as well as
# $v0 and $a0 for returning and syscalls), and the runtime stack to store the 
# local variables and parameters of function calls to numdigits. The special
# cases for this program are handled slightly differently than in prog2.c:
# there is no special case for if number parameters is 0, as if this is 
# the case, the program will set the local variable ans to 1 and return 
# immediately. 

# -*- mode: text -*-


# setting up the data segment 
.data
number: .word 0
base:   .word 0
result: .word 0
eoln:   .asciiz "\n"

.text
main:
    li      $sp,                0x7ffffffc                 # init $sp
    li      $v0,                5
    syscall 
    sw      $v0,                number
    sw      $v0,                ($sp)                     # storing num.
    sub     $sp,                $sp,                4     # updating $sp
    li      $v0,                5                         # taking input base
    syscall 
    sw      $v0,                base
    sw      $v0,                ($sp)                     # storing base
    sub     $sp,                $sp,                4     # updating $sp
    jal     numdigits                                     # jumping to func.
    add     $sp,                $sp,                8     # popping args
    sw      $v0,                result                    # setting result
    lw      $a0,                result                    # printing result
    li      $v0,                1
    syscall 
    la      $a0,                eoln                      # printing out \n
    li      $v0,                4
    syscall 
    li      $v0,                10                        # exiting program
    syscall 

numdigits:
                                                          # prologue
    sub     $sp,                $sp,                12    # setting $sp
    sw      $ra,                12($sp)                   # save $ra
    sw      $fp,                8($sp)                    # save $fp
    add     $fp,                $sp,                12    # set new $fp
    li      $t0,                0                         # ans= 0
    sw      $t0,                4($sp)                    # storing ans 
    lw      $t0,                8($fp)                    # storing number $t0
    lw      $t1,                4($fp)                    # storing base $t1
    lw      $t2,                4($sp)                    # storing ans $t2


# recursive part of numdigits (e.g. after prologue)

numdigitsrecursion:
    blez    $t1,                nonpositivebase           # base < 0, jump
    bltz    $t0,                negativenumber            # if n < 0, jump
    beq     $t1,                1,            baseone     # if base = 1, jump
    bgt     $t1,                $t0,          ansisone    # if base>n, ans=1

    div     $t0,                $t0,                $t1   # n = n/base
    sub     $sp,                $sp,                8     # preserving stack 
    sw      $t0,                8($sp)                    # loading in args
    sw      $t1,                4($sp)
    jal     numdigits;

    lw      $t0,                8($sp)                    # restoring frame
    lw      $t1,                4($sp)
    add     $sp,                $sp,                8

    move    $t2,                $v0
    add     $t2,                $t2,                1     # updating ret val.
    sw      $t2,                4($sp)
    j       ret

nonpositivebase:
    li      $t2,                -1
    sw      $t2,                4($sp)                     # ans= -1
    j       ret                                            # jump ret


ansisone:
    li      $t2,                1
    sw      $t2,                4($sp)                    # ans= 1
    move    $v0,                $t2
    j       ret                                           # jump to ret

baseone:
    sw      $t0,                4($sp)                    # ans= n
    lw      $t2,                4($sp)
    j       ret                                           # jump to ret

negativenumber:
    neg     $t0,                $t0                       # n= -n
    j       numdigitsrecursion


ret:                                                      # epilogue
    move    $v0,                $t2
    lw      $ra,                12($sp)                   # restore $ra
    lw      $fp,                8($sp)                    # restore $fp
    add     $sp,                $sp,          12          # reset $sp
    jr      $ra                                           # go back to main
