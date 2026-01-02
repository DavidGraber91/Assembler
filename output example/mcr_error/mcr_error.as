 .define x = 5
	.define   y   = 10
.entry LOOP
A: entry L
;אין הגיון בתוכנית היא רק נועדה לבדוק את רוב הפקודות

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

mcr a
cmp r5, r2
	bne EXIT
	jmp LOOP
endmcr

mcr b and
cmp r2,r3
endmcr

mcr c and
cmp r2,r3
endmcr and

EXIT:	jsr FOR
 
a

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

