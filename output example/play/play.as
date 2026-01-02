 .define x = 5
	.define   y   = 10
.entry LOOP
A: .extern L
;אין הגיון בקוד, זה רק לבדוק את כל הפקודות

mcr a 
mov L1 , r2
mov    #y ,   r0
  add r0 ,	  r2
endmcr

LOOP:  	lea L2  , r1
	L1:  .data 1, 3,	-13, +31
	sub #3,   r5
	not r5

a
mcr b
cmp r5, r2
	bne EXIT
	jmp LOOP
endmcr
 	
EXIT:	jsr FOR
 
a
b

jmp FOR		 
	
.extern FOR 
L2: 	.string "asdf"fsd"
clr L1[4]
inc 	L2[x]
dec r3
red L1
prn r7



rts
hlt

