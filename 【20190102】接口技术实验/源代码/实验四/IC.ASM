                   pa8255     	equ  0FF28h          ;8255A的A口地址
                   pb8255    	equ  0FF29h          ;8255A的B口地址
                   pc8255    	equ  0FF2Ah         ;8255A的C口地址
                   con8255		equ  0FF2Bh         ;8255A的控制端口地址
                   setclk       	equ   01h
                   clrclk       	equ   00h
                   setpw       	equ   03h
                   clrpw        equ   02h
                   add_w      	equ   0a0h        	;写卡地址
                   add_r       	equ   0a1h        	;读卡地址
                   assume   		cs:code
                   	code 	  segment public
	           		org 		1000h                   ;规定程序的起始地址
start:               	mov      	dx, con8255      	;8255控制字,PB输入,PA.PC输出
                   	mov      	al, 82h          ;A组方式0A输出C高四位输出
                                               ;B组方式0B输入C低四位输出
                   	out        	dx, al           ;将控制字压入寄存器
                   	mov      	al, clrpw         ;C口第1位复位
                   	out        	dx, al
start1:           	 	mov      	dx, pb8255
                   	in          	al, dx            ;将B口的内容送给AL
                   	test       	al, 01h           ;若al最低位不为0则跳转回START1
                   	jnz        	start1            ;检查是否插卡
                   	mov      	dx, con8255       ;给予8255A控制端口地址
                   	mov      	al, setpw          ;C口第1位置1
                   	out        	dx, al
                   	mov      	bh, 7fh                 ;写入地址7FH
                   	mov      	ah, 0abh                ;写入数据ABH
                   	call       	write_byte               ;调用写入子程序
                   	call       	delay10                 ;调用延时程序
                   	mov      	bh, 7fh                  ;写入地址7FH
                   	call       	read_byte                调用读取子程序
                   	nop                                  ;设断点处
                   	jmp       	start                     ;调回开始点
write_byte:        	call       	begin0                  ;开始信号
                   	
mov      	bl, add_w              	;写入器件地址
                   	call       	wr_byte          
                   	
mov      	bl, bh                  ;写入字节地址
                   	call       	wr_byte
                   	
mov      	bl, ah                  ;写入数据
                   	call       	wr_byte
                   	
call       	stop0
                   	ret


read_byte:        	call       	begin0
                  	
mov     	bl, add_w               ;执行空字节写序列
                  call      	wr_byte
           
mov     	bl, bh
                  call      	wr_byte
                  
call      	begin0
                  mov     	bl, add_r               ;立即地址读取
                  call      	wr_byte
                  mov     	dx, con8255
                  mov     	al, 92h                ;方式0A输入方式0B输入  C输出
                  out       	dx, al
                  mov      	al, setpw
                  out        	dx, al
                  call      	rd_byte
                  call      	stop0
                  ret
begin0:           mov      	dx, con8255               ;给予DX8255A的FF2BH端口地址
                 mov      	al, clrclk                  ;C口第0位复位
                 out        	dx, al
                 mov      	dx, pa8255
                 mov      	al, 01h
                 out        	dx, al                     ;将01H送入8255A的A数据接口
                 mov      	dx, con8255
                 mov      	al, setclk                  ;C口第0位置1
                 out        	dx, al
                 mov      	dx, pa8255
                 mov      	al, 00h                    ;将00H送入8255A的A数据接口
                 out        	dx, al
                 mov      	dx, con8255
                 mov      	al, clrclk                   ;C口第0位复位
                 out        	dx, al
                 ret
stop0:            mov      	dx, con8255
                 mov      	al, clrclk                   ;C口第0位复位,清空AL
                 out        	dx, al
                 mov      	dx, pa8255                 ;将00H送入8255A的A数据接口
                                                      ;将00H送入IC卡
                 mov      	al, 00h                    
                 out        	dx, al
                 mov      	dx, con8255                ;置空al
                 mov      	al, setclk                  ;C口第0位置1
                 out        	dx, al
                 mov      	dx, pa8255
                 mov      	al, 01h                    ;将01H送入8255A的A数据接口
                 out        	dx, al
                 mov      	dx, con8255
                 mov      	al, clrclk                    ;C口第0位复位
                 out        	dx, al
                 mov      	dx, pa8255  
                 mov      	al, 00h                      ;将00H送入8255A的A数据接口
                 out        	dx, al
                 ret


  
wr_byte:         mov      	cx, 0008h                    ;循环次数为8
                mov      	dx, con8255                  ;给予8255A控制端口地址
                mov      	al, clrclk                     ;C口第0位复位,清空al
                out        	dx, al

wbyte1:          rcl         	bl, 1                         ;BL循环左移1，将最高位移进入CF
                 mov      	al, 00h
                 rcl         al, 1                         ;AL循环左移1，获取进位CF
                 mov      	dx, pa8255                   ;将al送入A口
                 out        	dx, al                        ;a口数据送入ic卡，SDA连接着a口；SDA高
                 
mov      	dx, con8255
                 mov      	al, setclk                     ;C口第0位置1；SCL高
                 out        	dx, al                        ;给al赋值01h
                
 mov      	dx, con8255                  
                 mov      	al, clrclk                     ;C口第0位复位；SCL低
                 out        	dx, al                        ;将al清0
                 loop      	wbyte1                      ;循环
                 
mov      	dx, con8255
                 mov      	al, setclk                     ;C口第0位置1
                 out        	dx, al
                 mov      	cx, 0005h                    ;设置循环次数为5
 wait0:           nop                                    ;设置断点
                 loop      	wait0            
                 mov      	dx, con8255
                 mov      	al, clrclk                     ;C口第0位复位
                 out        	dx, al
                 ret
rd_byte:          mov      	ah, 00h                     
                 mov      	cx, 0008h                    ;给予cx08H
rbyte1:           mov      	dx, pa8255                   ;8255A端口
                 in          	al, dx                    ;将DX端口内容送给AL
                                                        ;读出IC卡数据一位
                 rcr         	al, 1                    ;al循环右移一位
                 mov      	dx, con8255
                 mov      	al, setclk                     ;C口第0位置1
                 out        	dx, al
                 rcl         	ah, 1                    ;AL循环左移1位
                 mov      	dx, con8255
                 mov      	al, clrclk                     ;C口第0位复位
                 out        	dx, al
                 loop      	rbyte1                       ;进入循环
                 ret
delay10:          mov     	cx, 1388h                     ;延时子程序
delay1:           nop                                     ;延时断点子程序
                 loop     	delay1 
                 ret               
                 code ends
                 end start 
