CODE SEGMENT            ;H8259.ASM
ASSUME CS:CODE
INTPORT1 EQU 0FF80H
INTPORT2 EQU 0FF81H
INTQ3	 EQU INTREEUP3
	ORG 12D0H
START:  JMP START0
BUF     DB ?,?,?,?,?,?
intcnt  db ?
data1:  db 0c0h,0f9h,0a4h,0b0h,99h,92h,82h,0f8h,80h,90h,88h,83h,0c6h,0a1h
        db 86h,8eh,0ffh,0ch,89h,0deh,0c7h,8ch,0f3h,0bfh,8FH
START0:	CLD
	       CALL WRINTVER		     ;WRITE INTRRUPT
       	MOV AL,13H
       	MOV DX,INTPORT1
       	OUT DX,AL
       	MOV AL,08H
       	MOV DX,INTPORT2
     	    OUT DX,AL
       	MOV AL,09H
        	OUT DX,AL
    	   MOV AL,0FBH;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
       	OUT DX,AL
       	MOV intcnt,01H	;TIME=1
	       STI

          MOV   BL,0FEH
WAITING:  MOV   AL,BL
          ROR   BL,1
          MOV   DX,0FF90H	;273¿ÚµØÖ· 
          OUT   DX,AL
          MOV   CX,0
          LOOP  $
          JMP   WAITING

WRINTVER:      MOV AX,0H
           	 MOV ES,AX
           	 MOV DI,0028H
            	 LEA AX,INTQ3
       	    STOSW
           	 MOV AX,0000h
           	 STOSW
           	 RET
INTREEUP3:    PUSH AX
	           PUSH BX	
	           PUSH DX
	           CLI
              MOV    BH,0AH
              MOV    AL,0FBH;;;;;;;;;;;;;;;;;;;;;;;;;
L1:           MOV    DX,0FF90H
              OUT    DX,AL
              MOV    CX,0
              LOOP   $
              XOR    AL,08
              OUT    DX,AL
              MOV    CX,0
              LOOP   $
              XOR    AL,08
              DEC    BH
              JNZ    L1
              MOV    AL,20H
              MOV    DX,0FF80H
              OUT    DX,AL
              STI 
	          POP DX
	          POP BX
	          POP AX
             IRET

CODE ENDS
END  START