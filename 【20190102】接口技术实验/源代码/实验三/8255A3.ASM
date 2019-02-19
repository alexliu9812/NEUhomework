CODE SEGMENT            ;BJ.ASM
ASSUME CS:CODE
IOCONPT EQU 0FF2BH
IOCPT	EQU 0FF2AH
IOBPT	EQU 0FF29H
IOAPT	EQU 0FF28H
	ORG 1630H
START:  JMP START0
KZ      DB ?	;正转键值 
time    dw ?	;电机转速时间 
flag	dw ?	;正反转标志，"0"正转，"1"反转 
START0: MOV AL,8BH	;PA输出，PC口输入
	MOV DX,IOCONPT
	OUT DX,AL
	mov time,1000h	;电机初始设定转速 
	mov flag,00h	;电机初始设定正转 
redkey:	call key	;键扫 
	test KZ,01h	;K1
        JNZ FF 
	CALL ZZ;正转
	jmp NX2
FF:	test KZ,02h
	jnz  NX2
	call FZ
NX2:	test KZ,04h	;AN0
        JNZ NX3
	CALL adds	;加速
NX3:    JMP REDKEY
F:	call key ;
	test KZ,02H
	JNZ NX2 
	CALL FZ;反转
	JMP NX2
ZZ:     mov flag,00h	;正转
	MOV DX,IOAPT
	MOV AL,03H
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	MOV AL,06H
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	MOV AL,0CH
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	MOV AL,09H
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	RET
;-------------------------
FZ:     ;反转
	mov flag,01h
	mov DX,IOAPT
	mov AL,09H
	mov DX,IOAPT
	OUT DX,AL
 	CALL delay
	MOV AL,0CH
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	MOV AL,06H
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	MOV AL,03H
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	RET	
;-----------------
adds:  	call del10ms	;加速 
	MOV DX,IOCPT
adds1:	IN AL,DX
	test al,04
	jnz exit
adds3:	MOV DX,IOCPT
	IN AL,DX
	test al,04
	jz adds4
	jmp adds5
adds4:	cmp flag,00
	jz adds6
	call FZ
	jmp adds3
adds6:	call zz
	jmp adds3
adds5:	mov ax,time
	sub ax,100h
	cmp ax,300h
 	jnz adds2
	mov ax,1000h	
adds2:	mov time,ax
exit:	ret
;-------------------------
key:	MOV DX,IOCPT	;键扫 
	IN AL,DX
	MOV KZ,AL
	RET	
delay:  mov cx,time	;调速时间 
        loop $
        RET
del10ms:MOV CX,2800	;10ms 
        LOOP $
	ret
CODE ENDS
END  START
