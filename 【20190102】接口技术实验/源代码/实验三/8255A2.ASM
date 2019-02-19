CODE SEGMENT            ;BJ.ASM
ASSUME CS:CODE
IOCONPT EQU 0FF2BH
IOCPT	EQU 0FF2AH
IOBPT	EQU 0FF29H
IOAPT	EQU 0FF28H
	ORG 1630H
START:  JMP START0
KZ      DB ?	;键值 
time    dw ?	;电机转速时间 
flag	dw ?	;正反转标志，“0”正转，“1”反转 
START0: MOV AL,89H	;PA输出，PC口输入 
	MOV DX,IOCONPT
	OUT DX,AL
	mov time,1000h	;电机初始设定转速 
	mov flag,00h	;电机初始设定正转 
redkey:	call key	;键扫 
	test KZ,01h	;K1 ;判断K1为高电平还是低电平
      JNZ NX2        ;不为低电平则跳转至NX2
	CALL ZZ		;正转
NX2:	test KZ,04h	;AN0
        JNZ NX3
	CALL adds	;加速
NX3:    JMP REDKEY

ZZ:     mov flag,00h	;正转
	MOV DX,IOAPT
	MOV AL,03H     ;0011
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay   ;delay为延时，使转速均匀
	MOV AL,06H     ;0110
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	MOV AL,0CH      ;1100
        MOV DX,IOAPT
	OUT DX,AL
     CALL delay
	MOV AL,09H      ;1001
        MOV DX,IOAPT
	OUT DX,AL
        CALL delay
	RET
;-------------------------
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
	call fz
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
	MOV KZ,AL      ;将获得的K键值赋给KZ
	RET	
delay:  mov cx,time	;调速时间 
        loop $       ;延时
        RET
del10ms:MOV CX,2800	;10ms 
        LOOP $       ;CX赋值2800，为10ms，通过loop 指令进行
	ret
CODE ENDS
END  START
