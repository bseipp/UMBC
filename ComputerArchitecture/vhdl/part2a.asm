-- part2a.asm
       lw   $15,w1($0)
       lw   $16,w2($0)
       nop    -- must wait to do add
       sll  $17,$16,1    -- $16 forwarded 
       add  $18,$17,$17  -- $17 forwarded on both
       nop               -- must wait to do beq
       beq  $17,$18,lab1 -- $18 forwarded, no br
       lw   $1,w1($0)
       j    lab1
       lw   $2,w1($0)    -- branch slot, always
       lw   $10,w6($0)   -- not executed
       nop
lab1:  sw   $1,w2($0)
       sw   $2,w4($0)
       beq  $2,$1,lab2   -- no forward, does branch 
       lw   $8,w2($0)    -- always execute
       lw   $9,w6($0)    -- not executed
       nop
lab2:  lw   $5,w5($0)
       beq  $2,$16,lab4  -- no forward, no branch
       lw   $6,w6($0) 
       addi $7,w1($0)
lab4:  sw   $6,0($7)
       sw   $7,w5($0)
       and  $3,$5,$15
       nop
       nop
       nop
w1:    word 0x11111111
w2:    word 0x22222222
w3:    word 0x33333333
w4:    word 0x44444444
w5:    word 0x55555555
w6:    word 0x66666666
       end
