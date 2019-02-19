code   segment
assume   cs:code
org 1290h
start:
mov       dx,0043h
mov       al,72h          ;Í¨µÀ1
out       dx,al
mov       dx,0041h
mov       al,00h
out       dx,al
mov       al,07Ah
out       dx,al
jmp       $
code   ends
end      start