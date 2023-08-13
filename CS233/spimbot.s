# syscall constants
PRINT_STRING            = 4
PRINT_CHAR              = 11
PRINT_INT               = 1

# memory-mapped I/O
VELOCITY                = 0xffff0010
ANGLE                   = 0xffff0014
ANGLE_CONTROL           = 0xffff0018

BOT_X                   = 0xffff0020
BOT_Y                   = 0xffff0024

OTHER_X                 = 0xffff00a0
OTHER_Y                 = 0xffff00a4

TIMER                   = 0xffff001c
GET_MAP                 = 0xffff2008
GET_TILE_INFO 			= 0xffff200c

REQUEST_PUZZLE          = 0xffff00d0  ## Puzzle
SUBMIT_SOLUTION         = 0xffff00d4  ## Puzzle

BONK_INT_MASK           = 0x1000
BONK_ACK                = 0xffff0060

TIMER_INT_MASK          = 0x8000
TIMER_ACK               = 0xffff006c

REQUEST_PUZZLE_INT_MASK = 0x800       ## Puzzle
REQUEST_PUZZLE_ACK      = 0xffff00d8  ## Puzzle

FALLING_INT_MASK        = 0x200
FALLING_ACK             = 0xffff00f4

STOP_FALLING_INT_MASK   = 0x400
STOP_FALLING_ACK        = 0xffff00f8

OUT_OF_WATER_INT_MASK 	= 0x2000	
OUT_OF_WATER_ACK 		= 0xffff00f0

POWERWASH_ON            = 0xffff2000
POWERWASH_OFF           = 0xffff2004

GET_WATER_LEVEL         = 0xffff201c

GET_SEED 				= 0xffff2040

MMIO_STATUS             = 0xffff204c

.data
### Puzzle
puzzlewrapper:     .byte 0:400
#### Puzzle

has_puzzle: .word 0

has_bonked: .byte 0

# -- string literals --
.text
main:
    sub $sp, $sp, 32
    sw  $ra, 0($sp)
    sw  $s0, 4($sp)
    sw  $s1, 8($sp)
    sw  $s2, 12($sp)
    sw  $s3, 16($sp)
    sw  $s4, 20($sp)
    sw  $s5, 24($sp)
    sw  $s6, 28($sp)
    # Construct interrupt mask
    li      $t4, 0
    or      $t4, $t4, TIMER_INT_MASK            # enable timer interrupt
    or      $t4, $t4, BONK_INT_MASK             # enable bonk interrupt
    or      $t4, $t4, REQUEST_PUZZLE_INT_MASK   # enable puzzle interrupt
    or      $t4, $t4, FALLING_INT_MASK          # enable falling interrupt
    or      $t4, $t4, STOP_FALLING_INT_MASK     # enable falling interrupt
    or      $t4, $t4, OUT_OF_WATER_INT_MASK     # enable out of water interrupt
    or      $t4, $t4, 1 # global enable
    mtc0    $t4, $12

    # YOUR CODE GOES HERE!!!!!!

    li $s0 0                # i = 0

puzzlepart:
    bge $s0 515 endfor
    sw $zero has_puzzle
    la $s1 puzzlewrapper
    sw $s1 REQUEST_PUZZLE
    la $s2 has_puzzle

    while:
        lb $s3 0($s2)
        beq $s3 $zero while

    endwhile:
        move $s5, $a0
        lw $t0 4($s1)
        lw $t1 0($s1)
        lw $t2 8($s1)
        lw $t3 12($s1)
        move $a0 $t0
        move $a1 $t1
        move $a2 $t2
        move $a3 $t3
        jal solve_queens
        la $t0 puzzlewrapper
        sw $t0 SUBMIT_SOLUTION
        addi $s0, $s0, 1
        j puzzlepart

endfor:

    la $s0 0x00040000

    sw $s0 POWERWASH_ON

    la $s1 GET_WATER_LEVEL

check_position:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s6 316 check_x_start

check_x_start:
    beq $s5 20 bot0_start
    beq $s5 300 bot1_start
    j check_position

bot0_start:

while2:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 20 check_y
    j while2

check_y:
    beq $s6 316 go
    j while2

go:
    li $t4 270 # normally 270
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

# go to bot1's position
# whilewhile:
#     lw $s5 BOT_X
#     lw $s6 BOT_Y

#     beq $s5 300 check_yy
#     j whilewhile

# check_yy:
#     beq $s6 316 gogo
#     j whilewhile

# gogo:
#     li $t4 270
#     sw $t4 ANGLE
#     li $t4, 1
#     sw $t4, ANGLE_CONTROL
#     li $t5 9
#     sw $t5, VELOCITY 

#     j bot1_start
while3:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 20 check_y2
    j while3

check_y2:
    beq $s6 220 go2
    j while3

go2:
    li $t4 0
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY 

while4:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 135 check_y3
    j while4

check_y3:
    beq $s6 220 go3
    j while4

go3:
    li $t4 90
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY 

while5:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 135 check_y4
    j while5

check_y4:
    beq $s6 316 go4
    j while5

go4:
    li $t4 0
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while6:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 187 check_y5
    j while6

check_y5:
    beq $s6 316 go5
    j while6

go5:
    li $t4 270
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while7:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 187 check_y6
    j while7

check_y6:
    beq $s6 220 go6
    j while7

go6:
    li $t4 0
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while8:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 260 check_y7
    j while8

check_y7:
    beq $s6 220 go7
    j while8

go7:
    li $t4 270
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while9:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 260 check_y8
    j while9

check_y8:
    beq $s6 150 go8
    j while9

go8:
    li $t4 180
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

#     li $s0 0                # i = 0

# puzzlepart2:
#     bge $s0 200 endfor2
#     sw $zero has_puzzle
#     la $s1 puzzlewrapper
#     sw $s1 REQUEST_PUZZLE
#     la $s2 has_puzzle

#     whilewhile:
#         lb $s3 0($s2)
#         beq $s3 $zero whilewhile

#     endwhilewhile:
#         move $s5, $a0
#         lw $t0 4($s1)
#         lw $t1 0($s1)
#         lw $t2 8($s1)
#         lw $t3 12($s1)
#         move $a0 $t0
#         move $a1 $t1
#         move $a2 $t2
#         move $a3 $t3
#         jal solve_queens
#         la $t0 puzzlewrapper
#         sw $t0 SUBMIT_SOLUTION
#         addi $s0, $s0, 1
#         j puzzlepart2

# endfor2:
#     la $s0 0x00040000

#     sw $s0 POWERWASH_ON

#     la $s1 GET_WATER_LEVEL

#     li $t4 180
#     sw $t4, ANGLE
#     li $t4, 1
#     sw $t4, ANGLE_CONTROL
#     li $t5 9
#     sw $t5, VELOCITY
    
while10:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 60 check_y9
    j while10

check_y9:
    beq $s6 150 go9
    j while10

go9:
    li $t4 270
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while11:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 60 check_y10
    j while11

check_y10:
    beq $s6 40 go10
    j while11

go10:
    li $t4 0
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

# whileint:
#     lw $s5 BOT_X
#     lw $s6 BOT_Y

#     beq $s5 260 check_yint
#     j whileint

# check_yint:
#     beq $s6 150 goint
#     j whileint

# goint:
#     li $t4 270
#     sw $t4, ANGLE
#     li $t4, 1
#     sw $t4, ANGLE_CONTROL
#     li $t5 2
#     sw $t5, VELOCITY

j endend

# ----------------------------------------------------------------------------------------------------------------------------------- #

bot1_start:

go11:
    li $t4 270
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while12:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 300 check_y12
    j while12

check_y12:
    beq $s6 220 go12
    j while12

go12:
    li $t4 180
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY 

while13:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 185 check_y13
    j while13

check_y13:
    beq $s6 220 go13
    j while13

go13:
    li $t4 90
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY 

while14:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 185 check_y14
    j while14

check_y14:
    beq $s6 316 go14
    j while14

go14:
    li $t4 180
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while15:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 135 check_y15
    j while15

check_y15:
    beq $s6 316 go15
    j while15

go15:
    li $t4 270
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while16:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 135 check_y16
    j while16

check_y16:
    beq $s6 220 go16
    j while16

go16:
    li $t4 180
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while17:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 60 check_y17
    j while17

check_y17:
    beq $s6 220 go17
    j while17

go17:
    li $t4 270
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while18:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 60 check_y18
    j while18

check_y18:
    beq $s6 150 go18
    j while18

go18:
    li $t4 0
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY
    
while19:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 260 check_y19
    j while19

check_y19:
    beq $s6 150 go19
    j while19

go19:
    li $t4 270
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

while20:
    lw $s5 BOT_X
    lw $s6 BOT_Y

    beq $s5 260 check_y20
    j while20

check_y20:
    beq $s6 25 go20
    j while20

go20:
    li $t4 180
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

endend:

loop: # Once done, enter an infinite loop so that your bot can be graded by QtSpimbot once 10,000,000 cycles have elapsed
    j loop
    

.kdata
chunkIH:    .space 40
non_intrpt_str:    .asciiz "Non-interrupt exception\n"
unhandled_str:    .asciiz "Unhandled interrupt type\n"
.ktext 0x80000180
interrupt_handler:
.set noat
    move    $k1, $at        # Save $at
                            # NOTE: Don't touch $k1 or else you destroy $at!
.set at
    la      $k0, chunkIH
    sw      $a0, 0($k0)        # Get some free registers
    sw      $v0, 4($k0)        # by storing them to a global variable
    sw      $t0, 8($k0)
    sw      $t1, 12($k0)
    sw      $t2, 16($k0)
    sw      $t3, 20($k0)
    sw      $t4, 24($k0)
    sw      $t5, 28($k0)

    # Save coprocessor1 registers!
    # If you don't do this and you decide to use division or multiplication
    #   in your main code, and interrupt handler code, you get WEIRD bugs.
    mfhi    $t0
    sw      $t0, 32($k0)
    mflo    $t0
    sw      $t0, 36($k0)

    mfc0    $k0, $13                # Get Cause register
    srl     $a0, $k0, 2
    and     $a0, $a0, 0xf           # ExcCode field
    bne     $a0, 0, non_intrpt



interrupt_dispatch:                 # Interrupt:
    mfc0    $k0, $13                # Get Cause register, again
    beq     $k0, 0, done            # handled all outstanding interrupts

    and     $a0, $k0, BONK_INT_MASK     # is there a bonk interrupt?
    bne     $a0, 0, bonk_interrupt

    and     $a0, $k0, TIMER_INT_MASK    # is there a timer interrupt?
    bne     $a0, 0, timer_interrupt

    and     $a0, $k0, REQUEST_PUZZLE_INT_MASK
    bne     $a0, 0, request_puzzle_interrupt

    and     $a0, $k0, FALLING_INT_MASK
    bne     $a0, 0, falling_interrupt

    and     $a0, $k0, STOP_FALLING_INT_MASK
    bne     $a0, 0, stop_falling_interrupt
	
	and		$a0, $k0, OUT_OF_WATER_INT_MASK
	bne		$a0, 0, out_of_water_interrupt

    li      $v0, PRINT_STRING       # Unhandled interrupt types
    la      $a0, unhandled_str
    syscall
    j       done

bonk_interrupt:
    sw      $0, BONK_ACK
    la      $t0, has_bonked
    li      $t1, 1
    sb      $t1, 0($t0)
    #Fill in your bonk handler code here

    lw $t1 ANGLE
    beq $t1 0 turn_left

    li $t4 0
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

    j endendendend

    turn_left:
    li $t4 180
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

    endendendend:
    j       interrupt_dispatch      # see if other interrupts are waiting

timer_interrupt:
    sw      $0, TIMER_ACK
    #Fill your timer interrupt code here
    j        interrupt_dispatch     # see if other interrupts are waiting

request_puzzle_interrupt:
    sw      $0, REQUEST_PUZZLE_ACK
    #Fill in your puzzle interrupt code here
    la      $t0, has_puzzle
    li      $t1, 1
    sw      $t1, 0($t0)
    j       interrupt_dispatch

falling_interrupt:
    sw      $0, FALLING_ACK
    #Fill in your falling interrupt handler code here

    j       interrupt_dispatch

stop_falling_interrupt:
    sw      $0, STOP_FALLING_ACK
    #Fill in your stop falling interrupt handler code here
    la $s0 0x00040000

    sw $s0 POWERWASH_ON

    la $s1 GET_WATER_LEVEL

    lw $t1 ANGLE
    beq $t1 0 keepgoing

    li $t4 180
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

    j endendendendend

    keepgoing:
    li $t4 0
    sw $t4, ANGLE
    li $t4, 1
    sw $t4, ANGLE_CONTROL
    li $t5 9
    sw $t5, VELOCITY

    endendendendend:

    j       interrupt_dispatch

out_of_water_interrupt:
	sw		$0, OUT_OF_WATER_ACK
	#Fill in your out of water interrupt handler code here

    j       interrupt_dispatch

non_intrpt:                         # was some non-interrupt
    li      $v0, PRINT_STRING
    la      $a0, non_intrpt_str
    syscall                         # print out an error message
    # fall through to done

done:
    la      $k0, chunkIH

    # Restore coprocessor1 registers!
    # If you don't do this and you decide to use division or multiplication
    #   in your main code, and interrupt handler code, you get WEIRD bugs.
    lw      $t0, 32($k0)
    mthi    $t0
    lw      $t0, 36($k0)
    mtlo    $t0

    lw      $a0, 0($k0)             # Restore saved registers
    lw      $v0, 4($k0)
    lw      $t0, 8($k0)
    lw      $t1, 12($k0)
    lw      $t2, 16($k0)
    lw      $t3, 20($k0)
    lw      $t4, 24($k0)
    lw      $t5, 28($k0)

.set noat
    move    $at, $k1        # Restore $at
.set at
    eret


# Below are the provided puzzle functionality.
.text
.globl is_attacked
is_attacked:
    prefor1:
        li $t0 0                       # int i = 0;
        j for1
     
    postfor1:
        add $t0 $t0 1
        j for1
        
    for1:
        bge $t0 $a1 prefor2           # i < n
        j if
        if:
            beq $t0 $a2 postfor1       # i != row
            
            mul $t1 $t0 4      # i * 4
            add $t2 $a0 $t1
            lw $t3 0($t2)
            
            add $t3 $t3 $a3     # + j

            lb $t4 0($t3)      # load actual element of that array
            
            li $t5 1           
            
            add $t0 $t0 1      # i++
            bne $t4 $t5 for1   # board[i][col] == 1
            li $v0 1           # return 1
            j end2
    
    prefor2:
        li $t0 0                   # int j = 0;
        j for2
        
    postfor2:
        add $t0 $t0 1
        j for2
        
    for2:
        bge $t0 $a1 prefor3           # j < n
        j if4
        if4:
            beq $t0 $a3 postfor2       # j != col
            mul $t1 $a2 4    # row * 4
            add $t2 $a0 $t1
            lw $t3 0($t2)
            
            add $t3 $t3 $t0    # row * 4 + j
            
            lb $t4 0($t3)      # load actual element of that array
            
            li $t5 1           
            
            add $t0 $t0 1      # j++
            bne $t4 $t5 for2   # board[row][j] == 1
            li $v0 1           # return 1
            j end2
    
    prefor3:
        li $t0 0                   # int i = 0;
        j for3
        
    postfor3:
        add $t0 $t0 1
        j for3
        
    for3:
        bge $t0 $a1 prefor4        # i < n
        j if5
        
        if5:
            beq $t0 $a2 postfor3       # i != row
            move $t1 $t0           # j = i
            sub $t1 $t1 $a2        # j = i - row
            add $t1 $t1 $a3        # j = i - row + col
            blt $t1 $0 postfor3        # j >= 0
            bge $t1 $a1 postfor3       # j < n
            
            mul $t2 $t0  4       # i * n
            add $t3 $a0 $t2
            lw $t4 0($t3)
            add $t4 $t4 $t1
            lb $t5 0($t4)
      
            li $t6 1
            add $t0 $t0 1          # i++

            bne $t6 $t5 for3       # board[i][j] == 1
            li $v0 1
            j end2
            
    prefor4:
        li $t0 0
        j for4
    
    postfor4:
        add $t0 $t0 1
        j for4
        
    for4:
        bge $t0 $a1 end        # i < n
        j if6
        
        if6:
            beq $t0 $a2 postfor4       # i != row
            move $t1 $a2           # j = row
            sub $t1 $t1 $t0        # j = row - i
            add $t1 $t1 $a3        # j = row - i + col
            blt $t1 $0 postfor4        # j >= 0
            bge $t1 $a1 postfor4       # j < n
            
            mul $t2 $t0  4        # i * n
            add $t3 $a0 $t2
            lw $t4 0($t3)
            add $t4 $t4 $t1
            lb $t5 0($t4)
   
            li $t6 1
            add $t0 $t0 1          # i++
            bne $t6 $t5 for4
            li $v0 1
            j end2
            
    end:
        li $v0 0
        jr $ra
        
    end2:
        jr $ra

.globl place_queen_step
place_queen_step:
    sub $sp $sp 40
    sw $ra 0($sp)
    sw $s0 4($sp)
    sw $s1 8($sp)
    sw $s2 12($sp)
    sw $s3 16($sp)
    sw $s4 20($sp)
    sw $s5 24($sp)
    sw $s6 28($sp)
    sw $s7 32($sp)
    sw $s8 36($sp)
    
    move $s0 $a0        # move all the original arguments into s registers
    move $s1 $a1
    move $s2 $a2            
    move $s3 $a3
    
    bne $a3 $0 prefor2_pqs # if (queens_left == 0)
    j endbasecase_pqs
    
    prefor2_pqs:
        move $s4 $s2    # i = pos
        mul $t1 $s1 $s1 # n * n 
        j for_pqs
        
    prefor_pqs:
        add $s4 $s4 1       # i++
        
        
        j for_pqs
    
    for_pqs:
        mul $t1 $s1 $s1
        bge $s4 $t1 end_pqs     # i < n * n
        
        div $s5 $s4 $s1     # row = i / n 1 t2
        rem $s8 $s4 $s1     # col = i % n 1 t3
        
        mul $t4 $s5 4       # pointer offset
        add $t5 $s0 $t4     # offset the array pointer
        lw $t6 0($t5)       # load the appropriate pointer
        
        add $t6 $t6 $s8     # offset array by col
        move $s7 $t6        # save the offset to the stack
        lb $t7 0($s7)       # board[row][col]
        bne $t7 $0 prefor_pqs   # board[row][col] == 0
        
        move $a0 $s0
        move $a1 $s1
        move $a2 $s5        # load new arugments for the function call
        move $a3 $s8 
        
        jal is_attacked
        mul $t1 $s1 $s1
        # move $s4 $v0        # return value from is_attacked
        
        bne $v0 $0 prefor_pqs   # is_attacked(board, n, row, col) == 0
        li $t0  1
        sb $t0 0($s7)       # board[row][col] = 1;
        
        add $s2 $s2 1       # pos + 1
        
        
        move $a0 $s0
        move $a1 $s1
        move $a2 $s2        # load args back
        move $a3 $s3
        
        sub $a3 $a3 1       # queens_left - 1
        
        jal place_queen_step    # fat recursion
        li $t0  1
      
        beq $v0 $t0 endbasecase_pqs  # if (place_queen_step(board, n, pos + 1, queens_left - 1) == 1)
        sb $0 0($s7)        # board[row][col] = 0;
        j prefor_pqs
        
    end_pqs:
        lw $ra 0($sp)
        lw $s0 4($sp)
        lw $s1 8($sp)
        lw $s2 12($sp)
        lw $s3 16($sp)
        lw $s4 20($sp)
        lw $s5 24($sp)
        lw $s6 28($sp)
        lw $s7 32($sp)
        lw $s8 36($sp)
        add $sp $sp 40
        
        li $v0 0          # return 0
        jr $ra
    
    endbasecase_pqs:
        lw $ra 0($sp)
        lw $s0 4($sp)
        lw $s1 8($sp)
        lw $s2 12($sp)
        lw $s3 16($sp)
        lw $s4 20($sp)
        lw $s5 24($sp)
        lw $s6 28($sp)
        lw $s7 32($sp)
        lw $s8 36($sp)
        add $sp $sp 40
        
        
        li $v0 1           # return 1
        jr $ra

.globl solve_queens
solve_queens:

    sub $sp $sp 20
    sw $ra 0($sp)
    sw $s0 4($sp)
    sw $s1 8($sp)
    sw $s2 12($sp)
    sw $s3 16($sp)
    li $t0 0                                    # i = 0
    for_sq:
        bge $t0 $a1 endfor_sq                      # i < n
        li $t1 0                                # j = 0
        
        for2_sq:
            bge $t1 $a1 endfor2_sq                 # j < n
            
            mul $t2 $t0 4                       # i * 4
            add $t3 $a0 $t2
            lw $t4 0($t3)                       # load pointer
            
            add $t4 $t4 $t1                     # + j
            
            sb $0 0($t4)                        # sol_board[i][j] = 0
            add $t1 $t1 1                       # j++
            j for2_sq
        
        endfor2_sq:
            add $t0 $t0 1                       # i++
            j for_sq
    
    endfor_sq:
        move $t5 $a2                            # list_node_t *curr = given_queens
        j for_linked_list_sq
        
    for_linked_list_sq:
        beq $t5 $0 end_sq                          # curr != null
        lw $t6 0($t5)                           # load curr->pos
        
        div $t7 $t6 $a1                         # row = curr->pos / n
        rem $t8 $t6 $a1                         # col = curr->pos % n
        
        mul $s0 $t7 4                           # row * 4 (pointer offset)
        add $s1 $a0 $s0                         # array pointer offset
        lw $s2 0($s1)                           # load that pointer
        
        add $s2 $s2 $t8                         # offset by col
        
        li $s3 1                                # temp = 1
        sb $s3 0($s2)                           # sol_board[row][col] = 1
        
        lw $t5 4($t5)                           # curr = curr->next
        
        j for_linked_list_sq

    end_sq:
        move $a2 $0
        jal place_queen_step
        
        move $t6 $v0                            # save return value 
        
        lw $ra 0($sp)
        lw $s0 4($sp)
        lw $s1 8($sp)
        lw $s2 12($sp)
        lw $s3 16($sp)
        add $sp $sp 20
        
        jr $ra
