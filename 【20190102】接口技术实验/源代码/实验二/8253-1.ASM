code   segment
assume   cs:code
org 1290h
start:   
mov     dx,0043h
mov      al,30h          ;00
out      dx,al
mov      dx,0040h
mov      al,00h
out      dx,al
mov      al,0ffh
out       dx,al
jmp       $
code   ends
end      start