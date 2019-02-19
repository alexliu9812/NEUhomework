code   segment
assume   cs:code
org 1290h
start:   
mov     dx,0043h
mov      al,36h          ;00
out      dx,al
mov      dx,0040h
mov      al,00h
out      dx,al
mov      al,0ffh
out       dx,al
mov       dx,0043h
mov       al,76h          ;Í¨µÀ1
out       dx,al
mov       dx,0041h
mov       al,02h
out       dx,al
mov       al,0h
out       dx,al
jmp       $
code   ends
end      start