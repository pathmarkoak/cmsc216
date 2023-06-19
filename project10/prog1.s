# Name: Omkar Pathak
# TerpConnect login ID: omkarp07
# University ID number: 119272961
# Section Number: 0206

# The following MIPS assembly program is a translation of the C program 
# in prog1.c, which is used to compare the area of two rectangles given 
# their length and width. The program outputs -2 if any of the dimensions 
# are negative; otherwise, it prints 0 if their areas are the same, -1 if 
# the first rectangle's area is less than that of the second, and 1
# if the first rectangle's area is greater than that of the second. This 
# function consists of only main() and does not utilize and local variables
# or parameters. As a result, it does not use the runtime stack to store 
# any local variables or parameters, and uses only the data segment and 
# registers $t0 to $t2, $v0, and $a0. 

# -*- mode: text -*-

# setting up data segment, initializing variables
.data
l1:     .word 0
w1:     .word 0
l2:     .word 0
w2:     .word 0
rect1:  .word 0
rect2:  .word 0
result: .word 0

eoln:   .asciiz "\n"

.text

main:
    li      $t0,    0                       # result = 0
    sw      $t0,    result
    li      $v0,    5                       # first scanf
    syscall 
    sw      $v0,    l1                      # storing into l1
    li      $v0,    5
    syscall 
    sw      $v0,    w1                      # storing into w1
    li      $v0,    5
    syscall 
    sw      $v0,    l2                      # storing into l2
    li      $v0,    5
    syscall 
    sw      $v0,    w2                      # storing into w2

    lw      $t0,    l1                      # checking if l1 < 0
    blt     $t0,    0,      negative
    lw      $t0,    w1
    blt     $t0,    0,      negative        # checking if w1 < 0
    lw      $t0,    l2
    blt     $t0,    0,      negative        # checking if l2 < 0
    lw      $t0,    w2
    blt     $t0,    0,      negative        # checking if w2 < 0

    lw      $t0,    l1                      # computing the area of rect1
    lw      $t1,    w1
    mul     $t0,    $t0,    $t1
    sw      $t0,    rect1                   # storing result in rect1

    lw      $t1,    l2                      # computing the area of rect2
    lw      $t2,    w2
    mul     $t1,    $t1,    $t2
    sw      $t1,    rect2                   # storing result in rect2

    blt     $t0,    $t1,    arealess
    bgt     $t0,    $t1,    areagreater
    beq     $t0,    $t1,    print

negative:
    li      $t0,    -2                      # storing -2 into $t0
    sw      $t0,    result                  # result = -2
    j       print                           # jump to print


arealess:
    li      $t0,    -1
    sw      $t0,    result
    j       print

areagreater:
    li      $t0,    1
    sw      $t0,    result
    j       print                           # jump to print


print:
    lw      $a0,    result                  # printing out result
    li      $v0,    1
    syscall 
    la      $a0,    eoln                    # printing out newline character
    li      $v0,    4
    syscall 
    li      $v0,    10                      # exiting program
    syscall 
